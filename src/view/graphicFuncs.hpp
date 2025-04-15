#ifndef GRAPHIC_FUNCS_HPP

#define GRAPHIC_FUNCS_HPP

#include <charconv>
#include <cstring>
#include <iostream>
#include <ncurses.h>
#include <ncurses.h>

struct WindowRegionNode {
    WINDOW *win;
    int start_y, start_x;
    int height, width;
    WindowRegionNode *next;
};

void init();
void startGame();
void endGame();
WINDOW *new_bordered_window(int height, int width, int y, int x);

void drawFilledCircle(int center_y, int center_x, int radius_x, int radius_y,int color) ;

bool isInside(const WindowRegionNode &region, int y, int x) ;

#endif