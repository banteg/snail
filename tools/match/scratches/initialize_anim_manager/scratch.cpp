// cRAnimManager::Init / initialize_anim_manager @ 0x4447c0 (thiscall, ret)

#include "anim_manager.h"

void AnimManager::initialize_anim_manager()
{
    progress = 0.0f;
    progress_step = 0.0f;
    state = 0;
    completed = 0;
}
