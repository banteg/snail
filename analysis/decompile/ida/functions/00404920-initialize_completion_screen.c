/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_completion_screen @ 0x404920 */
/* selector: initialize_completion_screen */

// Builds the Delivery Complete screen, seeds its package-count and bonus summary widgets, and lays out the continue prompt. Cross-port Android and iOS symbols match this helper to `cRCompletion::Init(int, bool)`.
void __thiscall sub_404920(int this, int a2, unsigned __int8 a3)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // esi
  int v9; // edx
  int v10; // esi
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  int v13; // eax
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  int v16; // ecx
  _DWORD *v17; // [esp-Ch] [ebp-2Ch]
  _DWORD *v18; // [esp-Ch] [ebp-2Ch]
  _DWORD *v19; // [esp-Ch] [ebp-2Ch]
  _DWORD *v20; // [esp-Ch] [ebp-2Ch]
  _DWORD v21[4]; // [esp+10h] [ebp-10h] BYREF

  v4 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
  if ( v4 )
  {
    if ( v4 == 1 )
    {
      if ( *((_BYTE *)MEMORY[0x4DF904] + 17198056) )
      {
        v5 = *((_DWORD *)MEMORY[0x4DF904] + 4299515);
        v6 = *(_DWORD *)(v5 + 80);
        v7 = *(_DWORD *)(v5 + 76);
        v8 = v6 / 20;
      }
      else
      {
        v7 = unk_4DF958;
        v8 = unk_4DF960 / 20;
      }
      v9 = v7 / 20;
      if ( v8 >= 0 )
      {
        if ( v8 > 5 )
          v8 = 5;
      }
      else
      {
        v8 = 0;
      }
      if ( v9 >= 0 )
      {
        if ( v9 > 5 )
          v9 = 5;
      }
      else
      {
        v9 = 0;
      }
      if ( v8 == 5 && v9 == 5 )
        *(_DWORD *)(this + 72) = 500000;
      else
        *(_DWORD *)(this + 72) = dword_4A1194[v8] + dword_4A11AC[v9];
    }
  }
  else if ( a3 )
  {
    *(_DWORD *)(this + 72) = 50000;
  }
  else
  {
    *(_DWORD *)(this + 72) = 0;
  }
  v10 = *(_DWORD *)(this + 72);
  *(_DWORD *)(this + 28) = a2;
  *(_DWORD *)(this + 32) = a3;
  *(_DWORD *)(this + 76) = v10 + *((_DWORD *)MEMORY[0x4DF904] + 1097752) + 100 * a2;
  *(_DWORD *)this = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v11 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_widget(*(_DWORD *)this, 541065218, aDeliveryComple, 20, 0, 80.0, (int)v11, 2, 0.0);
  *(_DWORD *)(this + 4) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( *(_DWORD *)(this + 28) == 1 )
  {
    v17 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 4), 541065218, a0PackageDelive, 20, 0, 160.0, (int)v17, 2, 0.0);
  }
  else
  {
    v18 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 4), 541065218, a00PackagesDeli, 20, 0, 160.0, (int)v18, 2, 0.0);
  }
  *(_DWORD *)(this + 12) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v12 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
  initialize_frontend_sprite_button(*(_DWORD *)(this + 12), 4196352, 122, 1120403456, 1125253120, v12, 0.0, 4);
  *(_DWORD *)(*(_DWORD *)(this + 12) + 376) = 0;
  *(_DWORD *)(this + 8) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v13 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
  if ( v13 )
  {
    if ( v13 == 1 )
    {
      v15 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
      initialize_frontend_widget(*(_DWORD *)(this + 8), 541065218, aLevelComplete, 20, 0, 302.0, (int)v15, 2, 0.0);
      border_add_text_number(*(_BYTE **)(this + 8), *(_DWORD *)(this + 72));
      strcat((char *)(*(_DWORD *)(this + 8) + 716), aBonusPoints);
    }
  }
  else
  {
    v14 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 8), 541065218, aPerfectScore50, 20, 0, 302.0, (int)v14, 2, 0.0);
  }
  hide_border_init(*(_DWORD **)(this + 8));
  *(_DWORD *)(this + 64) = 0;
  *(_DWORD *)(this + 68) = 1026206379;
  *(_DWORD *)(this + 16) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( *(_DWORD *)(this + 32) )
  {
    v19 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 16), 541065218, aClickToContinu, 20, 0, 400.0, (int)v19, 2, 0.0);
  }
  else
  {
    v20 = set_color_rgba(v21, 1065353216, 1065353216, 1065353216, 1065353216);
    initialize_frontend_widget(*(_DWORD *)(this + 16), 541065218, aClickToContinu, 20, 0, 320.0, (int)v20, 2, 0.0);
  }
  hide_border_init(*(_DWORD **)(this + 16));
  v16 = *(_DWORD *)(this + 28);
  *(_DWORD *)(this + 36) = 0;
  *(_DWORD *)(this + 40) = 0;
  *(_DWORD *)(this + 20) = 1;
  *(_DWORD *)(this + 44) = 1062557013;
  *(_BYTE *)(this + 24) = 1;
  *(float *)(this + 48) = 1.0 / (3.4000001 / (double)(v16 + 1) * 60.0);
}

