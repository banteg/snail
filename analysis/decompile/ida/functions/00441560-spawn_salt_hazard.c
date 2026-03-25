/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_salt_hazard @ 0x441560 */
/* selector: spawn_salt_hazard */

// Allocates one live salt.x hazard slot from the 40-slot pool and seeds its runtime state.
int __thiscall sub_441560(_DWORD *this, _DWORD *a2)
{
  int result; // eax
  _DWORD *i; // edx
  char *v4; // esi
  char *v5; // eax
  int v6; // eax
  float v7; // [esp+0h] [ebp-Ch]

  result = 0;
  for ( i = this + 32; *i; i += 38 )
  {
    if ( ++result >= 40 )
      return result;
  }
  v4 = (char *)(this + 38 * result);
  *((_DWORD *)v4 + 32) = 1;
  *((_DWORD *)v4 + 35) = 0;
  *((float *)v4 + 36) = *((float *)MEMORY[0x4DF904] + 119188) * 0.033333335;
  *((_DWORD *)v4 + 26) = *a2;
  *((_DWORD *)v4 + 27) = a2[1];
  *((_DWORD *)v4 + 28) = a2[2];
  set_matrix_rotation_identity((_DWORD *)v4 + 14);
  v7 = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
  rotate_matrix_world_y((float *)v4 + 14, v7);
  v4[148] = 1;
  v5 = (char *)MEMORY[0x4DF904] + 3973668;
  if ( (*((_DWORD *)v4 + 1) & 0x200) != 0 )
    return report_errorf(aListAddafter);
  *((_DWORD *)v4 + 2) = v5;
  *((_DWORD *)v4 + 3) = *((_DWORD *)v5 + 3);
  *((_DWORD *)v5 + 3) = v4;
  v6 = *((_DWORD *)v4 + 3);
  if ( v6 )
    *(_DWORD *)(v6 + 8) = v4;
  result = *((_DWORD *)v4 + 1) | 0x200;
  *((_DWORD *)v4 + 1) = result;
  return result;
}

