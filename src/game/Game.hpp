#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include "Snake.hpp"
#include "Food.hpp"
#include "data/ScoreBoard.hpp"
#include "core/GraphicsManager.hpp"

class Game {
private:
    GraphicsManager* graphics;
    WINDOW* gameWindow;
    Snake* snake;
    Food* food;
    ScoreBoard* scoreBoard;
    
    int width, height;
    int score;
    int startTime;
    bool gameRunning;
    
    char getInputWithTimeout(int timeout);
    int getMillis();
    void drawUI();
    void gameOver();
    
public:
    Game(GraphicsManager* gfxManager, int width = 100, int height = 50);
    ~Game();
    
    void init();
    void run();
    void cleanup();
};

#endif