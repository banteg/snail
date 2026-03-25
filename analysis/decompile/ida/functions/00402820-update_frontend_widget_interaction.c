/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_widget_interaction @ 0x402820 */
/* selector: update_frontend_widget_interaction */

// Runs one front-end widget's per-frame interaction state, including hover easing, delayed click-bit dispatch, slider-arrow adjustments, bounds refresh, and draw.
void __thiscall sub_402820(int this)
{
  unsigned int v2; // edx
  int v3; // eax
  int v4; // eax
  char *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char *v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  double v13; // st7
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  _DWORD *v25; // ecx
  int v26; // eax
  unsigned int v27; // edx
  int v28; // eax
  int v29; // eax
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  int v37; // edx
  int v38; // eax
  int v39; // ecx
  int v40; // eax
  double v41; // st7
  int v42; // ecx
  int v43; // eax
  double v44; // st7
  int v45; // eax
  int v46; // edx
  int v47; // eax
  int v48; // ecx
  _DWORD *v49; // ecx
  int v50; // [esp+0h] [ebp-24h]
  int v51; // [esp+0h] [ebp-24h]
  int v52; // [esp+4h] [ebp-20h]
  int v53; // [esp+4h] [ebp-20h]
  int v54; // [esp+8h] [ebp-1Ch]
  int v55; // [esp+8h] [ebp-1Ch]
  int v56; // [esp+Ch] [ebp-18h]
  int v57; // [esp+Ch] [ebp-18h]
  char v58; // [esp+1Ch] [ebp-8h]

  *(_DWORD *)(this + 420) = *(_DWORD *)(this + 416);
  v2 = *(_DWORD *)(this + 416) & 0xFFFDFFFF;
  *(_DWORD *)(this + 416) = v2;
  if ( (v2 & 0x100000) != 0 )
  {
    *(float *)(this + 388) = *(float *)(this + 584) * 0.1 + *(float *)(this + 568) + 4.0 - 12.0;
    *(float *)(this + 392) = *(float *)(this + 584) * 0.80000001 + *(float *)(this + 568) - 4.0;
    *(float *)(this + 396) = *(float *)(this + 588) * 0.5 + *(float *)(this + 572) - 6.0;
    *(float *)(this + 400) = *(float *)(this + 588) * 0.5 + *(float *)(this + 572) + 32.0 - 6.0;
  }
  *(float *)(this + 384) = (*(float *)(this + 380) - *(float *)(this + 384)) * 0.80000001 + *(float *)(this + 384);
  v3 = *(_DWORD *)(this + 416);
  if ( !v3 )
  {
    v4 = *(_DWORD *)(this + 4);
    v5 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v4 & 0x200) != 0 )
    {
      if ( (v4 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        reset_tooltip(this + 652);
      }
      else
      {
        v6 = *(_DWORD *)(this + 12);
        if ( v6 )
          *(_DWORD *)(v6 + 8) = *(_DWORD *)(this + 8);
        v7 = *(_DWORD *)(this + 8);
        if ( v7 )
          *(_DWORD *)(v7 + 12) = *(_DWORD *)(this + 12);
        else
          *((_DWORD *)v5 + 1) = *(_DWORD *)(this + 12);
        *(_DWORD *)(this + 12) = *((_DWORD *)v5 + 2);
        *((_DWORD *)v5 + 2) = this;
        v8 = *(_DWORD *)(this + 4);
        BYTE1(v8) &= ~2u;
        *(_DWORD *)(this + 4) = v8;
        reset_tooltip(this + 652);
      }
    }
    else
    {
      report_errorf(aListRemove);
      reset_tooltip(this + 652);
    }
    return;
  }
  if ( (v3 & 0x200) != 0 )
  {
    BYTE1(v3) &= ~2u;
    *(_DWORD *)(this + 416) = v3;
    v9 = (char *)MEMORY[0x4DF904] + 1448;
    v10 = *(_DWORD *)(this + 4);
    if ( (v10 & 0x200) == 0 )
    {
LABEL_16:
      report_errorf(aListRemove);
LABEL_33:
      reset_tooltip(this + 652);
      *(_DWORD *)(this + 416) = 0;
      return;
    }
    if ( (v10 & 0x40) != 0 )
    {
LABEL_18:
      report_errorf(aListRemoveNext);
      goto LABEL_33;
    }
    v11 = *(_DWORD *)(this + 12);
    if ( v11 )
      *(_DWORD *)(v11 + 8) = *(_DWORD *)(this + 8);
    v12 = *(_DWORD *)(this + 8);
    if ( v12 )
    {
      *(_DWORD *)(v12 + 12) = *(_DWORD *)(this + 12);
LABEL_32:
      *(_DWORD *)(this + 12) = *((_DWORD *)v9 + 2);
      *((_DWORD *)v9 + 2) = this;
      v17 = *(_DWORD *)(this + 4);
      BYTE1(v17) &= ~2u;
      *(_DWORD *)(this + 4) = v17;
      goto LABEL_33;
    }
    goto LABEL_31;
  }
  if ( (v3 & 0x400) == 0 )
  {
    if ( (v3 & 0x1000) != 0 )
      return;
    if ( (v3 & 0x8000) != 0 )
    {
      *(_DWORD *)(this + 548) = 0;
      v18 = *(_DWORD *)(this + 416);
LABEL_82:
      LOBYTE(v18) = v18 & 0xFD;
      *(_DWORD *)(this + 416) = v18;
      goto LABEL_83;
    }
    if ( (v3 & 2) != 0 )
      *(_DWORD *)(this + 524) = 1065353216;
    v19 = *(_DWORD *)(this + 416);
    if ( (v19 & 0x2000000) != 0
      && !*(_DWORD *)(this + 632)
      && (*((float *)MEMORY[0x4DF904] + 167) != *(float *)(this + 636)
       || *((float *)MEMORY[0x4DF904] + 168) != *(float *)(this + 640)) )
    {
      *(_DWORD *)(this + 416) = v19 | 0x4000000;
    }
    if ( (*(_DWORD *)(this + 416) & 0x80000) != 0
      && is_mouse_captured((char *)MEMORY[0x4DF904] + 656)
      && read_pressed_text_input_key_code() == *(_DWORD *)(this + 404) )
    {
      reset_tooltip(this + 652);
      v20 = *(_DWORD *)(this + 416);
      if ( (v20 & 0x1000000) != 0 )
      {
        LOBYTE(v20) = v20 | 0x20;
        *(_DWORD *)(this + 416) = v20;
      }
      else
      {
        queue_frontend_widget_flag_after_delay((int)MEMORY[0x4DF904] + 2892, this, 32);
      }
    }
    if ( !is_mouse_captured((char *)MEMORY[0x4DF904] + 656) || !border_mouse_test(this) )
    {
      v27 = *(_DWORD *)(this + 416) & 0xFFDFFFFF;
      *(_DWORD *)(this + 416) = v27;
      if ( (v27 & 0x2000) == 0 && (v27 & 4) != 0 )
        unhighlight_border((_DWORD *)this);
      *(_DWORD *)(this + 548) = 0;
      v18 = *(_DWORD *)(this + 416);
      if ( (v18 & 4) == 0 )
        goto LABEL_83;
      goto LABEL_82;
    }
    v21 = *(_DWORD *)(this + 416) | 0x20000;
    *(_DWORD *)(this + 416) = v21;
    if ( (v21 & 4) != 0 )
    {
      *(_DWORD *)(this + 524) = 1065353216;
      *(_DWORD *)(this + 540) = *(_DWORD *)(this + 536);
    }
    if ( (*(_BYTE *)(this + 416) & 8) != 0 )
      *(_DWORD *)(this + 548) = 1065353216;
    v22 = *(_DWORD *)(this + 416);
    if ( (v22 & 2) == 0 && (v22 & 4) != 0 )
    {
      if ( (v22 & 0x40000) == 0 )
        play_sound_effect(9);
      v23 = *(_DWORD *)(this + 416);
      LOBYTE(v23) = v23 | 2;
      *(_DWORD *)(this + 416) = v23;
    }
    v24 = *(_DWORD *)(this + 416);
    if ( (v24 & 0x10) != 0 )
    {
      v25 = MEMORY[0x4DF904];
      if ( *((_BYTE *)MEMORY[0x4DF904] + 278764) || (*(_BYTE *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 61) & 0x40) == 0 )
      {
LABEL_72:
        v26 = *(_DWORD *)(this + 416);
        if ( (v26 & 0x40) != 0 && *(char *)(v25[163] + 61) < 0 )
        {
          if ( (v26 & 0x1000000) != 0 )
          {
            LOBYTE(v26) = v26 | 0x80;
            *(_DWORD *)(this + 416) = v26;
          }
          else
          {
            queue_frontend_widget_flag_after_delay((int)(v25 + 723), this, 128);
          }
          play_sound_effect(8);
          reset_tooltip(this + 652);
        }
        goto LABEL_83;
      }
      if ( (v24 & 0x1000000) != 0 )
      {
        LOBYTE(v24) = v24 | 0x20;
        *(_DWORD *)(this + 416) = v24;
      }
      else
      {
        queue_frontend_widget_flag_after_delay((int)MEMORY[0x4DF904] + 2892, this, 32);
      }
      if ( ((unsigned int)&unk_800000 & *(_DWORD *)(this + 416)) == 0 )
        play_sound_effect(8);
      if ( (*(_BYTE *)(this + 660) & 0x20) == 0 )
        reset_tooltip(this + 652);
    }
    v25 = MEMORY[0x4DF904];
    goto LABEL_72;
  }
  v13 = *(float *)(this + 616) + *(float *)(this + 612);
  *(float *)(this + 612) = v13;
  if ( v13 > 1.0 )
  {
    v9 = (char *)MEMORY[0x4DF904] + 1448;
    v14 = *(_DWORD *)(this + 4);
    if ( (v14 & 0x200) == 0 )
      goto LABEL_16;
    if ( (v14 & 0x40) != 0 )
      goto LABEL_18;
    v15 = *(_DWORD *)(this + 12);
    if ( v15 )
      *(_DWORD *)(v15 + 8) = *(_DWORD *)(this + 8);
    v16 = *(_DWORD *)(this + 8);
    if ( v16 )
    {
      *(_DWORD *)(v16 + 12) = *(_DWORD *)(this + 12);
      goto LABEL_32;
    }
LABEL_31:
    *((_DWORD *)v9 + 1) = *(_DWORD *)(this + 12);
    goto LABEL_32;
  }
