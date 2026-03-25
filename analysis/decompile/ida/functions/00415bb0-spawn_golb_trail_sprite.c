/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_trail_sprite @ 0x415bb0 */
/* selector: spawn_golb_trail_sprite */

// Allocates one short-lived trail sprite for the straight-flight Golb family at the supplied world position. `update_golb_ai` emits it in a short three-point chain behind the projectile each tick.
_DWORD *__thiscall sub_415BB0(_DWORD *this, _DWORD *a2)
{
  _DWORD *result; // eax
  int v4; // ecx
  int v5; // ecx

  result = allocate_sprite(unk_790F30, *(_DWORD *)(*(this + 158) + 896), 33, -1, -1);
  v4 = result[1];
  BYTE1(v4) |= 8u;
  result[26] = 0;
  result[1] = v4;
  v5 = *(_DWORD *)(*(this + 158) + 824);
  if ( (v5 & 1) != 0 )
  {
    result[27] = 1047777085;
  }
  else if ( (v5 & 2) != 0 )
  {
    result[27] = 1051372203;
  }
  result[27] = 1057896676;
  result[28] = 0;
  result[29] = 0;
  result[24] = 1045220557;
  result[25] = 1022739087;
  result[23] = 0;
  result[22] = 0;
  result[21] = 0;
  result[30] = 0;
  result[18] = *a2;
  result[19] = a2[1];
  result[20] = a2[2];
  *result = *(this + 157);
  return result;
}

