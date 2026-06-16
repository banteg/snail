// update_ring_or_special_effect_particle @ 0x43e780 (thiscall)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

float sine(float radians);
float cosine(float radians);

class RingOrSpecialEffectParticle {
public:
    int update_ring_or_special_effect_particle();
    int emit_ring_star_shower(Player* owner); // @ 0x43e690

    Sprite* sprite; // +0x00
    RingOrSpecialEffectParent* parent; // +0x04
    Vector3 base_position; // +0x08
    float phase; // +0x14
    float phase_step; // +0x18
    float radius; // +0x1c
};

int RingOrSpecialEffectParticle::update_ring_or_special_effect_particle()
{
    RingOrSpecialEffectParent* owner = parent;
    if (owner->kind != 3)
        phase += phase_step;

    if (phase > 6.2831855f)
        phase -= 6.2831855f;

    Vector3 position;
    float orbit_y = cosine(phase) * radius;
    float orbit_x = sine(phase);
    RingOrSpecialEffectParent* live_owner = parent;
    Sprite* live_sprite = sprite;
    Vector3* owner_position = &live_owner->position;
    Vector3* sprite_position = &live_sprite->position;
    orbit_x *= radius;
    position.x = orbit_x + owner_position->x;
    position.y = orbit_y + owner_position->y;
    position.z = owner_position->z;

    *sprite_position = position;

    RingOrSpecialEffectParent* result_owner = parent;
    if (result_owner->star_shower_counter == 0)
        return emit_ring_star_shower(result_owner->owner_player);
    return (int)result_owner;
}
