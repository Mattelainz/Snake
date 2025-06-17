#include "view/mainMenu.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>


struct swag {
    swag*next;
    int y;
    int x;
    char type;
};

 int getMillis() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return uint64_t(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}


int ii = 0;
char getInput(WINDOW*win) {
    int TIMEOUT = 500;
    int start = getMillis();
    char lastInput = ERR;
    timeout(0);
    int i = 0;
    while((getMillis() - start) <= TIMEOUT) {
        //mvwprintw(win, 0, 20, "%d", (getMillis() - start));
        char temp = getch();
        if(temp != ERR)
            lastInput = temp;
    }
    ii++;
    return lastInput;
}

bool snake_move(char chinput, int*y, int*x) {
    switch (chinput) {
        case 'w': (*y)--; break;
        case 's': (*y)++; break;
        case 'a': (*x)--; break;
        case 'd': (*x)++; break;
        default:    return false;
    }
    return true;
}

int main(int, char**){
    srand(time(NULL));
    init();
    mainPage();

    int width = 100;
    int height = 50;
    WINDOW*win = newwin(height, width, 2, 2);
    refresh();

    box(win, ':', '=');
    wrefresh(win);

    int x = 20, y = 20;

    //swag map[50][100];

    int snakeSize = 10;
    int start = getMillis();

    
    // init serpente
    swag*head = new swag{nullptr, y, x, 'O'};
    swag*tail = head;
    for(int i = 0; i < snakeSize; i++) {
        swag*body = new swag{tail, y, x-i, 'o'};
        tail = body;
    }

    swag*cibo = new swag{nullptr, (int)(rand()%(height-1)), (int)(rand()%(width-1)), 'a'};

    int score = 0;

    wrefresh(win);

    char last_chinput = 'd';
    while(1) {
        char chinput = getInput(win);
        
        if(chinput == ERR) {
            chinput = last_chinput;
        }
        if(!snake_move(chinput, &y, &x)) {
            snake_move(last_chinput, &y, &x);
        } else last_chinput = chinput;


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
            cibo->y = (int)(rand()%(height-2))+2;
            cibo->x = (int)(rand()%(width-2))+2;
            score++;
        }

        mvwprintw(win, cibo->y, cibo->x, "%c", cibo->type);
        attroff(COLOR_PAIR(2));
        mvprintw(0, 0, "Score: %d", score);

        mvprintw(0, 20, "Time: %d", (getMillis()-start)/1000);

        wrefresh(win);

        //wtimeout(win, 500);
        
        //sleep()
    }


    getch();

    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    
    return 0;
}

/*


*/