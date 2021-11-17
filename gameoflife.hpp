#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <vector>
#include <string>

#include "util.hpp"




class GameOfLife {
    public:
        GameOfLife() : board(COLUMNS, std::vector<char> (ROWS, '.')) {}

        void set_map(std::string m) { map = m; }
        std::string get_map() { return map; }
        std::vector<std::vector<char>>& get_board() { return board; }

        void start_simulation(std::string map);

        int  update_round() { return round++; } // returns the current round and adds 1 to it.
        void reset_round() { round = 0; }
        void print_board();
        void populate_board();
        void update_board();
        void run();

    private:
        static const char LIVE_CELL = 'X';
        static const char DEAD_CELL = '.';
        std::string map;
        std::vector<std::vector<char>> board;
        int round = 0;
};



#endif // GAMEOFLIFE_H_
