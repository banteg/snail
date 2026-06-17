// Shared parcel runtime view, cross-checked by parcel pool management,
// spawn_track_parcel, update_track_parcels, update_row_event_display, and
// handle_subgoldy_collisions.
#ifndef TRACK_PARCEL_RUNTIME_H
#define TRACK_PARCEL_RUNTIME_H

#include "sprite.h"

struct TrackParcelRuntime {
    virtual void update_track_parcel();

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
    float progress; // +0x68
    float progress_step; // +0x6c
    float target_distance; // +0x70
    Vector3 travel_dir; // +0x74
    Vector3 delivery_offset; // +0x80
};

typedef char TrackParcelRuntime_must_be_0x8c[
    (sizeof(TrackParcelRuntime) == 0x8c) ? 1 : -1];

struct TrackParcelPool {
    TrackParcelRuntime* allocate_track_parcel_slot();
    void initialize_track_parcel_slots();
    void update_track_parcels();

    TrackParcelRuntime slots[50];
};

typedef char TrackParcelPool_must_be_0x1b58[
    (sizeof(TrackParcelPool) == 0x1b58) ? 1 : -1];

#endif
