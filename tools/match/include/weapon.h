#ifndef WEAPON_H
#define WEAPON_H

#include "anim_manager.h"
#include "bod_types.h"
#include "vector3.h"

struct PresentationAnimationSlot {
    RenderableBod body; // +0x00; body.object owns the animated Object link at +0x24
};

typedef char PresentationAnimationSlot_must_be_0x80[
    (sizeof(PresentationAnimationSlot) == 0x80) ? 1 : -1];

// Authored cRWeapon. Snail owns three weapon instances and one additional
// instance for the jetpack presentation channel.
class Weapon : public RenderableBod {
public:
    void set_weapon_animation(int animation_id, bool immediate, int mode_flags);

    // build_subgame_level links this inherited renderable BOD. The Weapon
    // remains embedded in the authored Snail owner; the list only borrows it.
    // The inherited +0x78 lane borrows the owned manager at +0x108 when this
    // linked body has the 0x800 animation-progress flag.
    // Exact construction calls the shared no-op slot constructor at +0x80 and
    // +0xc0 for the jetpack Weapon, and at +0xc0 for weapon channels. No
    // consumer yet proves the concrete types of those Weapon-owned lanes.
    char unknown_080[0x104 - 0x80];
    int selected_state; // +0x104
    AnimManager anim_manager; // +0x108
    PresentationAnimationSlot animation_slots[5]; // +0x150, owned renderable slots
    Vector3 release_step; // +0x3d0, additive offset when release flag is active
};

typedef char Weapon_must_be_0x3dc[(sizeof(Weapon) == 0x3dc) ? 1 : -1];

#endif
