#include "GameBoard.hpp"
#include "Snake/Snake.hpp"
#include <ncurses.h>



WINDOW* drawBoard(){
    max_y = getmaxy(stdscr);
    max_x = getmaxx(stdscr);

    height = max_y * 0.8;
    width = max_x * 0.8;

    WINDOW*win = newwin(height, width, max_y*0.1, max_x*0.1);

    box(win, 0,0);

    wrefresh(win);

    return win;
}


int getMillis() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return uint64_t(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

char getInput(WINDOW*win) {
    int TIMEOUT = 50;
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
    return lastInput;
}

void GameLoop( WINDOW* win){
    int start = getMillis();

    mvwprintw(win, max_y*0.05, (max_x*0.1)+1, "TIME : %d:%d", (((MAX_TIME)-(getMillis()-start))/60)/1000, ((MAX_TIME-(getMillis()-start))%60)/1000);
    mvwprintw(win, max_y*0.05, (max_x*0.5), "SCORE : %d",score);
    mvwprintw(win,  max_y*0.9 + 1, (max_x*0.5)-2 , "LEVEL : %d", 1); //TODO: getLevel

}

void startGame(){
    WINDOW* board = drawBoard();
    object*cibo = new object{nullptr, (int)(rand()%(height-1)), (int)(rand()%(width-1)), 'a'};
    score = 0;

    drawSnake(board); //init list snake


    char last_chinput = 'd';

    while(1){
        char chinput = getInput(board);
        
        if(chinput == ERR) {
            chinput = last_chinput;
        }
        if(!snake_move(chinput, &y, &x)) {
            snake_move(last_chinput, &y, &x);
        } else last_chinput = chinput;

        mvwprintw(board, cibo->y, cibo->x, "%c", cibo->type);
        attroff(COLOR_PAIR(2));

        wrefresh(board);

        if(x >= width-1 || y >= height-1 || x <= 0 || y <= 0) {
            x = head->x;
            y = head->y;
            break;
        }

        bool tailBitten = false;
        object*temp = tail;
        do {
            if(temp->x == x && temp->y == y) {
                x = head->x;
                y = head->y;
                tailBitten = true;
                break;
            }
        } while((temp = temp->next) != nullptr);
        if(tailBitten) {
            break;
        }

        mvwprintw(board, tail->y, tail->x, " ");

        head->next = tail;

        tail->x = x;
        tail->y = y;
        tail->type = 'O';

        tail = tail->next;          // salviamo nella nostra var tail, la nuova tail
        head->next->next = nullptr; // tail vecchia non ha un piu un next

        head->type = 'o';

        head = head->next;

        temp = tail;

        GameLoop(board);
        do {
            mvwprintw(board, temp->y, temp->x, "%c", temp->type);
        } while((temp = temp->next) != nullptr);

        if(head->x == cibo->x && head->y == cibo->y) {
            cibo->y = (int)(rand()%(height-2))+2;
            cibo->x = (int)(rand()%(width-2))+2;
            score++;
        }

        wrefresh(board);
    }


    

}
    
