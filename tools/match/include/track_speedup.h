// Authored cRSubSpeedUp singleton runtime, partial. The singleton derives from
// the shared RenderableBod prefix and remains linked through its inherited
// zero-offset BodNode.
// Proven by initialize_track_speedup_runtime, update_track_speedup,
// remove_subgame_bods, and the speedup branch in handle_subgoldy_collisions.
#ifndef TRACK_SPEEDUP_H
#define TRACK_SPEEDUP_H

#include "bod_types.h"

class Player;
class Sprite;
class SubgameRuntime;

class SubSpeedUp : public RenderableBod {
public:
    SubSpeedUp* initialize_track_speedup_runtime(); // @ 0x4084b0
    void update_track_speedup(); // @ 0x43ee50

    char unknown_78[0x80 - 0x78];
    int state; // +0x80
    Player* owner; // +0x84
    char unknown_88[0x8c - 0x88];
    SubgameRuntime* owner_game; // +0x8c, borrowed containing subgame
    char unknown_90[0xac - 0x90];
    Sprite* sprite; // +0xac
    char unknown_b0[0xb4 - 0xb0];
};

typedef SubSpeedUp TrackSpeedupRuntime;

typedef char SubSpeedUp_must_be_0xb4[
    (sizeof(SubSpeedUp) == 0xb4) ? 1 : -1];

#endif
