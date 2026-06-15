// update_track_parcels @ 0x443130 (thiscall, ret)

#include "track_parcel_runtime.h"

int TrackParcelPool::update_track_parcels()
{
    TrackParcelRuntime* slot = slots;
    int result;
    int count = 50;
    do {
        result = slot->state;
        if (result != 0) {
            result = slot->update_track_parcel();
        }
        ++slot;
        --count;
    } while (count != 0);
    return result;
}
