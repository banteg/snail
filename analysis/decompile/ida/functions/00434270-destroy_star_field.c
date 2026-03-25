/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_star_field @ 0x434270 */
/* selector: destroy_star_field */

// Destroys the live star-field sprite pool, tears down its per-entry records, and returns the controller to state 0.
int __thiscall sub_434270(int *this)
{
  int v2; // ebx
  int result; // eax
  int v4; // edi

  v2 = 0;
  result = *(this + 16);
  if ( result <= 0 )
  {
    *(this + 14) = 0;
  }
  else
  {
    v4 = 0;
    do
    {
      *(_DWORD *)(*(this + 15) + v4) = 0;
      kill_sprite(*(_DWORD *)(*(this + 15) + v4 + 28));
      result = *(this + 16);
      ++v2;
      v4 += 44;
    }
    while ( v2 < result );
    *(this + 14) = 0;
  }
  return result;
}

