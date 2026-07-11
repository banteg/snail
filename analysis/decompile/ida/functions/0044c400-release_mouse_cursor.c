/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_mouse_cursor @ 0x44c400 */
/* selector: release_mouse_cursor */

// Leaves captured-mouse mode for the shared Game + 0x290 pointer state by restoring the saved authored cursor coordinates into the live lanes and clearing the capture byte.
void __thiscall release_mouse_cursor(MouseCursorState *mouse)
{
  float saved_y; // edx

  if ( mouse->captured == 1 )
  {
    saved_y = mouse->saved_y;
    mouse->live_x = mouse->saved_x;
    mouse->live_y = saved_y;
  }
  mouse->captured = 0;
}

