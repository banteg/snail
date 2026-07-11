// initialize_slug_hazard_runtime @ 0x408530 (thiscall, ret)

#include "slug_hazard_types.h"

extern void* g_slug_vtable; // off_497324 / data_497324

Slug* Slug::initialize_slug_hazard_runtime()
{
    initialize_renderable_bod();
    vtable = &g_slug_vtable;
    return this;
}
