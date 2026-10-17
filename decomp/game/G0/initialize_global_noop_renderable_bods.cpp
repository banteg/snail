// initialize_global_noop_renderable_bods @ 0x406bd0 (compiler-generated initializer)

#include "bod_types.h"

struct StartupNoopRenderableBod : RenderableBod {
    StartupNoopRenderableBod() { vtable = &g_noop_runtime_callback_table; }

    char unknown_080[0xc4 - sizeof(RenderableBod)];
};
typedef char StartupNoopRenderableBod_must_be_0xc4[
    (sizeof(StartupNoopRenderableBod) == 0xc4) ? 1 : -1];

struct StartupNoopRenderableBods {
    StartupNoopRenderableBod first;
    StartupNoopRenderableBod second;
    StartupNoopRenderableBod third;
};

StartupNoopRenderableBods g_startup_noop_renderable_bods; // 0x4b6fb4
