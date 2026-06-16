// initialize_salt_hazard_runtime @ 0x408630 (thiscall, ret)

#include "bod_types.h"
#include "salt_hazard_types.h"

extern void* g_salt_hazard_vtable; // off_497340 / data_497340

SaltHazardSlot* SaltHazardSlot::initialize_salt_hazard_runtime()
{
    ((RenderableBod*)this)->initialize_renderable_bod();
    unknown_00 = (int)&g_salt_hazard_vtable;
    return this;
}
