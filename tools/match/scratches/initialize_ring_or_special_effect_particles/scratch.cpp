// initialize_ring_or_special_effect_particles @ 0x43e470 (thiscall, ret 0x4)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"
#include "subgame_runtime.h"

int SubRing::initialize_ring_or_special_effect_particles(int)
{
    int i = 0;
    state = SUB_RING_STATE_ACTIVE;
    star_shower_counter = 0;

    Vector3* parent_position = &transform.position;
    do {
        SubRingStar* particle = &particles[i];
        particle->phase = (float)i * 0.628318548f;
        float* phase_step = &particle->phase_step;
        *phase_step = rate_source->subgame_rate * 0.104719758f;
        particle->parent = this;
        Vector3* base_position = &particle->base_position;
        *base_position = *parent_position;
        particle->radius = 1.2f;

        SubRingKind effect_kind = kind;
        if (effect_kind == SUB_RING_KIND_NORMAL_DEFAULT
            || effect_kind == SUB_RING_KIND_NORMAL_AUTHORED
            || effect_kind == SUB_RING_KIND_POWER_UP_AUTHORED) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x87,
                -1,
                -1);
            star_sprite_id = 0x88;
            particle->sprite->draw_mode = 9;
        } else if (effect_kind == SUB_RING_KIND_EXPLODE_RAMP
            || effect_kind == SUB_RING_KIND_EXPLODE_AUTHORED) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x83,
                -1,
                -1);
            star_sprite_id = 0x84;
            particle->sprite->draw_mode = 0xd;
        } else if (effect_kind == SUB_RING_KIND_SLOW_DEFAULT
            || effect_kind == SUB_RING_KIND_SLOW_AUTHORED) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x85,
                -1,
                -1);
            star_sprite_id = 0x86;
            particle->sprite->draw_mode = 0xd;
        }

        tColour color;
        particle->sprite->color =
            *color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.800000012f);
        unsigned int flags = particle->sprite->flags;
        flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
        particle->sprite->flags = flags;
        particle->sprite->progress = 0.0f;
        particle->sprite->progress_step = 0.0f;
        particle->sprite->gravity_step = 0.0f;
        particle->sprite->size_start = 0.720000029f;
        particle->sprite->size_end = 0.720000029f;
        particle->sprite->position = *parent_position;
        particle->sprite->facing_angle = particle->phase;

        SubRingKind spin_kind = kind;
        if (spin_kind == SUB_RING_KIND_SLOW_DEFAULT
            || spin_kind == SUB_RING_KIND_EXPLODE_AUTHORED)
            particle->sprite->facing_angle_step = 0.0f;
        else
            particle->sprite->facing_angle_step = -particle->phase_step;

        particle->update_ring_or_special_effect_particle();
        i++;
    } while (i < SUB_RING_PARTICLE_COUNT);

    return i;
}
