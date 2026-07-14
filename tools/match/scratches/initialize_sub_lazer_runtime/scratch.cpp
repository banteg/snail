// initialize_sub_lazer_runtime @ 0x408610 (thiscall, ret)

#include "bod_types.h"
#include "sub_lazer_types.h"

extern void* g_sub_lazer_vtable; // off_49733c / data_49733c

SubLazer* SubLazer::initialize_sub_lazer_runtime()
{
    initialize_renderable_bod();
    vtable = &g_sub_lazer_vtable;
    return this;
}
