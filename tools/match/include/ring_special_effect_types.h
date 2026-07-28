// Authored cRSubRing/cRSubRingStar runtime views, partial.
#ifndef RING_SPECIAL_EFFECT_TYPES_H
#define RING_SPECIAL_EFFECT_TYPES_H

#include "bod_types.h"
#include "player_fwd.h"

class Sprite;
class cRSubGame;
class SubRing;
typedef SubRing RingOrSpecialEffectParent;

enum SubRingState {
    SUB_RING_STATE_INACTIVE = 0,
    SUB_RING_STATE_ACTIVE = 1,
    SUB_RING_STATE_COLLECT_PENDING = 2,
    SUB_RING_STATE_COLLECTING = 3,
    SUB_RING_STATE_EXPAND_PENDING = 4,
    SUB_RING_STATE_EXPANDING = 5,
};

enum SubRingKind {
    // No live Windows producer has been recovered for kinds 0 or 1 yet.
    SUB_RING_KIND_UNKNOWN_0 = 0,
    SUB_RING_KIND_UNKNOWN_1 = 1,
    SUB_RING_KIND_EXPLODE_RAMP = 2,
    SUB_RING_KIND_SLOW_DEFAULT = 3,
    SUB_RING_KIND_NORMAL_DEFAULT = 4,
    SUB_RING_KIND_NORMAL_AUTHORED = 5,
    SUB_RING_KIND_EXPLODE_AUTHORED = 6,
    SUB_RING_KIND_SLOW_AUTHORED = 7,
    SUB_RING_KIND_POWER_UP_AUTHORED = 8,
};

enum {
    SUB_RING_PARTICLE_COUNT = 10,
    SUB_RING_POOL_CAPACITY = 2,
};

class SubRingStar {
public:
    void update_ring_or_special_effect_particle(); // @ 0x43e780
    void emit_ring_star_shower(cRSubGoldy* owner); // @ 0x43e690

    // SpriteManager allocation handle; removal returns it through kill_sprite().
    Sprite* sprite; // +0x00, not inline storage owned by the particle
    SubRing* parent; // +0x04, non-owning backlink to embedded parent
    Vector3 base_position; // +0x08
    float phase; // +0x14
    float phase_step; // +0x18
    float radius; // +0x1c
};

typedef SubRingStar RingOrSpecialEffectParticle;

typedef char SubRingStar_must_be_0x20[(sizeof(SubRingStar) == 0x20) ? 1 : -1];

class SubRing : public RenderableBod {
public:
    SubRing* initialize_track_ring_or_special_effect_runtime(); // @ 0x408570
    void initialize_ring_or_special_effect_particles(int unused_lives_snapshot); // @ 0x43e470
    void update_ring_or_special_effect_parent(); // @ 0x43e830

    SubRingState state; // +0x80
    cRSubGoldy* owner_player; // +0x84, borrowed cRSubGoldy used for slot/lives state
    SubRingKind kind; // +0x88
    int owner_lives_snapshot; // +0x8c
    // Fixed child storage owned by this parent. Each child's sprite is a
    // separate SpriteManager allocation released on every parent-removal path.
    SubRingStar particles[SUB_RING_PARTICLE_COUNT]; // +0x90
    cRSubGame* rate_source; // +0x1d0, borrowed enclosing cRSubGame
    float transition_progress; // +0x1d4
    float transition_step; // +0x1d8
    unsigned char oscillate_x; // +0x1dc
    // +0x1dd..+0x1df is the compiler's natural float-alignment padding.
    float active_phase; // +0x1e0
    float active_phase_step; // +0x1e4
    int star_shower_counter; // +0x1e8
    int star_sprite_id; // +0x1ec
    char unknown_1f0[0x1f8 - 0x1f0];
};

typedef char SubRing_must_be_0x1f8[(sizeof(SubRing) == 0x1f8) ? 1 : -1];

typedef BodList SubRingListAnchor;
typedef SubRingListAnchor RingOrSpecialEffectListAnchor;

class SubRingPool {
public:
    // Fixed storage owned by cRSubGame; active-list linkage never owns it.
    SubRing slots[SUB_RING_POOL_CAPACITY]; // game +0x35b78c
};

typedef SubRingPool RingOrSpecialEffectPool;

typedef char SubRingPool_must_be_0x3f0[
    (sizeof(SubRingPool) == 0x3f0) ? 1 : -1];

#endif
