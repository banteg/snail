#ifndef PRESENTATION_ANIMATION_CHANNEL_H
#define PRESENTATION_ANIMATION_CHANNEL_H

#include "anim_manager.h"
#include "transform_matrix.h"
#include "vector3.h"

struct PresentationAnimationVisualRoot {
    char unknown_000[0xbc];
    ObjectAnimation* active_animation; // +0xbc
};

struct PresentationAnimationSlot {
    PresentationAnimationVisualRoot* visual_root; // +0x00
    char unknown_004[0x80 - 0x04];
};

class PresentationAnimationChannel {
public:
    int set_weapon_animation(int animation_id, unsigned char immediate, int initial_frame);

    // BOD-node-compatible prefix linked by build_subgame_level. The channel
    // remains embedded in PlayerPresentationController.
    void* vtable; // +0x00, shared no-op animation-channel callback
    char unknown_004[0x24 - 0x04];
    PresentationAnimationVisualRoot* visual_root; // +0x24
    char unknown_028[0x38 - 0x28];
    TransformMatrix live_matrix; // +0x38
    char unknown_078[0x104 - 0x78];
    int selected_state; // +0x104
    AnimManager anim_manager; // +0x108
    char unknown_150[0x174 - 0x150];
    char animation_slot_table[0x25c]; // +0x174, 0x80-byte records
    Vector3 release_step; // +0x3d0, additive offset when release flag is active
};

typedef char PresentationAnimationChannel_must_be_0x3dc[
    (sizeof(PresentationAnimationChannel) == 0x3dc) ? 1 : -1];

#endif
