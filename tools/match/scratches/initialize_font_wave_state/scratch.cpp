// initialize_font_wave_state @ 0x449c70 (cdecl, ret)

#include "font_system.h"

void initialize_font_wave_state()
{
    g_font_wave_phase_a = 0;
    g_font_wave_step_a = 0.104719758f;
    g_font_wave_phase_b = 0;
    g_font_wave_step_b = 0.080553666f;
}
