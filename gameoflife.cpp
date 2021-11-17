#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

#include "gameoflife.hpp"
#include "util.hpp"



void GameOfLife::simulate(std::string map) {
    set_map(map);
    reset_round();
    populate_board();
    bool running = true;
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
    mvprintw(0, get_width()-10, "(%d, %d)", LINES, COLS);
    mvprintw(get_height()-1, 0, "Round: %d", update_round());
    mvprintw(0, 0, "Map: %s", get_map().c_str());
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


//void GameOfLife::update_board() {
//    int rand_col = get_random_col();
//    int rand_row = get_random_row();
//    if (board[rand_col][rand_row] == LIVE_CELL)
//        board[rand_col][rand_row] = 'F';
//    else
//        board[rand_col][rand_row] = '*';
//
//}
/*
    Game of Life rules reference:

    1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    2. Any live cell with two or three live neighbours lives on to the next generation.
    3. Any live cell with more than three live neighbours dies, as if by overpopulation.
    4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

    Condensed form:
    1. Any live cell with two or three live neighbours survives.
    2. Any dead cell with three live neighbours becomes a live cell.
    3. All other live cells die in the next generation.
       Similarly, all other dead cells stay dead.

 */
void GameOfLife::update_board() {
    for (size_t y = 0; y < board.size(); ++y) {
        for (size_t x = 0; x < board[0].size(); ++x) {
            int alive_count = 0;
            // top left
            if (x != 0 && y != 0 && board[y-1][x-1] == LIVE_CELL) alive_count++;

            // top
            if (y != 0 && board[y-1][x] == LIVE_CELL) alive_count++;

            // top right
            if (y != 0 && board[y-1][x+1] == LIVE_CELL) alive_count++;

            // left
            if (x != 0 && board[y][x-1] == LIVE_CELL) alive_count++;

            // right
            if (x != board[0].size()-1 && board[y][x+1] == LIVE_CELL) alive_count++;

            // bottom left
            if (x != 0 && y != board.size()-1 && board[y+1][x-1] == LIVE_CELL) alive_count++;

            // bottom
            if (y != board.size()-1 && board[y+1][x] == LIVE_CELL) alive_count++;

            // bottom right
            if (y != board.size()-1 && x != board[0].size()-1 && board[y+1][x+1] == LIVE_CELL) alive_count++;

            if (board[y][x] == LIVE_CELL && alive_count < 2)
                board[y][x] = DEAD_CELL;
            else if (board[y][x] == LIVE_CELL && (alive_count == 2 || alive_count == 3))
                board[y][x] = LIVE_CELL;
            else if (board[y][x] == LIVE_CELL && alive_count > 3)
                board[y][x] = DEAD_CELL;
            else if (board[y][x] == DEAD_CELL && alive_count == 3)
                board[y][x] = LIVE_CELL;

            // Rule 1: Any live cell with two or three live neighbours survives.
            //if (board[y][x] == LIVE_CELL && (alive_count == 2 || alive_count == 3)) {
            //    board[y][x] = LIVE_CELL;
            //}

            //// Rule 2: Any dead cell with three live neighbours becomes a live cell.
            //else if (board[y][x] == DEAD_CELL && alive_count == 3)
            //    board[y][x] = LIVE_CELL;
        }
    }



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
            case 48 ... 51: // [0, 3] for now
                clear();
                map = get_filename(ascii_code);
                simulate(map);
                break;
            default: break;
        }
    }
}
