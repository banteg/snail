// initialize_garbage_hazard @ 0x408550 (thiscall, ret)

#include "bod_types.h"

extern void* g_garbage_hazard_vtable; // off_497328 / data_497328

class GarbageHazardRuntime : public RenderableBod {
public:
    GarbageHazardRuntime* initialize_garbage_hazard();
};

GarbageHazardRuntime* GarbageHazardRuntime::initialize_garbage_hazard()
{
    initialize_renderable_bod();
    vtable = &g_garbage_hazard_vtable;
    return this;
}
