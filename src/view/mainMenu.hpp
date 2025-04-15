#ifndef MAIN_MENU_HPP

#define MAIN_MENU_HPP
#include "graphicFuncs.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include <cstring>
#include <cmath>
#include "graphicFuncs.hpp"

#define COLOR_DARK_GREEN 5



// Snake head pattern: 8 rows x 14 columns (pixel map)
// Modify these numbers to adjust details of the head.
static const int SNAKE_HEAD_H = 8;
static const int SNAKE_HEAD_W = 14;
static const int SNAKE_HEAD[SNAKE_HEAD_H][SNAKE_HEAD_W] = {
    // Columns:  0 1 2 3 4 5 6 7 8 9 10 11 12 13
    {          0,0,1,1,1,1,1,1,1,0, 0, 0, 0, 0 },  // Row 0
    {          0,1,1,2,2,2,2,2,2,1, 1, 0, 0, 0 },  // Row 1
    {          1,1,2,2,2,3,2,2,2,2, 1, 1, 0, 0 },  // Row 2 (black “eye” as 3)
    {          1,2,2,2,2,2,2,2,2,2, 2, 1, 1, 0 },  // Row 3 (red “tongue” as 4)
    {          4,4,2,2,2,2,2,2,2,2, 2, 1, 1, 0 },  // Row 4
    {          1,1,2,2,2,2,2,2,2,2, 1, 1, 0, 0 },  // Row 5
    {          0,1,1,2,2,2,2,2,2,1, 1, 0, 0, 0 },  // Row 6
    {          0,0,1,1,1,1,1,1,1,0, 0, 0, 0, 0 }   // Row 7
};

// Snake body pattern: 8 rows x 10 columns (a simple bordered rectangle)
// Here, "1" (green) is used for the border and "2" (white) for the inside.
static const int SNAKE_BODY_H = 4;
static const int SNAKE_BODY_W = 15;
static const int SNAKE_BODY[SNAKE_BODY_H][SNAKE_BODY_W] = {
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
};

void drawShape(int originY, int originX, int height, int width, const int shape[][SNAKE_HEAD_W]);

void drawShape2(int originY, int originX, int height, int width, const int shape[][SNAKE_BODY_W]);


// Change the background color of the window (region) based on hover state.
void updateWindowColor(const WindowRegionNode &region, int mouse_y, int mouse_x, 
                         int hoverColorPair, int defaultColorPair) ;

int getIdPage(MEVENT *event);

WINDOW* page();

void insertNode(WindowRegionNode data);


void initPage(int max_x,int max_y);


WINDOW* mainPage();
#endif