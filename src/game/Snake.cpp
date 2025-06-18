#include "Snake.hpp"

SnakeSegment::SnakeSegment(int x, int y, char type) 
    : next(nullptr), x(x), y(y), type(type) {}

SnakeSegment::~SnakeSegment() {
    if (next) {
        delete next;
    }
}

Snake::Snake(int startX, int startY, int initialSize) 
    : size(initialSize), lastDirection('d') {
    
    // Crea la testa
    head = new SnakeSegment(startX, startY, 'O');
    tail = head;
    
    // Crea il corpo
    for (int i = 1; i < initialSize; i++) {
        SnakeSegment* segment = new SnakeSegment(startX - i, startY, 'o');
        segment->next = tail;
        tail = segment;
    }
}

Snake::~Snake() {
    delete tail; // Cancella ricorsivamente tutti i segmenti
}

bool Snake::move(char direction) {
    // Se la direzione non è valida, usa l'ultima direzione
    if (direction != 'w' && direction != 's' && direction != 'a' && direction != 'd') {
        direction = lastDirection;
    }
    
    int newX = head->x;
    int newY = head->y;
    
    switch (direction) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return false;
    }
    
    // Sposta la coda in testa
    SnakeSegment* oldTail = tail;
    SnakeSegment* newTail = tail->next;
    
    // Trova il nuovo tail (penultimo elemento)
    while (newTail && newTail->next != head) {
        newTail = newTail->next;
    }
    
    if (newTail) {
        newTail->next = nullptr;
        tail = newTail;
    }
    
    // La vecchia coda diventa la nuova testa
    oldTail->x = newX;
    oldTail->y = newY;
    oldTail->type = 'O';
    oldTail->next = head;
    
    // La vecchia testa diventa corpo
    head->type = 'o';
    head = oldTail;
    
    lastDirection = direction;
    return true;
}

void Snake::draw(WINDOW* win) {
    SnakeSegment* current = tail;
    while (current) {
        mvwprintw(win, current->y, current->x, "%c", current->type);
        current = current->next;
    }
}

void Snake::clear(WINDOW* win) {
    SnakeSegment* current = tail;
    while (current) {
        mvwprintw(win, current->y, current->x, " ");
        current = current->next;
    }
}

bool Snake::checkSelfCollision() {
    SnakeSegment* current = tail;
    while (current && current != head) {
        if (current->x == head->x && current->y == head->y) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool Snake::checkWallCollision(int width, int height) {
    return (head->x >= width - 1 || head->y >= height - 1 || 
            head->x <= 0 || head->y <= 0);
}

bool Snake::checkFoodCollision(int foodX, int foodY) {
    return (head->x == foodX && head->y == foodY);
}

void Snake::grow() {
    // Per ora non implementiamo la crescita, 
    // manterremo la dimensione costante come nel codice originale
    size++;
}