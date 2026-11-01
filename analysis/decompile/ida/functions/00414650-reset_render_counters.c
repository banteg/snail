/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: reset_render_counters @ 0x414650 */
/* selector: reset_render_counters */

// Clears the per-frame renderer counters for submitted triangles, DrawPrimitive calls, and texture binds before render_game_frame starts.
int32_t __cdecl reset_render_counters()
{
  g_render_triangle_count = 0;
  g_draw_primitive_call_count = 0;
  g_texture_bind_call_count = 0;
  return 0;
}
