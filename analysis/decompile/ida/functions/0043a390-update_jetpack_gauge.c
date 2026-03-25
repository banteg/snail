/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_jetpack_gauge @ 0x43a390 */
/* selector: update_jetpack_gauge */

// Advances the player jetpack countdown or warning controller at +0x2750: animates the near-empty meter, triggers the auto-shutoff branch when the current runtime cell carries flag 0x80, and clears the controller once the jetpack gauge drains. Cross-port Android and iOS symbols still name the owning class `cRDamageGuage::AI()`.
void __thiscall sub_43A390(int this)
{
  double v3; // st7
  char v4; // c0
  double v5; // st7
  float v6; // eax
  int v7; // [esp-4h] [ebp-18h]
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+0h] [ebp-14h]
  float v10; // [esp+0h] [ebp-14h]
  float v11; // [esp+0h] [ebp-14h]
  float v12; // [esp+Ch] [ebp-8h]

  if ( *(_DWORD *)(this + 12) == 1 )
  {
    v12 = *(float *)(this + 4) + *(float *)this;
    *(float *)this = v12;
    if ( v12 > 1.0 || (double)(*(_DWORD *)(*(_DWORD *)(this + 512) + 88) - 5) < *(float *)(*(_DWORD *)(this + 16) + 112) )
    {
      end_jetpack_hover((float *)this);
      if ( *(float *)this <= 0.94 )
        set_snail_jetpack((_DWORD *)MEMORY[0x4DF904] + 1100224, 0);
      *(_DWORD *)(this + 12) = 0;
      *(_DWORD *)(this + 28) = 0;
      *(_DWORD *)(this + 24) = 0;
      *(_DWORD *)(this + 20) = 0;
    }
    else
    {
      v3 = v12;
      if ( v4 )
      {
        *(float *)(this + 528) = v3 * 10.0;
      }
      else if ( v3 <= 0.94 )
      {
        *(_DWORD *)(this + 528) = 1065353216;
        if ( (BYTE1(*(_DWORD *)get_track_runtime_cell_at_world_z(
                                 (char *)MEMORY[0x4DF904] + 476696,
                                 (int)MEMORY[0x4DF904] + 4390372))
            & 0x80u) != 0 )
        {
          *(_DWORD *)this = 1064346583;
          sub_449C00();
        }
      }
      else
      {
        *(float *)(this + 528) = (1.0 - v12) * 16.666668;
        if ( v12 - *(float *)(this + 4) <= 0.94 )
        {
          set_snail_jetpack((_DWORD *)MEMORY[0x4DF904] + 1100224, 0);
          uninit_jet_particles((int *)this);
        }
      }
      v8 = *(float *)(this + 528) * 3.1415927;
      *(float *)(this + 528) = 1.0 - (cosine(v8) + 1.0) * 0.5;
      v9 = *(float *)this * 25.132742;
      *(float *)(this + 20) = sine(v9) * *(float *)(this + 528) * 0.25;
      v10 = *(float *)this * 37.699112;
      v5 = sine(v10);
      v6 = *(float *)(this + 528);
      v11 = *(float *)this;
      v7 = *(_DWORD *)(this + 16) + 104;
      *(_DWORD *)(this + 28) = 0;
      *(float *)(this + 524) = v6;
      *(float *)(this + 24) = (v5 * 0.25 + 1.0) * v6;
      spawn_track_speedup(v7, LODWORD(v11));
    }
  }
}

