/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_camera_view_matrix @ 0x451ad9 */
/* selector: build_camera_view_matrix */

// Builds the view matrix from camera eye, target, and up vectors by normalizing the look, right, and up axes and storing translated dot products. Called by `render_camera`.
float *__stdcall sub_451AD9(float *a1, float *a2, float *a3, float *a4)
{
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  float v10; // ecx
  double v11; // st4
  double v12; // st3
  float v13; // [esp+Ch] [ebp-24h]
  float v14; // [esp+10h] [ebp-20h]
  float v15; // [esp+14h] [ebp-1Ch]
  float v16; // [esp+18h] [ebp-18h] BYREF
  float v17; // [esp+1Ch] [ebp-14h]
  float v18; // [esp+20h] [ebp-10h]
  float v19; // [esp+24h] [ebp-Ch] BYREF
  float v20; // [esp+28h] [ebp-8h]
  float v21; // [esp+2Ch] [ebp-4h]

  v19 = *a2 - *a3;
  v20 = a2[1] - a3[1];
  v21 = a2[2] - a3[2];
  sub_44EBC1(&v19, &v19);
  v13 = v21 * a4[1] - v20 * a4[2];
  v14 = v19 * a4[2] - v21 * *a4;
  v15 = v20 * *a4 - v19 * a4[1];
  v16 = v13;
  v17 = v14;
  v18 = v15;
  sub_44EBC1(&v16, &v16);
  v5 = v20 * v18;
  a1[4] = v17;
  v6 = v21 * v17;
  a1[8] = v18;
  v7 = v5 - v6;
  v8 = v21 * v16 - v19 * v18;
  v9 = v19 * v17 - v20 * v16;
  *a1 = v16;
  a1[12] = -(v16 * *a2 + v17 * a2[1] + v18 * a2[2]);
  a1[1] = v7;
  v10 = v19;
  a1[5] = v8;
  a1[9] = v9;
  v11 = v7 * *a2 + v8 * a2[1];
  v12 = v9 * a2[2];
  a1[2] = v10;
  a1[6] = v20;
  a1[10] = v21;
  a1[13] = -(v11 + v12);
  a1[14] = -(v19 * *a2 + v20 * a2[1] + v21 * a2[2]);
  a1[3] = 0.0;
  a1[7] = 0.0;
  a1[11] = 0.0;
  a1[15] = 1.0;
  return a1;
}

