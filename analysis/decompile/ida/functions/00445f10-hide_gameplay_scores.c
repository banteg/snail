/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: hide_gameplay_scores @ 0x445f10 */
/* selector: hide_gameplay_scores */

void __thiscall sub_445F10(_DWORD *this)
{
  _DWORD *v2; // ecx
  _DWORD *v3; // ecx

  v2 = (_DWORD *)*(this + 880355);
  if ( v2 )
    hide_border_init(v2);
  v3 = (_DWORD *)*(this + 880354);
  if ( v3 )
    hide_border_init(v3);
}

