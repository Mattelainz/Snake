#ifndef FOOD_HPP
#define FOOD_HPP

#include <ncurses.h>

class Food {
private:
    int x, y;
    char type;
    int maxX, maxY;
    
public:
    Food(int maxWidth, int maxHeight, char foodType = 'a');
    
    void spawn();
    void draw(WINDOW* win);
    void clear(WINDOW* win);
    
    int getX() const { return x; }
    int getY() const { return y; }
    char getType() const { return type; }
};

#endif