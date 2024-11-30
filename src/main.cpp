#include <ncurses.h>
#include <array>
#include <cmath>
#include "config.h"
#include "display.h"
#include "entities.h"

extern "C" int step(char*);
extern "C" int update_suns(char*, int);

char* playing_field = new char[WIDTH * HEIGHT + 1]{
    "~>%?*.$....~>%?*.#*.*.~>%?*.#*.*.~>%?*.*&$$.~>%?*.*.*.."
};
std::array<const chtype, 13> entities{ '.', '%', '?', '!', '*', '#', '|',
                                       '&', '$', '@', '>', '~', '=' };

// 01 2 3 4 5 6 7 8 9 10
// ~> . . . . . @ . . .
// ~> . . . . . . . . .
// ~> . . . . # . . . .
// ~> . . . . . . . . .
// ~> . . . . . . . . .
// ~> . . . . . . . . .

void init_playing_field(char*);
int take_input(char*, int);
int create_plant(char*);
int delete_plant(char*);
int read_coords();

int main() {
    initscr();
    noecho();
    cbreak();

    int choice = menu();
    clear();

    bool game_on = true;

    switch (choice) {
        case 2:
            game_on = false;
            break;
    }
    /*init_playing_field(playing_field);*/
    /*init_entities(entities);*/
    int suns = 100;
    int game_result = 1;
    int cycles = 0;

    while (game_on) {
        suns = update_suns(playing_field, suns);
        if (step(playing_field) == -1) {
            game_on = false;
            game_result = -1;
        } else {
            update_game_screen(playing_field, entities, suns);
        }
        ++cycles;
        if (cycles >= 200) {
            game_on = false;
            game_result = 1;
        }
        if (!game_on) {
            choice = end_screen(game_result);
            switch (choice) {
                case 1:
                    init_playing_field(playing_field);
                    game_on = true;
                    game_result = 1;
                    suns = 100;
                    cycles = 0;
                    clear();
                    break;
            }
        } else {
            if (take_input(playing_field, suns) == -1) {
                game_on = false;
            }
        }
    }

    endwin();
    return 0;
}

int take_input(char* playing_field, int suns) {
    int result = 0;
    int y, x;
lp:
    getyx(stdscr, y, x);
    move(y + 4, 0);
    printw("Enter your action: ");
    refresh();
    int ch;
    while ((ch = getch()) != 'n') {
        if (ch == 'd') {
            if (delete_plant(playing_field) > 0) {
                update_game_screen(playing_field, entities, suns);
                goto lp;
            }
        } else if (ch == 'p') {
            if (create_plant(playing_field) > 0) {
                update_game_screen(playing_field, entities, suns);
                goto lp;
            }
        } else if (ch == 'q') {
            return -1;
        }
        getyx(stdscr, y, x);
        move(y, 0);
        clrtoeol();
        refresh();
        printw("Invalid input. Enter your action: ");
        refresh();
    }
    getyx(stdscr, y, x);
    move(y, 0);
    clrtoeol();
    move(y - 1, 0);
    clrtoeol();
    return result;
}

int read_coords() {
    echo();
    int y, x;
    getyx(stdscr, y, x);
    move(y, 0);
    printw(
        "Please enter a letter (A-I) followed by a "
        "number (1-5): ");
    refresh();
    char letter;
    int number;
    bool valid_input = false;
    while (!valid_input) {
        letter = getch();
        if (letter >= 'a' && letter <= 'i') {
            letter = letter - 'a' + 'A';
        }
        number = getch() - '0';
        if ((letter >= 'A' && letter <= 'I') && (number >= 1 && number <= 5)) {
            valid_input = true;
        } else {
            printw(
                "Invalid input. Please enter a letter (A-I) followed by a "
                "number (1-5): ");
            refresh();
        }
    }
    move(y, 0);
    clrtoeol();
    refresh();
    noecho();
    return (number - 1) * WIDTH + (letter - 'A' + 2);
}

int delete_plant(char* playing_field) {
    int coords = read_coords();
    if (coords < 0) {
        return -1;
    }
    switch (playing_field[coords]) {
        case '#':
            playing_field[coords] = '.';
            break;
        case '%':
            playing_field[coords] = '.';
            break;
        case '!':
            playing_field[coords] = '.';
            break;
        case '?':
            playing_field[coords] = '.';
            break;
    }
    return 1;
}

int create_plant(char* playing_field) {
    int coords = read_coords();
    if (coords < 0) {
        return -1;
    }
    return 1;
}

void init_playing_field(char* playing_field) {
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        playing_field[i] = '.';
    }
    playing_field[0] = '~';
    playing_field[11] = '~';
    playing_field[22] = '~';
    playing_field[33] = '~';
    playing_field[44] = '~';
    playing_field[1] = '>';
    playing_field[12] = '>';
    playing_field[23] = '>';
    playing_field[34] = '>';
    playing_field[45] = '>';
    playing_field[0 * WIDTH + 6] = '#';
    playing_field[1 * WIDTH + 6] = '#';
    playing_field[2 * WIDTH + 6] = '#';
    playing_field[3 * WIDTH + 6] = '#';
    playing_field[4 * WIDTH + 6] = '#';
    playing_field[0 * WIDTH + 2] = '%';
    playing_field[1 * WIDTH + 2] = '%';
    playing_field[2 * WIDTH + 2] = '%';
    playing_field[3 * WIDTH + 2] = '%';
    playing_field[4 * WIDTH + 2] = '%';
    playing_field[0 * WIDTH + 3] = '!';
    playing_field[1 * WIDTH + 3] = '!';
    playing_field[2 * WIDTH + 3] = '!';
    playing_field[3 * WIDTH + 3] = '!';
    playing_field[4 * WIDTH + 3] = '!';
}

void fake_step(char* playing_field) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 2; j < WIDTH; ++j) {
            int char_index = i * WIDTH + j;
            char cur_ch = playing_field[char_index];
            if (j == 2) {
                continue;
            }
            if (cur_ch == '&' || cur_ch == '@' || cur_ch == '$') {
                playing_field[char_index - 1] = cur_ch;
                playing_field[char_index] = '.';
            }
        }
    }
}
