/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_skirt_color @ 0x442120 */
/* selector: get_track_skirt_color */

// Builds the shared RGBA skirt or fringe colour from the current track colour scalars and a fixed alpha, then copies it into one runtime row or fringe object. Cross-port Android symbols match this helper to `cRSubGame::GetSkirtColour(tColourSmall)`.
_DWORD *__thiscall sub_442120(int *this, _DWORD *a2)
{
  _DWORD *v2; // ecx
  _DWORD v4[4]; // [esp+4h] [ebp-10h] BYREF

  v2 = set_color_rgba(v4, *(this + 442448), *(this + 442449), *(this + 442450), 1053609165);
  *a2 = *v2;
  a2[1] = v2[1];
  a2[2] = v2[2];
  a2[3] = v2[3];
  return a2;
}

