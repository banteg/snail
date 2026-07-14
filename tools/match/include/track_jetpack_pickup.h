// Authored cRJetPack singleton runtime, partial. The parent derives from the
// shared BodBase; its two child Vapours remain embedded below the pickup state.
// Proven by initialize_track_jetpack_pickup_runtime,
// spawn_track_jetpack_pickup, update_track_jetpack_pickup,
// remove_subgame_bods, and handle_subgoldy_collisions.
#ifndef TRACK_JETPACK_PICKUP_H
#define TRACK_JETPACK_PICKUP_H

#include "bod_types.h"
#include "sub_loc_fwd.h"
#include "vapour.h"

class Player;
class Sprite;
class SubgameRuntime;

class JetPack : public BodBase {
public:
    JetPack* initialize_track_jetpack_pickup_runtime(); // @ 0x4084d0
    void update_track_jetpack_pickup(); // @ 0x43efb0

    int state; // +0x38
    Player* owner; // +0x3c
    char unknown_40[0x44 - 0x40];
    SubgameRuntime* owner_game; // +0x44, borrowed containing subgame
    char unknown_48[0x64 - 0x48];
    Sprite* sprite; // +0x64
    TrackRowCell* source_cell; // +0x68
    float bob_phase; // +0x6c
    float bob_phase_step; // +0x70
    Vapour vapour_a; // +0x74, embedded cRVapour
    Vapour vapour_b; // +0x108, embedded cRVapour
};

typedef char JetPack_must_be_0x19c[
    (sizeof(JetPack) == 0x19c) ? 1 : -1];

#endif
