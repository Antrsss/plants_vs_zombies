#ifndef ENTITIES
#define ENTITIES

#include <cstdint>
#include "ncurses.h"

enum EntitiyIndex : int8_t {
    Empty = 0,
    Sunflower = 1,
    Peashooter = 2,
    Pea = 3,
    Wallnut = 4,
    SmallZombie = 5,
    MediumZombie = 6,
    BigZombie = 7,
    Lawnmower = 8,
};

void init_entities(chtype*);

#endif  // !ENTITIES
