// initialize_anim_manager @ 0x4447c0 (thiscall, returns 0)

#include "anim_manager.h"

int AnimManager::initialize_anim_manager()
{
    progress = 0.0f;
    progress_step = 0.0f;
    state = 0;
    completed = 0;
    return 0;
}
