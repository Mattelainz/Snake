#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <cstring>

Game::Game(GraphicsManager* gfxManager, int w, int h) 
    : graphics(gfxManager), width(w), height(h), score(0), gameRunning(false) {
    gameWindow = nullptr;
    snake = nullptr;
    food = nullptr;
    scoreBoard = new ScoreBoard();
}

Game::~Game() {
    cleanup();
    delete scoreBoard;
}

void Game::init() {
    srand(time(NULL));
    
    // Crea la finestra di gioco usando GraphicsManager
    gameWindow = graphics->createBorderedWindow(height, width, 2, 2);
    wrefresh(gameWindow);
    
    // Inizializza snake
    snake = new Snake(20, 20, 10);
    
    // Inizializza food
    food = new Food(width, height);
    
    // Carica i punteggi esistenti
    scoreBoard->loadFromFile();
    
    startTime = getMillis();
    gameRunning = true;
}

void Game::run() {
    if (!gameRunning) {
        init();
    }
    
    char lastInput = 'd';
    
    while (gameRunning) {
        char input = getInputWithTimeout(500);
        
        if (input == ERR) {
            input = lastInput;
        }
        
        // Muovi il serpente
        if (snake->move(input)) {
            lastInput = input;
        }
        
        // Disegna il cibo
        food->draw(gameWindow);
        
        // Disegna UI
        drawUI();
        
        // Controlla collisioni con le pareti
        if (snake->checkWallCollision(width, height)) {
            gameRunning = false;
            break;
        }
        
        // Controlla auto-collisione
        if (snake->checkSelfCollision()) {
            gameRunning = false;
            break;
        }
        
        // Cancella posizione precedente della coda (solo l'ultimo segmento)
        // Questo è un po' complicato da implementare esattamente come nel codice originale
        // Per ora disegniamo tutto il serpente ogni frame
        
        // Disegna il serpente
        snake->draw(gameWindow);
        
        // Controlla se ha mangiato il cibo
        if (snake->checkFoodCollision(food->getX(), food->getY())) {
            food->spawn();
            score++;
        }
        
        wrefresh(gameWindow);
    }
    
    gameOver();
}

void Game::cleanup() {
    if (gameWindow) {
        wclear(gameWindow);
        wrefresh(gameWindow);
        delwin(gameWindow);
        gameWindow = nullptr;
    }
}

char Game::getInputWithTimeout(int timeout) {
    int start = getMillis();
    char lastInput = ERR;
    ::timeout(0); // ncurses timeout
    
    while ((getMillis() - start) <= timeout) {
        char temp = getch();
        if (temp != ERR) {
            lastInput = temp;
        }
    }
    
    return lastInput;
}

int Game::getMillis() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return uint64_t(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

void Game::drawUI() {
    mvprintw(0, 0, "Score: %d", score);
    mvprintw(0, 20, "Time: %d", (getMillis() - startTime) / 1000);
    refresh();
}

void Game::gameOver() {
    clear();
    wclear(gameWindow);
    wrefresh(gameWindow);
    refresh();
    
    echo();
    mvwprintw(gameWindow, 20, 20, "Inserire il tuo nome: ");
    char playerName[100];
    flushinp();
    wgetstr(gameWindow, playerName);
    
    // Salva il punteggio
    scoreBoard->addScore(0, string(playerName), score);
    scoreBoard->saveToFile();
    
    wprintw(gameWindow, "\nHai scritto: %s", playerName);
    wprintw(gameWindow, "\nPunteggio finale: %d", score);
    wrefresh(gameWindow);
    
    wgetch(gameWindow);
}