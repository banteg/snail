/*
 * mangled: _ZN6cRExit4InitEv
 * demangled: cRExit::Init()
 * address: 00061dc4
 * size: 1748
 */

/* cRExit::Init() */

void __thiscall cRExit::Init(cRExit *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  tColour *ptVar5;
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
  float extraout_s0_11;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float fVar6;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s1_04;
  float extraout_s1_05;
  float extraout_s1_06;
  float extraout_s1_07;
  float extraout_s1_08;
  float extraout_s1_09;
  float extraout_s1_10;
  float extraout_s1_11;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float fVar7;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s2_04;
  float extraout_s2_05;
  float extraout_s2_06;
  float extraout_s2_07;
  float extraout_s2_08;
  float extraout_s2_09;
  float extraout_s2_10;
  float extraout_s2_11;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  float fVar8;
  float extraout_s3_02;
  float extraout_s3_03;
  float extraout_s3_04;
  float extraout_s3_05;
  float extraout_s3_06;
  float extraout_s3_07;
  float extraout_s3_08;
  float extraout_s3_09;
  float extraout_s3_10;
  float extraout_s3_11;
  float fVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  tColour *local_168;
  tColour *local_164;
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 local_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 local_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  tColour atStack_110 [16];
  tColour atStack_100 [16];
  tColour atStack_f0 [16];
  tColour atStack_e0 [16];
  tColour local_d0 [16];
  tColour local_c0 [16];
  tColour local_b0 [16];
  tColour local_a0 [16];
  tColour local_90 [16];
  tColour atStack_80 [16];
  tColour atStack_70 [16];
  tColour atStack_60 [16];
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;

  iVar1 = DAT_00062130;
  iVar3 = DAT_0006212c + 0x61de0;
  cRBorderManager::HideBorders((cRBorderManager *)(**(int **)(iVar3 + DAT_00062130) + 0xd14));
  uVar11 = DAT_00062174;
  uVar2 = DAT_00062128;
  switch(*(undefined4 *)this) {
  case 2:
    goto LAB_00061fbc;
  case 3:
    piVar4 = *(int **)(iVar3 + iVar1);
    local_168 = atStack_100;
    ptVar5 = atStack_f0;
    iVar1 = *piVar4;
    local_164 = atStack_110;
    goto LAB_00061fe8;
  case 4:
    piVar4 = *(int **)(iVar3 + iVar1);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    tColour::tColour((tColour *)&local_120,extraout_s0_05,extraout_s1_05,extraout_s2_05,
                     extraout_s3_05);
    cRBorder::Init(uVar2,0x400002,iVar3 + DAT_00062134,0x14,DAT_00062174,DAT_00062140,local_120,
                   uStack_11c,uStack_118,uStack_114,2,DAT_00062174);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar2;
    tColour::tColour((tColour *)&local_130,extraout_s0_06,extraout_s1_06,extraout_s2_06,
                     extraout_s3_06);
    cRBorder::Init(uVar2,0x40000014,iVar3 + DAT_00062138,0x14,DAT_00062144,DAT_00062148,local_130,
                   uStack_12c,uStack_128,uStack_124,2,DAT_0006214c);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar10;
    tColour::tColour((tColour *)&local_140,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    uVar11 = DAT_00062150;
    uVar2 = DAT_00062154;
    goto LAB_00061f7c;
  case 5:
    piVar4 = *(int **)(iVar3 + iVar1);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar2;
    tColour::tColour((tColour *)&local_150,extraout_s0_08,extraout_s1_08,extraout_s2_08,
                     extraout_s3_08);
    cRBorder::Init(uVar2,0x14,iVar3 + DAT_00062138,0x14,DAT_00062158,DAT_0006215c,local_150,
                   uStack_14c,uStack_148,uStack_144,0,uVar11);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar2;
    tColour::tColour((tColour *)&local_160,extraout_s0_09,extraout_s1_09,extraout_s2_09,
                     extraout_s3_09);
    cRBorder::Init(uVar2,0x14,iVar3 + DAT_0006213c,0x14,DAT_00062160,DAT_00062164,local_160,
                   uStack_15c,uStack_158,uStack_154,0,uVar11);
    break;
  case 6:
    break;
  case 7:
LAB_00061fbc:
    piVar4 = *(int **)(iVar3 + iVar1);
    ptVar5 = local_c0;
    local_164 = atStack_e0;
    iVar1 = *piVar4;
    local_168 = local_d0;
LAB_00061fe8:
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(iVar1 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar10;
    tColour::tColour(ptVar5,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02);
    cRBorder::Init(uVar10,0x400002,iVar3 + DAT_00062134,0x14,uVar11,DAT_00062140,
                   *(undefined4 *)ptVar5,*(undefined4 *)(ptVar5 + 4),*(undefined4 *)(ptVar5 + 8),
                   *(undefined4 *)(ptVar5 + 0xc),2,uVar11);
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar10;
    tColour::tColour(local_168,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03);
    cRBorder::Init(uVar10,0x40000014,iVar3 + DAT_00062138,0x14,uVar11,uVar2,*(undefined4 *)local_168
                   ,*(undefined4 *)(local_168 + 4),*(undefined4 *)(local_168 + 8),
                   *(undefined4 *)(local_168 + 0xc),2,DAT_0006214c);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar10;
    fVar9 = extraout_s0_04;
    fVar6 = extraout_s1_04;
    fVar7 = extraout_s2_04;
    fVar8 = extraout_s3_04;
LAB_00061f68:
    tColour::tColour(local_164,fVar9,fVar6,fVar7,fVar8);
    local_140 = *(undefined4 *)local_164;
    uStack_13c = *(undefined4 *)(local_164 + 4);
    uStack_138 = *(undefined4 *)(local_164 + 8);
    uStack_134 = *(undefined4 *)(local_164 + 0xc);
LAB_00061f7c:
    cRBorder::Init(uVar10,0x14,iVar3 + DAT_0006213c,0x14,uVar11,uVar2,local_140,uStack_13c,
                   uStack_138,uStack_134,2,DAT_00062124);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
    break;
  case 8:
    break;
  case 9:
    piVar4 = *(int **)(iVar3 + iVar1);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    fVar9 = *(float *)(this + 0xc) - DAT_00062168;
    *(undefined4 *)(this + 0x14) = uVar2;
    tColour::tColour((tColour *)&local_40,extraout_s0_10,extraout_s1_10,extraout_s2_10,
                     extraout_s3_10);
    cRBorder::Init(uVar2,0x14,iVar3 + DAT_00062138,0x14,uVar11,fVar9,local_40,uStack_3c,uStack_38,
                   uStack_34,2,DAT_0006216c);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    uVar10 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x18) = uVar2;
    tColour::tColour((tColour *)&local_50,extraout_s0_11,extraout_s1_11,extraout_s2_11,
                     extraout_s3_11);
    cRBorder::Init(uVar2,0x14,iVar3 + DAT_0006213c,0x14,uVar11,uVar10,local_50,uStack_4c,uStack_48,
                   uStack_44,2,DAT_00062170);
    break;
  case 10:
    piVar4 = *(int **)(iVar3 + iVar1);
    local_168 = atStack_70;
    ptVar5 = atStack_60;
    iVar1 = *piVar4;
    local_164 = atStack_80;
    goto LAB_00061e58;
  case 0xb:
    piVar4 = *(int **)(iVar3 + iVar1);
    ptVar5 = local_90;
    local_164 = local_b0;
    iVar1 = *piVar4;
    local_168 = local_a0;
LAB_00061e58:
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(iVar1 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    tColour::tColour(ptVar5,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar2,0x400002,iVar3 + DAT_00062134,0x14,uVar11,DAT_00062140,
                   *(undefined4 *)ptVar5,*(undefined4 *)(ptVar5 + 4),*(undefined4 *)(ptVar5 + 8),
                   *(undefined4 *)(ptVar5 + 0xc),2,uVar11);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar2;
    uVar10 = *(undefined4 *)(this + 0xc);
    tColour::tColour(local_168,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00);
    cRBorder::Init(uVar2,0x40000014,iVar3 + DAT_00062138,0x14,uVar11,uVar10,*(undefined4 *)local_168
                   ,*(undefined4 *)(local_168 + 4),*(undefined4 *)(local_168 + 8),
                   *(undefined4 *)(local_168 + 0xc),2,DAT_0006214c);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar10 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar4 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar10;
    uVar2 = *(undefined4 *)(this + 0xc);
    fVar9 = extraout_s0_01;
    fVar6 = extraout_s1_01;
    fVar7 = extraout_s2_01;
    fVar8 = extraout_s3_01;
    goto LAB_00061f68;
  }
  return;
}
