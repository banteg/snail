/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip_manager @ 0x448d80 */
/* selector: update_tip_manager */

void __thiscall update_tip_manager(_DWORD *this)
{
  _DWORD *v1; // esi
  int v2; // edi

  v1 = this + 14;
  v2 = 3;
  do
  {
    if ( *v1 == 1 )
      update_tip((int)v1);
    v1 += 8;
    --v2;
  }
  while ( v2 );
}

