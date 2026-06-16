// update_font_wave_state @ 0x449ca0 (cdecl)

extern float g_font_wave_phase_a; // data_7772e8
extern float g_font_wave_step_a;  // data_777b28
extern float g_font_wave_phase_b; // data_7772ec
extern float g_font_wave_step_b;  // data_7772f4
extern char g_font_text_buffer[]; // data_753ce8
extern char* g_font_text_cursor;  // data_7772f0
extern int g_registered_font_count; // data_777b20
extern int g_font_queue_count; // data_777b24

void update_font_wave_state()
{
    float phase_a = g_font_wave_phase_a + g_font_wave_step_a;
    g_font_text_cursor = g_font_text_buffer;
    g_registered_font_count = 0;
    g_font_queue_count = 0;
    g_font_wave_phase_a = phase_a;
    if (g_font_wave_phase_a > 6.2831855f)
        g_font_wave_phase_a -= 6.2831855f;

    float phase_b = g_font_wave_phase_b + g_font_wave_step_b;
    g_font_wave_phase_b = phase_b;
    if (g_font_wave_phase_b > 6.2831855f)
        g_font_wave_phase_b -= 6.2831855f;
}
