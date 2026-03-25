/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_pause_menu @ 0x440600 */
/* selector: uninit_pause_menu */

int __thiscall sub_440600(_DWORD **this)
{
  kill_border(*this);
  kill_border(*(this + 1));
  kill_border(*(this + 2));
  return release_mouse_cursor((_DWORD *)MEMORY[0x4DF904] + 164);
}

