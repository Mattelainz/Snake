#ifndef GAME_APPLICATION_HPP
#define GAME_APPLICATION_HPP

#include "GraphicsManager.hpp"
#include "ui/MainMenu.hpp"
#include "game/Game.hpp"

class GameApplication {
private:
    GraphicsManager graphics;
    
public:
    GameApplication();
    ~GameApplication();
    
    int run();
};

#endif