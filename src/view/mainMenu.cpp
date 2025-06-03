#include "mainMenu.hpp"
#include "view/graphicFuncs.hpp"
#include <ncurses.h>
#include <random>

static WindowRegionNode* windList = nullptr;

const static int RADIUS_CIRCLE_X = 15;
const static int RADIUS_CIRCLE_Y = 3;


void init_colorPairs() {
    //fare paring color dark green 
    init_color(COLOR_DARK_GREEN, 75,378, 154 );
    init_pair(1, COLOR_GREEN,  COLOR_GREEN);   // Green
    init_pair(2, COLOR_WHITE,  COLOR_WHITE);     // White
    init_pair(3, COLOR_BLACK,  COLOR_BLACK);     // Black (for details like eyes)
    init_pair(4, COLOR_RED,    COLOR_RED);       // Red (for tongue)
    init_pair(5, COLOR_DARK_GREEN, COLOR_DARK_GREEN);
    init_pair(6, COLOR_BLACK, COLOR_DARK_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
}


void drawShape(int originY, int originX, int height, int width, const int shape[][SNAKE_HEAD_W]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int colorIndex = shape[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}

void drawShape2(int originY, int originX, int height, int width, const int shape[][SNAKE_BODY_W]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int colorIndex = shape[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}


void drawSnake(int originY, int originX, int numBodySegments) {
    // Draw the snake head.
    drawShape(originY-2, originX+3, SNAKE_HEAD_H, SNAKE_HEAD_W, SNAKE_HEAD);

    // Draw the body segments to the right of the head.
    // Each body segment is drawn directly adjacent to the previous one.
    int seg_originX = originX + SNAKE_HEAD_W; // start right after the head
    for (int i = 0; i < numBodySegments; i++) {
        drawShape2(originY, seg_originX, SNAKE_BODY_H, SNAKE_BODY_W, SNAKE_BODY);
        seg_originX += SNAKE_BODY_W; // move to next segment
    }
}

WindowRegionNode * findWind(int num){
    WindowRegionNode* curr = windList;
    for(int i = 0; i < num-1; i++){
        curr = curr->next;
    }
    return curr;
}


int getIdPage(MEVENT *event){
    if(windList == nullptr) return -1;

    WindowRegionNode *curr = windList;
    int i = 1;
    while(curr != nullptr){
        if(isInside(*curr, event->y, event->x)){
            return i;
        }
        curr=curr->next;
        i++;
    }
    return 0;
}


void repaintAll(int max_x, int max_y, int selected){
    WINDOW *choises[] = {
      newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*2 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X)
    , newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*5 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X)
    , newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*8 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X)};

    WindowRegionNode *curr = windList;
    int i = 0;
    while(curr != nullptr && choises[i] != nullptr){
        delwin(curr->win);
        curr->win = choises[i];
        wrefresh(choises[i++]);
        curr = curr->next;
    }
    
    for (int i = 1; i <= 3; i++) {
        auto *node = findWind(i);
        int pair_id = (i == selected ? 5 : 1);
        int cy = node->start_y + node->height/2;
        int cx = node->start_x + node->width /2;
        drawFilledCircle(cy, cx, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, pair_id);
    }
    

    attron(COLOR_PAIR(selected == 2 ? 6 : 7));
    int textLen = strlen(" _____ __    _____ __ __");

    move(max_y/2-2, max_x/2-textLen/2);
    printw(" _____ __    _____ __ __");
    move(max_y/2-1, max_x/2-textLen/2);
    printw("|  _  |  |  |  _  |  |  |");
    move(max_y/2, max_x/2-textLen/2);
    printw("|   __|  |__|     |_   _|");
    move(max_y/2+1, max_x/2-textLen/2); 
    printw("|__|  |_____|__|__| |_|");

    attroff(COLOR_PAIR(selected == 2 ? 6 : 7));

    refresh();

}


WINDOW* page(){
    int max_x,max_y;
    max_y = getmaxy(stdscr);
    max_x = getmaxx(stdscr); 
    keypad(stdscr, TRUE);
    MEVENT event;
    mousemask(BUTTON1_CLICKED | REPORT_MOUSE_POSITION, NULL);

    int c; //getch of the button pressd 
    int numChoise = 1;

    int numSegments = 2;
    int totalSnakeWidth = SNAKE_HEAD_W + numSegments * SNAKE_BODY_W;
    
    int originX = (max_x - totalSnakeWidth) ;
    int originY = findWind(numChoise)->start_y +1;

    drawSnake(originY, originX, numSegments);
    repaintAll(max_x, max_y, numChoise);
    while ((c = getch()) != 27) {
        if(c == KEY_MOUSE){
            if (getmouse(&event) == OK) {
                if (BUTTON1_PRESSED) {
                    switch (getIdPage(&event)) {
                        case -1:
                            return nullptr;
                        break;
                        case 1:
                            return nullptr; // page 1
                        break;

                        case 2:
                        return nullptr; // page 2
                        break;

                        case 3:
                        return nullptr; // page 3
                        break;

                        default:
                            return nullptr; //how did you get here XD
                        break;
                    }
                }
            }
        }
        switch (c) {
            case KEY_UP :
                if(numChoise == 2 || numChoise == 3){
                    numChoise --;
                    originY = findWind(numChoise)->start_y +1 ;
                    clear();
                    drawSnake(originY, originX, numSegments);
                    repaintAll(max_x, max_y,numChoise);
                }
            break;
            case KEY_DOWN :
                if(numChoise == 1 || numChoise == 2 || numChoise == 0){
                    numChoise ++;
                    originY = findWind(numChoise)->start_y + 1;
                    clear();
                    repaintAll(max_x, max_y,numChoise);
                    drawSnake(originY, originX, numChoise);
                }
            break;
            case '\n' : 
                switch (numChoise) {
                    case 1: return nullptr;

                    case 2: return nullptr;

                    case 3: return nullptr;

                    default: return nullptr;
                }
            break;
        }
    }
    return nullptr;
}

