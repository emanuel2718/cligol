#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

#include "gameoflife.hpp"
#include "util.hpp"


void start_simulation(std::string map) {
    GameOfLife game;
    game.set_map(map);
    game.populate_board(game.get_board(), map);
    while (getch() != 27) {
        clear();
        refresh();
        game.print_board(game.get_board());
        refresh();

    }
}

// TODO(emanuel): print centered somehow?
void GameOfLife::print_board(std::vector<std::vector<char>>& board) {
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[0].size(); ++j) {
            mvaddch(i, j, board[i][j]);
        }
    }
}


void GameOfLife::populate_board(std::vector<std::vector<char>>& board, std::string map) {
    std::ifstream file;
    file.open(map);
    if (!file) return;
    for (int i = 0; i < COLUMNS; ++i) {
        for (int j = 0; j < ROWS; ++j)
            file >> board[i][j];
    return;
}
