// set_subgame_rate @ 0x4404c0 (thiscall, ret 0x4)

#include "subgame_runtime.h"

void SubgameRuntime::set_subgame_rate(float rate_value)
{
    base_rate = rate_value;
    subgame_rate = rate_value;
}
