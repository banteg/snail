// Authored cRParcel/cRParcelManager views, cross-checked by pool management,
// spawn_track_parcel, update_track_parcels, update_row_event_display, and
// handle_subgoldy_collisions.
#ifndef TRACK_PARCEL_RUNTIME_H
#define TRACK_PARCEL_RUNTIME_H

#include "bod_types.h"
#include "player_fwd.h"
#include "sprite_fwd.h"

class cRSubGame;

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

class cRParcel : public BodBase {
public:
    cRParcel(); // @ 0x408860
    void AI(); // @ 0x4431d0

    ParcelState state; // +0x38
    cRSubGame* owner_subgame; // +0x3c, borrowed backlink
    char unknown_40[0x54 - 0x40];
    cRSprite* sprite; // +0x54, borrowed cRSpriteManager handle
    char unknown_58[0x5c - 0x58];
    float bob_phase; // +0x5c
    float bob_phase_step; // +0x60
    cRSubGoldy* owner_player; // +0x64, borrowed embedded cRSubGoldy
    float progress; // +0x68
    float progress_step; // +0x6c
    float target_distance; // +0x70
    Vector3 travel_dir; // +0x74
    Vector3 delivery_offset; // +0x80
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRParcel Parcel;

typedef char cRParcel_must_be_0x8c[(sizeof(cRParcel) == 0x8c) ? 1 : -1];
typedef char Parcel_must_be_0x8c[(sizeof(Parcel) == 0x8c) ? 1 : -1];

class cRParcelManager {
public:
    cRParcel* New(); // @ 0x443190
    void Init(); // @ 0x443160
    void AI(); // @ 0x443130

    cRParcel slots[50]; // fixed storage owned by cRSubGame
};

typedef cRParcelManager ParcelManager;

typedef char cRParcelManager_must_be_0x1b58[
    (sizeof(cRParcelManager) == 0x1b58) ? 1 : -1];
typedef char ParcelManager_must_be_0x1b58[
    (sizeof(ParcelManager) == 0x1b58) ? 1 : -1];

#endif
