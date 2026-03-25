/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_galaxy_line @ 0x409b00 */
/* selector: draw_galaxy_line */

char __stdcall sub_409B00(int a1, float a2, float a3, float a4, float a5, float a6, int *a7)
{
  double v7; // st7
  double v8; // st6
  int v10; // [esp+0h] [ebp-54h]
  int v11; // [esp+4h] [ebp-50h]
  int v12; // [esp+8h] [ebp-4Ch]
  int v13; // [esp+Ch] [ebp-48h]
  int v14; // [esp+10h] [ebp-44h]
  int v15; // [esp+14h] [ebp-40h]
  int v16; // [esp+18h] [ebp-3Ch]
  int v17; // [esp+1Ch] [ebp-38h]
  float v18; // [esp+48h] [ebp-Ch] BYREF
  float v19; // [esp+4Ch] [ebp-8h]
  int v20; // [esp+50h] [ebp-4h]

  v20 = 0;
  v18 = a4 - a2;
  v19 = a5 - a3;
  normalize_vector(&v18);
  v7 = v19 * a6 * -0.5;
  v8 = v18 * a6 * 0.5;
  *(float *)&v17 = v8 + a3;
  *(float *)&v16 = v7 + a2;
  *(float *)&v15 = v8 + a5;
  *(float *)&v14 = v7 + a4;
  *(float *)&v13 = a5 - v8;
  *(float *)&v12 = a4 - v7;
  *(float *)&v11 = a3 - v8;
  *(float *)&v10 = a2 - v7;
  return queue_textured_quad_corners(
           a1,
           v10,
           v11,
           v12,
           v13,
           v14,
           v15,
           v16,
           v17,
           0,
           0,
           0x1000000,
           a7,
           0,
           0,
           1065353216,
           1065353216,
           15,
           0);
}

