#include <fstream>
#include <ncurses.h>
#include <string>

#include "util.hpp"

int get_width() { return LINES; }
int get_height() { return COLS; }

void print_centered(int y, int x, const char* str, int pad) {
    mvprintw(y/2, (x-strlen(str))/2 + pad, str);
}

void print_menu() {
    for (auto& line : main_menu_msg) {
        print_centered(get_width()+line.mod, get_height(), line.message, line.pad);
    }
}

std::string get_filename(int option) {
    int index = 0;
    switch (option) {
        case 48 ... 50:
            index = static_cast<int> (option - '0'); // convert to number
            break;

        // NOTE(emanuel): In case more than 10 maps get added
        //case 97 ... 102:
        //    index = static_cast<int> (option - '0') - 39; // to get 10 - 16
        //    break;
        default: break;
    }
    return MAPS[index];
}
