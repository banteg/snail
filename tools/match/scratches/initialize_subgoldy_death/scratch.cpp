// initialize_subgoldy_death @ 0x446e30 (thiscall, ret)

#include "player.h"

class Game {
public:
    char unknown_00[0x40];
    int level_mode; // +0x40
};

int Player::initialize_subgoldy_death()
{
    int mode = game->level_mode;

    switch (mode) {
    case 0:
        if (visible_life_stock <= 0)
            return initialize_subgoldy_resurrect(1);
        return initialize_subgoldy_resurrect(0);
    case 1:
    case 4:
        return initialize_subgoldy_resurrect(1);
    case 7:
        return initialize_subgoldy_resurrect(0);
    }

    return mode;
}
