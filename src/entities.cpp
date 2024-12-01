#include "entities.h"
#include <ncurses.h>
#include <array>

std::array<const chtype, 13> init_entities() {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    chtype empty = '.' | COLOR_PAIR(3);
    chtype sf = '%' | COLOR_PAIR(1);
    chtype nrp = '?' | COLOR_PAIR(2);
    chtype rp = '!' | COLOR_PAIR(2);
    chtype p = '*' | COLOR_PAIR(2);
    chtype wn = '#' | COLOR_PAIR(1);
    chtype dwn = '|' | COLOR_PAIR(1);
    chtype sz = '&' | COLOR_PAIR(4);
    chtype mz = '$' | COLOR_PAIR(4);
    chtype bz = '@' | COLOR_PAIR(4);
    chtype lm = '>' | COLOR_PAIR(5);
    chtype rlmb = '~' | COLOR_PAIR(5);
    chtype nrlmb = '=' | COLOR_PAIR(5);

    return std::array<const chtype, 13>{ empty, sf, nrp, rp, p,    wn,   dwn,
                                         sz,    mz, bz,  lm, rlmb, nrlmb };
}
