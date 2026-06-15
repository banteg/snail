// allocate_track_parcel_slot @ 0x443190 (thiscall, ret)

#include "track_parcel_runtime.h"

int report_errorf(char* format, ...);

TrackParcelRuntime* TrackParcelPool::allocate_track_parcel_slot()
{
    int index = 0;
    int* state = &slots[0].state;

    while (index < 50 && *state != 0) {
        ++index;
        state += 0x23;
        if (index >= 50) {
            report_errorf("Too Many Parcels increase RPARCEL_MAXIMUM");
            return 0;
        }
    }

    return &slots[index];
}
