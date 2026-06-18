/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_impact_sprite @ 0x415d80 */
/* selector: spawn_golb_impact_sprite */

// Allocates the short-lived impact sprite used when a Golb shot is killed or reaches a terminal collision point, seeded from the supplied world position.
char __thiscall sub_415D80(_DWORD *this, _DWORD *a2)
{
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  int v4; // ecx

  LOBYTE(v2) = byte_4DF934;
  if ( (byte_4DF934 & 0x10) != 0 )
  {
    v3 = allocate_sprite(g_sprite_manager, *(_DWORD *)(*(this + 158) + 896), 33, -1, -1);
    v4 = v3[1];
    BYTE1(v4) |= 8u;
    v3[1] = v4;
    v3[26] = 0;
    v3[21] = 0;
    v3[28] = 0;
    v3[22] = 1028443341;
    v3[30] = 0;
    v3[27] = 1029934648;
    v3[29] = 1062557014;
    v3[24] = 1056964608;
    v3[25] = 1065353216;
    v3[23] = 0;
    v2 = v3 + 18;
    *v2 = *a2;
    v2[1] = a2[1];
    v2[2] = a2[2];
  }
  return (char)v2;
}

