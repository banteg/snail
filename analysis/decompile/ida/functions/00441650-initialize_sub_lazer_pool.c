/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sub_lazer_pool @ 0x441650 */
/* selector: initialize_sub_lazer_pool */

// Clears the 20-slot SubLazer projectile pool (`cRSubLazerManager`) at `game + 0x356b00` by zeroing each slot state at +0x80 before a level build. Historically labelled `initialize_wall2_ambient_hazard_pool`; the Wall2 tile is the emitter, the slots themselves are projectiles.
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

