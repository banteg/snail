// open_star_field @ 0x4342c0 (thiscall, ret 4)

#include "star_manager.h"
#include "runtime_config.h"

void* allocate_tracked_memory(int size, char* name);

void StarManager::open_star_field(int star_count)
{
    entries = (StarManagerEntry*)allocate_tracked_memory(
        star_count * sizeof(StarManagerEntry),
        "StarField");
    count = star_count;
    if ((g_runtime_config.render_flags & RUNTIME_RENDER_STAR_FIELD) != 0) {
        state = 1;
        initialize_star_field();
    } else {
        state = 0;
    }
}