LABEL_83:
  v28 = *(_DWORD *)(this + 416);
  if ( (v28 & 0x8000) != 0 )
  {
    *(_DWORD *)(this + 416) = v28 & 0xFFDFFFFF;
    unhighlight_border((_DWORD *)this);
  }
  v29 = *(_DWORD *)(this + 416);
  if ( (v29 & 0x40000) != 0 )
  {
    *(_DWORD *)(this + 416) = v29 & 0xFFFBFFFF;
    *(_DWORD *)(this + 528) = *(_DWORD *)(this + 524);
    *(_DWORD *)(this + 544) = *(_DWORD *)(this + 540);
    *(_DWORD *)(this + 552) = *(_DWORD *)(this + 548);
  }
  else
  {
    *(float *)(this + 528) = (*(float *)(this + 524) - *(float *)(this + 528)) * 0.1 + *(float *)(this + 528);
    *(float *)(this + 544) = (*(float *)(this + 540) - *(float *)(this + 544)) * 0.1 + *(float *)(this + 544);
    v30 = (*(float *)(this + 548) - *(float *)(this + 552)) * 0.1 + *(float *)(this + 552);
    *(float *)(this + 552) = v30;
    v31 = *(float *)(this + 548) - v30;
    if ( v31 < 0.0 )
      v31 = -v31;
    if ( v31 < 0.1 )
      *(_DWORD *)(this + 552) = *(_DWORD *)(this + 548);
  }
  if ( (*(_DWORD *)(this + 416) & 0x2000) != 0 )
  {
    if ( is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
    {
      border_input_text(this);
      if ( (*(_DWORD *)(this + 416) & 0x2000) == 0 )
        activate_all_borders((int *)MEMORY[0x4DF904] + 723);
    }
  }
  update_twinkle_manager((_DWORD *)(this + 128));
  update_tooltip(this + 652);
  v58 = BYTE1(*(_DWORD *)(this + 416)) & 1;
  layout_frontend_widget(this);
  if ( (*(_DWORD *)(this + 416) & 0x1000) == 0 )
  {
    v32 = 1.0 - *(float *)(this + 528);
    *(float *)&v56 = *(float *)(this + 528) * *(float *)(this + 472) + v32 * *(float *)(this + 456);
    *(float *)&v54 = *(float *)(this + 528) * *(float *)(this + 468) + v32 * *(float *)(this + 452);
    *(float *)&v52 = *(float *)(this + 528) * *(float *)(this + 464) + v32 * *(float *)(this + 448);
    *(float *)&v50 = *(float *)(this + 528) * *(float *)(this + 460) + v32 * *(float *)(this + 444);
    store_color4f((_DWORD *)(this + 428), v50, v52, v54, v56);
    v33 = 1.0 - *(float *)(this + 528);
    *(float *)&v57 = *(float *)(this + 528) * *(float *)(this + 520) + v33 * *(float *)(this + 504);
    *(float *)&v55 = *(float *)(this + 528) * *(float *)(this + 516) + v33 * *(float *)(this + 500);
    *(float *)&v53 = *(float *)(this + 528) * *(float *)(this + 512) + v33 * *(float *)(this + 496);
    *(float *)&v51 = *(float *)(this + 528) * *(float *)(this + 508) + v33 * *(float *)(this + 492);
    store_color4f((_DWORD *)(this + 476), v51, v53, v55, v57);
    v34 = *(_DWORD *)(this + 416);
    if ( (v34 & 0x8000) != 0 )
    {
      *(float *)(this + 476) = *(float *)(this + 476) * 0.5;
      *(float *)(this + 480) = *(float *)(this + 480) * 0.5;
      *(float *)(this + 484) = *(float *)(this + 484) * 0.5;
      *(float *)(this + 488) = *(float *)(this + 488) * 0.5;
      *(float *)(this + 428) = *(float *)(this + 428) * 0.5;
      *(float *)(this + 432) = *(float *)(this + 432) * 0.5;
      *(float *)(this + 436) = *(float *)(this + 436) * 0.5;
      *(float *)(this + 440) = *(float *)(this + 440) * 0.5;
    }
    if ( (v34 & 0x800) == 0 )
    {
      if ( (v34 & 0x10000) != 0 )
      {
        v35 = *(_DWORD *)(this + 80);
        v36 = *(_DWORD *)(this + 84);
        *(_DWORD *)(this + 568) = *(_DWORD *)(this + 76);
        v37 = *(_DWORD *)(this + 88);
        *(_DWORD *)(this + 572) = v35;
        *(_DWORD *)(this + 584) = v36;
        *(_DWORD *)(this + 588) = v37;
      }
      else
      {
        layout_and_queue_wrapped_font_text(
          (char *)(this + 716),
          *(_DWORD *)(this + 1772),
          *(_DWORD *)(this + 1776),
          *(float *)(this + 1780),
          *(float *)(this + 1784),
          (float *)(this + 568),
          (float *)(this + 572),
          (float *)(this + 584),
          (float *)(this + 588),
          *(_DWORD *)(this + 552),
          BYTE1(byte_4DF934) & 1,
          *(_DWORD *)(this + 604),
          *(_DWORD *)(this + 608),
          0x1000000,
          this + 476,
          0,
          v58);
      }
    }
    draw_frontend_widget(this);
  }
  v38 = *(_DWORD *)(this + 632);
  if ( v38 )
    *(_DWORD *)(this + 632) = v38 - 1;
  *(_DWORD *)(this + 636) = *((_DWORD *)MEMORY[0x4DF904] + 167);
  *(_DWORD *)(this + 640) = *((_DWORD *)MEMORY[0x4DF904] + 168);
  if ( (*(_DWORD *)(this + 416) & 0x100000) != 0 )
  {
    v39 = *(_DWORD *)(this + 1820);
    v40 = *(_DWORD *)(v39 + 416);
    if ( (v40 & 0x20) != 0 )
    {
      LOBYTE(v40) = v40 & 0xDF;
      *(_DWORD *)(v39 + 416) = v40;
      v41 = *(float *)(this + 380) + 0.2;
      *(float *)(this + 380) = v41;
      if ( v41 >= 0.89999998 )
        *(_DWORD *)(this + 380) = 1065353216;
    }
    v42 = *(_DWORD *)(this + 1816);
    v43 = *(_DWORD *)(v42 + 416);
    if ( (v43 & 0x20) != 0 )
    {
      LOBYTE(v43) = v43 & 0xDF;
      *(_DWORD *)(v42 + 416) = v43;
      v44 = *(float *)(this + 380) - 0.2;
      *(float *)(this + 380) = v44;
      if ( v44 <= 0.1 )
        *(_DWORD *)(this + 380) = 0;
    }
    v45 = *(_DWORD *)(this + 1816);
    v46 = *(_DWORD *)(v45 + 416);
    if ( *(float *)(this + 380) == 0.0 )
      BYTE1(v46) |= 0x80u;
    else
      v46 &= ~0x8000u;
    *(_DWORD *)(v45 + 416) = v46;
    v47 = *(_DWORD *)(this + 1820);
    if ( *(_DWORD *)(this + 380) == 1065353216 )
    {
      v48 = *(_DWORD *)(v47 + 416);
      BYTE1(v48) |= 0x80u;
      *(_DWORD *)(v47 + 416) = v48;
    }
    else
    {
      *(_DWORD *)(v47 + 416) &= ~0x8000u;
    }
    v49 = (_DWORD *)(*(_DWORD *)(this + 1824) + 476);
    *v49 = *(_DWORD *)(this + 476);
    v49[1] = *(_DWORD *)(this + 480);
    v49[2] = *(_DWORD *)(this + 484);
    v49[3] = *(_DWORD *)(this + 488);
    *(_DWORD *)(*(_DWORD *)(this + 1824) + 524) = *(_DWORD *)(this + 524);
    *(_DWORD *)(*(_DWORD *)(this + 1824) + 528) = *(_DWORD *)(this + 528);
    sprintf(
      (char *const)(*(_DWORD *)(this + 1824) + 716),
      "%02i%%",
      (unsigned int)(__int64)(*(float *)(this + 380) * 100.0 + 0.1));
  }
}

