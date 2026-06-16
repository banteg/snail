// health_collect_particles @ 0x43a010 (thiscall, ret 0x4)

#include "player.h"
#include "sprite.h"

extern unsigned char g_render_flags; // byte_4df934

float sine(float radians);
float cosine(float radians);

class HealthPickupParticleSource {
public:
    char unknown_00[0x64];
    Sprite* sprite; // +0x64
};

int Player::health_collect_particles(void* pickup_)
{
    int result = g_render_flags;
    if ((result & 0x10) != 0) {
        HealthPickupParticleSource* pickup =
            (HealthPickupParticleSource*)pickup_;

        int index = 0;
        do {
            Sprite* sprite =
                g_sprite_manager.allocate_sprite(player_slot, 0x80, -1, -1);

            sprite->flags |= 0x800;
            sprite->progress = 0.0f;
            sprite->progress_step = 0.041666668f;
            *(int*)&sprite->gravity_step = 0xb951b717;

            Color4f color;
            Color4f* color_result =
                color.set_color_rgba(1.0f, 0.75f, 0.75f, 1.0f);
            sprite->color.r = color_result->r;
            sprite->color.g = color_result->g;
            sprite->color.b = color_result->b;
            sprite->color.a = color_result->a;

            sprite->size_start = 0.1f;
            sprite->size_end = 0.5f;

            sprite->position = pickup->sprite->position;

            float angle = (float)index * 0.785398185f;
            sprite->velocity.z = velocity.z * 0.400000006f;
            sprite->velocity.y = cosine(angle) * 0.0149999997f;
            sprite->velocity.x = sine(angle) * 0.0149999997f;

            sprite->position.x += velocity.x * 3.0f;
            sprite->position.y += velocity.y * 3.0f;
            result = index + 1;
            index++;
            sprite->position.z += velocity.z * 3.0f;
        } while (index < 8);
    }

    return result;
}
