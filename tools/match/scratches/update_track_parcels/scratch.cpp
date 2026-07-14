// update_track_parcels @ 0x443130 (thiscall, ret)

#include "bod_ai_dispatch.h"
#include "track_parcel_runtime.h"

void ParcelManager::update_track_parcels()
{
    Parcel* slot = slots;
    int count = sizeof(slots) / sizeof(slots[0]);
    do {
        if (slot->state != PARCEL_STATE_INACTIVE) {
            ((BodAiDispatch*)slot)->update_bod_ai();
        }
        ++slot;
        --count;
    } while (count != 0);
}
