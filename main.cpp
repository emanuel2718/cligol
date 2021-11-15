#include <iostream>
#include <ncurses.h>

#include "util.hpp"

using namespace std;


void run() {
    int ascii_code = 0;
    bool show_menu = true;
    while (show_menu) {
        print_menu();
        ascii_code = getch();
        switch (ascii_code) {
            case 27:  show_menu = false; break; // ESC --> quit
            case 113: show_menu = false; break; // q   --> quit
            case 109: show_menu = false; break; // m   --> go to main menu
            //case 48 ... 55: case 97 ... 102: // [0, 9] or [a, f]
            case 48 ... 50: // [0, 2] for now
                if (load_map(ascii_code))
                    mvprintw(8, 0,"Starting simulation");
                else
                    mvprintw(1, 1,"Failed to start simulation");
                refresh();
                break;
            default:  break;
        }
    }

}

int main(int argc, char* argv[]) {
    // init ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    run();

    endwin();
    clear();
    exit(0);
    return 0;
}
