// initialize_intro_logo_renderable @ 0x408490 (thiscall, ret)

#include "intro_screen_runtime.h"

extern void* g_intro_logo_renderable_vtable; // off_497310 / data_497310

IntroLogoRenderable* IntroLogoRenderable::initialize_intro_logo_renderable()
{
    initialize_renderable_bod();
    vtable = &g_intro_logo_renderable_vtable;
    return this;
}
