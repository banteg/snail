/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: capture_mouse_cursor @ 0x44c3c0 */
/* selector: capture_mouse_cursor */

// Enters captured-mouse mode for the shared Game + 0x290 pointer state: snapshots the current authored cursor coordinates, warps controller 0 there through click_mouse_screen, and marks the capture byte active.
void __thiscall capture_mouse_cursor(MouseCursorState *mouse)
{
  double live_x; // st7
  double live_y; // st6

  if ( !mouse->captured )
  {
    live_x = mouse->live_x;
    mouse->saved_x = mouse->live_x;
    live_y = mouse->live_y;
    mouse->saved_y = mouse->live_y;
    click_mouse_screen(0, (__int64)live_x, (__int64)live_y);
    mouse->suppress_next_draw = 1;
  }
  mouse->captured = 1;
}

