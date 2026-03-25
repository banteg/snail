/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_sprite_button @ 0x401a70 */
/* selector: initialize_frontend_sprite_button */

// Constructs one sprite-backed front-end child control, including arrow-button animation ids, authored anchor, and immediate-vs-delayed click behavior.
float *__thiscall sub_401A70(int this, int a2, int a3, int a4, int a5, _DWORD *a6, float a7, int a8)
{
  char *v8; // eax
  int v10; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  double v16; // st7
  double v17; // st7
  int v18; // edx
  _DWORD v20[4]; // [esp+8h] [ebp-10h] BYREF

  v8 = (char *)MEMORY[0x4DF904] + 2892;
  if ( (*(_DWORD *)(this + 4) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 8) = v8;
    *(_DWORD *)(this + 12) = *((_DWORD *)v8 + 3);
    *((_DWORD *)v8 + 3) = this;
    v10 = *(_DWORD *)(this + 12);
    if ( v10 )
      *(_DWORD *)(v10 + 8) = this;
    *(_DWORD *)(this + 4) |= 0x200u;
  }
  *(_DWORD *)(this + 72) = 5;
  *(_BYTE *)(this + 92) = 0;
  *(_DWORD *)(this + 656) = 0;
  *(_DWORD *)(this + 664) = this;
  *(_DWORD *)(this + 676) = 0;
  *(_DWORD *)(this + 708) = this;
  *(_DWORD *)(this + 556) = 0;
  *(_DWORD *)(this + 560) = 1101004800;
  *(_BYTE *)(this + 564) = 0;
  *(_DWORD *)(this + 376) = 1082130432;
  *(_DWORD *)(this + 1772) = 0;
  *(_DWORD *)(this + 1776) = 1065353216;
  *(_DWORD *)(this + 532) = 1092616192;
  *(_DWORD *)(this + 536) = 1097859072;
  *(_DWORD *)(this + 620) = 1101004800;
  *(_DWORD *)(this + 600) = 0;
  *(_DWORD *)(this + 56) = 1;
  unhide_border_init((_DWORD *)this);
  *(_DWORD *)(this + 1784) = a5;
  *(_DWORD *)(this + 416) = a2 | 0x40801;
  *(_DWORD *)(this + 420) = a2 | 0x40801;
  *(_BYTE *)(this + 716) = 0;
  *(_DWORD *)(this + 1780) = a4;
  *(_DWORD *)(this + 444) = *a6;
  *(_DWORD *)(this + 448) = a6[1];
  *(_DWORD *)(this + 452) = a6[2];
  *(_DWORD *)(this + 456) = a6[3];
  *(_DWORD *)(this + 460) = *a6;
  *(_DWORD *)(this + 464) = a6[1];
  *(_DWORD *)(this + 468) = a6[2];
  *(_DWORD *)(this + 472) = a6[3];
  v11 = set_color_rgba(v20, 1065353216, 1065353216, 1065353216, 1065353216);
  *(_DWORD *)(this + 492) = *v11;
  *(_DWORD *)(this + 496) = v11[1];
  *(_DWORD *)(this + 500) = v11[2];
  *(_DWORD *)(this + 504) = v11[3];
  v12 = set_color_rgba(v20, 1065353216, 1065353216, 1065353216, 1065353216);
  *(_DWORD *)(this + 508) = *v12;
  *(_DWORD *)(this + 512) = v12[1];
  *(_DWORD *)(this + 516) = v12[2];
  *(_DWORD *)(this + 520) = v12[3];
  if ( (*(_BYTE *)(this + 416) & 2) != 0 )
  {
    v13 = *(_DWORD *)(this + 536);
    *(_DWORD *)(this + 524) = 1065353216;
    *(_DWORD *)(this + 540) = v13;
  }
  else
  {
    v14 = *(_DWORD *)(this + 532);
    *(_DWORD *)(this + 524) = 0;
    *(_DWORD *)(this + 540) = v14;
  }
  v15 = *(_DWORD *)(this + 540);
  *(_DWORD *)(this + 528) = *(_DWORD *)(this + 524);
  *(_DWORD *)(this + 544) = v15;
  *(_DWORD *)(this + 548) = 0;
  *(_DWORD *)(this + 552) = 0;
  *(_DWORD *)(this + 604) = 0;
  *(float *)(this + 608) = a7;
  v16 = a7 + *((float *)MEMORY[0x4DF904] + 69695);
  *(_DWORD *)(this + 568) = a4;
  *(_DWORD *)(this + 572) = a5;
  *(float *)(this + 608) = v16;
  *(float *)(this + 584) = (float)*(int *)(LODWORD(unk_78FF90[a3]) + 4);
  v17 = (double)*(int *)(LODWORD(unk_78FF90[a3]) + 8);
  *(_DWORD *)(this + 592) = *(_DWORD *)(this + 584);
  *(_DWORD *)(this + 624) = a3;
  *(float *)(this + 588) = v17;
  v18 = *(_DWORD *)(this + 588);
  *(_DWORD *)(this + 1780) = a4;
  *(_DWORD *)(this + 596) = v18;
  *(_DWORD *)(this + 1784) = a5;
  *(_DWORD *)(this + 628) = a8;
  *(_DWORD *)(this + 612) = 0;
  *(_DWORD *)(this + 616) = 0;
  return layout_frontend_widget(this);
}

