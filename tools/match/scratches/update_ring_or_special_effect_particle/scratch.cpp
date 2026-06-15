// update_ring_or_special_effect_particle @ 0x43e780 (thiscall)

#include "sprite.h"

float sine(float radians);
float cosine(float radians);

struct Player {
    char unknown_00[0x380];
    int player_slot; // +0x380
};

class RingOrSpecialEffectParent {
public:
    char unknown_000[0x68];
    Vector3 position; // +0x68
    char unknown_074[0x84 - 0x74];
    Player* owner_player; // +0x84
    int kind; // +0x88
    char unknown_08c[0x1e8 - 0x8c];
    int star_shower_counter; // +0x1e8
};

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
