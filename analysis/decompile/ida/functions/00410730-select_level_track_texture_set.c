/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: select_level_track_texture_set @ 0x410730 */
/* selector: select_level_track_texture_set */

int __thiscall sub_410730(int *this, int a2)
{
  int v3; // edi
  int result; // eax

  switch ( a2 )
  {
    case 0:
      v3 = 0;
      break;
    case 1:
      v3 = 1;
      break;
    case 2:
      v3 = 2;
      break;
    case 3:
      v3 = 3;
      break;
    case 5:
      v3 = (__int64)random_float_below(4.0);
      break;
    default:
      v3 = a2;
      break;
  }
  result = *(this + 8);
  if ( v3 != result )
  {
    sub_430D90(unk_4B7648, *(this + v3), *(this + result));
    result = sub_430D90(unk_4B7648, *(this + v3 + 4), *(this + *(this + 8) + 4));
    *(this + 8) = v3;
  }
  return result;
}

