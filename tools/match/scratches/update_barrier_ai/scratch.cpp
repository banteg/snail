// update_barrier_ai @ 0x440f80 (thiscall, ret)

#include "barrier_actor.h"

void BarrierActor::update_barrier_ai()
{
    cRSubGoldy* owner = owner_player;
    position.z = owner->transform.position.z;
    position.y = 0.4f;
}
