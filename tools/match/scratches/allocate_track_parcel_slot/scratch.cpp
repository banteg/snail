// allocate_track_parcel_slot @ 0x443190 (thiscall, ret)

int report_errorf(char* format, ...);

struct TrackParcelSlot {
    char unknown_00[0x38];
    int state;                 // +0x38
    char unknown_3c[0x8c - 0x3c];
};

class TrackParcelSlots {
public:
    TrackParcelSlot* allocate_track_parcel_slot();

    TrackParcelSlot slots[50];
};

TrackParcelSlot* TrackParcelSlots::allocate_track_parcel_slot()
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
