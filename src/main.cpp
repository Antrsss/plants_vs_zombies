#include <ncurses.h>
#include "config.h"
#include "display.h"
#include "entities.h"

extern "C" int step(char*);

char* playing_field = new char[WIDTH * HEIGHT];
chtype* entities = new chtype[]{ '.', '%', '?', '!', '*', '#', '|',
                                 '&', '$', '@', '>', '~', '=' };

// 01 2 3 4 5 6 7 8 9 10
// => . . . . . @ . . .
// => . . . . . . . . .
// => . . . . # . . . .
// => . . . . . . . . .
// => . . . . . . . . .
// => . . . . . . . . .

void fake_step(char*);
void init_playing_field(char*);

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
    init_playing_field(playing_field);
    init_entities(entities);

    while (game_on) {
        display(playing_field, entities);
        if (step(playing_field) == -1) {
            game_on = false;
        }
        getch();
    }

    endwin();
    return 0;
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
    playing_field[0 * 11 + 3] = '?';
    playing_field[0 * 11 + 6] = '$';
    playing_field[1 * 11 + 3] = '!';
    playing_field[2 * 11 + 3] = '!';
    playing_field[3 * 11 + 3] = '!';
    playing_field[3 * 11 + 4] = '!';
    playing_field[0 * 11 + 9] = '&';
    playing_field[1 * 11 + 3] = '@';
    playing_field[4 * 11 + 2] = '@';
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
