// Ring/special-effect runtime views, partial.
#ifndef RING_SPECIAL_EFFECT_TYPES_H
#define RING_SPECIAL_EFFECT_TYPES_H

#include "bod_list.h"
#include "vector3.h"

class Player;
class Sprite;
class RingOrSpecialEffectParent;

class RingOrSpecialEffectParticle {
public:
    void update_ring_or_special_effect_particle(); // @ 0x43e780
    void emit_ring_star_shower(Player* owner); // @ 0x43e690

    Sprite* sprite; // +0x00
    RingOrSpecialEffectParent* parent; // +0x04
    Vector3 base_position; // +0x08
    float phase; // +0x14
    float phase_step; // +0x18
    float radius; // +0x1c
};

class RingEffectRateSource {
public:
    char unknown_00[0x09];
    unsigned char paused; // +0x09
    char unknown_0a[0x38 - 0x0a];
    float subgame_rate; // +0x38
};

// The first 0x10 bytes are the common intrusive BOD list prefix.
class RingOrSpecialEffectParent : public BodNode {
public:
    RingOrSpecialEffectParent* initialize_track_ring_or_special_effect_runtime(); // @ 0x408570
    int initialize_ring_or_special_effect_particles(int unused_lives_snapshot); // @ 0x43e470
    void update_ring_or_special_effect_parent(); // @ 0x43e830

    char unknown_010[0x38 - 0x10];
    // RenderableBod transform rows. Kept field-by-field because VC6 rejects a
    // union containing TransformMatrix's constructors.
    Vector3 basis_right; // +0x38
    float basis_right_w; // +0x44
    Vector3 basis_up; // +0x48
    float basis_up_w; // +0x54
    Vector3 basis_forward; // +0x58
    float basis_forward_w; // +0x64
    Vector3 position; // +0x68, RenderableBod::transform.position
    float position_w; // +0x74
    char unknown_078[0x80 - 0x78];
    int state; // +0x80, 0 inactive; 1 normal; 2..5 transitions
    Player* owner_player; // +0x84
    int kind; // +0x88
    int owner_lives_snapshot; // +0x8c
    RingOrSpecialEffectParticle particles[10]; // +0x90
    RingEffectRateSource* rate_source; // +0x1d0
    float transition_progress; // +0x1d4
    float transition_step; // +0x1d8
    unsigned char oscillate_x; // +0x1dc
    char unknown_1dd[0x1e0 - 0x1dd];
    float active_phase; // +0x1e0
    float active_phase_step; // +0x1e4
    int star_shower_counter; // +0x1e8
    int star_sprite_id; // +0x1ec
    char unknown_1f0[0x1f8 - 0x1f0];
};

typedef char RingOrSpecialEffectParent_must_match_pool_stride[
    (sizeof(RingOrSpecialEffectParent) == 0x1f8) ? 1 : -1];

typedef BodList RingOrSpecialEffectListAnchor;

#endif
