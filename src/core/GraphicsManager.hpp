#ifndef GRAPHICS_MANAGER_HPP
#define GRAPHICS_MANAGER_HPP

#include <ncurses.h>

class GraphicsManager {
private:
    bool initialized;
    
public:
    GraphicsManager();
    ~GraphicsManager();
    
    void initialize();
    void cleanup();
    void initializeColors();
    
    WINDOW* createBorderedWindow(int height, int width, int y, int x);
    void drawFilledCircle(int centerY, int centerX, int radiusX, int radiusY, int color);
    
    // Getter per dimensioni schermo
    void getScreenSize(int& maxY, int& maxX);
};

#endif