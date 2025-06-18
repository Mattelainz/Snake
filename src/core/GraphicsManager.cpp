#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager() : initialized(false) {}

GraphicsManager::~GraphicsManager() {
    cleanup();
}

void GraphicsManager::initialize() {
    if (!initialized) {
        initscr();
        cbreak(); // disabilita "terminal line buffering"
        noecho(); // previene l'eco tra caratteri
        curs_set(0); // nasconde il cursore
        keypad(stdscr, TRUE); // abilita tasti freccia
        start_color(); // attiva i colori
        
        initializeColors();
        initialized = true;
    }
}

void GraphicsManager::cleanup() {
    if (initialized) {
        endwin();
        initialized = false;
    }
}

void GraphicsManager::initializeColors() {
    // Definisce i colori personalizzati
    init_color(COLOR_MAGENTA, 75, 378, 154); // Dark green personalizzato
    
    // Definisce le coppie di colori
    init_pair(1, COLOR_GREEN, COLOR_GREEN);     // Verde
    init_pair(2, COLOR_WHITE, COLOR_WHITE);     // Bianco
    init_pair(3, COLOR_BLACK, COLOR_BLACK);     // Nero
    init_pair(4, COLOR_RED, COLOR_RED);         // Rosso
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA); // Verde scuro
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);   // Testo nero su verde scuro
    init_pair(7, COLOR_BLACK, COLOR_GREEN);     // Testo nero su verde
}

WINDOW* GraphicsManager::createBorderedWindow(int height, int width, int y, int x) {
    WINDOW* window = newwin(height, width, y, x);
    box(window, 0, 0);
    wrefresh(window);
    return window;
}

void GraphicsManager::drawFilledCircle(int centerY, int centerX, int radiusX, int radiusY, int color) {
    attron(COLOR_PAIR(color));
    
    for (int y = centerY - radiusY; y <= centerY + radiusY; y++) {
        for (int x = centerX - radiusX; x <= centerX + radiusX; x++) {
            // Formula ellisse: (x-x_center)^2/radius_x^2 + (y-y_center)^2/radius_y^2 < 1
            double dx = x - centerX;
            double dy = y - centerY;
            
            if ((dx * dx) / (radiusX * radiusX) + 
                (dy * dy) / (radiusY * radiusY) < 1.0) {
                mvaddch(y, x, ACS_BLOCK);
            }
        }
    }
    
    attroff(COLOR_PAIR(color));
}

void GraphicsManager::getScreenSize(int& maxY, int& maxX) {
    getmaxyx(stdscr, maxY, maxX);
}