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
    //nodelay(stdscr, TRUE);

    int ascii_code;
    bool running = true, delay = true;
    while (running) {
        clear();
        render_simulation();
        refresh();
        update_board();
        refresh();
        ascii_code = getch();

        if (!delay) timeout(500);
        switch (ascii_code) {
            case 27: case 113: // ESC
                running = false;
                endwin();
                exit(0);
                break;
            case 98: // 'b' for back
                running = false;
                run();
                break;
            case 114:
                break;
            case 112: // 'p' for pause
                if (delay) {
                    delay = false;
                    set_delay(false);
                }
                else {
                    delay = true;
                    set_delay(true);
                }
                break;
            default:
                break;
        }
    }
}

void GameOfLife::set_delay(bool delay) {
    if (delay)
        nodelay(stdscr, FALSE);
    else
        nodelay(stdscr, TRUE);
}

void GameOfLife::render_simulation() {
    mvprintw(0, get_width()-10, "(%d, %d)", LINES, COLS);
    mvprintw(get_height()-1, 0, "Round: %d", update_round());
    mvprintw(0, 0, "Map: %s", get_map().c_str());
    mvprintw(2, 0, "ROWS: %d, COLS: %d", board.size(), board[0].size());
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
    std::ofstream debug_log("debug.txt");
    file.open(map);
    if (!file) return;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            file >> board[i][j];
            debug_log << board[i][j];
        }
        debug_log << '\n';
    }
    return;
}


/*  Game of Life rules reference:

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
    //0  1  2  3
// [0, 0, 0, 0] size = 4, size-1 = 3
void GameOfLife::update_board() {

    // init temp board
    std::vector<std::vector<char>> temp_board(ROWS, std::vector<char>(COLUMNS, '.'));

    int alive_count = 0; // number of neighbors alive
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            alive_count = 0;

            // top left
            if (i != 0 && j != 0 && board[i-1][j-1] == LIVE_CELL)
                alive_count++;

            // top
            if (i != 0 && board[i-1][j] == LIVE_CELL)
                alive_count++;

            // top right
            if (i != 0 && j < board[0].size()-1 && board[i-1][j+1] == LIVE_CELL)
                alive_count++;

            // left
            if (j != 0 && board[i][j-1] == LIVE_CELL)
                alive_count++;

            // right
            if (j < board[0].size()-1 && board[i][j+1])
                alive_count++;

            // bottom left
            if (i < board.size()-1 && j != 0 && board[i+1][j-1] == LIVE_CELL)
                alive_count++;

            // bottom
            if (i < board.size()-1 && board[i+1][j] == LIVE_CELL)
                alive_count++;

            // bottom right
            if (i < board.size()-1 && j < board[0].size()-1 && board[i+1][j+1] == LIVE_CELL)
                alive_count++;


            /*
                1. Any LIVE cell with fewer than two live neighbours DIES
                2. Any LIVE cell with two or three live neighbours LIVES
                3. Any LIVE cell with more than three live neighbours DIES
                4. Any DEAD cell with exactly three live neighbours becomes a LIVE cell
            */

            // RULE 1
            if (board[i][j] == LIVE_CELL && alive_count < 2)
                temp_board[i][j] = DEAD_CELL;

            // RULE 2
            //else if (board[i][j] == LIVE_CELL && alive_count == 2)
            //    board[i][j] = LIVE_CELL;

            //else if (board[i][j] == LIVE_CELL && alive_count == 3)
            //    board[i][j] = LIVE_CELL;

            // RULE 3
            else if (board[i][j] == LIVE_CELL && alive_count > 3)
                temp_board[i][j] = DEAD_CELL;

            // RULE 4
            else if (board[i][j] == DEAD_CELL && alive_count == 3)
                temp_board[i][j] = LIVE_CELL;


            //if (board[i][j] == LIVE_CELL && alive_count < 2)
            //    board[i][j] = DEAD_CELL;

            //else if (board[i][j] == DEAD_CELL && (alive_count == 2 || alive_count == 3))
            //    board[i][j] = LIVE_CELL;

            //else if (board[i][j] == LIVE_CELL && alive_count > 3)
            //    board[i][j] = DEAD_CELL;

            //else if (board[i][j] == DEAD_CELL && alive_count == 3)
            //    board[i][j] = LIVE_CELL;
        }
    }

    // Fill the the actual board
    for (size_t i = 0; i < temp_board.size(); ++i)
        for (size_t j = 0; j < temp_board[0].size(); ++j)
            board[i][j] = temp_board[i][j];
}














//void GameOfLife::update_board() {
//    for (size_t y = 0; y < board.size(); ++y) {
//        for (size_t x = 0; x < board[0].size(); ++x) {
//            int alive_count = 0;
//            // top left
//            if (x != 0 && y != 0 && board[y-1][x-1] == LIVE_CELL) alive_count++;
//
//            // top
//            if (y != 0 && board[y-1][x] == LIVE_CELL) alive_count++;
//
//            // top right
//            if (y != 0 && board[y-1][x+1] == LIVE_CELL) alive_count++;
//
//            // left
//            if (x != 0 && board[y][x-1] == LIVE_CELL) alive_count++;
//
//            // right
//            if (x != board[0].size()-1 && board[y][x+1] == LIVE_CELL) alive_count++;
//
//            // bottom left
//            if (x != 0 && y != board.size()-1 && board[y+1][x-1] == LIVE_CELL) alive_count++;
//
//            // bottom
//            if (y != board.size()-1 && board[y+1][x] == LIVE_CELL) alive_count++;
//
//            // bottom right
//            if (y != board.size()-1 && x != board[0].size()-1 && board[y+1][x+1] == LIVE_CELL) alive_count++;
//
//            if (board[y][x] == LIVE_CELL && alive_count < 2)
//                board[y][x] = DEAD_CELL;
//            else if (board[y][x] == LIVE_CELL && (alive_count == 2 || alive_count == 3))
//                board[y][x] = LIVE_CELL;
//            else if (board[y][x] == LIVE_CELL && alive_count > 3)
//                board[y][x] = DEAD_CELL;
//            else if (board[y][x] == DEAD_CELL && alive_count == 3)
//                board[y][x] = LIVE_CELL;
//
//            // Rule 1: Any live cell with two or three live neighbours survives.
//            //if (board[y][x] == LIVE_CELL && (alive_count == 2 || alive_count == 3)) {
//            //    board[y][x] = LIVE_CELL;
//            //}
//
//            //// Rule 2: Any dead cell with three live neighbours becomes a live cell.
//            //else if (board[y][x] == DEAD_CELL && alive_count == 3)
//            //    board[y][x] = LIVE_CELL;
//        }
//    }
//
//
//
//}

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
