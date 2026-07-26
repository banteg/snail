/*
 * mangled: _ZN8cRBorder4InitEiPciff7tColourif
 * demangled: cRBorder::Init(int, char*, int, float, float, tColour, int, float)
 * address: 0005e85c
 * size: 1712
 */

/* cRBorder::Init(int, char*, int, float, float, tColour, int, float) */

void cRBorder::Init(cRBorder *param_1,uint param_2,char *param_3,undefined4 param_4,
                   undefined4 param_5,float param_6)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  uint uVar4;
  float fVar5;
  tColour *ptVar6;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float extraout_s0_06;
  float extraout_s0_07;
  float extraout_s0_08;
  float extraout_s0_09;
  float extraout_s0_10;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s1_06;
  float extraout_s1_07;
  float extraout_s1_08;
  float extraout_s1_09;
  float extraout_s1_10;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s2_06;
  float extraout_s2_07;
  float extraout_s2_08;
  float extraout_s2_09;
  float extraout_s2_10;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  float extraout_s3_06;
  float extraout_s3_07;
  float extraout_s3_08;
  float extraout_s3_09;
  float extraout_s3_10;
  float fVar7;
  float fVar8;
  undefined4 in_stack_00000018;
  float in_stack_0000001c;
  float local_1d4;
  undefined4 local_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  tColour *local_1b4;
  tColour *local_1b0;
  tColour *local_1ac;
  tColour local_1a8 [16];
  tColour local_198 [16];
  tColour local_188 [16];
  tColour local_178 [16];
  tColour local_168 [16];
  undefined4 local_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 local_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  tColour atStack_138 [16];
  tColour atStack_128 [16];
  tColour atStack_118 [16];
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  tColour atStack_f8 [16];
  tColour atStack_e8 [16];
  tColour local_d8 [16];
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  tColour atStack_b8 [16];
  tColour atStack_a8 [16];
  tColour atStack_98 [16];
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  tColour atStack_78 [16];
  tColour atStack_68 [16];
  tColour atStack_58 [16];
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  *(undefined4 *)(param_1 + 0x220) = 0;
  uVar4 = *(uint *)(param_1 + 4);
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x70) = param_4;
  param_1[0x228] = (cRBorder)0x0;
  iVar1 = Game;
  *(undefined4 *)(param_1 + 0x3c) = 6;
  param_1[0x50] = (cRBorder)0x0;
  if ((uVar4 & 0x200) == 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0xd20);
    *(int *)(param_1 + 8) = iVar1 + 0xd14;
    *(undefined4 *)(param_1 + 0xc) = uVar2;
    *(cRBorder **)(iVar1 + 0xd20) = param_1;
    *(uint *)(param_1 + 4) = uVar4 | 0x200;
    if (*(int *)(param_1 + 0xc) != 0) {
      *(cRBorder **)(*(int *)(param_1 + 0xc) + 8) = param_1;
    }
  }
  else {
    RShellError("List ADDafter");
  }
  *(uint *)(param_1 + 0x194) = param_2 | 0x40001;
  *(cRBorder **)(param_1 + 0x290) = param_1;
  *(undefined4 *)(param_1 + 0x29c) = 0;
  *(undefined4 *)(param_1 + 0x288) = 0;
  *(cRBorder **)(param_1 + 700) = param_1;
  tColour::White();
  tColour::White();
  switch(param_4) {
  case 0x14:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3fa66666;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    local_1b4 = atStack_68;
    ptVar6 = atStack_58;
    local_1b0 = atStack_78;
    local_c8 = local_48;
    uStack_c4 = uStack_44;
    uStack_c0 = uStack_40;
    uStack_bc = uStack_3c;
    fVar7 = extraout_s0_06;
    fVar3 = extraout_s1_06;
    fVar5 = extraout_s2_06;
    fVar8 = extraout_s3_06;
    break;
  case 0x15:
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_108,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    local_1b4 = atStack_128;
    ptVar6 = atStack_118;
    local_1b0 = atStack_138;
    local_c8 = local_108;
    uStack_c4 = uStack_104;
    uStack_c0 = uStack_100;
    uStack_bc = uStack_fc;
    fVar7 = extraout_s0_08;
    fVar3 = extraout_s1_08;
    fVar5 = extraout_s2_08;
    fVar8 = extraout_s3_08;
    break;
  case 0x16:
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x208) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x20c) = 0x40400000;
    param_1[0x228] = (cRBorder)0x1;
    *(undefined4 *)(param_1 + 0x264) = 0x40000000;
    *(undefined4 *)(param_1 + 0x224) = 0x41c80000;
    tColour::tColour((tColour *)&local_88,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    local_1b4 = atStack_a8;
    ptVar6 = atStack_98;
    local_1b0 = atStack_b8;
    local_c8 = local_88;
    uStack_c4 = uStack_84;
    uStack_c0 = uStack_80;
    uStack_bc = uStack_7c;
    fVar7 = extraout_s0_09;
    fVar3 = extraout_s1_09;
    fVar5 = extraout_s2_09;
    fVar8 = extraout_s3_09;
    break;
  case 0x17:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f91eb85;
    *(undefined4 *)(param_1 + 0x208) = 0x40c00000;
    *(undefined4 *)(param_1 + 0x20c) = 0x40e00000;
    *(undefined4 *)(param_1 + 0x264) = 0x40000000;
    *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
    tColour::tColour((tColour *)&local_c8,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    local_1b4 = atStack_e8;
    ptVar6 = local_d8;
    local_1b0 = atStack_f8;
    fVar7 = extraout_s0_10;
    fVar3 = extraout_s1_10;
    fVar5 = extraout_s2_10;
    fVar8 = extraout_s3_10;
    break;
  case 0x18:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3fa66666;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_148,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    local_1b4 = local_168;
    local_1b0 = local_178;
    *(undefined4 *)(param_1 + 0x1e0) = local_148;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_144;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_140;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_13c;
    tColour::tColour((tColour *)&local_158,extraout_s0_00,extraout_s1_00,extraout_s2_00,
                     extraout_s3_00);
    fVar7 = extraout_s0_01;
    fVar3 = extraout_s1_01;
    fVar5 = extraout_s2_01;
    fVar8 = extraout_s3_01;
    goto LAB_0005ea38;
  default:
    RShellError("Unknown Border Style Requested");
    goto LAB_0005ea8c;
  }
  *(undefined4 *)(param_1 + 0x1e0) = local_c8;
  *(undefined4 *)(param_1 + 0x1e4) = uStack_c4;
  *(undefined4 *)(param_1 + 0x1e8) = uStack_c0;
  *(undefined4 *)(param_1 + 0x1ec) = uStack_bc;
  tColour::tColour(ptVar6,fVar7,fVar3,fVar5,fVar8);
  local_158 = *(undefined4 *)ptVar6;
  uStack_154 = *(undefined4 *)(ptVar6 + 4);
  uStack_150 = *(undefined4 *)(ptVar6 + 8);
  uStack_14c = *(undefined4 *)(ptVar6 + 0xc);
  fVar7 = extraout_s0_07;
  fVar3 = extraout_s1_07;
  fVar5 = extraout_s2_07;
  fVar8 = extraout_s3_07;
LAB_0005ea38:
  *(undefined4 *)(param_1 + 0x1f0) = local_158;
  *(undefined4 *)(param_1 + 500) = uStack_154;
  *(undefined4 *)(param_1 + 0x1f8) = uStack_150;
  *(undefined4 *)(param_1 + 0x1fc) = uStack_14c;
  tColour::tColour(local_1b4,fVar7,fVar3,fVar5,fVar8);
  fVar7 = *(float *)(local_1b4 + 4);
  fVar3 = *(float *)(local_1b4 + 8);
  fVar5 = *(float *)(local_1b4 + 0xc);
  *(float *)(param_1 + 0x1b0) = *(float *)local_1b4;
  *(float *)(param_1 + 0x1b4) = fVar7;
  *(float *)(param_1 + 0x1b8) = fVar3;
  *(float *)(param_1 + 0x1bc) = fVar5;
  tColour::tColour(local_1b0,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02);
  fVar7 = *(float *)(local_1b0 + 4);
  fVar3 = *(float *)(local_1b0 + 8);
  fVar5 = *(float *)(local_1b0 + 0xc);
  *(float *)(param_1 + 0x1c0) = *(float *)local_1b0;
  *(float *)(param_1 + 0x1c4) = fVar7;
  *(float *)(param_1 + 0x1c8) = fVar3;
  *(float *)(param_1 + 0x1cc) = fVar5;
LAB_0005ea8c:
  *(undefined4 *)(param_1 + 0x174) = 0x3f000000;
  *(undefined4 *)(param_1 + 0x170) = 0x3f000000;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  UnHideInit(param_1);
  Rstrcpy((char *)(param_1 + 0x2c4),param_3);
  *(float *)(param_1 + 0x6f0) = param_6;
  *(undefined4 *)(param_1 + 0x6ec) = param_5;
  *(undefined4 *)(param_1 + 0x200) = 0x3f800000;
  if ((*(uint *)(param_1 + 0x194) & 2) == 0) {
    UnHighlight(param_1);
  }
  else {
    Highlight(param_1);
  }
  *(float *)(param_1 + 600) = in_stack_0000001c;
  iVar1 = Game;
  *(undefined4 *)(param_1 + 0x214) = *(undefined4 *)(param_1 + 0x208);
  *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_1 + 0x208);
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  *(undefined4 *)(param_1 + 0x204) = *(undefined4 *)(param_1 + 0x200);
  fVar7 = *(float *)(iVar1 + 0x43e08);
  *(undefined4 *)(param_1 + 0x270) = 1;
  *(undefined4 *)(param_1 + 0x254) = in_stack_00000018;
  *(float *)(param_1 + 600) = in_stack_0000001c + fVar7;
  if ((*(uint *)(param_1 + 0x194) & 0x100000) != 0) {
    param_6 = param_6 + 40.0;
    local_1b8 = cRBorderManager::GetBorder((cRBorderManager *)(iVar1 + 0xd14));
    uVar4 = *(uint *)(param_1 + 0x194);
    fVar7 = *(float *)(Game + 0x43e08);
    *(undefined4 *)(param_1 + 0x714) = local_1b8;
    tColour::tColour(local_188,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03);
    local_1b4 = (tColour *)&local_1d4;
    local_1b0 = local_198;
    local_1ac = local_1a8;
    local_1c4 = 0;
    local_1c0 = 1;
    Init(local_1b8,uVar4 & 0x800000 | 0x20400814,0x1c,fVar7 + 458.0,param_6);
    SpriteExtend(*(cRBorder **)(param_1 + 0x714),0x1e,0x1d,0x1f,true);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    uVar4 = *(uint *)(param_1 + 0x194);
    fVar8 = *(float *)(Game + 0x43e08);
    *(undefined4 *)(param_1 + 0x710) = uVar2;
    tColour::tColour(local_1b0,extraout_s0_04,extraout_s1_04,extraout_s2_04,extraout_s3_04);
    ptVar6 = local_1b4;
    fVar7 = *(float *)(local_1b0 + 4);
    fVar3 = *(float *)(local_1b0 + 8);
    fVar5 = *(float *)(local_1b0 + 0xc);
    *(float *)local_1b4 = *(float *)local_1b0;
    *(float *)(ptVar6 + 4) = fVar7;
    *(float *)(ptVar6 + 8) = fVar3;
    *(float *)(ptVar6 + 0xc) = fVar5;
    local_1c4 = 0;
    local_1c0 = 1;
    Init(uVar2,uVar4 & 0x800000 | 0x20400814,0x18,fVar8 + 118.0,param_6);
    SpriteExtend(*(cRBorder **)(param_1 + 0x710),0x1a,0x19,0x1b,false);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    fVar7 = *(float *)(param_1 + 0x6f0);
    *(undefined4 *)(param_1 + 0x718) = uVar2;
    tColour::tColour(local_1ac,extraout_s0_05,extraout_s1_05,extraout_s2_05,extraout_s3_05);
    local_1d0 = *(undefined4 *)local_1ac;
    uStack_1cc = *(undefined4 *)(local_1ac + 4);
    uStack_1c8 = *(undefined4 *)(local_1ac + 8);
    local_1c4 = *(undefined4 *)(local_1ac + 0xc);
    local_1bc = 0;
    local_1c0 = 2;
    local_1d4 = fVar7 + 40.0;
    Init(uVar2,0x400000,&DAT_00093278,0x15,0);
  }
  RePosition(param_1);
  return;
}
