/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_wall2_ambient_hazard_pool @ 0x441650 */
/* selector: initialize_wall2_ambient_hazard_pool */

// Clears the 20-slot `Wall2` ambient-hazard pool by zeroing each slot state at +0x80 before a level build.
_DWORD *__thiscall sub_441650(_DWORD *this)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 32;
  v2 = 20;
  do
  {
    *result = 0;
    result += 44;
    --v2;
  }
  while ( v2 );
  return result;
}

