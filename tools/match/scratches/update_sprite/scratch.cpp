// update_sprite @ 0x44df30 (thiscall)

#include "sprite.h"

void Sprite::update_sprite()
{
    unsigned int current_flags = flags;
    if ((current_flags & SPRITE_FLAG_GAMEPLAY_OWNED) != 0
        && g_sprite_manager.paused != 0) {
        return;
    }

    if ((current_flags & SPRITE_FLAG_SKIP_INITIAL_PROGRESS) == 0) {
        float next_progress = progress_step + progress;
        progress = next_progress;
        if (next_progress > 1.0f || next_progress < 0.0f) {
            progress = 1.0f;
            if ((current_flags & SPRITE_FLAG_PRESERVE_AT_PROGRESS_END) == 0) {
                kill_sprite();
            }
            return;
        }

        if (lifetime_step != 0.0f) {
            float next_lifetime = lifetime_step + lifetime;
            lifetime = next_lifetime;
            if (next_lifetime > 1.0f) {
                lifetime_step = 0.0f;
            }
        }
    } else {
        flags = current_flags & ~SPRITE_FLAG_SKIP_INITIAL_PROGRESS;
    }

    flags &= ~SPRITE_FLAG_SKIP_INITIAL_PROGRESS;

    Vector3* previous = &previous_position;
    Vector3* current = &position;
    *previous = *current;
    current->x += velocity.x;
    float next_y = velocity.y;
    next_y += current->y;
    current->y = next_y;
    current->z += velocity.z;
    velocity.y += gravity_step;
    facing_angle += facing_angle_step;

    if (lifetime_step > 0.0f) {
        flags |= SPRITE_FLAG_DELAYED_RENDER;
    } else {
        flags &= ~SPRITE_FLAG_DELAYED_RENDER;
    }

    unsigned int animation_flags = flags;
    if ((animation_flags & SPRITE_FLAG_ANIMATED) == 0) {
        return;
    }

    float next_frame_progress = frame_progress_step + frame_progress;
    frame_progress = next_frame_progress;
    if (next_frame_progress > 1.0f) {
        frame_progress = next_frame_progress - 1.0f;
        frame += frame_step;
        int next_frame = frame;

        if ((animation_flags & SPRITE_FLAG_ANIMATION_PING_PONG) != 0) {
            if (next_frame == frame_count) {
                frame_step = -1;
                frame = frame_count - 1;
            }
            if (frame == -1) {
                frame = 0;
                frame_step = 1;
            }
        } else {
            if (next_frame == frame_count) {
                frame = 0;
            }
        }

        set_sprite_texture_ref(texture_id, frame);
    }
}
