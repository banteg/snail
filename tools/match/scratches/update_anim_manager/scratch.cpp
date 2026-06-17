// update_anim_manager @ 0x4447d0 (thiscall, ret)

#include "anim_manager.h"

extern char* g_game_base; // data_4df904

struct AnimationRecord {
    char unknown_00[0x24];
    void* model_animation; // +0x24
    char unknown_28[0x80 - 0x28];
};

struct ModelInstance {
    unsigned int flags; // +0x00
    char unknown_04[0x24 - 0x04];
    void* active_animation; // +0x24
};

void AnimManager::update_anim_manager()
{
    completed = 0;
    if (state == 0)
        return;

    if (state == 1) {
        float delta = (*(float*)(g_game_base + 0x74648) * 2.0f - 0.200000003f + 1.0f)
            * progress_step;
        float next_progress = progress + delta;
        progress = next_progress;

        if (next_progress >= 1.0f) {
            unsigned short frame_flags = active_animation->flags;
            if ((frame_flags & 1) != 0) {
                completed = 1;
                progress = next_progress - 1.0f;
            }
            if ((frame_flags & 4) != 0) {
                progress = 0.999000013f;
                progress_step = 0.0f;
                completed = 1;
            }
            if ((frame_flags & 2) != 0) {
                progress = 2.0f - next_progress;
                progress_step *= -1.0f;
            }
        }

        if (progress < 0.0f) {
            unsigned short frame_flags = active_animation->flags;
            if ((frame_flags & 2) != 0) {
                progress = -progress;
                completed = 1;
                progress_step *= -1.0f;
            }
            if ((frame_flags & 8) != 0) {
                progress = 0.0f;
                progress_step = 0.0f;
                completed = 1;
            }
        }

        if (progress < 0.0f)
            progress = 0.0f;
        else if (progress > 0.999899983f)
            progress = 0.999899983f;
    }

    if (completed != 0 && queue_count > 0) {
        int next_animation = queued_animations[0];
        if (next_animation == -1) {
            progress = 0.0f;
            progress_step = 0.0f;
            ((ModelInstance*)target_model)->flags &= ~0x20u;
        } else {
            ((ModelInstance*)target_model)->flags |= 0x20u;
            AnimationRecord* record =
                (AnimationRecord*)(animation_table + next_animation * sizeof(AnimationRecord));
            progress = 0.0f;
            active_animation = (ObjectAnimation*)record->model_animation;
            progress_step = active_animation->progress_step;
            ((ModelInstance*)target_model)->active_animation = record->model_animation;
        }

        int new_count = queue_count - 1;
        queue_count = new_count;
        for (int i = 0; i < new_count; i++)
            queued_animations[i] = queued_animations[i + 1];
    }
}
