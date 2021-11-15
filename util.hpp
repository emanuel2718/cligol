#ifndef UTIL_H_
#define UTIL_H_


#include <cstring>
#include <string>
#include <iostream>
#include <vector>


static const int ROWS = 80;
static const int COLUMNS = 20;

enum class SCREEN_TYPE {
    MAIN_MENU,
    GOL_SIMULATION
};

static const std::vector<std::string> MAPS{
    "maps/explosion.txt",
    "maps/gun.txt",
    "maps/spaceship.txt"
};

struct Line {
    int mod; // vertical modifier for message (y) position (+y = downwards direction)
    int pad; // horizontal pad for message centering purposes
    const char* message;
};

static const std::vector<Line> main_menu_msg = {
    {0, 0, "Game of Life visualizer, CLI edition"},
    {2, 0, "by Emanuel Ramirez"},
    {8, 0, "Please, choose a initial map. Press ESC or q to quit."},
    {12, -1, "0. Explosion map"},
    {14, -4, "1. Gun map"},
    {16, -1, "2. Spaceship map"}
};

int get_width();
int get_height();
void print_menu();
std::string get_filename(int);
bool load_map();
void print_centered(int y, int x, const char* str, int pad=0);




#endif // UTIL_H_
