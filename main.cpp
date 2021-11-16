#include <iostream>
#include <string>
#include <ncurses.h>

#include "util.hpp"
#include "gameoflife.hpp"

using namespace std;


//void run() {
//    int ascii_code = 0;
//    bool show_menu = true;
//    string map;
//    GameOfLife game;
//    while (show_menu) {
//        print_menu();
//        ascii_code = getch();
//        switch (ascii_code) {
//            case 27:  show_menu = false; break; // ESC --> quit
//            case 113: show_menu = false; break; // q   --> quit
//            case 109: show_menu = false; break; // m   --> go to main menu
//            //case 48 ... 55: case 97 ... 102: // [0, 9] or [a, f]
//            case 48 ... 50: // [0, 2] for now
//                clear();
//                map = get_filename(ascii_code);
//                game.start_simulation(map);
//                refresh();
//                break;
//            default: break;
//        }
//    }
//}

int main(int argc, char* argv[]) {
    // init ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();

    //show_main_menu();
    //GameOfLife game;
    //game.run();
    run();

    endwin();
    clear();
    exit(0);
    return 0;
}
