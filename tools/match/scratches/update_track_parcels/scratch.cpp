// update_track_parcels @ 0x443130 (thiscall, ret)

#include "track_parcel_runtime.h"

class TrackParcelVirtualUpdater {
public:
    virtual void update_track_parcel();
};

void TrackParcelPool::update_track_parcels()
{
    TrackParcelRuntime* slot = slots;
    int count = 50;
    do {
        if (slot->state != 0) {
            ((TrackParcelVirtualUpdater*)slot)->update_track_parcel();
        }
        ++slot;
        --count;
    } while (count != 0);
}
