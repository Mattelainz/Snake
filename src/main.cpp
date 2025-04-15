#include "view/mainMenu.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>


int main(int, char**){
    init();
    mainPage();
    endGame();
    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    
    return 0;
}

/*


*/