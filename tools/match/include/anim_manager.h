// Authored cRAnimManager, exact 0x48-byte queued presentation-animation owner.
// Cross-checked by the Windows Init/AI pair and Android's identical field map.
#ifndef ANIM_MANAGER_H
#define ANIM_MANAGER_H

struct ObjectAnimation;

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
    int queued_animations[10]; // +0x14
    int queue_count;       // +0x3c
    void* target_model;    // +0x40
    // Biased base immediately after this owner; the first 0x80-byte animation
    // slot begins at +0x24 from this pointer.
    char* animation_slot_base_minus_24; // +0x44
};

typedef char AnimManager_must_be_0x48[
    (sizeof(AnimManager) == 0x48) ? 1 : -1];

#endif
