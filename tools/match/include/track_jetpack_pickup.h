// Track jetpack pickup singleton runtime, partial. iOS symbols name this
// runtime class cRJetPack and the spawning helper cRSubGame::AddJetPack.
// Proven by initialize_track_jetpack_pickup_runtime,
// spawn_track_jetpack_pickup, update_track_jetpack_pickup,
// remove_subgame_bods, and handle_subgoldy_collisions.
#ifndef TRACK_JETPACK_PICKUP_H
#define TRACK_JETPACK_PICKUP_H

#include "bod_list.h"
#include "bod_types.h"
#include "sub_loc_fwd.h"
#include "vector3.h"

class Player;
class Sprite;
class SubgameRuntime;

class TrackJetpackPickup : public BodNode {
public:
    TrackJetpackPickup* initialize_track_jetpack_pickup_runtime(); // @ 0x4084d0
    void update_track_jetpack_pickup(); // @ 0x43efb0

    Vector3 world_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    int state; // +0x38
    Player* owner; // +0x3c
    char unknown_40[0x44 - 0x40];
    SubgameRuntime* owner_game; // +0x44, borrowed containing subgame
    char unknown_48[0x64 - 0x48];
    Sprite* sprite; // +0x64
    TrackRowCell* source_cell; // +0x68
    float bob_phase; // +0x6c
    float bob_phase_step; // +0x70
    RenderableBod body_a; // +0x74
    char unknown_ec[0x108 - 0xec];
    RenderableBod body_b; // +0x108
    char unknown_180[0x19c - 0x180];
};

typedef char TrackJetpackPickup_must_be_0x19c[
    (sizeof(TrackJetpackPickup) == 0x19c) ? 1 : -1];

#endif
