#include "mainMenu.hpp"
#include <ncurses.h>

static WindowRegionNode* windList = nullptr;

// ------------------------------------------------------------------
// Initialize our color pairs.
// We use the same color for foreground and background to print a solid block.
void init_colorPairs() {
    //fare paring color dark green 
    init_color(COLOR_DARK_GREEN, 75,378, 154 );
    init_pair(1, COLOR_GREEN,  COLOR_GREEN);   // Green
    init_pair(2, COLOR_WHITE,  COLOR_WHITE);     // White
    init_pair(3, COLOR_BLACK,  COLOR_BLACK);     // Black (for details like eyes)
    init_pair(4, COLOR_RED,    COLOR_RED);       // Red (for tongue)
    init_pair(5, COLOR_DARK_GREEN, COLOR_DARK_GREEN);
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



// Change the background color of the window (region) based on hover state.
void updateWindowColor(const WindowRegionNode &region, int mouse_y, int mouse_x, 
                         int hoverColorPair, int defaultColorPair) { //unused
    if (isInside(region, mouse_y, mouse_x)) {
        // Set the window to use the hover background.
        wbkgd(region.win, COLOR_PAIR(hoverColorPair));
    } else {
        // Set the window back to the default background.
        wbkgd(region.win, COLOR_PAIR(defaultColorPair));
    }
    // Redraw the border if you want.
    box(region.win, 0, 0);
    wrefresh(region.win);
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

WINDOW* page(){
    //keypad(win1, TRUE); 
    //keypad(win2, TRUE); 
    //keypad(win3, TRUE); 
    keypad(stdscr, TRUE);
    MEVENT event;
    mousemask(BUTTON1_CLICKED | REPORT_MOUSE_POSITION, NULL);

    int c = 0;

    while(c != 120){
        c = getch();
        if(c == KEY_MOUSE){
            
            if (getmouse(&event) == OK) {
                if (BUTTON1_PRESSED) {
                    switch (getIdPage(&event)) {
                        case -1:
                            return nullptr;
                        break;

                        case 0:
                            continue;
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
            }else if(c == KEY_UP){
                printw("zios");
            }

        }
    }
    return nullptr;

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
    const int RADIUS_CIRCLE_X = 15;
    const int RADIUS_CIRCLE_Y = 3;

    

    WINDOW *choise_1 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*2 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X);
    WINDOW *choise_2 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*5 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X);
    WINDOW *choise_3 = newwin(RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, (max_y/10)*8 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X);
    
    insertNode({choise_1, (max_y/10)*2 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});
    insertNode({choise_2, (max_y/10)*5 - RADIUS_CIRCLE_Y , (max_x/2)-RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});
    insertNode({choise_3,(max_y/10)*8 - RADIUS_CIRCLE_Y, (max_x/2)-RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y*2+1, RADIUS_CIRCLE_X*2+1, nullptr});

   // box(choise_1, 0, 0);
   // box(choise_2, 0,0);
   // box(choise_3, 0, 0);
    wrefresh(choise_1);
    wrefresh(choise_2);
    wrefresh(choise_3);

    drawFilledCircle(max_y/2, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, COLOR_GREEN);
    drawFilledCircle((max_y/10)*2, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, COLOR_GREEN);
    drawFilledCircle((max_y/10)*8, max_x/2, RADIUS_CIRCLE_X,RADIUS_CIRCLE_Y, COLOR_GREEN);
    
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    attron(COLOR_PAIR(6));
    int textLen = strlen(" _____ __    _____ __ __");

    move(max_y/2-2, max_x/2-textLen/2);
    printw(" _____ __    _____ __ __");
    move(max_y/2-1, max_x/2-textLen/2);
    printw("|  _  |  |  |  _  |  |  |");
    move(max_y/2, max_x/2-textLen/2);
    printw("|   __|  |__|     |_   _|");
    move(max_y/2+1, max_x/2-textLen/2); 
    printw("|__|  |_____|__|__| |_|");

    refresh();

    init_colorPairs();
    int numSegments = (max_x - SNAKE_HEAD_W) / SNAKE_BODY_W;
    if(numSegments < 1) numSegments = 1; // ensure at least one segment

    int totalSnakeWidth = SNAKE_HEAD_W + numSegments * SNAKE_BODY_W;
    int originX = (max_x - totalSnakeWidth) ;      // center horizontally
    int originY = (0) ;            // center vertically

    drawSnake(originY, originX, numSegments);

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