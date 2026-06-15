// initialize_sub_lazer_runtime @ 0x408610 (thiscall, ret)

#include "bod_types.h"

extern void* g_sub_lazer_vtable; // off_49733c / data_49733c

class SubLazerRuntime : public RenderableBod {
public:
    SubLazerRuntime* initialize_sub_lazer_runtime();
};

SubLazerRuntime* SubLazerRuntime::initialize_sub_lazer_runtime()
{
    initialize_renderable_bod();
    vtable = &g_sub_lazer_vtable;
    return this;
}
