#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

#include "gameoflife.hpp"
#include "util.hpp"


void GameOfLife::simulate(std::string map) {
    set_map(map);
    reset_generation();
    populate_board();

    int ascii_code;
    bool simulating = true;
    while (simulating) {
        clear();
        render_simulation();
        refresh();
        ascii_code = getch();
        update_board();
        refresh();

        if (get_state() == State::RUNNING) timeout(100);
        switch (ascii_code) {
            case 27: case 113: // ESC
                simulating = false;
                endwin();
                exit(0);
                break;
            case 98: // 'b' for back
                simulating = false;
                run();
                break;
            case 112: // 'p' for pause
                toogle_state();
                break;
            default:
                break;
        }
    }
}

void GameOfLife::toogle_state() {
    if (get_state() == State::RUNNING) {
        set_state(State::PAUSED);
        nodelay(stdscr, FALSE);
    }
    else {
        set_state(State::RUNNING);
        nodelay(stdscr, TRUE);
    }
}

void GameOfLife::render_simulation() {
    mvprintw(0, get_width()-10, "(%d, %d)", LINES, COLS);
    mvprintw(get_height()-1, 0, "Generation #: %d", update_generation());
    mvprintw(0, 0, "Map: %s", get_map().c_str());
    mvprintw(2, 0, "ROWS: %d, COLS: %d", board.size(), board[0].size());
    mvprintw(get_height()-1, get_width()-15,
             get_state() == State::RUNNING ? "State: Running" : "State: Paused");
    refresh();
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            if (board[i][j] == LIVE_CELL)
                mvaddch(i+get_height()/2 - board.size()/2,
                        j+get_width()/2 - board[0].size()/2,
                        RENDER_LIVE_CELL);
            else
                mvaddch(i+get_height()/2 - board.size()/2,
                        j+get_width()/2 - board[0].size()/2,
                        RENDER_DEAD_CELL);
        }
    }
}


void GameOfLife::populate_board() {
    std::ifstream file;
    file.open(map);
    if (!file) return;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            file >> board[i][j];
        }
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
void GameOfLife::update_board() {
    // init temp board
    std::vector<std::vector<char>> temp_board(ROWS, std::vector<char>(COLUMNS, '.'));

    int alive_count;
    for (size_t y = 0; y < board.size(); ++y) {
        for (size_t x = 0; x < board[0].size(); ++x) {
            alive_count = 0;
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

            // RULE 1
            if (board[y][x] == LIVE_CELL && alive_count < 2)
                temp_board[y][x] = DEAD_CELL;

            // RULE 2
            else if (board[y][x] == LIVE_CELL && (alive_count == 2 || alive_count == 3))
                temp_board[y][x] = LIVE_CELL;

            // RULE 3
            else if (board[y][x] == LIVE_CELL && alive_count > 3)
                temp_board[y][x] = DEAD_CELL;

            // RULE 4
            else if (board[y][x] == DEAD_CELL && alive_count == 3)
                temp_board[y][x] = LIVE_CELL;
        }
    }
    // Fill the the actual board
    for (size_t y = 0; y < temp_board.size(); ++y)
        for (size_t x = 0; x < temp_board[0].size(); ++x)
            board[y][x] = temp_board[y][x];
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
