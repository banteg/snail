// Authored cRSubHealth runtime slot, partial. Each pickup derives from the
// shared BodBase initialized by its exact constructor; its live world position
// is the inherited BodBase::position.
// Proven by initialize_track_health_pickup_runtime, spawn_track_health_pickup,
// update_track_health_pickup, health_collect_particles, and the health loop in
// handle_subgoldy_collisions.
#ifndef TRACK_HEALTH_PICKUP_H
#define TRACK_HEALTH_PICKUP_H

#include "bod_types.h"
#include "sub_loc_fwd.h"

class Player;
class Sprite;
class SubgameRuntime;

class SubHealth : public BodBase {
public:
    SubHealth* initialize_track_health_pickup_runtime(); // @ 0x408510
    void update_track_health_pickup(); // @ 0x43ecc0

    int state; // +0x38
    Player* owner; // +0x3c
    char unknown_40[0x44 - 0x40];
    // Pause gate view initialized from SubgameRuntime during reset_subgame. This is
    // distinct from source_cell at +0x68, which spawn_track_health_pickup stores.
    SubgameRuntime* owner_game; // +0x44, borrowed containing subgame
    char unknown_48[0x64 - 0x48];
    Sprite* sprite; // +0x64
    TrackRowCell* source_cell; // +0x68
    float bob_phase; // +0x6c
    float bob_phase_step; // +0x70
};

typedef SubHealth TrackHealthPickup;

typedef char SubHealth_must_be_0x74[(sizeof(SubHealth) == 0x74) ? 1 : -1];

#endif
