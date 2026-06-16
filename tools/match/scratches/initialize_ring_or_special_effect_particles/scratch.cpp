// initialize_ring_or_special_effect_particles @ 0x43e470 (thiscall, ret 0x4)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

int RingOrSpecialEffectParent::initialize_ring_or_special_effect_particles(int)
{
    int i = 0;
    state = 1;
    star_shower_counter = 0;

    Vector3* parent_position = &position;
    do {
        RingOrSpecialEffectParticle* particle = &particles[i];
        particle->phase = (float)i * 0.628318548f;
        particle->phase_step = rate_source->subgame_rate * 0.104719758f;
        particle->parent = this;
        particle->base_position = *parent_position;
        particle->radius = 1.2f;

        int effect_kind = kind;
        if (effect_kind == 4 || effect_kind == 5 || effect_kind == 8) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x87,
                -1,
                -1);
            star_sprite_id = 0x88;
            particle->sprite->draw_mode = 9;
        } else if (effect_kind == 2 || effect_kind == 6) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x83,
                -1,
                -1);
            star_sprite_id = 0x84;
            particle->sprite->draw_mode = 0xd;
        } else if (effect_kind == 3 || effect_kind == 7) {
            particle->sprite = g_sprite_manager.allocate_sprite(
                owner_player->player_slot,
                0x85,
                -1,
                -1);
            star_sprite_id = 0x86;
            particle->sprite->draw_mode = 0xd;
        }

        Color4f color;
        particle->sprite->color =
            *color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.800000012f);
        unsigned int flags = particle->sprite->flags;
        flags |= 0x800;
        particle->sprite->flags = flags;
        particle->sprite->progress = 0.0f;
        particle->sprite->progress_step = 0.0f;
        particle->sprite->gravity_step = 0.0f;
        particle->sprite->size_start = 0.720000029f;
        particle->sprite->size_end = 0.720000029f;
        particle->sprite->position = *parent_position;
        particle->sprite->facing_angle = particle->phase;

        int spin_kind = kind;
        if (spin_kind == 3 || spin_kind == 6)
            particle->sprite->facing_angle_step = 0.0f;
        else
            particle->sprite->facing_angle_step = -particle->phase_step;

        particle->update_ring_or_special_effect_particle();
        i++;
    } while (i < 10);

    return i;
}
