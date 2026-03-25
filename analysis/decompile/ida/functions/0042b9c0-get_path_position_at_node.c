/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_path_position_at_node @ 0x42b9c0 */
/* selector: get_path_position_at_node */

int __thiscall sub_42B9C0(_DWORD *this, float *a2, int a3, int a4, float *a5)
{
  double v5; // st7
  float *v6; // eax
  double v7; // st6
  float v9; // [esp+4h] [ebp-24h]
  float v10; // [esp+4h] [ebp-24h]
  float v11; // [esp+8h] [ebp-20h]
  float v12; // [esp+8h] [ebp-20h]
  float v13; // [esp+Ch] [ebp-1Ch]
  float v14; // [esp+10h] [ebp-18h]
  float v15; // [esp+14h] [ebp-14h]
  float v16; // [esp+1Ch] [ebp-Ch]
  float v17; // [esp+20h] [ebp-8h]
  float v18; // [esp+24h] [ebp-4h]

  v5 = a5[1];
  v6 = (float *)(*(this + 22) + 168 * a3);
  v16 = v5 * v6[4];
  v17 = v5 * v6[5];
  v7 = *a5;
  v9 = v7 * *v6;
  v11 = v7 * v6[1];
  v14 = v9 + v6[12];
  v15 = v11 + v6[13];
  v10 = v14 + v16;
  v12 = v15 + v17;
  v13 = v7 * v6[2] + v6[14] + v5 * v6[6];
  *a2 = v10;
  a2[1] = v12;
  v18 = (double)a4 + v13;
  a2[2] = v18;
  return LODWORD(v18);
}

