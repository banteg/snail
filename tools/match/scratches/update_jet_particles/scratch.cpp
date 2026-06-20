// update_jet_particles @ 0x43a690 (fastcall)

#include "jetpack_gauge.h"
#include "sprite.h"

int next_math_random_value();

struct JetActiveRuntimeView {
    char unknown_000[0xbc];
    int active_player_ref; // +0xbc
};

struct JetGameView {
    char unknown_000000[0x3bbae4];
    int effect_sprite_owner; // +0x3bbae4
    char unknown_3bbae8[0x3bbb74 - 0x3bbae8];
    Vector3 trail_velocity; // +0x3bbb74
    char unknown_3bbb80[0x3bf3dc - 0x3bbb80];
    int active_player_ref; // +0x3bf3dc
    char unknown_3bf3e0[0x3bf43c - 0x3bf3e0];
    JetActiveRuntimeView* active_runtime; // +0x3bf43c
    char unknown_3bf440[0x3bf934 - 0x3bf440];
    Vector3 nozzle_positions[2]; // +0x3bf934, +0x3bf940
};

struct JetPlayerView {
    char unknown_0000[0x29dc];
    Vector3 basis_forward; // +0x29dc
};

void JetpackGaugeController::update_jet_particles()
{
    if (state != 1) {
        return;
    }

    if (((JetGameView*)game)->active_player_ref
        != ((JetGameView*)game)->active_runtime->active_player_ref) {
        return;
    }

    float size_scale =
        (float)next_math_random_value() * 0.00000152587893f + 0.119999997f;
    int row = 0;
    float forward_scale =
        (float)next_math_random_value() * 0.00000152587893f + 0.400000006f;

    do {
        int column = 0;
        float row_fraction = (float)row * 0.0714285746f;
        float sprite_size =
            (1.0f - row_fraction) * size_scale * warning_intensity;

        do {
            Vector3 base_position;
            if (column != 0) {
                Vector3* source = &((JetGameView*)game)->nozzle_positions[1];
                base_position = *source;
            } else {
                Vector3* source = &((JetGameView*)game)->nozzle_positions[0];
                base_position = *source;
            }
            Vector3* forward = &((JetPlayerView*)player)->basis_forward;
            float forward_offset =
                -(row_fraction * forward_scale * warning_intensity);
            Vector3 offset_position;
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
                        ((JetGameView*)game)->effect_sprite_owner, 0x21, -1, -1);
                unsigned int flags = sprite->flags;
                flags |= 0x800;
                sprite->flags = flags;
                sprite->progress = 0.0f;
                sprite->progress_step = 0.138888896f;
                sprite->lifetime = 0.0f;
                sprite->lifetime_step = 0.0f;

                Color4f color;
                sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
                sprite->size_start = 0.1f;
                sprite->size_end = 0.300000012f;

                Vector3* velocity = &sprite->velocity;
                Vector3* out_position = &sprite->position;
                float velocity_x =
                    ((JetGameView*)game)->trail_velocity.x * 0.850000024f;
                float velocity_y =
                    ((JetGameView*)game)->trail_velocity.y * 0.850000024f;
                float velocity_z =
                    ((JetGameView*)game)->trail_velocity.z * 0.850000024f;
                sprite->gravity_step = 0.00100000005f;
                velocity->x = velocity_x;
                velocity->y = velocity_y;
                velocity->z = velocity_z;
                out_position->x = base_position.x;
                out_position->y = base_position.y;
                out_position->z = base_position.z;
            }

            column++;
        } while (column < 2);

        row++;
    } while (row < 15);
}
