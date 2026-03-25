/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_voice_manager @ 0x448ec0 */
/* selector: reset_voice_manager */

_DWORD *__thiscall sub_448EC0(_DWORD *this)
{
  _DWORD *result; // eax
  int v2; // ecx

  *(this + 96) = 0;
  result = this + 4;
  v2 = 16;
  do
  {
    *result = 0;
    result += 6;
    --v2;
  }
  while ( v2 );
  return result;
}

