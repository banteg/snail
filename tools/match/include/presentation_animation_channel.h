#ifndef PRESENTATION_ANIMATION_CHANNEL_H
#define PRESENTATION_ANIMATION_CHANNEL_H

#include "anim_manager.h"

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

    char unknown_000[0x24];
    PresentationAnimationVisualRoot* visual_root; // +0x24
    char unknown_028[0x104 - 0x28];
    int selected_state; // +0x104
    AnimManager anim_manager; // +0x108
    char unknown_150[0x174 - 0x150];
    char animation_slot_table[0x25c]; // +0x174, 0x80-byte records
    char unknown_3d0[0x3dc - 0x3d0];
};

typedef char PresentationAnimationChannel_must_be_0x3dc[
    (sizeof(PresentationAnimationChannel) == 0x3dc) ? 1 : -1];

#endif
