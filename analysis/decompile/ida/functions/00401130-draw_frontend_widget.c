/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_frontend_widget @ 0x401130 */
/* selector: draw_frontend_widget */

// Renders one shell-font front-end widget, including nine-slice border styles, slider-track strips, optional glow overlay, icon sprites, and the final text draw.
void __thiscall sub_401130(int this)
{
  int v2; // eax
  int v3; // ebx
  double v4; // st7
  int v5; // edx
  double v6; // st7
  double v7; // st6
  double v8; // st7
  int *v9; // eax
  double v10; // st7
  double v11; // st7
  int v12; // edi
  int v13; // ebp
  int v14; // ebx
  int v15; // ebp
  int v16; // esi
  int v17; // [esp-Ch] [ebp-C4h]
  int v18; // [esp+0h] [ebp-B8h]
  int v19; // [esp+0h] [ebp-B8h]
  int v20; // [esp+0h] [ebp-B8h]
  int v21; // [esp+0h] [ebp-B8h]
  int v22; // [esp+0h] [ebp-B8h]
  int v23; // [esp+4h] [ebp-B4h]
  int v24; // [esp+4h] [ebp-B4h]
  int v25; // [esp+4h] [ebp-B4h]
  int v26; // [esp+4h] [ebp-B4h]
  int v27; // [esp+4h] [ebp-B4h]
  int v28; // [esp+8h] [ebp-B0h]
  int v29; // [esp+8h] [ebp-B0h]
  int v30; // [esp+8h] [ebp-B0h]
  int v31; // [esp+8h] [ebp-B0h]
  int v32; // [esp+8h] [ebp-B0h]
  int v33; // [esp+Ch] [ebp-ACh]
  int v34; // [esp+Ch] [ebp-ACh]
  int v35; // [esp+Ch] [ebp-ACh]
  int *v36; // [esp+14h] [ebp-A4h]
  int v37; // [esp+28h] [ebp-90h]
  float v38; // [esp+2Ch] [ebp-8Ch]
  int v39; // [esp+2Ch] [ebp-8Ch]
  int v40; // [esp+40h] [ebp-78h]
  int v41; // [esp+44h] [ebp-74h]
  int v42; // [esp+48h] [ebp-70h]
  int v43; // [esp+4Ch] [ebp-6Ch]
  int v44; // [esp+50h] [ebp-68h]
  float v45; // [esp+54h] [ebp-64h]
  int v46; // [esp+58h] [ebp-60h]
  float v47; // [esp+58h] [ebp-60h]
  int v48; // [esp+58h] [ebp-60h]
  float v49; // [esp+5Ch] [ebp-5Ch]
  int v50; // [esp+5Ch] [ebp-5Ch]
  int v51; // [esp+5Ch] [ebp-5Ch]
  int v52; // [esp+60h] [ebp-58h]
  int v53; // [esp+60h] [ebp-58h]
  float v54; // [esp+64h] [ebp-54h]
  int v55; // [esp+64h] [ebp-54h]
  int v56; // [esp+64h] [ebp-54h]
  int v57[4]; // [esp+68h] [ebp-50h] BYREF
  int v58[4]; // [esp+78h] [ebp-40h] BYREF
  int v59[4]; // [esp+88h] [ebp-30h] BYREF
  _BYTE v60[12]; // [esp+98h] [ebp-20h] BYREF
  int v61; // [esp+A4h] [ebp-14h]
  _BYTE v62[16]; // [esp+A8h] [ebp-10h] BYREF

  Iostream_init::Iostream_init((#93 *)v59);
  Iostream_init::Iostream_init((#93 *)v58);
  Iostream_init::Iostream_init((#93 *)v62);
  Iostream_init::Iostream_init((#93 *)v60);
  if ( unk_4B7236 )
  {
    v2 = *(_DWORD *)(this + 416);
    if ( (v2 & 0x1000) == 0 )
    {
      if ( (byte_4DF934 & 0x80u) != 0 )
      {
        v42 = 3;
        v3 = 3;
      }
      else
      {
        v3 = 0;
        v59[3] = 1065353216;
        v61 = 1065353216;
        v42 = 0;
      }
      v44 = *(int *)(this + 584);
      v43 = *(int *)(this + 588);
      if ( (v2 & 0x100000) != 0 )
      {
        v4 = *(float *)(this + 384);
        v46 = *(int *)(this + 384);
        v5 = *(_DWORD *)(this + 480);
        v58[0] = *(_DWORD *)(this + 476);
        v58[1] = v5;
        v58[2] = *(_DWORD *)(this + 484);
        v58[3] = *(_DWORD *)(this + 488);
        if ( v4 > 0.0 )
        {
          *(float *)&v28 = *(float *)(this + 384) * 256.0;
          *(float *)&v23 = *(float *)(this + 580) + 50.0;
          *(float *)&v18 = *(float *)&v44 * 0.5 + *(float *)(this + 576) - 128.0;
          queue_axis_aligned_textured_quad_uv(
            37,
            v18,
            v23,
            v28,
            1107296256,
            0x1000000,
            v58,
            0,
            0,
            v46,
            1065353216,
            v3,
            0);
        }
        if ( *(float *)(this + 384) < 1.0 )
        {
          *(float *)&v29 = (1.0 - *(float *)(this + 384)) * 256.0;
          *(float *)&v24 = *(float *)(this + 580) + 50.0;
          *(float *)&v19 = *(float *)&v44 * 0.5 + *(float *)(this + 576) - 128.0 + *(float *)(this + 384) * 256.0;
          queue_axis_aligned_textured_quad_uv(
            36,
            v19,
            v24,
            v29,
            1107296256,
            0x1000000,
            v58,
            COERCE_INT(*(float *)(this + 384)),
            0,
            1065353216,
            1065353216,
            v3,
            0);
        }
      }
      if ( *(_BYTE *)(this + 92) )
      {
        v6 = 0.0;
        if ( *((_BYTE *)MEMORY[0x4DF904] + 278764) )
        {
          if ( this == *((_DWORD *)MEMORY[0x4DF904] + 69694) )
          {
            v38 = *((float *)MEMORY[0x4DF904] + 69692) * 3.1415927;
            v6 = sine(v38) * 3.0;
            if ( !*(_BYTE *)(this + 93) )
              v6 = v6 * -1.0;
          }
        }
        v7 = *(float *)(this + 600) * 0.5;
        v37 = *(_DWORD *)(this + 628);
        v36 = (int *)(this + 476);
        *(float *)&v33 = *(float *)(this + 596) + *(float *)(this + 600);
        *(float *)&v30 = *(float *)(this + 592) + *(float *)(this + 600);
        *(float *)&v25 = *(float *)(this + 580) - v7;
        *(float *)&v20 = v6 + *(float *)(this + 576) - v7;
        if ( (*(_BYTE *)(this + 416) & 2) != 0 )
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 96),
            v20,
            v25,
            v30,
            v33,
            0x1000000,
            v36,
            0,
            0,
            1065353216,
            1065353216,
            v37,
            0);
        else
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 624),
            v20,
            v25,
            v30,
            v33,
            0x1000000,
            v36,
            0,
            0,
            1065353216,
            1065353216,
            v37,
            0);
      }
      else
      {
        if ( (*(_DWORD *)(this + 416) & 0x800) != 0 )
        {
          v8 = *(float *)(this + 600) * 0.5;
          *(float *)&v34 = *(float *)(this + 596) + *(float *)(this + 600);
          *(float *)&v31 = *(float *)(this + 600) + *(float *)(this + 592);
          *(float *)&v26 = *(float *)(this + 580) - v8;
          *(float *)&v21 = *(float *)(this + 576) - v8;
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 624),
            v21,
            v26,
            v31,
            v34,
            0x1000000,
            (int *)(this + 476),
            0,
            0,
            1065353216,
            1065353216,
            *(_DWORD *)(this + 628),
            0);
          if ( *(float *)(this + 376) > 0.0 )
          {
            v54 = *(float *)(this + 600) * 0.5;
            v9 = set_color_rgba(v57, 0, 0, 0, 1063675494);
            *(float *)&v35 = *(float *)(this + 596) + *(float *)(this + 600);
            *(float *)&v32 = *(float *)(this + 600) + *(float *)(this + 592);
            *(float *)&v27 = *(float *)(this + 376) + *(float *)(this + 580) - v54;
            *(float *)&v22 = *(float *)(this + 376) + *(float *)(this + 576) - v54;
            queue_axis_aligned_textured_quad_uv(
              *(_DWORD *)(this + 624),
              v22,
              v27,
              v32,
              v35,
              0x1000000,
              v9,
              0,
              0,
              1065353216,
              1065353216,
              2,
              0);
          }
        }
        if ( (*(_DWORD *)(this + 416) & 0x400000) == 0 )
        {
          if ( *(_BYTE *)(this + 564) )
          {
            v45 = 4.0;
            v47 = 0.1;
            v49 = 0.89999998;
            *(float *)&v41 = *(float *)(this + 576) + 4.0;
            *(float *)&v40 = *(float *)(this + 580) + 3.0;
            *(float *)&v44 = *(float *)&v44 - 8.0;
            *(float *)&v43 = *(float *)&v43 - 6.0;
          }
          else if ( *(float *)(this + 544) >= (double)*(float *)(this + 560) )
          {
            v41 = *(int *)(this + 576);
            v40 = *(int *)(this + 580);
            v45 = *(float *)(this + 544);
            v47 = 0.2;
            v49 = 0.80000001;
          }
          else
          {
            v10 = *(float *)(this + 560) - *(float *)(this + 544);
            v45 = *(float *)(this + 560);
            *(float *)(this + 556) = v10;
            *(float *)&v41 = v10 + *(float *)(this + 576);
            *(float *)&v40 = v10 + *(float *)(this + 580);
            v11 = v10 + v10;
            *(float *)&v44 = *(float *)&v44 - v11;
            *(float *)&v43 = *(float *)&v43 - v11;
            v47 = v45 * 0.0078125;
            v49 = 1.0 - v47;
          }
          v12 = LODWORD(v47);
          v13 = LODWORD(v45);
          *(float *)&v52 = *(float *)&v40 - v45;
          *(float *)&v55 = *(float *)&v41 - v45;
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v55,
            v52,
            SLODWORD(v45),
            SLODWORD(v45),
            0x1000000,
            (int *)(this + 428),
            0,
            0,
            SLODWORD(v47),
            SLODWORD(v47),
            v3,
            0);
          v17 = v3;
          v14 = LODWORD(v49);
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v41,
            v52,
            v44,
            SLODWORD(v45),
            0x1000000,
            (int *)(this + 428),
            v12,
            0,
            SLODWORD(v49),
            v12,
            v17,
            0);
          *(float *)&v50 = *(float *)&v44 + *(float *)&v41;
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v50,
            v52,
            v13,
            v13,
            0x1000000,
            (int *)(this + 428),
            v14,
            0,
            1065353216,
            SLODWORD(v47),
            v42,
            0);
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v55,
            v40,
            SLODWORD(v45),
            v43,
            0x1000000,
            (int *)(this + 428),
            0,
            v12,
            v12,
            v14,
            v42,
            0);
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v41,
            v40,
            v44,
            v43,
            0x1000000,
            (int *)(this + 428),
            v12,
            v12,
            v14,
            v14,
            v42,
            0);
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v50,
            v40,
            SLODWORD(v45),
            v43,
            0x1000000,
            (int *)(this + 428),
            v14,
            SLODWORD(v47),
            1065353216,
            v14,
            v42,
            0);
          *(float *)&v48 = *(float *)&v43 + *(float *)&v40;
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v55,
            v48,
            v13,
            v13,
            0x1000000,
            (int *)(this + 428),
            0,
            v14,
            v12,
            1065353216,
            v42,
            0);
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v41,
            v48,
            v44,
            SLODWORD(v45),
            0x1000000,
            (int *)(this + 428),
            v12,
            v14,
            v14,
            1065353216,
            v42,
            0);
          v15 = v50;
          queue_axis_aligned_textured_quad_uv(
            *(_DWORD *)(this + 72),
            v50,
            v48,
            SLODWORD(v45),
            SLODWORD(v45),
            0x1000000,
            (int *)(this + 428),
            v14,
            v14,
            1065353216,
            1065353216,
            v42,
            0);
          if ( *((_BYTE *)MEMORY[0x4DF904] + 278764) )
          {
            if ( this == *((_DWORD *)MEMORY[0x4DF904] + 69694) )
            {
              Iostream_init::Iostream_init((#93 *)v57);
              set_color_white(v59);
              *(float *)&v39 = 1.0 - *((float *)MEMORY[0x4DF904] + 69692);
              sub_44DBB0(v57, v59[0], v59[1], v59[2], v39);
              *(float *)&v56 = (*((float *)MEMORY[0x4DF904] + 69692) * 0.69999999 + 1.0) * v45;
              v16 = v56;
              *(float *)&v53 = *(float *)&v40 - *(float *)&v56;
              *(float *)&v51 = *(float *)&v41 - *(float *)&v56;
              queue_axis_aligned_textured_quad_uv(99, v51, v53, v56, v56, 0x1000000, v57, 0, 0, v12, v12, 3, 0);
              queue_axis_aligned_textured_quad_uv(99, v41, v53, v44, v56, 0x1000000, v57, v12, 0, v14, v12, 3, 0);
              queue_axis_aligned_textured_quad_uv(99, v15, v53, v16, v16, 0x1000000, v57, v14, 0, 1065353216, v12, 3, 0);
              queue_axis_aligned_textured_quad_uv(99, v51, v40, v56, v43, 0x1000000, v57, 0, v12, v12, v14, 3, 0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v15,
                v40,
                v56,
                v43,
                0x1000000,
                v57,
                v14,
                v12,
                1065353216,
                v14,
                3,
                0);
              queue_axis_aligned_textured_quad_uv(99, v51, v48, v16, v16, 0x1000000, v57, 0, v14, v12, 1065353216, 3, 0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v41,
                v48,
                v44,
                v56,
                0x1000000,
                v57,
                v12,
                v14,
                v14,
                1065353216,
                3,
                0);
              queue_axis_aligned_textured_quad_uv(
                99,
                v15,
                v48,
                v16,
                v16,
                0x1000000,
                v57,
                v14,
                v14,
                1065353216,
                1065353216,
                3,
                0);
            }
          }
        }
      }
    }
  }
}

