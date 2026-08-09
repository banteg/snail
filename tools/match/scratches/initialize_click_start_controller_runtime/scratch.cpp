// initialize_click_start_controller_runtime @ 0x408670 (thiscall, ret)
// Authored owner: cRClickStart::cRClickStart().

#include "click_start.h"

extern void* g_click_start_controller_vtable; // off_497348 / data_497348

cRClickStart::cRClickStart()
{
    initialize_renderable_bod();
    vtable = &g_click_start_controller_vtable;
}
