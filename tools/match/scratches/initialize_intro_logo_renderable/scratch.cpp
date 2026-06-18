// initialize_intro_logo_renderable @ 0x408490 (thiscall, ret)

#include "bod_types.h"

extern void* g_intro_logo_renderable_vtable; // off_497310 / data_497310

class IntroLogoRenderable : public RenderableBod {
public:
    IntroLogoRenderable* initialize_intro_logo_renderable();

    char unknown_078[0x90 - 0x078];
};

IntroLogoRenderable* IntroLogoRenderable::initialize_intro_logo_renderable()
{
    initialize_renderable_bod();
    vtable = &g_intro_logo_renderable_vtable;
    return this;
}
