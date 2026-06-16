// Presentation animation manager view, partial.
// Cross-checked by initialize_anim_manager and update_anim_manager.
#ifndef ANIM_MANAGER_H
#define ANIM_MANAGER_H

class AnimManager {
public:
    int initialize_anim_manager(); // @ 0x4447c0
    void update_anim_manager();    // @ 0x4447d0

    int state;              // +0x00
    float progress;         // +0x04
    float progress_step;    // +0x08
    unsigned int* flags;    // +0x0c, current animation flags
    unsigned char completed; // +0x10
    char unknown_11[0x14 - 0x11];
    int queued_animations[10]; // +0x14
    int queue_count;       // +0x3c
    void* target_model;    // +0x40
    char* animation_table; // +0x44, 0x80-byte animation records
};

typedef char AnimManager_must_be_0x48[
    (sizeof(AnimManager) == 0x48) ? 1 : -1];

#endif
