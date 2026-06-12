// update_track_parcels @ 0x443130 (thiscall, ret)

class TrackParcelSlot {
public:
    virtual int update_track_parcel();
    int update_track_parcels();

    char unknown_04[0x38 - 0x04];
    int state;                 // +0x38
    char unknown_3c[0x8c - 0x3c];
};

int TrackParcelSlot::update_track_parcels()
{
    TrackParcelSlot* slot = this;
    int result;
    int count = 50;
    do {
        result = slot->state;
        if (result != 0) {
            result = slot->update_track_parcel();
        }
        slot = (TrackParcelSlot*)((char*)slot + 0x8c);
        --count;
    } while (count != 0);
    return result;
}
