// kill_subgoldy @ 0x445840 (thiscall, ret)

#include "player.h"

void cRSubGoldy::Kill()
{
    FallingInit();
    transform.position.y = -8.0f;
}
