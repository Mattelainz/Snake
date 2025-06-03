#include "view/mainMenu.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void draw() {

}

void sleep() {
    for(int i = 0; i < 50000000; i++);
}

struct swag {
    swag*next;
    int y;
    int x;
    char type;
};

int main(int, char**){
    srand(time(NULL));
    init();
    //mainPage();


    /*int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // Get screen size
    WINDOW* ret = new_bordered_window(max_y , max_x , 0,0);

    start_color();          // attivare colori

    // Enable mouse tracking for xterm-compatible terminals.
    //printf("\033[?1003h\n");
    //fflush(stdout);
    //initPage(max_x, max_y);

    // gameloop
    while(1) {
        draw();
    }*/

    /*printw("swag");
    int x = 0, y = 0;
    char a = 'A';
    while(1) {
        mvprintw(y++, x++, "%c", a++);
        refresh();
        
    }*/
    int width = 100;
    int height = 50;
    WINDOW*win = newwin(height, width, 2, 2);
    refresh();

    box(win, ':', '=');
    wrefresh(win);

    int x = 20, y = 20;

    //swag map[50][100];

    int snakeSize = 10;

    
    // init serpente
    swag*head = new swag{nullptr, y, x, 'O'};
    swag*tail = head;
    for(int i = 0; i < snakeSize; i++) {
        swag*body = new swag{tail, y, x-i, 'o'};
        tail = body;
    }

    swag*cibo = new swag{nullptr, (int)(rand()%(height-1)), (int)(rand()%(width-1)), 'a'};

    int score = 0;

    while(1) {
        switch (getch())
        {
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        default:
            break;
        }

        if(x >= width-1 || y >= height-1 || x <= 0 || y <= 0) {
            x = head->x;
            y = head->y;
            continue;
        }

        bool tailBitten = false;
        swag*temp = tail;
        do {
            if(temp->x == x && temp->y == y) {
                x = head->x;
                y = head->y;
                tailBitten = true;
                break;
            }
        } while((temp = temp->next) != nullptr);
        if(tailBitten) continue;

        mvwprintw(win, tail->y, tail->x, " ");

        head->next = tail;

        tail->x = x;
        tail->y = y;
        tail->type = 'O';

        tail = tail->next;          // salviamo nella nostra var tail, la nuova tail
        head->next->next = nullptr; // tail vecchia non ha un piu un next

        head->type = 'o';

        head = head->next;
        
        //wclear(win);
        //box(win, ':', '=');

        temp = tail;
        do {
            mvwprintw(win, temp->y, temp->x, "%c", temp->type);
        } while((temp = temp->next) != nullptr);

        if(head->x == cibo->x && head->y == cibo->y) {
            cibo->y = (int)(rand()%(height-2))+1;
            cibo->x = (int)(rand()%(width-2))+1;
            score++;
        }

        mvwprintw(win, cibo->y, cibo->x, "%c", cibo->type);

        mvprintw(0, 0, "Score: %d", score);

        wrefresh(win);
        
        //sleep();
    }


    getch();
    endGame();
    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    
    return 0;
}

/*


*/