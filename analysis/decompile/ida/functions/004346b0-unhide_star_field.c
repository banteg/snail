/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: unhide_star_field @ 0x4346b0 */
/* selector: unhide_star_field */

// Sets bit 0x40 on every live star-field sprite, re-enabling the background streak pass without rebuilding the controller.
int __thiscall sub_4346B0(int *this)
{
  int result; // eax
  int v2; // edx
  int v3; // esi
  int v4; // eax

  result = *(this + 14);
  if ( result )
  {
    result = *(this + 16);
    v2 = 0;
    if ( result > 0 )
    {
      v3 = 0;
      do
      {
        v3 += 44;
        v4 = *(_DWORD *)(*(this + 15) + v3 - 16);
        ++v2;
        *(_DWORD *)(v4 + 4) |= 0x40u;
        result = *(this + 16);
      }
      while ( v2 < result );
    }
  }
  return result;
}

