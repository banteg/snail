/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_progress_bar @ 0x437c40 */
/* selector: update_progress_bar */

void sub_437C40()
{
  double v0; // st6
  double v1; // st7
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v5; // [esp+0h] [ebp-4Ch]
  int v6; // [esp+8h] [ebp-44h]
  int v7; // [esp+30h] [ebp-1Ch]
  int v8; // [esp+34h] [ebp-18h]
  int v9; // [esp+38h] [ebp-14h]
  _DWORD v10[4]; // [esp+3Ch] [ebp-10h] BYREF

  v0 = (*((float *)MEMORY[0x4DF904] + 1097595) - (double)*((int *)MEMORY[0x4DF904] + 119194))
     / ((double)*((int *)MEMORY[0x4DF904] + 119196) - (double)*((int *)MEMORY[0x4DF904] + 119194));
  v1 = v0;
  if ( v0 >= 0.0 )
  {
    if ( v0 > 1.0 )
      v1 = 1.0;
  }
  else
  {
    v1 = 0.0;
  }
  *(float *)&v7 = (1.0 - v1) * 232.0 + 12.0;
  *(float *)&v8 = *(float *)&v7 + 150.0;
  v2 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  *(float *)&v5 = *(float *)&v8 - 39.0;
  queue_axis_aligned_textured_quad_uv(
    157,
    1094713344,
    v5,
    1115684864,
    1115684864,
    0x1000000,
    v2,
    0,
    0,
    1065353216,
    1065353216,
    3,
    0);
  *(float *)&v9 = *(float *)&v7 * 0.00390625;
  v3 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  queue_axis_aligned_textured_quad_uv(
    155,
    1095761920,
    1125515264,
    1115684864,
    v7,
    0x1000000,
    v3,
    0,
    0,
    1065353216,
    v9,
    3,
    0);
  v4 = set_color_rgba(v10, 1065353216, 1065353216, 1065353216, 1065353216);
  *(float *)&v6 = 256.0 - *(float *)&v7;
  queue_axis_aligned_textured_quad_uv(
    156,
    1095761920,
    v8,
    1115684864,
    v6,
    0x1000000,
    v4,
    0,
    v9,
    1065353216,
    1065353216,
    3,
    0);
}

