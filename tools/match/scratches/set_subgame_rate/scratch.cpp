// set_subgame_rate @ 0x4404c0 (thiscall, ret 0x4)

#include "subgame_runtime.h"

void cRSubGame::set_subgame_rate(float rate_value)
{
    base_rate = rate_value;
    subgame_rate = rate_value;
}
