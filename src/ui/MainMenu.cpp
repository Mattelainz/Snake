#include "MainMenu.hpp"
#include <cstring>

// Definizione dei pattern statici
const int MainMenu::SNAKE_HEAD[SNAKE_HEAD_H][SNAKE_HEAD_W] = {
    {0,0,5,5,5,5,5,5,5,0,0,0,0,0},
    {0,5,5,1,1,1,1,1,1,5,5,0,0,0},
    {5,5,1,1,1,3,1,1,1,1,5,5,0,0},
    {5,1,1,1,1,1,1,1,1,1,1,5,5,0},
    {4,4,1,1,1,1,1,1,1,1,1,5,5,0},
    {5,5,1,1,1,1,1,1,1,1,5,5,0,0},
    {0,5,5,1,1,1,1,1,1,5,5,0,0,0},
    {0,0,5,5,5,5,5,5,5,0,0,0,0,0}
};

const int MainMenu::SNAKE_BODY[SNAKE_BODY_H][SNAKE_BODY_W] = {
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
};

MainMenu::MainMenu(GraphicsManager* gfxManager) 
    : graphics(gfxManager), menuWindow(nullptr), selectedOption(0) {
    
    graphics->getScreenSize(maxY, maxX);
    menuWindow = graphics->createBorderedWindow(maxY, maxX, 0, 0);
    initializeMenuPositions();
}

MainMenu::~MainMenu() {
    if (menuWindow) {
        wclear(menuWindow);
        wrefresh(menuWindow);
        delwin(menuWindow);
    }
}

void MainMenu::initializeMenuPositions() {
    menuPositions.clear();
    menuPositions.push_back({static_cast<int>(maxY * 0.2), maxX / 2});
    menuPositions.push_back({static_cast<int>(maxY * 0.5), maxX / 2});
    menuPositions.push_back({static_cast<int>(maxY * 0.8), maxX / 2});
}

void MainMenu::drawSnakeHead(int originY, int originX) {
    for (int row = 0; row < SNAKE_HEAD_H; row++) {
        for (int col = 0; col < SNAKE_HEAD_W; col++) {
            int colorIndex = SNAKE_HEAD[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}

void MainMenu::drawSnakeBody(int originY, int originX) {
    for (int row = 0; row < SNAKE_BODY_H; row++) {
        for (int col = 0; col < SNAKE_BODY_W; col++) {
            int colorIndex = SNAKE_BODY[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}

void MainMenu::drawSnake(int originY, int originX, int numBodySegments) {
    // Disegna la testa
    drawSnakeHead(originY - 2, originX + 3);
    
    // Disegna il corpo
    int segmentOriginX = originX + SNAKE_HEAD_W;
    for (int i = 0; i < numBodySegments; i++) {
        drawSnakeBody(originY, segmentOriginX);
        segmentOriginX += SNAKE_BODY_W;
    }
}

void MainMenu::drawVerticalSnake(int startY) {
    const int LETTERS = 5;
    const int H = 5, W = 5;
    const int SPACING = 1;
    
    static const int pattern[LETTERS][H][W] = {
        // S
        {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,1}},
        // N
        {{1,0,0,0,1}, {1,1,0,0,1}, {1,0,1,0,1}, {1,0,0,1,1}, {1,0,0,0,1}},
        // A
        {{0,1,1,1,0}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {1,0,0,0,1}},
        // K
        {{1,0,0,0,1}, {1,0,0,1,0}, {1,1,1,0,0}, {1,0,0,1,0}, {1,0,0,0,1}},
        // E
        {{1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,0}, {1,0,0,0,0}, {1,1,1,1,1}}
    };
    
    attron(COLOR_PAIR(1));
    for (int L = 0; L < LETTERS; L++) {
        int baseY = startY + L * (H + SPACING);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (pattern[L][r][c]) {
                    mvaddch(baseY + r, 1 + c, ACS_BLOCK);
                }
            }
        }
    }
    attroff(COLOR_PAIR(1));
}

void MainMenu::drawTitle() {
    attron(COLOR_PAIR(selectedOption == 1 ? 6 : 7));
    
    const char* title[] = {
        " _____ __    _____ __ __",
        "|  _  |  |  |  _  |  |  |",
        "|   __|  |__|     |_   _|",
        "|__|  |_____|__|__| |_|"
    };
    
    int textLen = strlen(title[0]);
    int startY = maxY / 2 - 2;
    int startX = maxX / 2 - textLen / 2;
    
    for (int i = 0; i < 4; i++) {
        mvprintw(startY + i, startX, "%s", title[i]);
    }
    
    attroff(COLOR_PAIR(selectedOption == 1 ? 6 : 7));
}

void MainMenu::drawMenuOptions() {
    // Disegna i cerchi colorati per le opzioni del menu
    for (int i = 0; i < 3; i++) {
        int colorPair = (i == selectedOption ? 5 : 1);
        graphics->drawFilledCircle(menuPositions[i].posY, menuPositions[i].posX, 
                                 RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, colorPair);
    }
}

void MainMenu::repaintAll() {
    clear();
    
    drawTitle();
    drawMenuOptions();
    
    // Disegna il serpente
    int numSegments = (maxX / 3) / SNAKE_BODY_W - 1;
    int totalSnakeWidth = SNAKE_HEAD_W + numSegments * SNAKE_BODY_W;
    int originX = maxX - totalSnakeWidth;
    int originY = menuPositions[selectedOption].posY + 1;
    
    drawSnake(originY, originX, numSegments);
    drawVerticalSnake((maxY < 32) ? 1 : maxY / 2 - 16);
    
    refresh();
}

bool MainMenu::handleInput() {
    int key = getch();
    
    switch (key) {
        case KEY_UP:
            if (selectedOption > 0) {
                selectedOption--;
            }
            break;
            
        case KEY_DOWN:
            if (selectedOption < 2) {
                selectedOption++;
            }
            break;
            
        case '\n':
        case '\r':
            return false; // Esce dal loop
            
        case 27: // ESC
            selectedOption = 2; // EXIT
            return false;
    }
    
    return true; // Continua il loop
}

MenuChoice MainMenu::show() {
    repaintAll();
    
    while (handleInput()) {
        repaintAll();
    }
    
    return static_cast<MenuChoice>(selectedOption);
}