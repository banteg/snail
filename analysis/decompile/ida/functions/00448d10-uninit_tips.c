/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tips @ 0x448d10 */
/* selector: uninit_tips */

void __thiscall uninit_tips(_DWORD **this)
{
  _DWORD **v1; // esi
  int v2; // edi

  v1 = this + 14;
  v2 = 3;
  do
  {
    if ( *v1 == (_DWORD *)1 )
      kill_tip_widgets(v1);
    v1 += 8;
    --v2;
  }
  while ( v2 );
}

