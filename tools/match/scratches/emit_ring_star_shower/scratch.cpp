// emit_ring_star_shower @ 0x43e690 (thiscall, ret 0x4)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

float sine(float radians);
float cosine(float radians);

extern unsigned char g_render_flags; // byte_4df934

char RingOrSpecialEffectParticle::emit_ring_star_shower(Player* owner)
{
    char result = g_render_flags;
    if ((result & 0x10) != 0) {
        float velocity_z = 0.0f;
        Sprite* star = g_sprite_manager.allocate_sprite(
            owner->player_slot,
            parent->star_sprite_id,
            -1,
            -1);
        star->progress = 0.0f;
        star->flags |= 0x800;
        star->progress_step = 0.111111104f;
        star->size_start = 0.40000001f;
        star->size_end = 0.2f;

        float velocity_x = sine(phase + 1.0471976f) * radius;
        float velocity_y = cosine(phase + 1.0471976f) * radius;
        float scaled_x = velocity_x * 0.30000001f;
        float scaled_y = velocity_y * 0.30000001f;
        Vector3* velocity = &star->velocity;
        velocity->x = scaled_x;
        velocity->y = scaled_y;
        velocity->z = velocity_z;

        Vector3* source_position = &sprite->position;
        star->position = *source_position;
        star->gravity_step = 0.0f;
        result = *(char*)&source_position->z;
    }
    return result;
}
