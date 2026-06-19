# update_mouse_authored_scale @ 0x44bbd0

Computes screen-to-authored mouse scale factors from the cached Win32 clip
rectangle. The x factor lives at `g_mouse_screen_to_authored_x_scale`
(`data_777d6c`), the y factor at `g_mouse_screen_to_authored_y_scale`
(`data_777d68`), and `convert_mouse_screen_xy` consumes both.

2026-06-20 type consolidation: the cached clip rectangle now uses
`include/rect.h`. Focused rerun remains exact at 100.00%, 17/17 instructions,
with 6 masked operands OK.
