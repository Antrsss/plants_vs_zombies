#ifndef ENTITIES
#define ENTITIES

#include <array>
#include <cstdint>
#include "ncurses.h"

enum EntitiyIndex : int8_t {
    Empty = 0,
    Sunflower = 1,
    NotReadyPeashooter = 2,
    ReadyPeashooter = 3,
    Pea = 4,
    Wallnut = 5,
    DamagedWallnut = 6,
    SmallZombie = 7,
    MediumZombie = 8,
    BigZombie = 9,
    Lawnmower = 10,
    ReadyLawnmowerBase = 11,
    NotReadyLawnmowerBase = 12
};

std::array<const chtype, 13> init_entities();

#endif  // !ENTITIES
