// set_weapon_animation @ 0x4446e0 (thiscall, ret 0xc)

#include "anim_manager.h"

struct WeaponVisualRoot {
    char unknown_000[0xbc];
    ObjectAnimation* active_animation; // +0xbc
};

struct WeaponAnimationSlot {
    WeaponVisualRoot* visual_root; // +0x00
    char unknown_04[0x80 - 0x04];
};

class WeaponChannel {
public:
    int set_weapon_animation(int animation_id, unsigned char immediate, int initial_frame);

    char unknown_000[0x24];
    WeaponVisualRoot* visual_root; // +0x24
    char unknown_028[0x108 - 0x028];
    AnimManager anim_manager; // +0x108
    char unknown_150[0x174 - 0x150];
    WeaponAnimationSlot animation_slots[1]; // +0x174, indexed by animation_id
};

int WeaponChannel::set_weapon_animation(
    int animation_id,
    unsigned char immediate,
    int initial_frame)
{
    if (immediate != 0) {
        WeaponAnimationSlot* slot = &animation_slots[animation_id];
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

        WeaponVisualRoot* root = slot->visual_root;
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
