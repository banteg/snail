// initialize_track_parcel_slots @ 0x443160 (thiscall, ret)

#include "track_parcel_runtime.h"

extern char* g_game_base; // data_4df904

void TrackParcelPool::initialize_track_parcel_slots()
{
    TrackParcelRuntime* slot = slots;
    int count = 50;
    do {
        slot->state = 0;
        slot->game = g_game_base + 0x74618;
        ++slot;
        --count;
    } while (count != 0);
}
