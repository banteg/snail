/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: emit_ring_star_shower @ 0x43e690 */
/* selector: emit_ring_star_shower */

void __thiscall emit_ring_star_shower(float *particle, int owner)
{
  float *star; // esi
  int flags; // eax
  double star_velocity_y; // st7
  float *source_position; // eax
  int source_z; // eax
  float v9; // [esp+0h] [ebp-24h]
  float v10; // [esp+0h] [ebp-24h]
  float v11; // [esp+Ch] [ebp-18h]
  float v12; // [esp+10h] [ebp-14h]
  float v13; // [esp+18h] [ebp-Ch]

  if ( (byte_4DF934 & 0x10) == 0 )
    return;
  star = (float *)allocate_sprite(unk_790F30, *(_DWORD *)(owner + 896), *(_DWORD *)(*((_DWORD *)particle + 1) + 492), -1, -1);
  flags = *((_DWORD *)star + 1);
  star[26] = 0.0;
  BYTE1(flags) |= 8u;
  star[27] = 0.1111111;
  *((_DWORD *)star + 1) = flags;
  star[24] = 0.40000001;
  star[25] = 0.2;
  v9 = *(particle + 5) + 1.0471976;
  v13 = sine(v9) * *(particle + 7);
  v10 = *(particle + 5) + 1.0471976;
  v11 = v13 * 0.30000001;
  star_velocity_y = cosine(v10) * *(particle + 7) * 0.30000001;
  star[21] = v11;
  v12 = star_velocity_y;
  star[22] = v12;
  star[23] = 0.0;
  source_position = (float *)(*(_DWORD *)particle + 72);
  star[18] = *source_position;
  star[19] = source_position[1];
  source_z = *((_DWORD *)source_position + 2);
  star[30] = 0.0;
  *((_DWORD *)star + 20) = source_z;
}
