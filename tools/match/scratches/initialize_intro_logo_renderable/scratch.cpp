// cRLogoLetter::cRLogoLetter @ 0x408490 (thiscall, ret)

#include "intro_screen_runtime.h"

extern void* g_logo_letter_vtable; // off_497310 / data_497310

cRLogoLetter::cRLogoLetter()
{
    initialize_renderable_bod();
    vtable = &g_logo_letter_vtable;
}
