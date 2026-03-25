/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_tooltip @ 0x403be0 */
/* selector: reset_tooltip */

void __thiscall sub_403BE0(int this)
{
  if ( *(_DWORD *)(this + 4) != 2 )
  {
    if ( *(_DWORD *)(this + 4) != 3 )
      return;
    kill_border(*(_DWORD **)(this + 24));
    *(_DWORD *)(this + 24) = 0;
  }
  *(_DWORD *)(this + 4) = 1;
}

