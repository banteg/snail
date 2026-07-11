/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_mouse_authored_scale @ 0x44bbd0 */
/* selector: update_mouse_authored_scale */

// Computes the shared mouse screen-to-authored X/Y scale factors from the cached clip rectangle and the supplied authored width and height. convert_mouse_screen_xy consumes those scales.
int __cdecl update_mouse_authored_scale(float authored_width, float authored_height)
{
  g_mouse_screen_to_authored_x_scale = authored_width / (double)(g_mouse_clip_rect.right - g_mouse_clip_rect.left);
  g_mouse_screen_to_authored_y_scale = authored_height / (double)(g_mouse_clip_rect.bottom - g_mouse_clip_rect.top);
  return g_mouse_clip_rect.top;
}
