// initialize_global_noop_renderable_bods @ 0x406bd0 (compiler-generated initializer)

#include "bod_types.h"

struct StartupNoopRenderableBod : RenderableBod {
    StartupNoopRenderableBod() { vtable = &g_noop_runtime_callback_table; }

    char unknown_080[0xc4 - sizeof(RenderableBod)];
};
typedef char StartupNoopRenderableBod_must_be_0xc4[
    (sizeof(StartupNoopRenderableBod) == 0xc4) ? 1 : -1];

StartupNoopRenderableBod g_startup_noop_renderable_bod_0, // 0x4b6fb4
    g_startup_noop_renderable_bod_1,                      // 0x4b7078
    g_startup_noop_renderable_bod_2;                      // 0x4b713c
