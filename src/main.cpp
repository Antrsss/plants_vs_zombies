#include <ncurses.h>
#include "config.h"
#include "display.h"
#include "entities.h"

extern "C" int step(char*);

char* playing_field = new char[45];

// 0 1 2 3 4 5 6 7 8
// . . . . . . . @ .
// . . . . . . . . .
// . . . . . . # . .
// . . . . . . . . .
// . . . . . . . . .
// . . . . . . . . .


int main() {
    initscr();
    char* entities = new char[]{ '.', '%', '}', '*', '#', '&', '$', '@', '>' };
    init_entities(entities);
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        playing_field[i] = '.';
    }
    playing_field[0 * 8 + 7] = '@';
    playing_field[1 * 8 + 6] = '#';
    display(playing_field);

    endwin();
    return 0;
}
