// open_star_field @ 0x4342c0 (thiscall, ret 4)

#include "star_field.h"

void* allocate_tracked_memory(int size, char* name);
extern unsigned char g_render_flags; // byte_4df934

void StarField::open_star_field(int star_count)
{
    entries = (StarFieldEntry*)allocate_tracked_memory(
        star_count * sizeof(StarFieldEntry),
        "StarField");
    count = star_count;
    if ((g_render_flags & 4) != 0) {
        state = 1;
        initialize_star_field();
    } else {
        state = 0;
    }
}
