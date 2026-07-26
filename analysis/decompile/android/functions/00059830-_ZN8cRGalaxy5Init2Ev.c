/*
 * mangled: _ZN8cRGalaxy5Init2Ev
 * demangled: cRGalaxy::Init2()
 * address: 00059830
 * size: 2392
 */

/* cRGalaxy::Init2() */

void __thiscall cRGalaxy::Init2(cRGalaxy *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  cRBorder *this_00;
  cRBorder *pcVar8;
  undefined4 *puVar9;
  cRGalaxy *pcVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
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
  float extraout_s0_12;
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
  float extraout_s1_11;
  float extraout_s1_12;
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
  float extraout_s2_11;
  float extraout_s2_12;
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
  float extraout_s3_11;
  float extraout_s3_12;
  undefined4 uVar15;
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
  undefined4 local_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
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
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;

  iVar7 = DAT_00059c64;
  uVar4 = DAT_00059c38;
  iVar12 = DAT_00059c60 + 0x59850;
  *(undefined4 *)this = 1;
  piVar13 = *(int **)(iVar12 + iVar7);
  iVar14 = 0;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar13 + 0xd14));
  *(undefined4 *)(this + 0x8e2c) = uVar2;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar2,0x400000,iVar12 + DAT_00059c68,0x14,DAT_00059c3c,DAT_00059c3c,local_48,
                 uStack_44,uStack_40,uStack_3c,0,uVar4);
  iVar3 = *piVar13;
  *(undefined4 *)(*(int *)(this + 0x8e2c) + 0x6e8) = DAT_00059c40;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
  *(undefined4 *)(this + 0x8e30) = uVar2;
  tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar2,0x20400802,0x7d,0x43b90000,DAT_00059cb8,local_58,uStack_54,uStack_50,
                 uStack_4c,uVar4,1);
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar13 + 0xd14));
  *(undefined4 *)(this + 0x8e28) = uVar2;
  tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar2,0x60000014,iVar12 + DAT_00059c6c,0x14,DAT_00059ca0,DAT_00059cac,local_68,
                 uStack_64,uStack_60,uStack_5c,0,uVar4);
  iVar3 = *(int *)(this + 0x18);
  pcVar10 = this;
  if (-1 < iVar3) {
    do {
      iVar14 = iVar14 + 1;
      *(undefined4 *)(pcVar10 + 0x21c) = uVar4;
      *(undefined4 *)(pcVar10 + 0x220) = uVar4;
      pcVar10 = pcVar10 + 0x2a0;
    } while (iVar14 <= iVar3);
  }
  iVar3 = DAT_00059c70;
  piVar13 = *(int **)(iVar12 + iVar7);
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar13 + 0xd14));
  *(undefined4 *)(this + 0x8e40) = uVar4;
  tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar4,0x20010002,iVar12 + iVar3,0x14,DAT_00059c44,DAT_00059c48,local_78,uStack_74,
                 uStack_70,uStack_6c,0,DAT_00059c38);
  tColour::Set((tColour *)(*(int *)(this + 0x8e40) + 0x1c0),extraout_s0_03,extraout_s1_03,
               extraout_s2_03,extraout_s3_03);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e40));
  if (*(int *)(gOFOData + *piVar13 + 0x1ebc) == 0) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x7f;
  }
  else if (*(int *)(gOFOData + *piVar13 + 0x1ebc) == 1) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x82;
  }
  uVar2 = DAT_00059c4c;
  iVar14 = *(int *)(this + 0x8e40);
  *(undefined4 *)(iVar14 + 0x40) = DAT_00059c50;
  piVar13 = *(int **)(iVar12 + iVar7);
  *(undefined4 *)(iVar14 + 0x4c) = uVar2;
  *(undefined4 *)(iVar14 + 0x44) = DAT_00059c54;
  *(undefined4 *)(iVar14 + 0x48) = DAT_00059c58;
  uVar1 = DAT_00059ca4;
  uVar4 = DAT_00059c38;
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar13 + 0xd14));
  uVar6 = DAT_00059cb4;
  *(undefined4 *)(this + 0x8e44) = uVar5;
  tColour::tColour((tColour *)&local_88,extraout_s0_04,extraout_s1_04,extraout_s2_04,extraout_s3_04)
  ;
  iVar3 = iVar12 + iVar3;
  uVar15 = 0;
  cRBorder::Init(uVar5,0x20400002,iVar3,0x14,uVar2,DAT_00059c48,local_88,uStack_84,uStack_80,
                 uStack_7c,0,uVar4,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e44));
  uVar5 = DAT_00059c5c;
  iVar11 = *(int *)(this + 0x8e44);
  iVar14 = *piVar13;
  *(undefined4 *)(iVar11 + 0x264) = uVar4;
  *(undefined4 *)(iVar11 + 0x6e8) = uVar5;
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(iVar14 + 0xd14));
  *(undefined4 *)(this + 0x8e48) = uVar5;
  tColour::tColour((tColour *)&local_98,extraout_s0_05,extraout_s1_05,extraout_s2_05,extraout_s3_05)
  ;
  cRBorder::Init(uVar5,0x20400002,iVar3,0x14,uVar1,uVar6,local_98,uStack_94,uStack_90,uStack_8c,
                 uVar15,uVar4);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e48));
  uVar5 = DAT_00059c9c;
  iVar11 = *(int *)(this + 0x8e48);
  iVar14 = *piVar13;
  *(undefined4 *)(iVar11 + 0x264) = uVar4;
  *(undefined4 *)(iVar11 + 0x6e8) = uVar5;
  uVar5 = cRBorderManager::GetBorder((cRBorderManager *)(iVar14 + 0xd14));
  *(undefined4 *)(this + 0x8e4c) = uVar5;
  tColour::tColour((tColour *)&local_a8,extraout_s0_06,extraout_s1_06,extraout_s2_06,extraout_s3_06)
  ;
  cRBorder::Init(uVar5,0x20400002,iVar3,0x14,uVar1,uVar6,local_a8,uStack_a4,uStack_a0,uStack_9c,
                 uVar15,uVar4);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e4c));
  iVar3 = *piVar13;
  iVar14 = *(int *)(this + 0x8e4c);
  *(undefined4 *)(iVar14 + 0x264) = uVar4;
  *(undefined4 *)(iVar14 + 0x6e8) = 0x3f800000;
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(iVar3 + 0xd14));
  iVar3 = *(int *)(*(int *)(this + 0x8e24) + 0x60);
  *(undefined4 *)(this + 0x8e50) = uVar4;
  if (iVar3 == 0) {
    tColour::tColour((tColour *)&local_b8,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    iVar3 = DAT_00059c74;
  }
  else {
    tColour::tColour((tColour *)&local_c8,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    iVar3 = DAT_00059c90;
    local_b8 = local_c8;
    uStack_b4 = uStack_c4;
    uStack_b0 = uStack_c0;
    uStack_ac = uStack_bc;
  }
  cRBorder::Init(uVar4,0x60000014,iVar12 + iVar3,0x14,uVar1,uVar6,local_b8,uStack_b4,uStack_b0,
                 uStack_ac,2,uVar2);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e50));
  uVar4 = DAT_00059ca4;
  piVar13 = *(int **)(iVar12 + iVar7);
  *(undefined4 *)(*(int *)(this + 0x8e50) + 0x264) = DAT_00059ca0;
  uVar1 = DAT_00059cb0;
  uVar5 = DAT_00059cac;
  uVar2 = DAT_00059ca8;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(*piVar13 + 0xd14));
  *(undefined4 *)(this + 0x8e54) = uVar6;
  tColour::tColour((tColour *)&local_d8,extraout_s0_08,extraout_s1_08,extraout_s2_08,extraout_s3_08)
  ;
  cRBorder::Init(uVar6,0x60000014,iVar12 + DAT_00059c78,0x14,uVar4,DAT_00059cb4,local_d8,uStack_d4,
                 uStack_d0,uStack_cc,2,uVar2);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
  iVar7 = *piVar13;
  iVar3 = *(int *)(this + 0x8e54);
  *(undefined4 *)(iVar3 + 0x264) = DAT_00059cb8;
  uVar6 = DAT_00059cbc;
  puVar9 = *(undefined4 **)(iVar12 + DAT_00059c7c);
  *(undefined4 *)(iVar3 + 0x208) = DAT_00059cc0;
  *(undefined4 *)(iVar3 + 0x6e8) = uVar6;
  *puVar9 = 1;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar7 + 0xd14));
  *(undefined4 *)(this + 0x8e5c) = uVar6;
  tColour::tColour((tColour *)&local_e8,extraout_s0_09,extraout_s1_09,extraout_s2_09,extraout_s3_09)
  ;
  cRBorder::Init(uVar6,0x20000014,iVar12 + DAT_00059c80,0x14,DAT_00059cc4,uVar5,local_e8,uStack_e4,
                 uStack_e0,uStack_dc,2,DAT_00059cc8);
  iVar7 = *piVar13;
  *(undefined4 *)(*(int *)(this + 0x8e5c) + 0x264) = uVar1;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar7 + 0xd14));
  *(undefined4 *)(this + 0x8e60) = uVar6;
  tColour::tColour((tColour *)&local_f8,extraout_s0_10,extraout_s1_10,extraout_s2_10,extraout_s3_10)
  ;
  cRBorder::Init(uVar6,0x20000014,iVar12 + DAT_00059c84,0x14,uVar4,uVar5,local_f8,uStack_f4,
                 uStack_f0,uStack_ec,2,uVar2);
  iVar7 = *piVar13;
  *(undefined4 *)(*(int *)(this + 0x8e60) + 0x264) = uVar1;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar7 + 0xd14));
  *(undefined4 *)(this + 0x8e64) = uVar6;
  tColour::tColour((tColour *)&local_108,extraout_s0_11,extraout_s1_11,extraout_s2_11,extraout_s3_11
                  );
  cRBorder::Init(uVar6,0x20000014,iVar12 + DAT_00059c88,0x14,uVar4,uVar5,local_108,uStack_104,
                 uStack_100,uStack_fc,2,uVar2);
  iVar7 = *piVar13;
  *(undefined4 *)(*(int *)(this + 0x8e64) + 0x264) = uVar1;
  uVar6 = cRBorderManager::GetBorder((cRBorderManager *)(iVar7 + 0xd14));
  *(undefined4 *)(this + 0x8e68) = uVar6;
  tColour::tColour((tColour *)&local_118,extraout_s0_12,extraout_s1_12,extraout_s2_12,extraout_s3_12
                  );
  cRBorder::Init(uVar6,0x20000014,iVar12 + DAT_00059c8c,0x14,uVar4,uVar5,local_118,uStack_114,
                 uStack_110,uStack_10c,2,uVar2);
  this_00 = *(cRBorder **)(this + 0x8e60);
  pcVar8 = *(cRBorder **)(this + 0x8e5c);
  *(undefined4 *)(*(int *)(this + 0x8e68) + 0x264) = uVar1;
  cRBorder::SetRight(this_00,pcVar8);
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e64),*(cRBorder **)(this + 0x8e60));
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e68),*(cRBorder **)(this + 0x8e64));
  if (*(int *)(gOFOData + *piVar13 + 0x1ebc) == 1) {
    Rstrcmp((char *)(iVar12 + DAT_00059c98),(char *)(*(int *)(iVar12 + DAT_00059c94) + 0x60));
  }
  if (*(int *)(this + 0xc) != 2 && *(int *)(this + 0xc) != 0) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e5c));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e60));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e64));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e68));
  }
  BoxOn(this,*(int *)(this + 0x8e34));
  return;
}
