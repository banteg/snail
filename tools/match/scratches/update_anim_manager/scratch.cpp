// update_anim_manager @ 0x4447d0 (thiscall, ret)

#include "object_animation_types.h"
#include "object_render_types.h"
#include "anim_manager.h"
#include "game_root.h"
#include "presentation_animation_channel.h"

extern GameRoot* g_game; // data_4df904

void AnimManager::update_anim_manager()
{
    completed = false;
    switch (state) {
    case 0:
        return;
    case 1: {
        float delta = (g_game->subgame.base_rate * 2.0f - 0.200000003f + 1.0f)
            * progress_step;
        float next_progress = progress + delta;
        progress = next_progress;

        if (next_progress >= 1.0f) {
            unsigned short frame_flags = active_animation->flags;
            if ((frame_flags & OBJECT_ANIMATION_MODE_LOOP) != 0) {
                completed = true;
                progress = next_progress - 1.0f;
            } else if ((frame_flags & OBJECT_ANIMATION_MODE_ONCE) != 0) {
                progress = 0.999000013f;
                progress_step = 0.0f;
                completed = true;
            } else if ((frame_flags & OBJECT_ANIMATION_MODE_PING_PONG) != 0) {
                progress = 2.0f - next_progress;
                progress_step *= -1.0f;
            }
        }

        if (progress < 0.0f) {
            unsigned char* frame_flags = (unsigned char*)&active_animation->flags;
            if ((*frame_flags & OBJECT_ANIMATION_MODE_PING_PONG) != 0) {
                progress = -progress;
                completed = true;
                progress_step *= -1.0f;
            }
            if ((*frame_flags & OBJECT_ANIMATION_MODE_ONCE_REVERSE) != 0) {
                progress = 0.0f;
                progress_step = 0.0f;
                completed = true;
            }
        }

        float clamped_progress;
        if (progress < 0.0f) {
            clamped_progress = 0.0f;
        } else {
            if (progress > 0.999899983f)
                clamped_progress = 0.999899983f;
            else
                clamped_progress = progress;
        }
        progress = clamped_progress;
        break;
    }
    }

    if (completed && queue_count > 0) {
        int next_animation = queued_animations[0];
        if (next_animation == ANIM_MANAGER_HIDE_ANIMATION_ID) {
            progress = 0.0f;
            progress_step = 0.0f;
            target_model->list_flags &= ~0x20u;
        } else {
            target_model->list_flags |= 0x20u;
            Object** slot_object =
                &animation_slots[queued_animations[0]].body.object;
            ObjectAnimation* animation = (*slot_object)->animation;
            progress = 0.0f;
            active_animation = animation;
            progress_step = active_animation->progress_step;
            target_model->object = *slot_object;
        }

        --queue_count;
        int shift_index = 0;
        while (shift_index < queue_count) {
            queued_animations[shift_index] = queued_animations[shift_index + 1];
            shift_index++;
        }
    }
}
