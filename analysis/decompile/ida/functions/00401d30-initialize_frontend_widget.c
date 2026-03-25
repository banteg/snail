/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_widget @ 0x401d30 */
/* selector: initialize_frontend_widget */

// Constructs one shell-font front-end widget, seeds its border style, text scale, alignment, colors, and optional slider-child controls, then links it into the active widget list.
float *__thiscall sub_401D30(int this, int a2, char *a3, int a4, int a5, float a6, int a7, int a8, float a9)
{
  char *v10; // eax
  int v11; // eax
  _DWORD *v12; // edi
  _DWORD *v13; // eax
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  _DWORD *v17; // eax
  _DWORD *v18; // eax
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  _DWORD *v21; // eax
  _DWORD *v22; // eax
  _DWORD *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  char v26; // al
  double v27; // st7
  int v28; // eax
  double v29; // st7
  _DWORD *v30; // eax
  _DWORD *v31; // eax
  _DWORD *v32; // eax
  int v34; // [esp+0h] [ebp-128h]
  int v35; // [esp+0h] [ebp-128h]
  float v36; // [esp+4h] [ebp-124h]
  int ArgList; // [esp+24h] [ebp-104h]
  _DWORD v38[4]; // [esp+28h] [ebp-100h] BYREF
  _DWORD v39[4]; // [esp+38h] [ebp-F0h] BYREF
  _DWORD v40[4]; // [esp+48h] [ebp-E0h] BYREF
  _DWORD v41[4]; // [esp+58h] [ebp-D0h] BYREF
  _DWORD v42[4]; // [esp+68h] [ebp-C0h] BYREF
  _DWORD v43[4]; // [esp+78h] [ebp-B0h] BYREF
  _DWORD v44[4]; // [esp+88h] [ebp-A0h] BYREF
  _DWORD v45[4]; // [esp+98h] [ebp-90h] BYREF
  _DWORD v46[4]; // [esp+A8h] [ebp-80h] BYREF
  _DWORD v47[4]; // [esp+B8h] [ebp-70h] BYREF
  _DWORD v48[4]; // [esp+C8h] [ebp-60h] BYREF
  _DWORD v49[4]; // [esp+D8h] [ebp-50h] BYREF
  _DWORD v50[4]; // [esp+E8h] [ebp-40h] BYREF
  _DWORD v51[4]; // [esp+F8h] [ebp-30h] BYREF
  _DWORD v52[4]; // [esp+108h] [ebp-20h] BYREF
  _DWORD v53[4]; // [esp+118h] [ebp-10h] BYREF

  *(_DWORD *)(this + 124) = a4;
  *(_DWORD *)(this + 72) = 5;
  *(_BYTE *)(this + 92) = 0;
  *(_DWORD *)(this + 556) = 0;
  *(_DWORD *)(this + 560) = 1101004800;
  *(_BYTE *)(this + 564) = 0;
  v10 = (char *)MEMORY[0x4DF904] + 2892;
  if ( (*(_DWORD *)(this + 4) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 8) = v10;
    *(_DWORD *)(this + 12) = *((_DWORD *)v10 + 3);
    *((_DWORD *)v10 + 3) = this;
    v11 = *(_DWORD *)(this + 12);
    if ( v11 )
      *(_DWORD *)(v11 + 8) = this;
    *(_DWORD *)(this + 4) |= 0x200u;
  }
  v12 = (_DWORD *)(this + 508);
  *(_DWORD *)(this + 656) = 0;
  *(_DWORD *)(this + 664) = this;
  *(_DWORD *)(this + 676) = 0;
  *(_DWORD *)(this + 708) = this;
  *(_DWORD *)(this + 416) = a2 | 0x40001;
  set_color_white((_DWORD *)(this + 508));
  set_color_white((_DWORD *)(this + 460));
  switch ( a4 )
  {
    case 20:
      *(_DWORD *)(this + 1772) = 0;
      *(_DWORD *)(this + 1776) = 1067869798;
      *(_DWORD *)(this + 532) = 1091567616;
      *(_DWORD *)(this + 536) = 1095761920;
      *(_DWORD *)(this + 620) = 1104150528;
      v13 = set_color_rgba(v46, 1065353216, 1057326470, 0, 1060320051);
      *(_DWORD *)(this + 492) = *v13;
      *(_DWORD *)(this + 496) = v13[1];
      *(_DWORD *)(this + 500) = v13[2];
      *(_DWORD *)(this + 504) = v13[3];
      v14 = set_color_rgba(v53, 1065353216, 1065353216, 1065353216, 1065353216);
      *v12 = *v14;
      *(_DWORD *)(this + 512) = v14[1];
      *(_DWORD *)(this + 516) = v14[2];
      *(_DWORD *)(this + 520) = v14[3];
      v15 = set_color_rgba(v50, 1051240617, 1046799589, 1056997505, 1060320051);
      *(_DWORD *)(this + 444) = *v15;
      *(_DWORD *)(this + 448) = v15[1];
      *(_DWORD *)(this + 452) = v15[2];
      *(_DWORD *)(this + 456) = v15[3];
      v16 = set_color_rgba(v42, 1058773916, 1050582687, 1060221362, 1065353216);
      goto LABEL_11;
    case 21:
      *(_DWORD *)(this + 1772) = 0;
      *(_DWORD *)(this + 1776) = 1065353216;
      *(_DWORD *)(this + 532) = 1091567616;
      *(_DWORD *)(this + 536) = 1095761920;
      *(_DWORD *)(this + 620) = 1104150528;
      v23 = set_color_rgba(v47, 1065353216, 1057326470, 0, 1060320051);
      *(_DWORD *)(this + 492) = *v23;
      *(_DWORD *)(this + 496) = v23[1];
      *(_DWORD *)(this + 500) = v23[2];
      *(_DWORD *)(this + 504) = v23[3];
      v24 = set_color_rgba(v49, 1065353216, 1065353216, 1065353216, 1065353216);
      *v12 = *v24;
      *(_DWORD *)(this + 512) = v24[1];
      *(_DWORD *)(this + 516) = v24[2];
      *(_DWORD *)(this + 520) = v24[3];
      v25 = set_color_rgba(v51, 1051240617, 1046799589, 1056997505, 1060320051);
      *(_DWORD *)(this + 444) = *v25;
      *(_DWORD *)(this + 448) = v25[1];
      *(_DWORD *)(this + 452) = v25[2];
      *(_DWORD *)(this + 456) = v25[3];
      v16 = set_color_rgba(v38, 1058773916, 1050582687, 1060221362, 1065353216);
      goto LABEL_11;
    case 22:
      *(_DWORD *)(this + 560) = 1101004800;
      *(_DWORD *)(this + 1772) = 0;
      *(_DWORD *)(this + 1776) = 1059481190;
      *(_DWORD *)(this + 532) = 1065353216;
      *(_DWORD *)(this + 536) = 1077936128;
      *(_DWORD *)(this + 620) = 0x40000000;
      *(_BYTE *)(this + 564) = 1;
      v17 = set_color_rgba(v48, 1065353216, 1057326470, 0, 1060320051);
      *(_DWORD *)(this + 492) = *v17;
      *(_DWORD *)(this + 496) = v17[1];
      *(_DWORD *)(this + 500) = v17[2];
      *(_DWORD *)(this + 504) = v17[3];
      v18 = set_color_rgba(v44, 1065353216, 1065353216, 1065353216, 1065353216);
      *v12 = *v18;
      *(_DWORD *)(this + 512) = v18[1];
      *(_DWORD *)(this + 516) = v18[2];
      *(_DWORD *)(this + 520) = v18[3];
      v19 = set_color_rgba(v52, 1051240617, 1046799589, 1056997505, 1060320051);
      *(_DWORD *)(this + 444) = *v19;
      *(_DWORD *)(this + 448) = v19[1];
      *(_DWORD *)(this + 452) = v19[2];
      *(_DWORD *)(this + 456) = v19[3];
      v16 = set_color_rgba(v39, 1058773916, 1050582687, 1060221362, 1065353216);
      goto LABEL_11;
    case 23:
      *(_DWORD *)(this + 1772) = 0;
      *(_DWORD *)(this + 1776) = 1066527621;
      *(_DWORD *)(this + 532) = 1086324736;
      *(_DWORD *)(this + 536) = 1088421888;
      *(_DWORD *)(this + 620) = 0x40000000;
      *(_DWORD *)(this + 560) = 1101004800;
      v20 = set_color_rgba(v40, 1065353216, 1057326470, 0, 1060320051);
      *(_DWORD *)(this + 492) = *v20;
      *(_DWORD *)(this + 496) = v20[1];
      *(_DWORD *)(this + 500) = v20[2];
      *(_DWORD *)(this + 504) = v20[3];
      v21 = set_color_rgba(v41, 1065353216, 1065353216, 1065353216, 1065353216);
      *v12 = *v21;
      *(_DWORD *)(this + 512) = v21[1];
      *(_DWORD *)(this + 516) = v21[2];
      *(_DWORD *)(this + 520) = v21[3];
      v22 = set_color_rgba(v43, 1051240617, 1046799589, 1056997505, 1060320051);
      *(_DWORD *)(this + 444) = *v22;
      *(_DWORD *)(this + 448) = v22[1];
      *(_DWORD *)(this + 452) = v22[2];
      *(_DWORD *)(this + 456) = v22[3];
      v16 = set_color_rgba(v45, 1058773916, 1050582687, 1060221362, 1065353216);
LABEL_11:
      *(_DWORD *)(this + 460) = *v16;
      *(_DWORD *)(this + 464) = v16[1];
      *(_DWORD *)(this + 468) = v16[2];
      *(_DWORD *)(this + 472) = v16[3];
      break;
    default:
      report_errorf(aUnknownBorderS);
      break;
  }
  *(_DWORD *)(this + 380) = 1056964608;
  *(_DWORD *)(this + 384) = 1056964608;
  *(_DWORD *)(this + 56) = 1;
  unhide_border_init((_DWORD *)this);
  sub_44E5B0((char *)(this + 716), a3);
  *(float *)(this + 1784) = a6;
  v26 = *(_BYTE *)(this + 416);
  *(_DWORD *)(this + 1780) = a5;
  *(_DWORD *)(this + 524) = 1065353216;
  if ( (v26 & 2) != 0 )
    highlight_border((_DWORD *)this);
  else
    unhighlight_border((_DWORD *)this);
  v27 = *(float *)(this + 532);
  *(_DWORD *)(this + 528) = *(_DWORD *)(this + 524);
  *(float *)(this + 540) = v27;
  *(float *)(this + 544) = v27;
  *(_DWORD *)(this + 548) = 0;
  *(_DWORD *)(this + 552) = 0;
  *(_DWORD *)(this + 604) = a8;
  *(float *)(this + 608) = a9;
  v28 = *(_DWORD *)(this + 416);
  v29 = a9 + *((float *)MEMORY[0x4DF904] + 69695);
  *(_DWORD *)(this + 632) = 1;
  *(float *)(this + 608) = v29;
  if ( (v28 & 0x100000) != 0 )
  {
    *(float *)&ArgList = a6 + 40.0;
    *(_DWORD *)(this + 1820) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v30 = set_color_rgba(v38, 1065353216, 1065353216, 1065353216, 1065353216);
    *(float *)&v34 = *((float *)MEMORY[0x4DF904] + 69695) + 458.0;
    initialize_frontend_sprite_button(
      *(_DWORD *)(this + 1820),
      (unsigned int)&unk_800000 & *(_DWORD *)(this + 416) | 0x20400814,
      42,
      v34,
      ArgList,
      v30,
      0.0,
      4);
    border_sprite_extend(*(_DWORD *)(this + 1820), 44, 43, 45, 1);
    *(_DWORD *)(this + 1816) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v31 = set_color_rgba(v38, 1065353216, 1065353216, 1065353216, 1065353216);
    *(float *)&v35 = *((float *)MEMORY[0x4DF904] + 69695) + 118.0;
    initialize_frontend_sprite_button(
      *(_DWORD *)(this + 1816),
      (unsigned int)&unk_800000 & *(_DWORD *)(this + 416) | 0x20400814,
      38,
      v35,
      ArgList,
      v31,
      0.0,
      4);
    border_sprite_extend(*(_DWORD *)(this + 1816), 40, 39, 41, 0);
    *(_DWORD *)(this + 1824) = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v32 = set_color_rgba(v38, 1065353216, 1065353216, 1065353216, 1065353216);
    v36 = *(float *)(this + 1784) + 40.0;
    initialize_frontend_widget(0x400000, (char)a00, 21, 0, LODWORD(v36), v32, 2, 0);
  }
  return layout_frontend_widget(this);
}