void drawVerticalSnake(int startY) {
    const int LETTERS = 5;
    const int H = 5, W = 5;
    const int SPACING = 1;  // blank rows between letters

    // 5 letters × 5 rows × 5 cols: 1 = draw block; 0 = leave blank
    static const int pattern[LETTERS][H][W] = {
      // S
      {{1,1,1,1,1},
       {1,0,0,0,0},
       {1,1,1,1,0},
       {0,0,0,0,1},
       {1,1,1,1,1}},
      // N
      {{1,0,0,0,1},
       {1,1,0,0,1},
       {1,0,1,0,1},
       {1,0,0,1,1},
       {1,0,0,0,1}},
      // A
      {{0,1,1,1,0},
       {1,0,0,0,1},
       {1,1,1,1,1},
       {1,0,0,0,1},
       {1,0,0,0,1}},
      // K
      {{1,0,0,0,1},
       {1,0,0,1,0},
       {1,1,1,0,0},
       {1,0,0,1,0},
       {1,0,0,0,1}},
      // E
      {{1,1,1,1,1},
       {1,0,0,0,0},
       {1,1,1,1,0},
       {1,0,0,0,0},
       {1,1,1,1,1}}
    };

    attron(COLOR_PAIR(1));
    for (int L = 0; L < LETTERS; L++) {
        int baseY = startY + L * (H + SPACING);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (pattern[L][r][c]) {
                    mvaddch(baseY + r, /*col=*/1 + c, ACS_BLOCK);
                }
            }
        }
    }
    attron(COLOR_PAIR(2));

}


void insertNode(WindowRegionNode data){
    if(windList == nullptr){
        windList = new WindowRegionNode;
        windList->height = data.height;
        windList->width = data.width;
        windList->start_x = data.start_x;
        windList->start_y = data.start_y;
        windList->win = data.win;
        windList->next = nullptr;
        return;
    }
    WindowRegionNode *curr = windList;

    while (curr->next != nullptr) {
        curr = curr->next;
    }
    
    WindowRegionNode* newNode = new WindowRegionNode;
    newNode->height = data.height;
    newNode->width = data.width;
    newNode->start_x = data.start_x;
    newNode->start_y = data.start_y;
    newNode->win = data.win;
    newNode->next = nullptr;
    curr->next = newNode;
}


void initPage(int max_x,int max_y){

    WINDOW *choise_1 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*2 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X);
    WINDOW *choise_2 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*5 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X);
    WINDOW *choise_3 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*8 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X);
    
    insertNode({choise_1, (max_y/10)*2 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});
    insertNode({choise_2, (max_y/10)*5 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});
    insertNode({choise_3,(max_y/10)*8 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});

    wrefresh(choise_1);
    wrefresh(choise_2);
    wrefresh(choise_3);

    drawFilledCircle(max_y/2, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, 1);
    drawFilledCircle((max_y/10)*2, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, 1);
    drawFilledCircle((max_y/10)*8, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, 1);
    
    init_colorPairs();
    attron(COLOR_PAIR(7));
    int textLen = strlen(" _____ __    _____ __ __");

    move(max_y/2-2, max_x/2-textLen/2);
    printw(" _____ __    _____ __ __");
    move(max_y/2-1, max_x/2-textLen/2);
    printw("|  _  |  |  |  _  |  |  |");
    move(max_y/2, max_x/2-textLen/2);
    printw("|   __|  |__|     |_   _|");
    move(max_y/2+1, max_x/2-textLen/2); 
    printw("|__|  |_____|__|__| |_|");

    attroff(COLOR_PAIR(7));

    drawVerticalSnake(1);   

    refresh();
    page();
}


WINDOW* mainPage(){
    
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // Get screen size
    WINDOW* ret = new_bordered_window(max_y , max_x , 0,0);

    start_color();          // attivare colori

    // Enable mouse tracking for xterm-compatible terminals.
    printf("\033[?1003h\n");
    fflush(stdout);
    initPage(max_x, max_y);


     
    return ret;
}

/*

                           
 _____ __    _____ __ __   
|  _  |  |  |  _  |  |  |  
|   __|  |__|     |_   _|  
|__|  |_____|__|__| |_|    
                           

*/