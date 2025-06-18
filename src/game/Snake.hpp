#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <ncurses.h>

class SnakeSegment {
public:
    SnakeSegment* next;
    int x, y;
    char type;
    
    SnakeSegment(int x, int y, char type);
    ~SnakeSegment();
};

class Snake {
private:
    SnakeSegment* head;
    SnakeSegment* tail;
    int size;
    char lastDirection;
    
public:
    Snake(int startX, int startY, int initialSize);
    ~Snake();
    
    bool move(char direction);
    void draw(WINDOW* win);
    void clear(WINDOW* win);
    bool checkSelfCollision();
    bool checkWallCollision(int width, int height);
    bool checkFoodCollision(int foodX, int foodY);
    void grow();
    
    int getHeadX() const { return head->x; }
    int getHeadY() const { return head->y; }
    int getSize() const { return size; }
};

#endif