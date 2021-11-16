#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <vector>
#include <string>

#include "util.hpp"




class GameOfLife {
    public:
        //GameOfLife() : board(get_width()-4, std::vector<char> (get_height(), '.')) {}
        GameOfLife() : board(COLUMNS, std::vector<char> (ROWS, '.')) {}

        void set_map(std::string m) { map = m; }
        std::string get_map() { return map; }
        std::vector<std::vector<char>>& get_board() { return board; }

        void start_simulation(std::string map);
        //void start_simulation(std::string map);
        //void print_board(std::vector<std::vector<char>>& vec);
        //void populate_board(std::vector<std::vector<char>>& vec, std::string map);
        void print_board();
        void populate_board();
        void update_board();

    private:
        static const char LIVE_CELL = 'X';
        static const char DEAD_CELL = '.';
        std::string map;
        std::vector<std::vector<char>> board;
};


void run();

#endif // GAMEOFLIFE_H_
