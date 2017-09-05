#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#define DELAY 120000

std::vector<int> A, B, C;
int N;
int max_y, max_x;

//r = 0 means no disc, just pole
void drawDisc(int y, int x, int r){
    for (int i=0; i <= r; i++){
        mvprintw( max_y - y - 1, x+i,"#");
        mvprintw( max_y - y - 1, x-i,"#");
    }
}

//Drawing Stacks
int DrawStacks(){
    clear();
    int current;
    int offset = N;
    for (int i=0; i<N; i++){
        current =  ( i < A.size() ) ? A[i] : 0;
        drawDisc(i,N + offset, current);
    }
    offset += 2*N + 1;
    for (int i=0; i<N; i++){
        current =  ( i < B.size() ) ? B[i] : 0;
        drawDisc(i,N + offset, current);
    }
    offset += 2*N + 1;
    for (int i=0; i<N; i++){
        current =  ( i < C.size() ) ? C[i] : 0;
        drawDisc(i,N + offset, current);
    }

    refresh();
    usleep(DELAY);  //u = mu = sleep for microseconds
}

//move n discs from a to b with c as spare
void MoveTo(std::vector<int> &a, std::vector<int> &b, std::vector<int> &c, int n){
    if (n == 0)
        return;
    //moving a to b, using c as spare

    //move other stack elsewhere
    MoveTo(a, c, b, n-1);

    //move the bottom tile to b
    int tile = a.back();
    a.pop_back();
    b.push_back(tile);

    //draw current state
    DrawStacks();

    //move the others back
    MoveTo(c, b, a, n-1);
}



int main(int argc, char** argv)
{
    if (argc != 2){
        std::cout << "Usage : ./hanoi <towersize>";
        return 0;
    }

    //ncurses settings
	initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, max_y, max_x);

    N = atoi(argv[1]);
    //initialize 1st stack
    for (int i=0; i<N; i++){
        A.push_back(N-i);
    }
    MoveTo(A, B, C, N);

    refresh();

    //wait before closing
    mvprintw( 2, 3, "press any key to exit..");
    getch();
    endwin();

    return 0;
}
