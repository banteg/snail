// Authored cRAnimManager, exact 0x48-byte queued presentation-animation owner.
// Cross-checked by the Windows Init/AI pair and Android's identical field map.
#ifndef ANIM_MANAGER_H
#define ANIM_MANAGER_H

#include "object_animation_types.h"

class RenderableBod;
struct PresentationAnimationSlot;

enum {
    ANIM_MANAGER_QUEUE_CAPACITY = 10,
    ANIM_MANAGER_HIDE_ANIMATION_ID = -1,
};

class AnimManager {
public:
    void initialize_anim_manager(); // @ 0x4447c0, cRAnimManager::Init
    void update_anim_manager();     // @ 0x4447d0, cRAnimManager::AI

    int state;              // +0x00
    float progress;         // +0x04
    float progress_step;    // +0x08
    ObjectAnimation* active_animation; // +0x0c
    bool completed;          // +0x10
    char unknown_11[0x14 - 0x11];
    int queued_animations[ANIM_MANAGER_QUEUE_CAPACITY]; // +0x14
    int queue_count;       // +0x3c
    RenderableBod* target_model; // +0x40, borrowed Snail/channel renderable owner
    PresentationAnimationSlot* animation_slots; // +0x44, borrowed inline slot bank
};

typedef char AnimManager_must_be_0x48[
    (sizeof(AnimManager) == 0x48) ? 1 : -1];

#endif
