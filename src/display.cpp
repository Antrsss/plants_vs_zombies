#include "display.h"
#include <ncurses.h>
#include <cmath>
#include <string>
#include "config.h"
#include "entities.h"

void update_game_screen(char* playing_field,
                        std::array<const chtype, 13> entities, int suns) {
    int start_row = 0, start_col = 0;
    getmaxyx(stdscr, start_row, start_col);
    start_col /= 2;
    start_row /= 2;
    start_col -= 10;
    start_row -= 5;
    std::string suns_msg = "Suns: " + std::to_string(suns);
    move(start_row - 2, 0);
    clrtoeol();
    move(start_row - 2, start_col);
    addstr(suns_msg.c_str());
    refresh();

    getmaxyx(stdscr, start_row, start_col);
    start_col = 0;
    start_row /= 2;
    move(start_row, start_col);
    addstr("Sunflower (%): 50 suns");
    move(++start_row, start_col);
    addstr("Peashooter(!/?): 100 suns");
    move(++start_row, start_col);
    addstr("Wallnut(#): 75 suns");
    display(playing_field, entities);
}

void display(char* playing_field, std::array<const chtype, 13> entities) {
    int start_row = 0, start_col = 0;
    getmaxyx(stdscr, start_row, start_col);
    start_col /= 2;
    start_row /= 2;
    start_col -= 10;
    start_row -= 5;
    int row = start_row, col = start_col;
    row -= 1;
    col += 3;
    for (int i = 0; i < WIDTH - 2; ++i) {
        move(row, col);
        addch('A' + i);
        col += 2;
    }

    row = start_row;
    col = start_col - 2;
    for (int i = 0; i < HEIGHT; ++i) {
        move(row, col);
        addch('1' + i);
        row += 1;
    }

    row = start_row;
    col = start_col;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            move(row, col);
            chtype ch;
            switch (playing_field[i * WIDTH + j]) {
                case '.':
                    ch = entities[EntitiyIndex::Empty];
                    break;
                case '%':
                    ch = entities[EntitiyIndex::Sunflower];
                    break;
                case '?':
                    ch = entities[EntitiyIndex::NotReadyPeashooter];
                    break;
                case '!':
                    ch = entities[EntitiyIndex::ReadyPeashooter];
                    break;
                case '*':
                    ch = entities[EntitiyIndex::Pea];
                    break;
                case '#':
                    ch = entities[EntitiyIndex::Wallnut];
                    break;
                case '|':
                    ch = entities[EntitiyIndex::DamagedWallnut];
                    break;
                case '&':
                    ch = entities[EntitiyIndex::SmallZombie];
                    break;
                case '$':
                    ch = entities[EntitiyIndex::MediumZombie];
                    break;
                case '@':
                    ch = entities[EntitiyIndex::BigZombie];
                    break;
                case '>':
                    ch = entities[EntitiyIndex::Lawnmower];
                    break;
                case '~':
                    ch = entities[EntitiyIndex::ReadyLawnmowerBase];
                    break;
                case '=':
                    ch = entities[EntitiyIndex::NotReadyLawnmowerBase];
                    break;
            }
            addch(ch);
            refresh();
            col += 1 + (ch != entities[EntitiyIndex::ReadyLawnmowerBase] &&
                        ch != entities[EntitiyIndex::NotReadyLawnmowerBase]);
        }
        addch('\n');
        row += 1;
        col = start_col;
    }
    refresh();
}

void print_menu(WINDOW* menu_win, int highlight,
                std::vector<std::string>& choices, int n_choices) {
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        ++y;
    }
    wrefresh(menu_win);
}

int menu() {
    int height, width;
    getmaxyx(stdscr, height, width);
    std::vector<std::string> logo = {
        // clang-format off
        " ___  _              _                             ____             _     _          ",
        "| _ \\| | __ _  _ _  | |_  ___      __ __ ___      |_  / ___  _ __  | |__ (_) ___  ___",
        "|  _/| |/ _` || ' \\ |  _|(_-/      \\ V /(_-/       / / / _ \\| '  \\ |  _ \\| |/ -_)(_-/",
        "|_|  |_|\\__/_||_||_| \\__|/__/       \\_/ /__/      /___|\\___/|_|_|_||____/|_|\\___|/__/",
        // clang-format on
    };
    int startx = (width - 40) / 2;
    int starty = (height - 10) / 2;
    WINDOW* menu_win = newwin(10, 40, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    std::vector<std::string> choices = { "Play", "Exit" };
    int n_choices = choices.size();
    int highlight = 1;
    int choice = -1;
    int c;
    print_logo(logo);
    print_menu(menu_win, highlight, choices, n_choices);
    while (true) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1) {
                    highlight = n_choices;
                } else {
                    --highlight;
                }
                break;
            case KEY_DOWN:
                if (highlight == n_choices) {
                    highlight = 1;
                } else {
                    ++highlight;
                }
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        print_menu(menu_win, highlight, choices, n_choices);
        if (choice != -1) {
            break;
        }
    }
    return choice;
}

void print_logo(const std::vector<std::string>& logo) {
    int x, y;
    getmaxyx(stdscr, y, x);
    x /= 2;
    y /= 2;
    y -= 3 * logo.size();
    x -= logo[0].size() / 2;
    for (const auto& line : logo) {
        mvprintw(y++, x, "%s", line.c_str());
    }
    refresh();
}

int end_screen(int result) {
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);
    std::vector<std::string> logo_win = {
        // clang-format off
        "__      __ ___  _  _ ",
        "\\ \\    / /|_ _|| \\| |",
        " \\ \\/\\/ /  | | | .  |",
        "  \\_/\\_/  |___||_|\\_|",
        // clang-format on
    };
    std::vector<std::string> logo_loss = {
        // clang-format off
        " _      ___   ___  ___ ",
        "| |    / _ \\ / __|/ __|",
        "| |__ | (_) |\\__ \\\\__ \\",
        "|____| \\___/ |___/|___/"
        // clang-format on
    };
    int startx = (width - 40) / 2;
    int starty = (height - 10) / 2;
    WINDOW* menu_win = newwin(10, 40, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    std::vector<std::string> choices = { "New game", "Exit" };
    int n_choices = choices.size();
    int highlight = 1;
    int choice = -1;
    int c;
    if (result == 1) {
        print_logo(logo_win);
    } else {
        choices[0] = "Retry";
        print_logo(logo_loss);
    }
    print_menu(menu_win, highlight, choices, n_choices);
    while (true) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1) {
                    highlight = n_choices;
                } else {
                    --highlight;
                }
                break;
            case KEY_DOWN:
                if (highlight == n_choices) {
                    highlight = 1;
                } else {
                    ++highlight;
                }
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        print_menu(menu_win, highlight, choices, n_choices);
        if (choice != -1) {
            break;
        }
    }
    return choice;
}
