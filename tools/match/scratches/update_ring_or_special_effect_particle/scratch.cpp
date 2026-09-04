// update_ring_or_special_effect_particle @ 0x43e780 (thiscall)
// Authored owner: cRSubRingStar::AI().

#include "player.h"
#include "ring_special_effect_types.h"
#include "sprite.h"

float Sin(float radians);
float Cos(float radians);

void cRSubRingStar::AI()
{
    cRSubRing* source_parent = parent;
    if (source_parent->kind != SUB_RING_KIND_SLOW_DEFAULT)
        phase += phase_step;

    if (phase > 6.2831855f)
        phase -= 6.2831855f;

    Vector3 offset(Sin(phase) * radius, Cos(phase) * radius, 0.0f);
    sprite->position = parent->transform.position + offset;

    cRSubRing* result_parent = parent;
    if (result_parent->star_shower_counter == 0)
        Shower(result_parent->owner_player);
}
