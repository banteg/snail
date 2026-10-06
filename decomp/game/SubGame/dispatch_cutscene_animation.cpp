// dispatch_cutscene_animation @ 0x444600 (thiscall, ret 0xc)

#include "object_animation_types.h"
#include "object_render_types.h"
#include "player.h"

void cRSnail::SetAnimation(
    int animation_id,
    bool immediate,
    int mode_flags)
{
    if (immediate != 0) {
        anim_manager.active_animation = cutscene_animation_slots[animation_id].body.object->animation;
        if (mode_flags != OBJECT_ANIMATION_MODE_UNCHANGED)
            anim_manager.active_animation->flags = (unsigned short)mode_flags;

        if ((anim_manager.active_animation->flags
                & OBJECT_ANIMATION_MODE_ONCE_REVERSE)
            != 0) {
            ObjectAnimation* active_animation = anim_manager.active_animation;
            float step;
            if (active_animation->progress_step < 0.0f)
                step = -active_animation->progress_step;
            else
                step = active_animation->progress_step;
            step = -step;
            anim_manager.progress_step = step;
            anim_manager.progress = step + 1.0f;
        } else {
            anim_manager.progress = 0.0f;
            ObjectAnimation* active_animation = anim_manager.active_animation;
            float step;
            if (active_animation->progress_step < 0.0f)
                step = -active_animation->progress_step;
            else
                step = active_animation->progress_step;
            anim_manager.progress_step = step;
        }

        object = cutscene_animation_slots[animation_id].body.object;
        anim_manager.queue_count = 0;
        int flags = anim_manager.target_model->list_flags;
        flags |= 0x20;
        anim_manager.target_model->list_flags = flags;
        return;
    }

    anim_manager.queued_animations[anim_manager.queue_count] = animation_id;
    ++anim_manager.queue_count;
}
