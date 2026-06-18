// initialize_sprite @ 0x44de90 (thiscall)

#include "sprite.h"

void Sprite::initialize_sprite()
{
    flags = 0x49;
    color.set_color_white();

    int zero = 0;
    gravity_step = -0.013f;
    draw_mode = zero;
    progress = 0.0f;
    lifetime = 0.0f;
    lifetime_step = 0.0f;
    facing_angle = 0.0f;
    facing_angle_step = 0.0f;
    reserved_84 = zero;
    corner_scale = 1.0f;
    facing_refresh_progress = 0.0f;
    facing_refresh_step = 0.0f;
    depth_offset = -500.0f;
    texture_ref_a = 0;
    texture_ref_b = 0;
    velocity.z = 0.0f;
    velocity.y = 0.0f;
    velocity.x = 0.0f;
    depth_bias = 0.0f;
    object_ref = (void*)-1;
    texture_id = zero;
    frame_count = zero;
    frame = zero;
    frame_progress = 0.0f;
    frame_progress_step = 0.0f;
    frame_step = 1;
}
