#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <vector>
#include <string>

#include "util.hpp"


class GameOfLife {
    public:
        GameOfLife() : board(ROWS, std::vector<char> (COLUMNS, '.')) {}

        void set_map(std::string m) { map = m; }
        std::string get_map() { return map; }
        std::vector<std::vector<char>>& get_board() { return board; }

        void simulate(std::string map);

        int  update_round() { return round++; } // returns the current round and adds 1 to it.
        void reset_round() { round = 0; }
        void update_board();
        void populate_board();
        void render_simulation();
        void set_delay(bool delay_on);
        void run();

    private:
        static const char LIVE_CELL = 'X';
        static const char DEAD_CELL = '.';
        std::string map;
        std::vector<std::vector<char>> board;
        int round = 0;
};



#endif // GAMEOFLIFE_H_
