// reset_render_counters @ 0x414650 (cdecl)

#include "render_pipeline_state.h"

int reset_render_counters()
{
    g_render_triangle_count = 0;
    g_draw_primitive_call_count = 0;
    g_texture_bind_call_count = 0;
    return 0;
}
