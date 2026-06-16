// Track speedup singleton runtime, partial.
// Proven by initialize_track_speedup_runtime, update_track_speedup,
// remove_subgame_bods, and the speedup branch in handle_subgoldy_collisions.
#ifndef TRACK_SPEEDUP_H
#define TRACK_SPEEDUP_H

#include "bod_list.h"
#include "bod_types.h"
#include "vector3.h"

class Player;
class Sprite;

struct TrackSpeedupGameView {
    char unknown_00[0x09];
    unsigned char paused; // +0x09
};

class TrackSpeedupRuntime : public BodNode {
public:
    TrackSpeedupRuntime* initialize_track_speedup_runtime(); // @ 0x4084b0
    void update_track_speedup(); // @ 0x43ee50

    char unknown_10[0x68 - 0x10];
    Vector3 world_position; // +0x68, collision uses x/y/z; updater culls on z
    char unknown_74[0x80 - 0x74];
    int state; // +0x80
    Player* owner; // +0x84
    char unknown_88[0x8c - 0x88];
    TrackSpeedupGameView* owner_game; // +0x8c
    char unknown_90[0xac - 0x90];
    Sprite* sprite; // +0xac
    char unknown_b0[0xb4 - 0xb0];
};

typedef char TrackSpeedupRuntime_must_be_0xb4[
    (sizeof(TrackSpeedupRuntime) == 0xb4) ? 1 : -1];

#endif
