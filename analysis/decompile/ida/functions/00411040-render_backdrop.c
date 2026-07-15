/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: render_backdrop @ 0x411040 */
/* selector: render_backdrop */

// Draws the single-texture 320x240 backdrop crop through the animated distortion grid. Cross-port Android and iOS symbols match this helper to `cRBackdrop::Render()`.
void __thiscall render_backdrop(Backdrop *backdrop)
{
  double v2; // st7
  double v3; // st6
  float *v4; // esi
  double v5; // st7
  float v6; // [esp+0h] [ebp-8Ch]
  float v7; // [esp+4h] [ebp-88h]
  float v8; // [esp+8h] [ebp-84h]
  float v9; // [esp+Ch] [ebp-80h]
  float v10; // [esp+10h] [ebp-7Ch]
  float v11; // [esp+14h] [ebp-78h]
  float v12; // [esp+18h] [ebp-74h]
  float v13; // [esp+1Ch] [ebp-70h]
  tColour *v14; // [esp+2Ch] [ebp-60h]
  float v15; // [esp+30h] [ebp-5Ch]
  float v16; // [esp+34h] [ebp-58h]
  float v17; // [esp+38h] [ebp-54h]
  float v18; // [esp+3Ch] [ebp-50h]
  float v19; // [esp+54h] [ebp-38h]
  float v20; // [esp+58h] [ebp-34h]
  float v21; // [esp+5Ch] [ebp-30h]
  float v22; // [esp+60h] [ebp-2Ch]
  float v23; // [esp+64h] [ebp-28h]
  float v24; // [esp+68h] [ebp-24h]
  Color4f color; // [esp+6Ch] [ebp-20h] BYREF
  Color4f v26; // [esp+7Ch] [ebp-10h] BYREF

  v19 = 0.0;
  do
  {
    v2 = 0.0;
    do
    {
      v20 = v2 + 1.0;
      v3 = v19 + 1.0;
      v21 = v20 * 68.571426;
      v4 = (float *)&backdrop->bod_base[192 * (__int64)v2 + 24 * (__int64)v19];
      v24 = v19 * 91.428574;
      v22 = v3 * 91.428574;
      v23 = v2 * 68.571426;
      if ( backdrop->active_flip )
      {
        v17 = 0.80000001 - v3 * 0.089285716;
        v16 = v2 * 0.13392857;
        v15 = 0.80000001 - v19 * 0.089285716;
        v14 = set_color_rgba((tColour *)&v26, 1.0, 1.0, 1.0, 1.0);
      }
      else
      {
        v17 = v3 * 0.089285716;
        v16 = v2 * 0.13392857;
        v15 = v19 * 0.089285716;
        v14 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      }
      v13 = v21 + v4[75];
      v12 = v24 + v4[74];
      v11 = v21 + v4[81];
      v10 = v22 + v4[80];
      v9 = v23 + v4[33];
      v8 = v22 + v4[32];
      v7 = v23 + v4[27];
      v6 = v24 + v4[26];
      v18 = v20 * 0.13392857;
      queue_textured_quad_corners(
        backdrop->active_primary_texture_id,
        v6,
        v7,
        v8,
        v9,
        v10,
        v11,
        v12,
        v13,
        0,
        0,
        0x8000000u,
        v14,
        v15,
        v16,
        v17,
        v18,
        0,
        0.0);
      v2 = v20;
    }
    while ( v20 < 7.0 );
    v5 = v19 + 1.0;
    v19 = v5;
  }
  while ( v5 < 7.0 );
}
