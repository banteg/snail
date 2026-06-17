// Root subgame runtime view, partial. This intentionally stays sparse: fields
// are added only when an exact helper or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "track_parcel_runtime.h"

class SubgameRuntime {
public:
    Color4f* get_track_skirt_color(Color4f* out); // @ 0x442120
    TrackParcelRuntime* spawn_track_parcel(
        Vector3* world_position,
        void* owner_hint); // @ 0x443730

    char unknown_000000[0x1b0140];
    float track_skirt_r; // +0x1b0140
    float track_skirt_g; // +0x1b0144
    float track_skirt_b; // +0x1b0148
    char unknown_1b014c[0x3bb764 - 0x1b014c];
    char score_stats; // +0x3bb764, owner anchor used by parcels
    char unknown_3bb765[0x3bbae4 - 0x3bb765];
    int parcel_sprite_owner; // +0x3bbae4
    char unknown_3bbae8[0x125e480 - 0x3bbae8];
    TrackParcelPool parcel_pool; // +0x125e480
};

#endif
