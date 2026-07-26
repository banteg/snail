/*
 * mangled: _ZN8cRBorder4InitEiPciff7tColourif
 * demangled: cRBorder::Init(int, char*, int, float, float, tColour, int, float)
 * address: 0003a3ac
 * size: 2296
 */

/* cRBorder::Init(int, char*, int, float, float, tColour, int, float) */

void cRBorder::Init(cRBorder *param_1,uint param_2,char *param_3,undefined4 param_4,
                   undefined4 param_5,undefined4 param_6)

{
  undefined *puVar1;
  tColour *this;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  cRBorder *pcVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 uVar8;
  tColour *ptVar9;
  cRBorder *pcVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  float fVar14;
  undefined8 uVar15;
  float fVar16;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  undefined4 local_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 local_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  tColour local_168 [16];
  undefined4 local_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 local_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 local_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  tColour atStack_128 [16];
  undefined4 local_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 local_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  tColour atStack_e8 [16];
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 local_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  tColour atStack_68 [16];
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  *(undefined4 *)(param_1 + 0x70) = param_4;
  uVar15 = CONCAT44(param_6,in_stack_0000001c);
  *(undefined4 *)(param_1 + 0x3c) = 6;
  *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
  *(undefined4 *)(param_1 + 0x244) = 0;
  *(undefined4 *)(param_1 + 0x220) = 0;
  puVar1 = PTR__Game_001b60b8;
  uVar2 = *(uint *)(param_1 + 4);
  param_1[0x50] = (cRBorder)0x0;
  param_1[0x228] = (cRBorder)0x0;
  iVar3 = *(int *)puVar1;
  if ((uVar2 & 0x200) == 0) {
    *(int *)(param_1 + 8) = iVar3 + 0xd14;
    *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar3 + 0xd20);
    *(cRBorder **)(iVar3 + 0xd20) = param_1;
    if (*(int *)(param_1 + 0xc) != 0) {
      *(cRBorder **)(*(int *)(param_1 + 0xc) + 8) = param_1;
    }
    *(uint *)(param_1 + 4) = uVar2 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  *(undefined4 *)(param_1 + 0x288) = 0;
  *(undefined4 *)(param_1 + 0x29c) = 0;
  *(cRBorder **)(param_1 + 0x290) = param_1;
  *(uint *)(param_1 + 0x194) = param_2 | 0x40001;
  *(cRBorder **)(param_1 + 700) = param_1;
  tColour::White((tColour *)(param_1 + 0x1f0));
  tColour::White((tColour *)(param_1 + 0x1c0));
  pcVar10 = param_1 + 0x1f0;
  switch(param_4) {
  case 0x14:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3fa66666;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_38,1.0,0.52156866,0.0,0.7);
    *(undefined4 *)(param_1 + 0x1e0) = local_38;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_34;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_30;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_2c;
    tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
    *(undefined4 *)pcVar10 = local_48;
    *(undefined4 *)(param_1 + 500) = uStack_44;
    *(undefined4 *)(param_1 + 0x1f8) = uStack_40;
    *(undefined4 *)(param_1 + 0x1fc) = uStack_3c;
    tColour::tColour((tColour *)&local_58,0.8627451,0.8627451,0.8627451,0.7);
    ptVar9 = atStack_68;
    *(undefined4 *)(param_1 + 0x1b0) = local_58;
    *(undefined4 *)(param_1 + 0x1b4) = uStack_54;
    *(undefined4 *)(param_1 + 0x1b8) = uStack_50;
    *(undefined4 *)(param_1 + 0x1bc) = uStack_4c;
    this = atStack_68;
    break;
  case 0x15:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_f8,1.0,0.52156866,0.0,0.7);
    *(undefined4 *)(param_1 + 0x1e0) = local_f8;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_f4;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_f0;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_ec;
    tColour::tColour((tColour *)&local_108,1.0,1.0,1.0,1.0);
    *(undefined4 *)pcVar10 = local_108;
    *(undefined4 *)(param_1 + 500) = uStack_104;
    *(undefined4 *)(param_1 + 0x1f8) = uStack_100;
    *(undefined4 *)(param_1 + 0x1fc) = uStack_fc;
    tColour::tColour((tColour *)&local_118,0.8627451,0.8627451,0.8627451,0.7);
    ptVar9 = atStack_128;
    *(undefined4 *)(param_1 + 0x1b0) = local_118;
    *(undefined4 *)(param_1 + 0x1b4) = uStack_114;
    *(undefined4 *)(param_1 + 0x1b8) = uStack_110;
    *(undefined4 *)(param_1 + 0x1bc) = uStack_10c;
    this = atStack_128;
    break;
  case 0x16:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x20c) = 0x40400000;
    *(undefined4 *)(param_1 + 0x264) = 0x40000000;
    *(undefined4 *)(param_1 + 0x224) = 0x41c80000;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f800000;
    param_1[0x228] = (cRBorder)0x1;
    *(undefined4 *)(param_1 + 0x208) = 0x3f800000;
    tColour::tColour((tColour *)&local_78,1.0,0.52156866,0.0,0.7);
    *(undefined4 *)(param_1 + 0x1e0) = local_78;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_74;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_70;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_6c;
    tColour::tColour((tColour *)&local_88,1.0,1.0,1.0,1.0);
    *(undefined4 *)pcVar10 = local_88;
    *(undefined4 *)(param_1 + 500) = uStack_84;
    *(undefined4 *)(param_1 + 0x1f8) = uStack_80;
    *(undefined4 *)(param_1 + 0x1fc) = uStack_7c;
    tColour::tColour((tColour *)&local_98,0.8627451,0.8627451,0.8627451,0.7);
    *(undefined4 *)(param_1 + 0x1b0) = local_98;
    *(undefined4 *)(param_1 + 0x1b4) = uStack_94;
    *(undefined4 *)(param_1 + 0x1b8) = uStack_90;
    *(undefined4 *)(param_1 + 0x1bc) = uStack_8c;
    tColour::tColour((tColour *)&local_a8,0.98039216,0.98039216,0.98039216,1.0);
    *(undefined4 *)(param_1 + 0x1c0) = local_a8;
    *(undefined4 *)(param_1 + 0x1c4) = uStack_a4;
    *(undefined4 *)(param_1 + 0x1c8) = uStack_a0;
    *(undefined4 *)(param_1 + 0x1cc) = uStack_9c;
    goto LAB_0003a4b8;
  case 0x17:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3f91eb85;
    *(undefined4 *)(param_1 + 0x20c) = 0x40e00000;
    *(undefined4 *)(param_1 + 0x264) = 0x40000000;
    *(undefined4 *)(param_1 + 0x208) = 0x40c00000;
    *(undefined4 *)(param_1 + 0x224) = 0x41a00000;
    tColour::tColour((tColour *)&local_b8,1.0,0.52156866,0.0,0.7);
    *(undefined4 *)(param_1 + 0x1e0) = local_b8;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_b4;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_b0;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_ac;
    tColour::tColour((tColour *)&local_c8,1.0,1.0,1.0,1.0);
    *(undefined4 *)pcVar10 = local_c8;
    *(undefined4 *)(param_1 + 500) = uStack_c4;
    *(undefined4 *)(param_1 + 0x1f8) = uStack_c0;
    *(undefined4 *)(param_1 + 0x1fc) = uStack_bc;
    tColour::tColour((tColour *)&local_d8,0.8627451,0.8627451,0.8627451,0.7);
    ptVar9 = atStack_e8;
    *(undefined4 *)(param_1 + 0x1b0) = local_d8;
    *(undefined4 *)(param_1 + 0x1b4) = uStack_d4;
    *(undefined4 *)(param_1 + 0x1b8) = uStack_d0;
    *(undefined4 *)(param_1 + 0x1bc) = uStack_cc;
    this = atStack_e8;
    break;
  case 0x18:
    *(undefined4 *)(param_1 + 0x6e4) = 0;
    *(undefined4 *)(param_1 + 0x6e8) = 0x3fa66666;
    *(undefined4 *)(param_1 + 0x208) = 0x41100000;
    *(undefined4 *)(param_1 + 0x20c) = 0x41500000;
    *(undefined4 *)(param_1 + 0x264) = 0x41d00000;
    tColour::tColour((tColour *)&local_138,1.0,1.0,1.0,1.0);
    *(undefined4 *)(param_1 + 0x1e0) = local_138;
    *(undefined4 *)(param_1 + 0x1e4) = uStack_134;
    *(undefined4 *)(param_1 + 0x1e8) = uStack_130;
    *(undefined4 *)(param_1 + 0x1ec) = uStack_12c;
    tColour::tColour((tColour *)&local_148,1.0,1.0,1.0,1.0);
    *(undefined4 *)pcVar10 = local_148;
    *(undefined4 *)(param_1 + 500) = uStack_144;
    *(undefined4 *)(param_1 + 0x1f8) = uStack_140;
    *(undefined4 *)(param_1 + 0x1fc) = uStack_13c;
    tColour::tColour((tColour *)&local_158,0.8627451,0.8627451,0.8627451,0.7);
    ptVar9 = local_168;
    *(undefined4 *)(param_1 + 0x1b0) = local_158;
    *(undefined4 *)(param_1 + 0x1b4) = uStack_154;
    *(undefined4 *)(param_1 + 0x1b8) = uStack_150;
    *(undefined4 *)(param_1 + 0x1bc) = uStack_14c;
    this = local_168;
    break;
  default:
    RShellError("Unknown Border Style Requested");
    goto LAB_0003a4b8;
  }
  tColour::tColour(this,0.98039216,0.98039216,0.98039216,1.0);
  uVar6 = *(undefined4 *)(ptVar9 + 4);
  uVar4 = *(undefined4 *)(ptVar9 + 8);
  uVar8 = *(undefined4 *)(ptVar9 + 0xc);
  *(undefined4 *)(param_1 + 0x1c0) = *(undefined4 *)ptVar9;
  *(undefined4 *)(param_1 + 0x1c4) = uVar6;
  *(undefined4 *)(param_1 + 0x1c8) = uVar4;
  *(undefined4 *)(param_1 + 0x1cc) = uVar8;
