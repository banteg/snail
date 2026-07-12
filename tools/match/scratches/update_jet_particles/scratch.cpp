// update_jet_particles @ 0x43a690 (fastcall)

#include "sub_hover.h"
#include "object_render_types.h"
#include "player.h"
#include "sprite.h"
#include "subgame_runtime.h"

int next_math_random_value();

void SubHover::update_jet_particles()
{
    if (state != 1) {
        return;
    }

    if (game->embedded_player()->presentation.jetpack_channel.anim_manager.active_animation
        != game->embedded_player()->presentation.jetpack_channel.animation_slots[0]
               .body.object->animation) {
        return;
    }

    int row;
    int column;
    float row_fraction;
    float sprite_size;
    float size_scale;
    float forward_scale;
    Vector3 base_position;
    float velocity_x;
    float velocity_y;
    float velocity_z;
    Vector3 offset_position;
    Color4f color;

    forward_scale =
        (float)next_math_random_value() * 0.00000152587893f + 0.400000006f;
    size_scale =
        (float)next_math_random_value() * 0.00000152587893f + 0.119999997f;
    row = 0;

    for (; row < 15; ++row) {
        column = 0;
        row_fraction = (float)row * 0.0714285746f;
        sprite_size = (1.0f - row_fraction) * size_scale * warning_intensity;

        do {
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
            Vector3* forward = &player->presentation.live_matrix.basis_forward;
            float forward_offset =
                -(row_fraction * forward_scale * warning_intensity);
            offset_position.x = forward_offset * forward->x;
            offset_position.y = forward_offset * forward->y;
            offset_position.z = forward_offset * forward->z;
            base_position.x = base_position.x + offset_position.x;
            base_position.y = base_position.y + offset_position.y;
            base_position.z = base_position.z + offset_position.z;

            JetParticleSlot* slot =
                (JetParticleSlot*)((char*)this + ((column + row * 2 + 2) << 4));
            slot->sprite->size_end = sprite_size;
            slot->sprite->size_start = sprite_size;
            slot->sprite->position.x = base_position.x;
            slot->sprite->position.y = base_position.y;
            slot->sprite->position.z = base_position.z;

            if (row == 14
                && (float)next_math_random_value() * 0.0000305175781f
                       > 0.899999976f) {
                Sprite* sprite =
                    g_sprite_manager.allocate_sprite(
                        game->embedded_player()->player_slot, 0x21, -1, -1);
                unsigned int flags = sprite->flags;
                flags |= 0x800;
                sprite->flags = flags;
                sprite->progress = 0.0f;
                sprite->progress_step = 0.138888896f;
                sprite->lifetime = 0.0f;
                sprite->lifetime_step = 0.0f;

                sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
                sprite->size_start = 0.1f;
                sprite->size_end = 0.300000012f;

                Vector3* velocity = &sprite->velocity;
                Vector3* out_position = &sprite->position;
                Vector3* trail_source = &game->embedded_player()->velocity;
                velocity_x = trail_source->x * 0.850000024f;
                velocity_y = trail_source->y * 0.850000024f;
                velocity_z = trail_source->z * 0.850000024f;
                sprite->gravity_step = 0.00100000005f;
                velocity->x = velocity_x;
                velocity->y = velocity_y;
                velocity->z = velocity_z;
                out_position->x = base_position.x;
                out_position->y = base_position.y;
                out_position->z = base_position.z;
            }
            ++column;
        } while (column < 2);
    }
}
