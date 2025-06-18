#include "Food.hpp"
#include <cstdlib>

Food::Food(int maxWidth, int maxHeight, char foodType) 
    : maxX(maxWidth), maxY(maxHeight), type(foodType) {
    spawn();
}

void Food::spawn() {
    x = (rand() % (maxX - 2)) + 2;
    y = (rand() % (maxY - 2)) + 2;
}

void Food::draw(WINDOW* win) {
    mvwprintw(win, y, x, "%c", type);
}

void Food::clear(WINDOW* win) {
    mvwprintw(win, y, x, " ");
}