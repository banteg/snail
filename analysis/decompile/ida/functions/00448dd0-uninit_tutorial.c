/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tutorial @ 0x448dd0 */
/* selector: uninit_tutorial */

void sub_448DD0()
{
  _DWORD **v0; // esi
  int v1; // edi

  v0 = (_DWORD **)((char *)MEMORY[0x4DF904] + 19820432);
  v1 = 3;
  do
  {
    if ( *v0 == (_DWORD *)1 )
      kill_tip_widgets(v0);
    v0 += 8;
    --v1;
  }
  while ( v1 );
}

