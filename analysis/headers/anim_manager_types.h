#ifndef ANIM_MANAGER_TYPES_H
#define ANIM_MANAGER_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRAnimManager. The exact Init/AI pair covers every field through +0x44;
 * Android independently preserves the complete owner and iOS preserves both
 * authored class-qualified methods.
 */

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct ObjectAnimation ObjectAnimation;
typedef struct PresentationAnimationSlot PresentationAnimationSlot;
typedef struct RenderableBod RenderableBod;

typedef struct cRAnimManager {
    int32_t state;
    float progress;
    float progress_step;
    ObjectAnimation* active_animation;
    uint8_t completed;
    uint8_t _pad_11[0x3];
    int32_t queued_animations[10];
    int32_t queue_count;
    RenderableBod* target_model;
    PresentationAnimationSlot* animation_slots;
} cRAnimManager;

typedef char cRAnimManager_must_be_0x48[
    (sizeof(cRAnimManager) == 0x48) ? 1 : -1];

#endif
