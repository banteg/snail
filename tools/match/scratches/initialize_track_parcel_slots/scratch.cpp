// initialize_track_parcel_slots @ 0x443160 (thiscall, ret)

#include "game_root.h"
#include "track_parcel_runtime.h"

extern GameRoot* g_game; // data_4df904

void ParcelManager::initialize_track_parcel_slots()
{
    Parcel* slot = slots;
    int count = 50;
    do {
        slot->state = 0;
        slot->owner_subgame = &g_game->subgame;
        ++slot;
        --count;
    } while (count != 0);
}
