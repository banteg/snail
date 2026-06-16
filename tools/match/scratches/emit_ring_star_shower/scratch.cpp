// emit_ring_star_shower @ 0x43e690 (thiscall, ret 0x4)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

float sine(float radians);
float cosine(float radians);

class RingOrSpecialEffectParticle {
public:
    char emit_ring_star_shower(Player* owner);

    Sprite* sprite; // +0x00
    RingOrSpecialEffectParent* parent; // +0x04
    Vector3 base_position; // +0x08
    float phase; // +0x14
    float phase_step; // +0x18
    float radius; // +0x1c
};

extern unsigned char g_render_flags; // byte_4df934

char RingOrSpecialEffectParticle::emit_ring_star_shower(Player* owner)
{
    char result = g_render_flags;
    if ((result & 0x10) != 0) {
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

        float angle = phase + 1.0471976f;
        float velocity_x = sine(angle) * radius;
        float angle_2 = phase + 1.0471976f;
        float scaled_x = velocity_x * 0.30000001f;
        float scaled_y = cosine(angle_2) * radius * 0.30000001f;
        float zero = 0.0f;
        float* velocity = &star->velocity.x;
        velocity[0] = scaled_x;
        velocity[1] = scaled_y;
        velocity[2] = zero;

        Vector3* source_position = &sprite->position;
        star->position = *source_position;
        star->gravity_step = 0.0f;
        result = *(char*)&source_position->z;
    }
    return result;
}
