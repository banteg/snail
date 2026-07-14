// update_ring_or_special_effect_particle @ 0x43e780 (thiscall)

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

float sine(float radians);
float cosine(float radians);

void SubRingStar::update_ring_or_special_effect_particle()
{
    SubRing* source_parent = parent;
    if (source_parent->kind != SUB_RING_KIND_SLOW_DEFAULT)
        phase += phase_step;

    if (phase > 6.2831855f)
        phase -= 6.2831855f;

    Vector3 staged_position;
    float orbit_y = cosine(phase) * radius;
    float orbit_x = sine(phase);
    SubRing* live_parent = parent;
    Sprite* live_sprite = sprite;
    Vector3* parent_position = &live_parent->transform.position;
    Vector3* sprite_position = &live_sprite->position;
    orbit_x *= radius;
    staged_position.x = orbit_x + parent_position->x;
    staged_position.y = orbit_y + parent_position->y;
    staged_position.z = parent_position->z;

    *sprite_position = staged_position;

    SubRing* result_parent = parent;
    if (result_parent->star_shower_counter == 0)
        emit_ring_star_shower(result_parent->owner_player);
}
