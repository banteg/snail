/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: explode_slug_hazard @ 0x43f680 */
/* selector: explode_slug_hazard */

int __thiscall sub_43F680(int this)
{
  char *v2; // esi
  int v3; // edx
  double v4; // st7
  double v5; // st7
  int v6; // eax
  int v7; // ebx
  double v8; // st7
  double v9; // st6
  float *v10; // ebx
  double v11; // st7
  double v12; // st7
  int result; // eax
  int v14; // [esp+0h] [ebp-54h]
  float v15; // [esp+14h] [ebp-40h]
  float v16; // [esp+18h] [ebp-3Ch]
  int v17; // [esp+1Ch] [ebp-38h]
  float v18; // [esp+24h] [ebp-30h]
  float v19; // [esp+28h] [ebp-2Ch]
  float v20; // [esp+2Ch] [ebp-28h]
  float v21; // [esp+30h] [ebp-24h]
  float v22; // [esp+34h] [ebp-20h]
  float v23; // [esp+38h] [ebp-1Ch]
  float v24; // [esp+3Ch] [ebp-18h]
  float v25; // [esp+40h] [ebp-14h]
  float v26; // [esp+48h] [ebp-Ch]
  float v27; // [esp+4Ch] [ebp-8h]

  v17 = 70;
  do
  {
    v16 = (double)next_math_random_value() * 0.0000061035157 + 0.2;
    v15 = (double)next_math_random_value() * 0.000030517578 * 0.75 + 0.25;
    v2 = (char *)allocate_sprite(g_sprite_manager, 1, 129, -1, -1);
    v3 = *((_DWORD *)v2 + 1);
    *((_DWORD *)v2 + 26) = 0;
    *((_DWORD *)v2 + 1) = v3 | 0x802;
    *((float *)v2 + 34) = v15 + v15;
    v4 = 1.0
       / (((double)next_math_random_value() * 0.000015258789 + 0.60000002)
        * 60.0)
       * *(float *)(*(_DWORD *)(this + 136) + 56);
    *((_DWORD *)v2 + 28) = 0;
    *((_DWORD *)v2 + 29) = 0;
    *((float *)v2 + 27) = v4;
    *(float *)&v14 = (double)next_math_random_value() * 0.0000091552738 + 0.69999999;
    set_color_grayscale((_DWORD *)v2 + 11, v14);
    *((float *)v2 + 24) = v15 * 0.30000001;
    *((float *)v2 + 25) = v15 * 1.2;
    v5 = *(float *)(*(_DWORD *)(this + 136) + 56);
    *((float *)v2 + 30) = v5 * v5 * -0.0099999998 * 2.2;
    v24 = ((double)next_math_random_value() - 16384.0) * v16 * 0.000061035156;
    v6 = next_math_random_value();
    v7 = *(_DWORD *)(this + 136);
    v25 = (double)v6 * (v16 + 0.30000001) * 0.000030517578;
    v8 = (double)next_math_random_value() * v16 * 0.000030517578 + *(float *)(v7 + 3914620);
    v9 = *(float *)(v7 + 56);
    v10 = (float *)(v2 + 84);
    v18 = v9 * v24;
    *((float *)v2 + 21) = v18;
    v19 = v25 * v9;
    *((float *)v2 + 22) = v19;
    v20 = v8 * v9;
    *((float *)v2 + 23) = v20;
    v2 += 72;
    v11 = (double)next_math_random_value() * 0.00030517578;
    v26 = v11 * *v10;
    v27 = v11 * v10[1];
    v21 = v26 + *(float *)(this + 104);
    v22 = v27 + *(float *)(this + 108);
    v12 = v11 * v10[2] + *(float *)(this + 112);
    *(float *)v2 = v21;
    *((float *)v2 + 1) = v22;
    v23 = v12;
    *((float *)v2 + 2) = v23;
    result = --v17;
  }
  while ( v17 );
  return result;
}

