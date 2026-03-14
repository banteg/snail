/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cutscene @ 0x4428d0 */
/* selector: initialize_cutscene */

// Seeds and polls the player-side cutscene controller from the live player transform, cached effect anchors, and completion handoff state; Windows `update_subgoldy` calls it every tick, and it dispatches `update_cutscene` whenever the controller is active. Cross-port Android symbols still match the helper family to `cRCutScene::Init()`.
void __thiscall sub_4428D0(int this)
{
  int v2; // ecx
  int v3; // ecx
  const void *v4; // eax
  double v5; // st7
  _DWORD *v6; // eax
  const void *v7; // ebp
  const void *v8; // esi
  double v9; // st7
  double v10; // st7
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c3
  double v14; // st7
  unsigned __int8 v16; // c0
  unsigned __int8 v17; // c3
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  _DWORD *v22; // eax
  const void *v23; // esi
  float v24; // [esp+0h] [ebp-170h]
  float v25; // [esp+0h] [ebp-170h]
  float v26; // [esp+0h] [ebp-170h]
  float v27; // [esp+0h] [ebp-170h]
  float v28; // [esp+0h] [ebp-170h]
  float v29; // [esp+14h] [ebp-15Ch]
  float v30; // [esp+18h] [ebp-158h]
  float v31; // [esp+1Ch] [ebp-154h]
  float v32; // [esp+24h] [ebp-14Ch]
  float v33; // [esp+28h] [ebp-148h]
  int v34[16]; // [esp+30h] [ebp-140h] BYREF
  int v35[16]; // [esp+70h] [ebp-100h] BYREF
  float v36[16]; // [esp+B0h] [ebp-C0h] BYREF
  float v37[16]; // [esp+F0h] [ebp-80h] BYREF
  float v38[16]; // [esp+130h] [ebp-40h] BYREF

  if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    sub_445F80((float *)(this + 6456));
    v2 = *(_DWORD *)(this + 256);
    if ( *(float *)(v2 + 732) <= 0.0 )
    {
      if ( *(_BYTE *)(v2 + 1053) )
      {
        qmemcpy(v34, (const void *)(v2 + 56), sizeof(v34));
        qmemcpy(v35, (const void *)(v2 + 56), sizeof(v35));
        set_matrix_rotation_identity(v34);
        linear_interpolate_matrix((float *)(*(_DWORD *)(this + 256) + 56), (float *)v34, (float *)v35, 0.97000003);
      }
    }
    else
    {
      *(float *)(v2 + 732) = *(float *)(v2 + 736) + *(float *)(v2 + 732);
      v3 = *(_DWORD *)(this + 256);
      if ( *(float *)(v3 + 732) > 1.0 )
        *(_DWORD *)(v3 + 732) = 0;
      v4 = (const void *)(*(_DWORD *)(this + 256) + 56);
      qmemcpy(v34, v4, sizeof(v34));
      qmemcpy(v35, v4, sizeof(v35));
      set_matrix_rotation_identity(v34);
      v5 = (-0.78539819 - *(float *)(*(_DWORD *)(this + 256) + 732) * 6.2831855) * 1.4;
      v29 = v5;
      if ( v5 < -6.2831855 )
        v29 = -6.2831855;
      rotate_matrix_world_x((float *)v34, v29);
      linear_interpolate_matrix((float *)(*(_DWORD *)(this + 256) + 56), (float *)v34, (float *)v35, 0.94);
    }
    v6 = *(_DWORD **)(this + 256);
    v7 = (const void *)(this + 56);
    v8 = v6 + 14;
    v6 += 2649;
    qmemcpy((void *)(this + 56), v8, 0x40u);
    *(_DWORD *)(this + 104) = *v6;
    *(_DWORD *)(this + 108) = v6[1];
    *(_DWORD *)(this + 112) = v6[2];
    qmemcpy(v34, (const void *)(this + 56), sizeof(v34));
    linear_interpolate_matrix((float *)(this + 56), (float *)v34, (float *)(this + 192), 0.69999999);
    v9 = *(float *)(this + 76);
    *(_DWORD *)(this + 104) = v34[12];
    *(_DWORD *)(this + 108) = v34[13];
    *(_DWORD *)(this + 112) = v34[14];
    if ( v9 > 0.0 )
    {
      v24 = (*(float *)(this + 104) - *(float *)(this + 240)) * 0.80000001;
      rotate_matrix_world_y((float *)(this + 56), v24);
    }
    v10 = *(float *)(this + 5568) + *(float *)(this + 5564);
    *(float *)(this + 5564) = v10;
    if ( !(v12 | v13) )
      *(float *)(this + 5564) = v10 - 1.0;
    v14 = *(float *)(this + 5576) + *(float *)(this + 5572);
    *(float *)(this + 5572) = v14;
    if ( !(v16 | v17) )
      *(float *)(this + 5572) = v14 - 1.0;
    qmemcpy(v38, v7, sizeof(v38));
    set_matrix_identity(v36);
    v25 = *(float *)(this + 5564) * 6.2831855;
    v26 = sine(v25) * 0.017449999;
    rotate_matrix_world_z(v36, v26);
    invert_matrix_from_source(v37, (float *)(this + 56));
    multiply_matrix_in_place((void *)(this + 56), v37);
    *(float *)(this + 108) = *(float *)(this + 108) + 1.3;
    multiply_matrix_in_place((void *)(this + 56), v36);
    *(float *)(this + 108) = *(float *)(this + 108) - 1.3;
    multiply_matrix_in_place((void *)(this + 56), v38);
    v27 = *(float *)(this + 5572) * 6.2831855;
    v18 = sine(v27);
    v30 = v18 * *(float *)(this + 72);
    v31 = v18 * *(float *)(this + 76);
    v19 = v18 * *(float *)(this + 80);
    v32 = v30 * 0.029999999;
    v33 = v31 * 0.029999999;
    *(float *)(this + 104) = v32 + *(float *)(this + 104);
    *(float *)(this + 108) = v33 + *(float *)(this + 108);
    *(float *)(this + 112) = v19 * 0.029999999 + *(float *)(this + 112);
    v20 = *(float *)(this + 6444);
    qmemcpy((void *)(this + 192), v7, 0x40u);
    if ( v20 > 0.0 )
    {
      v28 = *(float *)(this + 6444) * -2.0943952;
      rotate_matrix_world_y((float *)(this + 56), v28);
      v21 = *(float *)(this + 6448) + *(float *)(this + 6444);
      *(float *)(this + 6444) = v21;
      if ( v21 > 1.0 )
        *(_DWORD *)(this + 6444) = 1065353216;
    }
    if ( *(_BYTE *)(this + 6452) )
    {
      *(float *)(this + 4680) = *(float *)(this + 5552) + *(float *)(this + 4680);
      *(float *)(this + 4684) = *(float *)(this + 5556) + *(float *)(this + 4684);
      *(float *)(this + 4688) = *(float *)(this + 5560) + *(float *)(this + 4688);
      *(float *)(this + 1716) = *(float *)(this + 2588) + *(float *)(this + 1716);
      *(float *)(this + 1720) = *(float *)(this + 2592) + *(float *)(this + 1720);
      *(float *)(this + 1724) = *(float *)(this + 2596) + *(float *)(this + 1724);
      *(float *)(this + 3692) = *(float *)(this + 4564) + *(float *)(this + 3692);
      *(float *)(this + 3696) = *(float *)(this + 4568) + *(float *)(this + 3696);
      *(float *)(this + 3700) = *(float *)(this + 4572) + *(float *)(this + 3700);
      *(float *)(this + 2704) = *(float *)(this + 3576) + *(float *)(this + 2704);
      *(float *)(this + 2708) = *(float *)(this + 3580) + *(float *)(this + 2708);
      *(float *)(this + 2712) = *(float *)(this + 3584) + *(float *)(this + 2712);
    }
    else
    {
      qmemcpy((void *)(this + 4632), v7, 0x40u);
      qmemcpy((void *)(this + 1668), v7, 0x40u);
      qmemcpy((void *)(this + 3644), v7, 0x40u);
      qmemcpy((void *)(this + 2656), v7, 0x40u);
    }
    v22 = *(_DWORD **)(this + 256);
    qmemcpy((void *)(this + 5636), v7, 0x40u);
    v23 = v22 + 14;
    v22 += 2649;
    qmemcpy((void *)(this + 5764), v23, 0x40u);
    *(_DWORD *)(this + 5812) = *v22;
    *(_DWORD *)(this + 5816) = v22[1];
    *(_DWORD *)(this + 5820) = v22[2];
    update_snail_skin((_DWORD *)this);
    if ( *(_DWORD *)(this + 6500) )
    {
      update_cutscene(this + 6488);
    }
    else if ( !*(_DWORD *)(this + 320) && !*(_BYTE *)(*(_DWORD *)(this + 256) + 728) )
    {
      dispatch_cutscene_animation(this, 1, 0, -1);
    }
    update_jet_particles(*(_DWORD *)(this + 256) + 10064);
  }
}
