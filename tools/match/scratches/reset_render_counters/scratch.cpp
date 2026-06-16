// reset_render_counters @ 0x414650 (cdecl)

extern int g_render_triangle_count;       // data_4f7450
extern int g_draw_primitive_call_count;   // data_503170
extern int g_texture_bind_call_count;     // data_5031c0

int reset_render_counters()
{
    g_render_triangle_count = 0;
    g_draw_primitive_call_count = 0;
    g_texture_bind_call_count = 0;
    return 0;
}
