// emit_ring_star_shower @ 0x43e690 (thiscall)

#include "player.h"
#include "ring_special_effect_types.h"
#include "runtime_config.h"
#include "sprite.h"

float sine(float radians);
float cosine(float radians);


void SubRingStar::emit_ring_star_shower(Player* owner)
{
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) != 0) {
        Vector3 velocity;
        Vector3 orbit_velocity;
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

        orbit_velocity.x = sine(phase + 1.0471976f) * radius;
        orbit_velocity.y = cosine(phase + 1.0471976f) * radius;
        velocity.x = orbit_velocity.x * 0.30000001f;
        velocity.y = orbit_velocity.y * 0.30000001f;
        star->velocity = velocity;

        star->position = sprite->position;
        star->gravity_step = 0.0f;
    }
}
