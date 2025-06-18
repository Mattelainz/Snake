#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "core/GraphicsManager.hpp"
#include <vector>

struct MenuPosition {
    int posY, posX;
};

enum class MenuChoice {
    PLAY = 0,
    SETTINGS = 1,
    EXIT = 2
};

class MainMenu {
private:
    static const int SNAKE_HEAD_H = 8;
    static const int SNAKE_HEAD_W = 14;
    static const int SNAKE_BODY_H = 4;
    static const int SNAKE_BODY_W = 15;
    static const int RADIUS_CIRCLE_X = 15;
    static const int RADIUS_CIRCLE_Y = 3;
    
    GraphicsManager* graphics;
    WINDOW* menuWindow;
    std::vector<MenuPosition> menuPositions;
    int selectedOption;
    int maxX, maxY;
    
    // Pattern per la grafica del serpente
    static const int SNAKE_HEAD[SNAKE_HEAD_H][SNAKE_HEAD_W];
    static const int SNAKE_BODY[SNAKE_BODY_H][SNAKE_BODY_W];
    
    void initializeMenuPositions();
    void drawSnakeHead(int originY, int originX);
    void drawSnakeBody(int originY, int originX);
    void drawSnake(int originY, int originX, int numBodySegments);
    void drawVerticalSnake(int startY);
    void drawTitle();
    void drawMenuOptions();
    void repaintAll();
    
    bool handleInput();
    
public:
    MainMenu(GraphicsManager* gfxManager);
    ~MainMenu();
    
    MenuChoice show();
};

#endif