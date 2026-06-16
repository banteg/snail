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
        Vector3 velocity;
        velocity.z = 0.0f;
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

        velocity.x = sine(phase + 1.0471976f) * radius;
        velocity.y = cosine(phase + 1.0471976f) * radius;
        velocity.x *= 0.30000001f;
        velocity.y *= 0.30000001f;
        star->velocity = velocity;

        int* source_position_words = (int*)&sprite->position;
        int* star_position_words = (int*)&star->position;
        star_position_words[0] = source_position_words[0];
        star_position_words[1] = source_position_words[1];
        int source_z = source_position_words[2];
        star->gravity_step = 0.0f;
        star_position_words[2] = source_z;
        result = (char)source_z;
    }
    return result;
}
