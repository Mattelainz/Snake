#include <charconv>
#include <cstring>
#include <iostream>
#include <ncurses.h>
#include "view/graphicFuncs.hpp"

using namespace std;

void init(){
    initscr();
    cbreak(); //serve per disabilitare "terminal line buffering"
    noecho(); //previene l'eco tra caratteri
    curs_set(0); //visibilità schermo

}


WINDOW *new_bordered_window(int height, int width, int y, int x) {
    WINDOW *window = newwin(height, width, y, x);
    refresh();
    box(window, 0, 0);
    wrefresh(window);
    return window;
}



void endGame(){
    endwin();
}

void startGame(WINDOW* win){
    int character = getch();
    int posY = getmaxy(win) / 2;
    int posX = (getmaxx(win) - strlen("X")) / 2;
    mvwprintw(win, posY, posX, "%s", "X");

    while(character != 120){

        mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen("X")) / 2, "%s", "X");
        character = getch();

        if(character == 66){ 
            mvwprintw(win, posY++, posX, "%s", "X");
        }
        if(character == 67){ 
            mvwprintw(win, posY, posX++, "%s", "X");
        }
        if(character == 65){
            mvwprintw(win, posY--, posX, "%s", "X");
        }
        if(character == 68){ 
            mvwprintw(win, posY, posX--, "%s", "X");
        }

        wrefresh(win);

    }

}
/*
void getChars(WINDOW* win){
    while(true){
        int c = getch();
        mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - 3) / 2, "%d", c);
        wrefresh(win);
    }
}


*/