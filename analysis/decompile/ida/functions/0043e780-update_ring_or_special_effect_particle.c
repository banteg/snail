/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */
/* selector: update_ring_or_special_effect_particle */

// Advances one child sprite in the bullet-owned ring or special-effect halo, updating its circular phase around the parent projectile and refreshing the live effect position before optional star-shower emission.
char __thiscall sub_43E780(int this)
{
  double v2; // st7
  int v3; // eax
  double v4; // st7
  int v5; // ecx
  double v6; // st7
  int v7; // eax
  float v9; // [esp+4h] [ebp-10h]
  float v10; // [esp+8h] [ebp-Ch]
  float v11; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  if ( *(_DWORD *)(*(_DWORD *)(this + 4) + 136) != 3 )
    *(float *)(this + 20) = *(float *)(this + 24) + *(float *)(this + 20);
  if ( *(float *)(this + 20) > 6.2831855 )
    *(float *)(this + 20) = *(float *)(this + 20) - 6.2831855;
  v9 = cosine(*(float *)(this + 20)) * *(float *)(this + 28);
  v2 = sine(*(float *)(this + 20));
  v3 = *(_DWORD *)(this + 4);
  v4 = v2 * *(float *)(this + 28) + *(float *)(v3 + 104);
  v3 += 104;
  v5 = *(_DWORD *)this + 72;
  v10 = v4;
  v6 = v9 + *(float *)(v3 + 4);
  v12 = *(_DWORD *)(v3 + 8);
  *(float *)v5 = v10;
  v11 = v6;
  *(float *)(v5 + 4) = v11;
  *(_DWORD *)(v5 + 8) = v12;
  v7 = *(_DWORD *)(this + 4);
  if ( !*(_DWORD *)(v7 + 488) )
    LOBYTE(v7) = emit_ring_star_shower((float *)this, *(_DWORD *)(v7 + 132));
  return v7;
}

