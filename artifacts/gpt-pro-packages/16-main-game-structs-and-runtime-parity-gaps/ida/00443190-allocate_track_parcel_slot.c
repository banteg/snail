/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sub_443190 @ 0x443190 */
/* selector: 0x443190 */

char *__thiscall sub_443190(_DWORD *this)
{
  int v1; // eax
  _DWORD *i; // edx

  v1 = 0;
  for ( i = this + 14; *i; i += 35 )
  {
    if ( ++v1 >= 50 )
    {
      sub_431CC0(aTooManyParcels);
      return nullptr;
    }
  }
  return (char *)(this + 35 * v1);
}

