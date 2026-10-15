// Authored cRSubHover, exact 0x214-byte hover countdown and jet-VFX owner.
#ifndef SUB_HOVER_H
#define SUB_HOVER_H

#include "player_fwd.h"
#include "sprite_fwd.h"

class cRSubGame;
struct tVector;
typedef tVector Vector3;

struct JetParticleSlot {
    cRSprite* sprite; // +0x00
    float wobble_x; // +0x04
    float wobble_y; // +0x08
    float wobble_alpha; // +0x0c
};

typedef char JetParticleSlot_must_be_0x10[
    (sizeof(JetParticleSlot) == 0x10) ? 1 : -1];

enum {
    JET_PARTICLE_ROW_COUNT = 15,
    JET_PARTICLE_COLUMN_COUNT = 2,
    JET_PARTICLE_LAST_ROW_INDEX = JET_PARTICLE_ROW_COUNT - 1,
};

enum SubHoverState {
    SUB_HOVER_STATE_INACTIVE = 0,
    SUB_HOVER_STATE_ACTIVE = 1,
};

class cRSubHover {
public:
    // Authored lifecycle surface retained by both mobile builds.
    void Init(int player_slot); // @ 0x43a930
    void On(); // @ 0x43a980
    void End(); // @ 0x43a370
    void JetUnInit(); // @ 0x43a580
    void JetInit(); // @ 0x43a5b0
    void Jets(); // @ 0x43a690
    void AI(); // @ 0x43a390
    void Hover(Vector3& position, float progress); // folded alias @ 0x43d880

    float progress; // +0x00
    float progress_step; // +0x04
    int unknown_08; // +0x08
    SubHoverState state; // +0x0c
    cRSubGoldy* player; // +0x10, borrowed containing player
    float wobble_x; // +0x14
    float wobble_y; // +0x18
    float wobble_alpha; // +0x1c
    JetParticleSlot
        particle_slots[JET_PARTICLE_ROW_COUNT][JET_PARTICLE_COLUMN_COUNT]; // +0x20
    cRSubGame* game; // +0x200, borrowed owning subgame
    char unknown_204[0x20c - 0x204];
    float warning_intensity_latch; // +0x20c
    float warning_intensity; // +0x210
};

typedef cRSubHover SubHover;
typedef char cRSubHover_must_be_0x214[(sizeof(cRSubHover) == 0x214) ? 1 : -1];
typedef char SubHover_must_be_0x214[(sizeof(SubHover) == 0x214) ? 1 : -1];

#endif
