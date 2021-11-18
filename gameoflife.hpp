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

        int  update_generation() { return generation++; } // returns the current generation and adds 1 to it.
        void reset_generation() { generation = 0; }
        void update_board();
        void populate_board();
        void render_simulation();
        void run();

        // NOTE: for the reset I need to grab the map code. Because
        //       if we try to reset the map using the current map is going to be
        //       already changed

        enum class State { RUNNING, PAUSED };
        State get_state() { return state; }
        void set_state(State st) { state = st; }
        void toogle_state(); // toogles between State::RUNNING and State::PAUSED


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
        int generation = 0;
        State state = State::PAUSED; // start in paused state always
};



#endif // GAMEOFLIFE_H_
