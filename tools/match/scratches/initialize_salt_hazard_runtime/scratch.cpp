// initialize_salt_hazard_runtime @ 0x408630 (thiscall, ret)

#include "bod_types.h"
#include "salt_hazard_types.h"

extern void* g_salt_vtable; // off_497340 / data_497340

Salt* Salt::initialize_salt_hazard_runtime()
{
    initialize_renderable_bod();
    vtable = &g_salt_vtable;
    return this;
}
