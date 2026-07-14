#ifndef PRESENTATION_ANIMATION_CHANNEL_H
#define PRESENTATION_ANIMATION_CHANNEL_H

#include "anim_manager.h"
#include "bod_types.h"
#include "vector3.h"

struct PresentationAnimationSlot {
    RenderableBod body; // +0x00; body.object owns the animated Object link at +0x24
    char unknown_078[0x80 - 0x78];
};

typedef char PresentationAnimationSlot_must_be_0x80[
    (sizeof(PresentationAnimationSlot) == 0x80) ? 1 : -1];

class PresentationAnimationChannel : public RenderableBod {
public:
    void set_weapon_animation(int animation_id, bool immediate, int initial_frame);

    // build_subgame_level links this inherited renderable BOD. The channel
    // remains embedded in the authored Snail owner; the list only borrows it.
    // Installed only when the linked Object owns generated animation frames.
    // cRGame::Render borrows this manager's progress for Object::animation.
    AnimManager* render_animation_manager; // +0x78, borrowed owned manager at +0x108
    char unknown_07c[0x104 - 0x7c];
    int selected_state; // +0x104
    AnimManager anim_manager; // +0x108
    PresentationAnimationSlot animation_slots[5]; // +0x150, owned renderable slots
    Vector3 release_step; // +0x3d0, additive offset when release flag is active
};

typedef char PresentationAnimationChannel_must_be_0x3dc[
    (sizeof(PresentationAnimationChannel) == 0x3dc) ? 1 : -1];

#endif
