#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

#include "gameoflife.hpp"
#include "util.hpp"



void GameOfLife::start_simulation(std::string map) {
    set_map(map);
    populate_board();
    bool running = true;
    //int ascii_code = 0;
    nodelay(stdscr, TRUE);
    while (running) {
        clear();
        refresh();
        print_board();
        update_board();
        refresh();
        timeout(50);

        if (getch() == 27) { // ESC
            running = false;
        }
        else if (getch() == 98) { // b to go back
            running = false;
            // Are we leaking memory?
            run();
            return;
        }
    }
}

void GameOfLife::print_board() {
    mvprintw(0, 0, "Screen Coordinates: (%d, %d)", LINES, COLS);

    refresh();
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            mvaddch(i+get_height()/2 - board.size()/2,
                    j+get_width()/2 - board[0].size()/2,
                    board[i][j]);
        }
    }
}


void GameOfLife::populate_board() {
    std::ifstream file;
    file.open(map);
    if (!file) return;
    for (int i = 0; i < COLUMNS; ++i)
        for (int j = 0; j < ROWS; ++j)
            file >> board[i][j];
    return;
}


void GameOfLife::update_board() {
    int rand_col = get_random_col();
    int rand_row = get_random_row();
    if (board[rand_col][rand_row] == LIVE_CELL)
        board[rand_col][rand_row] = 'F';
    else
        board[rand_col][rand_row] = '*';

}

void GameOfLife::run() {
    clear();
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
                clear();
                map = get_filename(ascii_code);
                start_simulation(map);
                break;
            default: break;
        }
    }
}
