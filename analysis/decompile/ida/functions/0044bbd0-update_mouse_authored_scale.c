/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_mouse_authored_scale @ 0x44bbd0 */
/* selector: update_mouse_authored_scale */

// Computes the shared mouse screen-to-authored X/Y scale factors from the cached clip rectangle and the supplied authored width and height. convert_mouse_screen_xy consumes those scales.
int __cdecl update_mouse_authored_scale(float a1, float a2)
{
  g_mouse_screen_to_authored_x_scale = a1 / (double)(dword_777B2C[153] - dword_777B2C[151]);
  g_mouse_screen_to_authored_y_scale = a2 / (double)(dword_777B2C[154] - dword_777B2C[152]);
  return dword_777B2C[152];
}
