// Authored cRParcel/cRParcelManager views, cross-checked by pool management,
// spawn_track_parcel, update_track_parcels, update_row_event_display, and
// handle_subgoldy_collisions.
#ifndef TRACK_PARCEL_RUNTIME_H
#define TRACK_PARCEL_RUNTIME_H

#include "bod_types.h"

class Player;
class SubgameRuntime;

enum ParcelState {
    PARCEL_STATE_INACTIVE = 0,
    PARCEL_STATE_TRACK_ACTIVE = 1,
    // The updater preserves values 2 and 3, but no live Windows writer is known.
    PARCEL_STATE_UNKNOWN_2 = 2,
    PARCEL_STATE_UNKNOWN_3 = 3,
    PARCEL_STATE_COLLECT_PENDING = 4,
    PARCEL_STATE_COLLECTING = 5,
    PARCEL_STATE_DELIVERY_PENDING = 6,
    PARCEL_STATE_DELIVERING = 7,
};

class Parcel : public BodBase {
public:
    Parcel* initialize_track_parcel_runtime(); // @ 0x408860
    void update_track_parcel();

    ParcelState state; // +0x38
    SubgameRuntime* owner_subgame; // +0x3c, borrowed backlink
    char unknown_40[0x54 - 0x40];
    Sprite* sprite; // +0x54, borrowed SpriteManager handle
    char unknown_58[0x5c - 0x58];
    float bob_phase; // +0x5c
    float bob_phase_step; // +0x60
    Player* owner_player; // +0x64, borrowed embedded Player
    float progress; // +0x68
    float progress_step; // +0x6c
    float target_distance; // +0x70
    Vector3 travel_dir; // +0x74
    Vector3 delivery_offset; // +0x80
};

typedef char Parcel_must_be_0x8c[(sizeof(Parcel) == 0x8c) ? 1 : -1];

struct ParcelManager {
    Parcel* allocate_track_parcel_slot();
    void initialize_track_parcel_slots();
    void update_track_parcels();

    Parcel slots[50]; // fixed storage owned by SubgameRuntime
};

typedef char ParcelManager_must_be_0x1b58[
    (sizeof(ParcelManager) == 0x1b58) ? 1 : -1];

#endif