LAB_0003a4b8:
  *(undefined4 *)(param_1 + 0x170) = 0x3f000000;
  *(undefined4 *)(param_1 + 0x174) = 0x3f000000;
  *(uint *)(param_1 + 0x194) = *(uint *)(param_1 + 0x194) & 0xffffefff;
  *(undefined4 *)(param_1 + 0x38) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  Rstrcpy((char *)(param_1 + 0x2c4),param_3);
  uVar2 = *(uint *)(param_1 + 0x194);
  bVar13 = (uVar2 & 2) != 0;
  *(undefined4 *)(param_1 + 0x6ec) = param_5;
  pcVar5 = param_1 + 0x6f0;
  *(int *)pcVar5 = (int)((ulonglong)uVar15 >> 0x20);
  pcVar10 = pcVar5;
  if (bVar13) {
    pcVar10 = *(cRBorder **)(param_1 + 0x20c);
  }
  *(undefined4 *)(param_1 + 0x200) = 0x3f800000;
  if (bVar13) {
    *(cRBorder **)(param_1 + 0x210) = pcVar10;
    uVar6 = *(undefined4 *)(param_1 + 0x200);
  }
  else {
    uVar6 = 0;
    *(undefined4 *)(param_1 + 0x200) = 0;
  }
  *(float *)(param_1 + 600) = (float)uVar15;
  *(undefined4 *)(param_1 + 0x204) = uVar6;
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  if (bVar13) {
    uVar6 = *(undefined4 *)(param_1 + 0x208);
  }
  else {
    uVar6 = *(undefined4 *)(param_1 + 0x208);
  }
  *(undefined4 *)(param_1 + 0x254) = in_stack_00000018;
  if (!bVar13) {
    *(undefined4 *)(param_1 + 0x210) = uVar6;
  }
  *(undefined4 *)(param_1 + 0x214) = uVar6;
  *(undefined4 *)(param_1 + 0x210) = uVar6;
  puVar1 = PTR__Game_001b60b8;
  fVar14 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x43e08);
  *(undefined4 *)(param_1 + 0x270) = 1;
  *(float *)(param_1 + 600) = (float)uVar15 + fVar14;
  if ((uVar2 & 0x100000) != 0) {
    iVar12 = *(int *)puVar1;
    iVar3 = 0;
    pcVar7 = section_00001504.segname + iVar12 + 0xc;
    do {
      if (*(int *)pcVar7 == 0) {
        iVar11 = iVar12 + iVar3 * 0x71c + 0x138c;
        *(undefined4 *)((int)&section_00001504 + iVar3 * 0x71c + iVar12 + 0x18) =
             *(undefined4 *)(iVar12 + 0x2d8);
        goto LAB_0003a5e8;
      }
      iVar3 = iVar3 + 1;
      pcVar7 = pcVar7 + 0x71c;
    } while (iVar3 != 0x96);
    RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    uVar2 = *(uint *)(param_1 + 0x194);
    iVar11 = 0;
LAB_0003a5e8:
    *(int *)(param_1 + 0x714) = iVar11;
    fVar14 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x43e08) + 458.0;
    fVar16 = (float)((ulonglong)uVar15 >> 0x20) + 40.0;
    tColour::tColour((tColour *)&local_178,1.0,1.0,1.0,1.0);
    Init(iVar11,uVar2 & 0x800000 | 0x20400814,0x1c,fVar14,fVar16,local_178,uStack_174,uStack_170,
         uStack_16c,0,1);
    iVar12 = *(int *)(param_1 + 0x714);
    iVar3 = 0;
    *(undefined4 *)(iVar12 + 0x54) = 0x1e;
    *(undefined4 *)(iVar12 + 0x58) = 0x1f;
    *(undefined1 *)(iVar12 + 0x50) = 1;
    *(undefined4 *)(iVar12 + 0x5c) = 0x1d;
    *(undefined1 *)(iVar12 + 0x51) = 1;
    *(undefined4 *)(iVar12 + 0x210) = 0;
    *(undefined4 *)(iVar12 + 0x208) = 0;
    *(undefined4 *)(iVar12 + 0x20c) = 0;
    iVar12 = *(int *)PTR__Game_001b60b8;
    pcVar7 = section_00001504.segname + iVar12 + 0xc;
    do {
      if (*(int *)pcVar7 == 0) {
        iVar11 = iVar12 + iVar3 * 0x71c + 0x138c;
        *(undefined4 *)((int)&section_00001504 + iVar3 * 0x71c + iVar12 + 0x18) =
             *(undefined4 *)(iVar12 + 0x2d8);
        goto LAB_0003a708;
      }
      iVar3 = iVar3 + 1;
      pcVar7 = pcVar7 + 0x71c;
    } while (iVar3 != 0x96);
    RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    iVar11 = 0;
