#include "entities.h"
#include <ncurses.h>

void init_entities(chtype* entities) {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    entities[EntitiyIndex::Empty] |= COLOR_PAIR(3);
    entities[EntitiyIndex::Sunflower] |= COLOR_PAIR(1);
    entities[EntitiyIndex::NotReadyPeashooter] |= COLOR_PAIR(2);
    entities[EntitiyIndex::ReadyPeashooter] |= COLOR_PAIR(2);
    entities[EntitiyIndex::Pea] |= COLOR_PAIR(2);
    entities[EntitiyIndex::Wallnut] |= COLOR_PAIR(1);
    entities[EntitiyIndex::DamagedWallnut] |= COLOR_PAIR(1);
    entities[EntitiyIndex::SmallZombie] |= COLOR_PAIR(4);
    entities[EntitiyIndex::MediumZombie] |= COLOR_PAIR(4);
    entities[EntitiyIndex::BigZombie] |= COLOR_PAIR(4);
    entities[EntitiyIndex::Lawnmower] |= COLOR_PAIR(5);
    entities[EntitiyIndex::ReadyLawnmowerBase] |= COLOR_PAIR(5);
    entities[EntitiyIndex::NotReadyLawnmowerBase] |= COLOR_PAIR(5);
}
