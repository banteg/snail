// initialize_salt_hazard_runtime @ 0x408630 (thiscall, ret)

#include "bod_types.h"

extern void* g_salt_hazard_vtable; // off_497340 / data_497340

class SaltHazardRuntime : public RenderableBod {
public:
    SaltHazardRuntime* initialize_salt_hazard_runtime();
};

SaltHazardRuntime* SaltHazardRuntime::initialize_salt_hazard_runtime()
{
    initialize_renderable_bod();
    vtable = &g_salt_hazard_vtable;
    return this;
}
