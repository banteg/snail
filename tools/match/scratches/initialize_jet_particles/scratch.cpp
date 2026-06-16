// initialize_jet_particles @ 0x43a5b0 (fastcall)

#include "jetpack_gauge.h"
#include "sprite.h"

void __fastcall initialize_jet_particles(JetpackGaugeController* gauge)
{
    JetParticleSlot* slot = &gauge->particle_slots[0][0];
    int rows = 15;
    do {
        int columns = 2;
        do {
            slot->sprite = g_sprite_manager.allocate_sprite(1, 0x9e, -1, -1);
            unsigned int flags = slot->sprite->flags;
            flags |= 0x800;
            slot->sprite->flags = flags;
            slot->sprite->progress = 0.0f;
            slot->sprite->progress_step = 0.0f;
            slot->sprite->lifetime = 0.0f;
            slot->sprite->lifetime_step = 0.0f;
            slot->sprite->size_end = 0.0f;
            slot->sprite->size_start = 0.0f;
            Vector3* velocity = &slot->sprite->velocity;
            velocity->z = 0.0f;
            velocity->y = 0.0f;
            velocity->x = 0.0f;
            slot->sprite->gravity_step = 0.0f;

            Color4f color;
            slot->sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.999000013f);
            float* wobble_x = &slot->wobble_x;
            *wobble_x = 0.0f;
            slot->sprite->draw_mode = 0;
            slot->wobble_y = 0.0f;
            slot->wobble_alpha = 0.166666672f;
            slot++;
            columns--;
        } while (columns != 0);
        rows--;
    } while (rows != 0);
}
