// update_jet_particles @ 0x43a690 (fastcall)

#include "sub_hover.h"
#include "object_render_types.h"
#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"

int next_math_random_value();

void SubHover::update_jet_particles()
{
    if (state != SUB_HOVER_STATE_ACTIVE) {
        return;
    }

    if (game->embedded_player()->presentation.jetpack_channel.anim_manager.active_animation
        != game->embedded_player()->presentation.jetpack_channel.animation_slots[0]
               .body.object->animation) {
        return;
    }

    float forward_scale =
        (float)next_math_random_value() * 0.0000305175781f * 0.05f
        + 0.400000006f;
    float size_scale =
        (float)next_math_random_value() * 0.0000305175781f * 0.05f
        + 0.119999997f;
    int row = 0;

    for (; row < JET_PARTICLE_ROW_COUNT; ++row) {
        int column = 0;
        float row_fraction = (float)row / (float)JET_PARTICLE_LAST_ROW_INDEX;
        float sprite_size =
            (1.0f - row_fraction) * size_scale * warning_intensity;

        do {
            Vector3 base_position;
            if (column == 0) {
                Vector3* source =
                    &game->embedded_player()->presentation.snail_hotspots_world[
                        SNAIL_HOTSPOT_JETPACK_LEFT];
                base_position = *source;
            } else {
                Vector3* source =
                    &game->embedded_player()->presentation.snail_hotspots_world[
                        SNAIL_HOTSPOT_JETPACK_RIGHT];
                base_position = *source;
            }
            Vector3* forward = &player->presentation.transform.basis_forward;
            float forward_offset =
                -(row_fraction * forward_scale * warning_intensity);
            Vector3 offset_position;
            offset_position.x = forward_offset * forward->x;
            offset_position.y = forward_offset * forward->y;
            offset_position.z = forward_offset * forward->z;
            base_position += offset_position;

            JetParticleSlot* slot = &particle_slots[row][column];
            slot->sprite->size_end = sprite_size;
            slot->sprite->size_start = sprite_size;
            slot->sprite->position = base_position;

            if (row == JET_PARTICLE_LAST_ROW_INDEX
                && (float)next_math_random_value() * 0.0000305175781f
                       > 0.899999976f) {
                cRSprite* sprite =
                    g_sprite_manager.New(
                        game->embedded_player()->player_slot, 0x21, -1, -1);
                sprite->flags |= SPRITE_FLAG_GAMEPLAY_OWNED;
                sprite->progress = 0.0f;
                sprite->progress_step = 0.138888896f;
                sprite->lifetime = 0.0f;
                sprite->lifetime_step = 0.0f;

                tColour color;
                sprite->color = *color.Set(1.0f, 1.0f, 1.0f, 1.0f);
                sprite->size_start = 0.1f;
                sprite->size_end = 0.300000012f;

                Vector3* trail_source = &game->embedded_player()->velocity;
                Vector3 staged_velocity;
                staged_velocity.x = trail_source->x * 0.850000024f;
                staged_velocity.y = trail_source->y * 0.850000024f;
                staged_velocity.z = trail_source->z * 0.850000024f;
                sprite->gravity_step = 0.00100000005f;
                sprite->velocity = staged_velocity;
                sprite->position = base_position;
            }
            ++column;
        } while (column < JET_PARTICLE_COLUMN_COUNT);
    }
}
