// Authored cRSubSpeedUp singleton runtime, partial. The singleton derives from
// the shared RenderableBod prefix and remains linked through its inherited
// zero-offset BodNode.
// Proven by initialize_track_speedup_runtime, update_track_speedup,
// remove_subgame_bods, and the speedup branch in handle_subgoldy_collisions.
#ifndef TRACK_SPEEDUP_H
#define TRACK_SPEEDUP_H

#include "bod_types.h"
#include "player_fwd.h"
#include "sprite_fwd.h"
#include "track_pickup_state.h"

class cRSubGame;

class cRSubSpeedUp : public RenderableBod {
public:
    cRSubSpeedUp(); // @ 0x4084b0
    void AI(); // @ 0x43ee50

    TrackPickupState state; // +0x80
    cRSubGoldy* owner; // +0x84
    char unknown_88[0x8c - 0x88];
    cRSubGame* owner_game; // +0x8c, borrowed containing subgame
    char unknown_90[0xac - 0x90];
    cRSprite* sprite; // +0xac
    char unknown_b0[0xb4 - 0xb0];
};

typedef cRSubSpeedUp SubSpeedUp;
typedef cRSubSpeedUp TrackSpeedupRuntime;

typedef char cRSubSpeedUp_must_be_0xb4[
    (sizeof(cRSubSpeedUp) == 0xb4) ? 1 : -1];
typedef char SubSpeedUp_must_be_0xb4[
    (sizeof(SubSpeedUp) == 0xb4) ? 1 : -1];

#endif
