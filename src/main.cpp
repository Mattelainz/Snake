#include "view/mainMenu.hpp"
#include "game/Game.hpp"
#include "scoreBoard/ScoreBoard.hpp"
#include "Levels/levels.hpp"
#include "view/mainMenu.hpp"
#include "scoreBoard/ScoreBoard.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>

int main(int, char**){
    srand(time(NULL));
    init();
    
    int choice = mainMenu::mainPage();
    levels*lvl = new levels(10);

    while(choice != -1) {
        
        if(choice == 0) {
            WINDOW*score = newwin(getmaxy(stdscr)*0.8,getmaxx(stdscr)*0.8, getmaxy(stdscr)*0.1,getmaxx(stdscr)*0.1);
            wrefresh(score);
            // scoreBoard s;
            // memset(&s, 0x00, sizeof(scoreBoard));
            // scoreBoard::DataPlayer p1 {"chr",2};
            // scoreBoard::DataPlayer p2 {"ddd",5};
            // scoreBoard::DataPlayer p3 {"sss",6};
            // scoreBoard::DataPlayer p4{"cri",7};
            // scoreBoard::DataPlayer p5 {"cnn",2};
            // scoreBoard::saveScore(0, p1, &s);
            // scoreBoard::saveScore(0, p2, &s);
            // scoreBoard::saveScore(0, p3, &s);
            // scoreBoard::saveScore(0, p4,  &s);
            // scoreBoard::saveScore(0, p5,  &s);
            // scoreBoard::serialize(s);
            scoreBoard s2;
            memset(&s2, 0x00, sizeof(scoreBoard));
            scoreBoard::deserialize(&s2);
            attroff(COLOR_PAIR(2));
            scoreBoard::printData(s2,0,score);
        } else if(choice == 1) {
            Game game;
            int start = game.getMillis();
            WINDOW*win = game.setBoard();
            game.run(win, start);
            scoreBoard::DataPlayer dp = game.gameOver(win);
            scoreBoard toSerialize;
            scoreBoard::saveScore(0, dp, &toSerialize);
            scoreBoard::serialize(toSerialize);
        } else if(choice == 2) {
            levels::level*currLvl = lvl->getCurrLevel();
            WINDOW*lvlWindow = newwin(getmaxy(stdscr)*0.8,getmaxx(stdscr)*0.8, getmaxy(stdscr)*0.1,getmaxx(stdscr)*0.1);

            mvwprintw(lvlWindow, 1, 1, "Selected Level: %d", currLvl->num);
            mvwprintw(lvlWindow, 4, 1, "Velocita': %d  -  Bonus: %f  -  Lunghezza: %d", currLvl->vel, currLvl->bonus, currLvl->snakelen);
            wrefresh(lvlWindow);

            char input = ' ';
            while((input = wgetch(lvlWindow)) != '\n') {
                if(input == 'd') {
                    currLvl = lvl->nextLevel();
                } else if(input == 'a') {
                    currLvl = lvl->prevLevel();
                }

                mvwprintw(lvlWindow, 1, 1, "Selected Level: %d", currLvl->num);
                mvwprintw(lvlWindow, 4, 1, "Velocita': %d  -  Bonus: %f  -  Lunghezza: %d", currLvl->vel, currLvl->bonus, currLvl->snakelen);
                wrefresh(lvlWindow);
            }
            
            // TODO: arrivati qui avrai in currLvl il livello selezionato.
            // c'e' da vedere se la classe di matte levels si salva il livello selezionato
            // in base a quello poi quando fai game.run alla riga 51 passi insieme al resto anche levels o il level a seconda del come viene salvato
            // FIXME: c'e' da aggiustare nella classe di matte levels, quando cerchi di andare in negativo (tipo lvl < 1) ti blocca
            // ma se provi invece ad andare in overflow (tipo lvl > 10) non ti mostra che lo sta facendo ma si sballa il pointer 4some reason
        }

        choice = mainMenu::mainPage();
    }


    endwin();

    // clear();
    // wclear(win);
    // wrefresh(win);
    // refresh();

    // mvwprintw(win, 50, 50, "boiode de dio can");

    // getch();
    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    
    return 0;
}

/*


*/