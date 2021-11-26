#ifndef UTIL_H_
#define UTIL_H_


#include <cstring>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>


static const int ROWS = 20;
static const int COLUMNS = 80;


static const std::vector<std::string> MAPS{
    "maps/explosion.txt",
    "maps/gun.txt",
    "maps/spaceship.txt",
    "maps/snake.txt"
};

struct Line {
    int mod; // vertical modifier for message (y) position (+y = downwards direction)
    int pad; // horizontal pad for message centering purposes (+x right pad, -x left pad)
    const char* message;
};

static const std::vector<Line> main_menu_msg = {
    {0, 0, "Game of Life visualizer, CLI edition"},
    {2, 0, "by Emanuel Ramirez"},
    {8, 0, "Please, choose a initial map. Press ESC or q to quit."},
    {12, -1, "0. Explosion map"},
    {14, -4, "1. Gun map"},
    {16, -1, "2. Spaceship map"},
    {18, -3, "3. Snake map"},
};

static const std::vector<Line> keybinds_help_msg = {
    {-8, 0, "Cligol keybind panel"},
    {0, 0, "ESC        - Quit Cligol"},
    {2, 0, "q          - Quit Cligol"},
    {4, -2, "b          - go back"},
    {6, 1, "h          - Show this page"},
    {8, 2, "p          - Pause simulation"},
    {10, 1, "UP arrow   - Increase speed"},
    {12, 1, "DOWN arrow - Decrease speed"}
};

// Type of menu to be rendered on the screen
enum class MenuType { main_menu, keybind_menu };

// Maps the MenuType to it's corresponding screen text message
static const std::unordered_map<MenuType, const std::vector<Line>> menu_map {
    {MenuType::main_menu, main_menu_msg},
    {MenuType::keybind_menu, keybinds_help_msg},
};

bool load_map();
int get_width();
int get_height();
void print_menu(MenuType m_type); // will render the corresponding MenuType message on the screen
int get_random_col();
int get_random_row();

std::string get_filename(int f);
void print_centered(int y, int x, const char* str, int pad=0);




#endif // UTIL_H_
