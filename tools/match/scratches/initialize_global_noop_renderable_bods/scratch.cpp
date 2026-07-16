// initialize_global_noop_renderable_bods @ 0x406bd0 (cdecl)

#include "bod_types.h"

struct StartupNoopRenderableBod : RenderableBod {
    char unknown_080[0xc4 - sizeof(RenderableBod)];
};
typedef char StartupNoopRenderableBod_must_be_0xc4[
    (sizeof(StartupNoopRenderableBod) == 0xc4) ? 1 : -1];

extern StartupNoopRenderableBod g_startup_noop_renderable_bods[3]; // data_4b6fb4

void initialize_global_noop_renderable_bods()
{
    g_startup_noop_renderable_bods[0].initialize_renderable_bod();
    g_startup_noop_renderable_bods[0].vtable = &g_noop_runtime_callback_table;
    g_startup_noop_renderable_bods[1].initialize_renderable_bod();
    g_startup_noop_renderable_bods[1].vtable = &g_noop_runtime_callback_table;
    g_startup_noop_renderable_bods[2].initialize_renderable_bod();
    g_startup_noop_renderable_bods[2].vtable = &g_noop_runtime_callback_table;
}