LAB_0003a708:
    uVar2 = *(uint *)(param_1 + 0x194);
    *(int *)(param_1 + 0x710) = iVar11;
    puVar1 = PTR__Game_001b60b8;
    fVar14 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x43e08) + 118.0;
    tColour::tColour((tColour *)&local_188,1.0,1.0,1.0,1.0);
    Init(iVar11,uVar2 & 0x800000 | 0x20400814,0x18,fVar14,fVar16,local_188,uStack_184,uStack_180,
         uStack_17c,0,1);
    iVar12 = *(int *)(param_1 + 0x710);
    iVar3 = 0;
    *(undefined4 *)(iVar12 + 0x54) = 0x1a;
    *(undefined4 *)(iVar12 + 0x58) = 0x1b;
    *(undefined1 *)(iVar12 + 0x50) = 1;
    *(undefined4 *)(iVar12 + 0x5c) = 0x19;
    *(undefined1 *)(iVar12 + 0x51) = 0;
    *(undefined4 *)(iVar12 + 0x210) = 0;
    *(undefined4 *)(iVar12 + 0x208) = 0;
    *(undefined4 *)(iVar12 + 0x20c) = 0;
    iVar12 = *(int *)puVar1;
    pcVar7 = section_00001504.segname + iVar12 + 0xc;
    do {
      if (*(int *)pcVar7 == 0) {
        iVar11 = iVar12 + iVar3 * 0x71c + 0x138c;
        *(undefined4 *)((int)&section_00001504 + iVar3 * 0x71c + iVar12 + 0x18) =
             *(undefined4 *)(iVar12 + 0x2d8);
        goto LAB_0003a818;
      }
      iVar3 = iVar3 + 1;
      pcVar7 = pcVar7 + 0x71c;
    } while (iVar3 != 0x96);
    RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    iVar11 = 0;
LAB_0003a818:
    fVar14 = *(float *)pcVar5 + 40.0;
    *(int *)(param_1 + 0x718) = iVar11;
    tColour::tColour((tColour *)&local_198,1.0,1.0,1.0,1.0);
    Init(iVar11,0x400000,"00%",0x15,0,fVar14,local_198,uStack_194,uStack_190,uStack_18c,2,0);
  }
  RePosition(param_1);
  return;
}
