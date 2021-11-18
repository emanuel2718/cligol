#include <iostream>
#include <string>
#include <ncurses.h>

#include "util.hpp"
#include "gameoflife.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // init ncurses
    initscr();
    curs_set(0); // don't show cursor
    //raw();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    // Init game of life
    GameOfLife game;
    game.run();

    endwin();
    clear();
    exit(0);
    return 0;
}
