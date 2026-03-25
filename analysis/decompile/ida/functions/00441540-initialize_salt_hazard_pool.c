/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_salt_hazard_pool @ 0x441540 */
/* selector: initialize_salt_hazard_pool */

_DWORD *__thiscall sub_441540(_DWORD *this)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 32;
  v2 = 40;
  do
  {
    *result = 0;
    result += 38;
    --v2;
  }
  while ( v2 );
  return result;
}

