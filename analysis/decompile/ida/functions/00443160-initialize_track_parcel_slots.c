/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_parcel_slots @ 0x443160 */
/* selector: initialize_track_parcel_slots */

// Clears the live state on the 50-slot gameplay parcel array and reseeds each slot's `game` pointer before any authored parcel placements are spawned for the current level.
_DWORD *__thiscall sub_443160(_DWORD *this)
{
  _DWORD *result; // eax
  int v2; // ecx

  result = this + 15;
  v2 = 50;
  do
  {
    *(result - 1) = 0;
    *result = (char *)MEMORY[0x4DF904] + 476696;
    result += 35;
    --v2;
  }
  while ( v2 );
  return result;
}

