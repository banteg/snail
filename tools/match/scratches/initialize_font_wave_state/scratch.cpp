// initialize_font_wave_state @ 0x449c70 (cdecl, ret)

extern float g_font_wave_phase_a; // data_7772e8
extern float g_font_wave_step_a;  // data_777b28
extern float g_font_wave_phase_b; // data_7772ec
extern float g_font_wave_step_b;  // data_7772f4

void initialize_font_wave_state()
{
    g_font_wave_phase_a = 0;
    g_font_wave_step_a = 0.104719758f;
    g_font_wave_phase_b = 0;
    g_font_wave_step_b = 0.080553666f;
}
