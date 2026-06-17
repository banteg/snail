// dispatch_cutscene_animation @ 0x444600 (thiscall, ret 0xc)

#include "object_animation_types.h"
#include "player.h"

int PlayerPresentationController::dispatch_cutscene_animation(
    int animation_id,
    unsigned char immediate,
    int initial_frame)
{
    if (immediate != 0) {
        PresentationAnimationSlot* slot =
            (PresentationAnimationSlot*)(cutscene_animation_slot_table + animation_id * 0x80);
        ObjectAnimation* active_animation = slot->visual_root->active_animation;
        anim_manager.active_animation = active_animation;
        if (initial_frame != -1)
            active_animation->flags = (unsigned short)initial_frame;

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
            ObjectAnimation* active_animation = anim_manager.active_animation;
            anim_manager.progress = 0.0f;
            float step;
            if (active_animation->progress_step < 0.0f)
                step = -active_animation->progress_step;
            else
                step = active_animation->progress_step;
            anim_manager.progress_step = step;
        }

        PresentationAnimationVisualRoot* root = slot->visual_root;
        anim_manager.queue_count = 0;
        visual_root = root;
        int flags = *(int*)((char*)anim_manager.target_model + 4);
        flags |= 0x20;
        *(int*)((char*)anim_manager.target_model + 4) = flags;
        return flags;
    }

    int queue_count = anim_manager.queue_count;
    int queued_animation = animation_id;
    anim_manager.queued_animations[queue_count] = queued_animation;
    int result = anim_manager.queue_count + 1;
    anim_manager.queue_count = result;
    return result;
}
