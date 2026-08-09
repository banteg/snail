// cRStarManager::Open @ 0x4342c0 (thiscall, ret 4)

#include "star_manager.h"
#include "runtime_config.h"

void* allocate_tracked_memory(int size, char* name);

void cRStarManager::Open(int star_count)
{
    entries = (StarManagerEntry*)allocate_tracked_memory(
        star_count * sizeof(StarManagerEntry),
        "StarField");
    count = star_count;
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
        state = 1;
        Init();
    } else {
        state = 0;
    }
}
