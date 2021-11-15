#include <fstream>
#include <ncurses.h>

#include "util.hpp"

int get_max_rows() { return LINES; }
int get_max_cols() { return COLS; }

void print_centered(int y, int x, const char* str, int pad) {
    mvprintw(y/2, (x-strlen(str))/2 + pad, str);
}

void print_menu() {
    auto message = main_menu_msg;
    for (auto& line : message) {
        print_centered(get_max_rows()+line.mod, get_max_cols(), line.message, line.pad);
    }
}

bool load_map(int option) {
    int index = 0;
    std::ifstream file;
    switch (option) {
        case 48 ... 50:
            index = static_cast<int> (option - '0'); // convert to number
            break;

        // NOTE(emanuel): In case more than 10 maps get added
        //case 97 ... 102:
        //    index = static_cast<int> (option - '0') - 39; // to get 10 - 16
        //    mvprintw(3, 3, "The option = %d", index);
        //    refresh();
        //    break;
        default:
            break;
    }

    file.open(MAPS[index].c_str());
    if (!file) return false;
    file.close();

    return true;
}
