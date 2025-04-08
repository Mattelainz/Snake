#include <cstring>
#include <iostream>
#include <ncurses.h>
#include "view/graphicFuncs.hpp"

using namespace std;

int main(int, char**){
    init();
    
    WINDOW *win = new_bordered_window(20, 100, 0, 0);

    wrefresh(win);
    startGame(win);
    delwin(win);
    endGame();
    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    //cout << "dd";
    
    return 0;
}


