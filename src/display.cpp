#include "display.h"
#include <ncurses.h>

void display(char* playing_field) {
    int row, col;
    getmaxyx(stdscr, row, col);

    // перемещение курсора в стандартном экране
    row /= 2;
    col /= 2;

    for (int i = 0; i < 9; ++i) {
        move(row, col);
        addch(playing_field[i]);
        getch();  // ждём нажатия символа
    }
    refresh();  // обновить экран
    getch();    // ждём нажатия символа
}
