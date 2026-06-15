// Shared parcel runtime view, cross-checked by parcel pool management,
// spawn_track_parcel, and update_row_event_display.
#ifndef TRACK_PARCEL_RUNTIME_H
#define TRACK_PARCEL_RUNTIME_H

#include "sprite.h"

struct TrackParcelRuntime {
    virtual int update_track_parcel();

    char unknown_04[0x10 - 0x04];
    Vector3 world_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    int state; // +0x38
    void* game; // +0x3c, initialized to root game +0x74618
    char unknown_40[0x54 - 0x40];
    Sprite* sprite; // +0x54
    char unknown_58[0x5c - 0x58];
    float bob_phase; // +0x5c
    float bob_phase_step; // +0x60
    void* owner; // +0x64
    char unknown_68[0x8c - 0x68];
};

struct TrackParcelPool {
    TrackParcelRuntime* allocate_track_parcel_slot();
    void initialize_track_parcel_slots();
    int update_track_parcels();

    TrackParcelRuntime slots[50];
};

#endif
