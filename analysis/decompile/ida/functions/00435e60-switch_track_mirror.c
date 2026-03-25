/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: switch_track_mirror @ 0x435e60 */
/* selector: switch_track_mirror */

bool __thiscall sub_435E60(int this)
{
  double v2; // st7
  bool result; // al

  v2 = random_float_below(1.0);
  result = v2 > 0.5;
  if ( v2 > 0.5 == *(_BYTE *)(this + 2) )
    ++*(_DWORD *)(this + 4);
  else
    *(_DWORD *)(this + 4) = 0;
  if ( *(int *)(this + 4) >= 4 )
  {
    *(_DWORD *)(this + 4) = 0;
    result = v2 <= 0.5;
  }
  *(_BYTE *)(this + 2) = result;
  return result;
}

