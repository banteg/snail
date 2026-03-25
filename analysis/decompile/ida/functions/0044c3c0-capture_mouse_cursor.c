/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: capture_mouse_cursor @ 0x44c3c0 */
/* selector: capture_mouse_cursor */

// Enters captured-mouse mode for the shared Game + 0x290 pointer state: snapshots the current authored cursor coordinates, warps controller 0 there through click_mouse_screen, and marks the capture byte active.
void __thiscall sub_44C3C0(float *this)
{
  double v2; // st7
  double v3; // st6

  if ( !*(_BYTE *)this )
  {
    v2 = *(this + 1);
    *(this + 3) = *(this + 1);
    v3 = *(this + 2);
    *(this + 4) = *(this + 2);
    click_mouse_screen(0, (__int64)v2, (__int64)v3);
    *((_BYTE *)this + 20) = 1;
  }
  *(_BYTE *)this = 1;
}

