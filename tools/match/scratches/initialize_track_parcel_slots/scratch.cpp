// initialize_track_parcel_slots @ 0x443160 (thiscall, ret)

extern char* g_game_base; // data_4df904

struct TrackParcelSlot {
    char unknown_00[0x38];
    int state;                 // +0x38
    char* game;                // +0x3c
    char unknown_40[0x8c - 0x40];
};

class TrackParcelSlots {
public:
    void initialize_track_parcel_slots();

    TrackParcelSlot slots[50];
};

void TrackParcelSlots::initialize_track_parcel_slots()
{
    TrackParcelSlot* slot = slots;
    int count = 50;
    do {
        slot->state = 0;
        slot->game = g_game_base + 0x74618;
        ++slot;
        --count;
    } while (count != 0);
}
