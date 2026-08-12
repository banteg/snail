// update_barrier_ai @ 0x440f80 (thiscall, ret)

#include "barrier_actor.h"

void cRBarrier::AI()
{
    cRSubGoldy* owner = owner_player;
    position.z = owner->transform.position.z;
    position.y = 0.4f;
}
