#ifndef DISPLAY
#define DISPLAY

#include <string>
#include <vector>
#include "config.h"
#include "ncurses.h"

void update_game_screen(char* playing_field, chtype* entities, int suns);
void display(char* playing_field, chtype* entities);
int menu();
void print_menu(WINDOW* menu_win, int highlight,
                std::vector<std::string>& choices, int n_choices);
void print_logo(const std::vector<std::string>& logo);
int end_screen(int result);

#endif  // !DISPLAY
