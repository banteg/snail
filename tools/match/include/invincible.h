// Authored cRInvincible, exact 0x98-byte spinning shell visual owner.
#ifndef INVINCIBLE_H
#define INVINCIBLE_H

#include "bod_types.h"
#include "transform_matrix.h"

enum InvincibleState {
    INVINCIBLE_STATE_INACTIVE = 0,
    INVINCIBLE_STATE_FADING_IN = 1,
    INVINCIBLE_STATE_ACTIVE = 2,
    INVINCIBLE_STATE_FADING_OUT = 3,
};

class Invincible : public RenderableBod {
public:
    void initialize_invincible_shell(); // @ 0x444ac0, cRInvincible::Init
    void start_invincible_shell(); // @ 0x444ae0, cRInvincible::Start
    void update_invincible_shell(); // @ 0x444b50, cRInvincible::AI

    // The complete inherited renderable BOD is linked by build_subgame_level
    // and owns the invincible shell render object. This child remains embedded
    // in the authored Snail owner.
    InvincibleState state; // +0x80
    float spin_phase; // +0x84
    float spin_phase_step; // +0x88
    float fade_progress; // +0x8c
    float fade_step; // +0x90
    // Both mobile ports preserve the same otherwise-unread trailing word.
    // The cRSnail-owned cutscene/release lanes begin after this extent.
    char unknown_94[0x98 - 0x94];
};

typedef char Invincible_must_be_0x98[(sizeof(Invincible) == 0x98) ? 1 : -1];

#endif
