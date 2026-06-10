/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_damage_gauge @ 0x440fd0 */
/* selector: update_damage_gauge */

// Advances the player contact-damage gauge controller at +0x3c4, smoothing its displayed fill, driving the warning or drain presentation, rendering the sprite-backed gauge widget, and applying state-2 drain. Native global gates now recovered here include the suspend byte `Game+0x74621`, warning-start blockers `Game+0x430199`/`Game+0x4301bc`, the `Game+0x42fde8 == 0.49f` drain transition gate, and state-2 exit gates `Game+0x4301c0`, `Game+0x42fe08`, and `Game+0x434064`; some writers remain unresolved.
void __thiscall sub_440FD0(int this)
{
  float *v2; // ecx
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int *v6; // eax
  int *v7; // eax
  int v8; // [esp+0h] [ebp-48h]
  int v9; // [esp+8h] [ebp-40h]
  float v10; // [esp+28h] [ebp-20h]
  float v11; // [esp+30h] [ebp-18h]
  int v12; // [esp+30h] [ebp-18h]
  int v13; // [esp+30h] [ebp-18h]
  float v14; // [esp+34h] [ebp-14h]
  _DWORD v15[4]; // [esp+38h] [ebp-10h] BYREF

  v2 = (float *)MEMORY[0x4DF904];
  if ( *((_BYTE *)MEMORY[0x4DF904] + 476705) )
    goto LABEL_26;
  *(float *)(this + 32) = (*(float *)(this + 28) - *(float *)(this + 32)) * 0.2 + *(float *)(this + 32);
  if ( *(float *)(this + 36) > 0.0 )
  {
    v3 = *(float *)(this + 40) + *(float *)(this + 36);
    *(float *)(this + 36) = v3;
    if ( v3 > 1.0 )
      *(_DWORD *)(this + 36) = 0;
  }
  if ( !*(_DWORD *)this )
  {
    if ( *(_DWORD *)(this + 28) == 1065353216 )
    {
      v2 = (float *)MEMORY[0x4DF904];
      if ( *((_BYTE *)&loc_430199 + (_DWORD)MEMORY[0x4DF904]) || *((_BYTE *)&loc_4301BC + (_DWORD)MEMORY[0x4DF904]) )
        goto LABEL_26;
      *(_DWORD *)this = 1;
      *(_DWORD *)(this + 16) = 0;
      *(_DWORD *)(this + 20) = 1042983595;
      start_warning((_DWORD *)MEMORY[0x4DF904] + 1097820);
    }
    goto LABEL_25;
  }
  if ( *(_DWORD *)this == 1 )
  {
    if ( *((_BYTE *)&loc_4301BC + (_DWORD)MEMORY[0x4DF904]) )
      *(_DWORD *)(this + 16) = 1065353216;
    v4 = *(float *)(this + 20) + *(float *)(this + 16);
    *(float *)(this + 16) = v4;
    if ( v4 >= 1.0 )
    {
      v2 = (float *)MEMORY[0x4DF904];
      if ( *((_DWORD *)MEMORY[0x4DF904] + 1097594) != 1056629064 )
        goto LABEL_26;
      *(_DWORD *)this = 2;
      play_voice_manager((int)unk_751498, 14, 0, -1);
    }
    goto LABEL_25;
  }
  if ( *(_DWORD *)this != 2 )
  {
LABEL_25:
    v2 = (float *)MEMORY[0x4DF904];
    goto LABEL_26;
  }
  change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 1, 0.2);
  apply_damage_gauge_delta((float *)this, -0.0016666667, 1);
  *(_DWORD *)(this + 24) = 5;
  v2 = (float *)MEMORY[0x4DF904];
  if ( *((_BYTE *)&loc_4301BC + (_DWORD)MEMORY[0x4DF904]) )
  {
    apply_damage_gauge_delta((float *)this, -0.0066666668, 0);
    v2 = (float *)MEMORY[0x4DF904];
  }
  if ( *(float *)(this + 28) == 0.0 && *((_DWORD *)v2 + 1097594) == 1056629064
    || v2[1097840] > 0.0
    || v2[1097602] > 0.0
    || *((_DWORD *)v2 + 1101849) )
  {
    *(_DWORD *)this = 0;
    stop_warning((_DWORD **)MEMORY[0x4DF904] + 1097820);
    stop_warning_sample();
    goto LABEL_25;
  }
LABEL_26:
  if ( *(float *)(this + 32) <= 0.99900001 )
  {
    if ( *(float *)(this + 32) >= 0.0099999998 )
      v14 = 351.0 - *(float *)(this + 32) * 308.0;
    else
      v14 = 396.0;
  }
  else
  {
    v14 = 0.0;
  }
  if ( !*((_BYTE *)v2 + 476705) )
    *(float *)(this + 4) = *(float *)(this + 8) + *(float *)(this + 4);
  if ( *(float *)(this + 4) > 1.0 )
    *(float *)(this + 4) = *(float *)(this + 4) - 1.0;
  if ( *(float *)(this + 32) > 0.89999998 || *(_DWORD *)this )
  {
    if ( *(float *)(this + 32) <= 0.89999998 )
    {
      if ( *(float *)(this + 32) < 0.1 )
      {
        v11 = *(float *)(this + 32) * 10.0;
        goto LABEL_43;
      }
    }
    else if ( !*(_DWORD *)this )
    {
      v11 = (*(float *)(this + 32) - 0.89999998) * 10.0;
LABEL_43:
      v10 = *(float *)(this + 4) * 6.2831855;
      *(float *)&v12 = v11 - (sine(v10) + 1.0) * 0.5 * v11 * 0.5;
      v5 = set_color_rgba(v15, 1065353216, 1065353216, 1065353216, v12);
      queue_axis_aligned_textured_quad_uv(
        91,
        1141637120,
        1116471296,
        1115684864,
        1137049600,
        0x1000000,
        v5,
        0,
        0,
        1065353216,
        1061552128,
        3,
        0);
      goto LABEL_44;
    }
    v11 = 1.0;
    goto LABEL_43;
  }
LABEL_44:
  *(float *)&v13 = v14 * 0.001953125;
  v6 = set_color_rgba(v15, 1065353216, 1065353216, 1065353216, 1065353216);
  queue_axis_aligned_textured_quad_uv(
    89,
    1141637120,
    1116471296,
    1115684864,
    SLODWORD(v14),
    0x1000000,
    v6,
    0,
    0,
    1065353216,
    v13,
    3,
    0);
  v7 = set_color_rgba(v15, 1065353216, 1065353216, 1065353216, 1065353216);
  *(float *)&v9 = 396.0 - v14;
  *(float *)&v8 = v14 + 70.0;
  queue_axis_aligned_textured_quad_uv(
    90,
    1141637120,
    v8,
    1115684864,
    v9,
    0x1000000,
    v7,
    0,
    v13,
    1065353216,
    1061552128,
    3,
    0);
}

