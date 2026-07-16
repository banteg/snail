// initialize_track_parcel_slots @ 0x443160 (thiscall, ret)

#include "game_root.h"
#include "track_parcel_runtime.h"


void ParcelManager::initialize_track_parcel_slots()
{
    Parcel* slot = slots;
    int count = sizeof(slots) / sizeof(slots[0]);
    do {
        slot->state = PARCEL_STATE_INACTIVE;
        slot->owner_subgame = &g_game->subgame;
        ++slot;
        --count;
    } while (count != 0);
}
