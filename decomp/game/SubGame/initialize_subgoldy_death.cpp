// initialize_subgoldy_death @ 0x446e30 (thiscall, ret)

#include "player.h"
#include "subgame_runtime.h"

void cRSubGoldy::DeathInit()
{
    int mode = ((cRSubGame*)game)->level_mode;

    switch (mode) {
    case 0:
        if (visible_life_stock <= 0) {
            RessurectInit(1);
            return;
        }
        RessurectInit(0);
        return;
    case 1:
    case 4:
        RessurectInit(1);
        return;
    case 7:
        RessurectInit(0);
        return;
    }
}
