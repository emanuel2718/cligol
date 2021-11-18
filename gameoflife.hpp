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
        void toogle_delay();

        // NOTE: for the reset I need to grab the map code. Because
        //       if we try to reset the map using the current map is going to be
        //       already changed
        //void reset_map(std::string map);
        bool is_delay() { return delay_on; }
        void set_delay(bool delay) { delay_on = delay; }
        void run();

    private:
        // the board only knows about these two chars
        static const char LIVE_CELL = 'X';
        static const char DEAD_CELL = '.';

        // if the cell is a LIVE_CELL it will render as RENDER_LIVE_CELL in the screen
        static const char RENDER_LIVE_CELL = 'X';
        // if the cell is a DEAD_CELL it will render as RENDER_DEAD_CELL in the screen
        static const char RENDER_DEAD_CELL = ' ';

        std::string map;
        std::vector<std::vector<char>> board;
        int round = 0;
        bool delay_on = false; // basically control run or pause. Might change the name.
};



#endif // GAMEOFLIFE_H_
