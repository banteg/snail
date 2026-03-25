/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_snail_weapons @ 0x442e40 */
/* selector: release_snail_weapons */

void __thiscall sub_442E40(int this)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  int v6; // eax
  float v7; // [esp+4h] [ebp-1Ch]
  float v8; // [esp+4h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-1Ch]
  float v10; // [esp+8h] [ebp-18h]
  float v11; // [esp+8h] [ebp-18h]
  float v12; // [esp+8h] [ebp-18h]
  float v13; // [esp+8h] [ebp-18h]
  float v14; // [esp+Ch] [ebp-14h]
  float v15; // [esp+Ch] [ebp-14h]
  float v16; // [esp+Ch] [ebp-14h]
  float v17; // [esp+Ch] [ebp-14h]
  float v18; // [esp+10h] [ebp-10h]
  float v19; // [esp+10h] [ebp-10h]
  float v20; // [esp+10h] [ebp-10h]
  float v21; // [esp+10h] [ebp-10h]
  float v22; // [esp+14h] [ebp-Ch]
  float v23; // [esp+1Ch] [ebp-4h]
  float v24; // [esp+1Ch] [ebp-4h]
  float v25; // [esp+1Ch] [ebp-4h]
  float v26; // [esp+1Ch] [ebp-4h]

  if ( !*(_BYTE *)(this + 6452) )
  {
    v22 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v2 = random_float_below(1.0);
    v23 = *(float *)(*(_DWORD *)(this + 256) + 1048);
    v10 = v22 * 0.30000001;
    *(float *)(this + 5552) = v10;
    v14 = (v2 + 0.5) * 0.30000001;
    *(float *)(this + 5556) = v14;
    v18 = v23 * 0.30000001;
    *(float *)(this + 5560) = v18;
    v7 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v3 = random_float_below(1.0);
    v24 = *(float *)(*(_DWORD *)(this + 256) + 1048);
    v11 = v7 * 0.30000001;
    *(float *)(this + 2588) = v11;
    v15 = (v3 + 0.5) * 0.30000001;
    *(float *)(this + 2592) = v15;
    v19 = v24 * 0.30000001;
    *(float *)(this + 2596) = v19;
    v8 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v4 = random_float_below(1.0);
    v25 = *(float *)(*(_DWORD *)(this + 256) + 1048);
    v12 = v8 * 0.30000001;
    *(float *)(this + 4564) = v12;
    v16 = (v4 + 0.5) * 0.30000001;
    *(float *)(this + 4568) = v16;
    v20 = v25 * 0.30000001;
    *(float *)(this + 4572) = v20;
    v9 = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
    v5 = random_float_below(1.0);
    v6 = *(_DWORD *)(this + 256);
    v26 = *(float *)(v6 + 1048);
    v13 = v9 * 0.30000001;
    *(float *)(this + 3576) = v13;
    v17 = (v5 + 0.5) * 0.30000001;
    *(float *)(this + 3580) = v17;
    v21 = v26 * 0.30000001;
    *(float *)(this + 3584) = v21;
    end_jetpack_hover((float *)(v6 + 10064));
  }
  *(_BYTE *)(this + 6452) = 1;
}

