// allocate_track_parcel_slot @ 0x443190 (thiscall, ret)

#include "track_parcel_runtime.h"

int report_errorf(char* format, ...);

Parcel* ParcelManager::allocate_track_parcel_slot()
{
    int index = 0;
    Parcel* scan = slots;

    while (index < 50 && scan->state != 0) {
        ++index;
        ++scan;
        if (index >= 50) {
            report_errorf("Too Many Parcels increase RPARCEL_MAXIMUM");
            return 0;
        }
    }

    return &slots[index];
}
