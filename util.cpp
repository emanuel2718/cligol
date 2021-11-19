#include <fstream>
#include <ncurses.h>
#include <string>
#include <random>

#include "util.hpp"

int get_height() { return LINES; }
int get_width() { return COLS; }

void print_centered(int y, int x, const char* str, int pad) {
    mvprintw(y/2, (x-strlen(str))/2 + pad, str);
}

void print_menu() {
    for (auto& line : main_menu_msg) {
        print_centered(get_height()+line.mod, get_width(), line.message, line.pad);
    }
}

std::string get_filename(int option) {
    int index = 0;
    switch (option) {
        case 48 ... 51:
            index = static_cast<int> (option - '0'); // convert to number
            break;
        default: break;
    }
    return MAPS[index];
}


int get_random_col() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, COLUMNS-1);
    return dist6(rng);

}

int get_random_row() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, ROWS-1);
    return dist6(rng);

}
