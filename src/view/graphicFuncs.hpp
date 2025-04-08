#ifndef GRAPHIC_FUNCS_HPP

#define GRAPHIC_FUNCS_HPP
#include <ncurses.h>

void init();
void startGame(WINDOW* win);
void endGame();
WINDOW *new_bordered_window(int height, int width, int y, int x);

#endif