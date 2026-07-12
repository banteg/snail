// set_weapon_animation @ 0x4446e0 (thiscall, ret 0xc)

#include "object_animation_types.h"
#include "object_render_types.h"
#include "presentation_animation_channel.h"

int PresentationAnimationChannel::set_weapon_animation(
    int animation_id,
    unsigned char immediate,
    int initial_frame)
{
    if (immediate != 0) {
        Object** slot_object = &animation_slots[animation_id].body.object;
        anim_manager.active_animation = (*slot_object)->animation;
        if (initial_frame != -1)
            anim_manager.active_animation->flags = (unsigned short)initial_frame;

        if ((anim_manager.active_animation->flags & 8) != 0) {
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

        Object* root = *slot_object;
        anim_manager.queue_count = 0;
        object = root;
        int flags = anim_manager.target_model->list_flags;
        flags |= 0x20;
        anim_manager.target_model->list_flags = flags;
        return flags;
    }

    anim_manager.queued_animations[anim_manager.queue_count] = animation_id;
    return ++anim_manager.queue_count;
}
