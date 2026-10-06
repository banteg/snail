// emit_ring_star_shower @ 0x43e690 (thiscall)
// Authored owner: cRSubRingStar::Shower(cRSubGoldy*).

#include "player.h"
#include "ring_special_effect_types.h"
#include "runtime_config.h"
#include "sprite.h"

float Sin(float radians);
float Cos(float radians);


void cRSubRingStar::Shower(cRSubGoldy* owner)
{
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_PARTICLE_EFFECTS) != 0) {
        Vector3 velocity;
        Vector3 orbit_velocity;
        velocity.z = 0.0f;
        cRSprite* star = g_sprite_manager.New(
            owner->player_slot,
            parent->star_sprite_id,
            -1,
            -1);
        star->progress = 0.0f;
        star->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        star->progress_step = 0.111111104f;
        star->size_start = 0.40000001f;
        star->size_end = 0.2f;

        orbit_velocity.x = Sin(phase + 1.0471976f) * radius;
        orbit_velocity.y = Cos(phase + 1.0471976f) * radius;
        velocity.x = orbit_velocity.x * 0.30000001f;
        velocity.y = orbit_velocity.y * 0.30000001f;
        star->velocity = velocity;

        star->position = sprite->position;
        star->gravity_step = 0.0f;
    }
}
