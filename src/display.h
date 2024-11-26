#ifndef DISPLAY
#define DISPLAY

#include <string>
#include <vector>
#include "config.h"
#include "ncurses.h"

void display_game_screen();
void display(char* playing_field, chtype* entities);
int menu();
void print_menu(WINDOW* menu_win, int highlight,
                std::vector<std::string>& choices, int n_choices);
void print_logo(const std::vector<std::string>& logo);

#endif  // !DISPLAY
