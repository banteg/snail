// kill_subgoldy @ 0x445840 (thiscall, ret)

#include "player.h"

void cRSubGoldy::Kill()
{
    begin_post_follow_carryover();
    transform.position.y = -8.0f;
}
