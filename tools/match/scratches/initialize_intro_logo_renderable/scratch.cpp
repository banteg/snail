// initialize_intro_logo_renderable @ 0x408490 (thiscall, ret)

#include "intro_screen_runtime.h"

extern void* g_logo_letter_vtable; // off_497310 / data_497310

LogoLetter* LogoLetter::initialize_intro_logo_renderable()
{
    initialize_renderable_bod();
    vtable = &g_logo_letter_vtable;
    return this;
}
