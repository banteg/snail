/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_ring_or_special_effect_particles @ 0x43e470 */
/* selector: initialize_ring_or_special_effect_particles */

// Maps ring or special-effect modes onto the ParticleRing, ParticleExplode, and ParticleSlow sprite families.
int __thiscall sub_43E470(_DWORD *this, int a2)
{
  _DWORD *v3; // ebp
  int v4; // esi
  int v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // edx
  int v8; // ecx
  _DWORD *v9; // edx
  int v10; // eax
  int result; // eax
  int v12; // [esp+10h] [ebp-14h]
  _DWORD v13[4]; // [esp+14h] [ebp-10h] BYREF

  v12 = 0;
  *(this + 32) = 1;
  *(this + 122) = 0;
  v3 = this + 26;
  v4 = (int)(this + 36);
  do
  {
    *(float *)(v4 + 20) = (double)v12 * 0.62831855;
    *(float *)(v4 + 24) = *(float *)(*(this + 116) + 56) * 0.10471976;
    *(_DWORD *)(v4 + 4) = this;
    *(_DWORD *)(v4 + 8) = *v3;
    *(_DWORD *)(v4 + 12) = v3[1];
    *(_DWORD *)(v4 + 16) = v3[2];
    *(_DWORD *)(v4 + 28) = 1067030938;
    v5 = *(this + 34);
    switch ( v5 )
    {
      case 4:
      case 5:
      case 8:
        *(_DWORD *)v4 = allocate_sprite(g_sprite_manager, *(_DWORD *)(*(this + 33) + 896), 135, -1, -1);
        *(this + 123) = 136;
        *(_DWORD *)(*(_DWORD *)v4 + 40) = 9;
        break;
      case 2:
      case 6:
        *(_DWORD *)v4 = allocate_sprite(g_sprite_manager, *(_DWORD *)(*(this + 33) + 896), 131, -1, -1);
        *(this + 123) = 132;
        *(_DWORD *)(*(_DWORD *)v4 + 40) = 13;
        break;
      case 3:
      case 7:
        *(_DWORD *)v4 = allocate_sprite(g_sprite_manager, *(_DWORD *)(*(this + 33) + 896), 133, -1, -1);
        *(this + 123) = 134;
        *(_DWORD *)(*(_DWORD *)v4 + 40) = 13;
        break;
    }
    v6 = set_color_rgba(v13, 1065353216, 1065353216, 1065353216, 1061997773);
    v7 = (_DWORD *)(*(_DWORD *)v4 + 44);
    *v7 = *v6;
    v7[1] = v6[1];
    v7[2] = v6[2];
    v7[3] = v6[3];
    v8 = *(_DWORD *)(*(_DWORD *)v4 + 4);
    BYTE1(v8) |= 8u;
    *(_DWORD *)(*(_DWORD *)v4 + 4) = v8;
    *(_DWORD *)(*(_DWORD *)v4 + 104) = 0;
    *(_DWORD *)(*(_DWORD *)v4 + 108) = 0;
    *(_DWORD *)(*(_DWORD *)v4 + 120) = 0;
    *(_DWORD *)(*(_DWORD *)v4 + 96) = 1060655596;
    *(_DWORD *)(*(_DWORD *)v4 + 100) = 1060655596;
    v9 = (_DWORD *)(*(_DWORD *)v4 + 72);
    *v9 = *v3;
    v9[1] = v3[1];
    v9[2] = v3[2];
    *(_DWORD *)(*(_DWORD *)v4 + 124) = *(_DWORD *)(v4 + 20);
    v10 = *(this + 34);
    if ( v10 == 3 || v10 == 6 )
      *(_DWORD *)(*(_DWORD *)v4 + 128) = 0;
    else
      *(float *)(*(_DWORD *)v4 + 128) = -*(float *)(v4 + 24);
    update_ring_or_special_effect_particle(v4);
    v4 += 32;
    result = ++v12;
  }
  while ( v12 < 10 );
  return result;
}

