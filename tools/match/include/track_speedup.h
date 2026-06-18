// Track speedup singleton runtime, partial.
// Proven by initialize_track_speedup_runtime, update_track_speedup,
// remove_subgame_bods, and the speedup branch in handle_subgoldy_collisions.
#ifndef TRACK_SPEEDUP_H
#define TRACK_SPEEDUP_H

#include "bod_list.h"
#include "bod_types.h"
#include "track_pickup_owner_game_view.h"
#include "vector3.h"

class Player;
class Sprite;

class TrackSpeedupRuntime : public BodNode {
public:
    TrackSpeedupRuntime* initialize_track_speedup_runtime(); // @ 0x4084b0
    void update_track_speedup(); // @ 0x43ee50

    Vector3 bod_position; // +0x10, BodBase::position
    int render_arg_1c; // +0x1c, BodBase render argument
    float render_arg_20; // +0x20, BodBase render argument
    void* object; // +0x24
    Color4f color; // +0x28
    // RenderableBod transform rows. Kept field-by-field because the singleton
    // also uses the zero-offset BodNode list overlay.
    Vector3 basis_right; // +0x38
    float basis_right_w; // +0x44
    Vector3 basis_up; // +0x48
    float basis_up_w; // +0x54
    Vector3 basis_forward; // +0x58
    float basis_forward_w; // +0x64
    Vector3 world_position; // +0x68, RenderableBod::transform.position
    float world_position_w; // +0x74
    char unknown_78[0x80 - 0x78];
    int state; // +0x80
    Player* owner; // +0x84
    char unknown_88[0x8c - 0x88];
    TrackPickupOwnerGameView* owner_game; // +0x8c
    char unknown_90[0xac - 0x90];
    Sprite* sprite; // +0xac
    char unknown_b0[0xb4 - 0xb0];
};

typedef char TrackSpeedupRuntime_must_be_0xb4[
    (sizeof(TrackSpeedupRuntime) == 0xb4) ? 1 : -1];

#endif
