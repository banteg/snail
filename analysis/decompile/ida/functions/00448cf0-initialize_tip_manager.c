/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip_manager @ 0x448cf0 */
/* selector: initialize_tip_manager */

_DWORD *__thiscall sub_448CF0(_DWORD *this)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 14;
  v2 = 3;
  do
  {
    *result = 0;
    result += 8;
    --v2;
  }
  while ( v2 );
  return result;
}

