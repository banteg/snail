/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_mouse_cursor @ 0x44c400 */
/* selector: release_mouse_cursor */

// Leaves captured-mouse mode for the shared Game + 0x290 pointer state by restoring the saved authored cursor coordinates into the live lanes and clearing the capture byte.
int __thiscall sub_44C400(_DWORD *this)
{
  int result; // eax
  int v2; // edx

  if ( *(_BYTE *)this == 1 )
  {
    result = *(this + 3);
    v2 = *(this + 4);
    *(this + 1) = result;
    *(this + 2) = v2;
  }
  *(_BYTE *)this = 0;
  return result;
}

