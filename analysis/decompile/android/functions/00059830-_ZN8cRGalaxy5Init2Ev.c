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
  cRBorderManager *pcVar2;
  cRBorder *this_00;
  cRBorder *pcVar3;
  int iVar4;
  cRGalaxy *pcVar5;
  int iVar6;
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
  undefined4 uVar7;
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

  *(undefined4 *)this = 1;
  iVar6 = 0;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x8e2c) = uVar1;
  tColour::tColour((tColour *)&local_48,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  cRBorder::Init(uVar1,0x400000,"Intergalactic Delivery Route",0x14,0x41700000,0x41700000,local_48,
                 uStack_44,uStack_40,uStack_3c,0,0);
  pcVar2 = (cRBorderManager *)(Game + 0xd14);
  *(undefined4 *)(*(int *)(this + 0x8e2c) + 0x6e8) = 0x3f547ae1;
  uVar1 = cRBorderManager::GetBorder(pcVar2);
  *(undefined4 *)(this + 0x8e30) = uVar1;
  tColour::tColour((tColour *)&local_58,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00)
  ;
  cRBorder::Init(uVar1,0x20400802,0x7d,0x43b90000,0x41200000,local_58,uStack_54,uStack_50,uStack_4c,
                 0,1);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x8e28) = uVar1;
  tColour::tColour((tColour *)&local_68,extraout_s0_01,extraout_s1_01,extraout_s2_01,extraout_s3_01)
  ;
  cRBorder::Init(uVar1,0x60000014,&DAT_00092f10,0x14,0x41a00000,0x43d20000,local_68,uStack_64,
                 uStack_60,uStack_5c,0,0);
  iVar4 = *(int *)(this + 0x18);
  pcVar5 = this;
  if (-1 < iVar4) {
    do {
      iVar6 = iVar6 + 1;
      *(undefined4 *)(pcVar5 + 0x21c) = 0;
      *(undefined4 *)(pcVar5 + 0x220) = 0;
      pcVar5 = pcVar5 + 0x2a0;
    } while (iVar6 <= iVar4);
  }
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x8e40) = uVar1;
  tColour::tColour((tColour *)&local_78,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02)
  ;
  cRBorder::Init(uVar1,0x20010002,"",0x14,0x41f00000,0x42a00000,local_78,uStack_74,uStack_70,
                 uStack_6c,0,0);
  tColour::Set((tColour *)(*(int *)(this + 0x8e40) + 0x1c0),extraout_s0_03,extraout_s1_03,
               extraout_s2_03,extraout_s3_03);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e40));
  if (*(int *)(gOFOData + Game + 0x1ebc) == 0) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x7f;
  }
  else if (*(int *)(gOFOData + Game + 0x1ebc) == 1) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x82;
  }
  iVar4 = *(int *)(this + 0x8e40);
  *(undefined4 *)(iVar4 + 0x40) = 0x43a00000;
  *(undefined4 *)(iVar4 + 0x4c) = 0x42c80000;
  *(undefined4 *)(iVar4 + 0x44) = 0x43700000;
  *(undefined4 *)(iVar4 + 0x48) = 0x43480000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x8e44) = uVar1;
  tColour::tColour((tColour *)&local_88,extraout_s0_04,extraout_s1_04,extraout_s2_04,extraout_s3_04)
  ;
  uVar7 = 0;
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x42c80000,0x42a00000,local_88,uStack_84,uStack_80,
                 uStack_7c,0,0,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e44));
  iVar4 = Game;
  iVar6 = *(int *)(this + 0x8e44);
  *(undefined4 *)(iVar6 + 0x264) = 0;
  *(undefined4 *)(iVar6 + 0x6e8) = 0x3f99999a;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  *(undefined4 *)(this + 0x8e48) = uVar1;
  tColour::tColour((tColour *)&local_98,extraout_s0_05,extraout_s1_05,extraout_s2_05,extraout_s3_05)
  ;
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x43960000,0x43dc0000,local_98,uStack_94,uStack_90,
                 uStack_8c,uVar7,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e48));
  iVar4 = Game;
  iVar6 = *(int *)(this + 0x8e48);
  *(undefined4 *)(iVar6 + 0x264) = 0;
  *(undefined4 *)(iVar6 + 0x6e8) = 0x3f8ccccd;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  *(undefined4 *)(this + 0x8e4c) = uVar1;
  tColour::tColour((tColour *)&local_a8,extraout_s0_06,extraout_s1_06,extraout_s2_06,extraout_s3_06)
  ;
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x43960000,0x43dc0000,local_a8,uStack_a4,uStack_a0,
                 uStack_9c,uVar7,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e4c));
  iVar4 = Game;
  iVar6 = *(int *)(this + 0x8e4c);
  *(undefined4 *)(iVar6 + 0x264) = 0;
  *(undefined4 *)(iVar6 + 0x6e8) = 0x3f800000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  iVar4 = *(int *)(*(int *)(this + 0x8e24) + 0x60);
  *(undefined4 *)(this + 0x8e50) = uVar1;
  if (iVar4 == 0) {
    tColour::tColour((tColour *)&local_b8,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    iVar4 = -0x7ff8;
  }
  else {
    tColour::tColour((tColour *)&local_c8,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    iVar4 = -0x7fec;
    local_b8 = local_c8;
    uStack_b4 = uStack_c4;
    uStack_b0 = uStack_c0;
    uStack_ac = uStack_bc;
  }
  cRBorder::Init(uVar1,0x60000014,(int)&__DT_PLTGOT + iVar4,0x14,0x43960000,0x43dc0000,local_b8,
                 uStack_b4,uStack_b0,uStack_ac,2,0x42c80000);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e50));
  *(undefined4 *)(*(int *)(this + 0x8e50) + 0x264) = 0x41a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
  *(undefined4 *)(this + 0x8e54) = uVar1;
  tColour::tColour((tColour *)&local_d8,extraout_s0_08,extraout_s1_08,extraout_s2_08,extraout_s3_08)
  ;
  cRBorder::Init(uVar1,0x60000014,"Watch Best Trial",0x14,0x43960000,0x43dc0000,local_d8,uStack_d4,
                 uStack_d0,uStack_cc,2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
  iVar4 = Game;
  iVar6 = *(int *)(this + 0x8e54);
  *(undefined4 *)(iVar6 + 0x264) = 0x41200000;
  *(undefined4 *)(iVar6 + 0x208) = 0x41000000;
  *(undefined4 *)(iVar6 + 0x6e8) = 0x3f4ccccd;
  RFontTypeSet = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  *(undefined4 *)(this + 0x8e5c) = uVar1;
  tColour::tColour((tColour *)&local_e8,extraout_s0_09,extraout_s1_09,extraout_s2_09,extraout_s3_09)
  ;
  cRBorder::Init(uVar1,0x20000014,&DAT_00092f40,0x14,0x437a0000,0x43d20000,local_e8,uStack_e4,
                 uStack_e0,uStack_dc,2,0xc2a00000);
  pcVar2 = (cRBorderManager *)(Game + 0xd14);
  *(undefined4 *)(*(int *)(this + 0x8e5c) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder(pcVar2);
  *(undefined4 *)(this + 0x8e60) = uVar1;
  tColour::tColour((tColour *)&local_f8,extraout_s0_10,extraout_s1_10,extraout_s2_10,extraout_s3_10)
  ;
  cRBorder::Init(uVar1,0x20000014,&DAT_00092f44,0x14,0x43960000,0x43d20000,local_f8,uStack_f4,
                 uStack_f0,uStack_ec,2,0);
  iVar4 = Game;
  *(undefined4 *)(*(int *)(this + 0x8e60) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  *(undefined4 *)(this + 0x8e64) = uVar1;
  tColour::tColour((tColour *)&local_108,extraout_s0_11,extraout_s1_11,extraout_s2_11,extraout_s3_11
                  );
  cRBorder::Init(uVar1,0x20000014,"]",0x14,0x43960000,0x43d20000,local_108,uStack_104,uStack_100,
                 uStack_fc,2,0);
  iVar4 = Game;
  *(undefined4 *)(*(int *)(this + 0x8e64) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(iVar4 + 0xd14));
  *(undefined4 *)(this + 0x8e68) = uVar1;
  tColour::tColour((tColour *)&local_118,extraout_s0_12,extraout_s1_12,extraout_s2_12,extraout_s3_12
                  );
  cRBorder::Init(uVar1,0x20000014,&DAT_00092f48,0x14,0x43960000,0x43d20000,local_118,uStack_114,
                 uStack_110,uStack_10c,2,0);
  this_00 = *(cRBorder **)(this + 0x8e60);
  pcVar3 = *(cRBorder **)(this + 0x8e5c);
  *(undefined4 *)(*(int *)(this + 0x8e68) + 0x264) = 0x40a00000;
  cRBorder::SetRight(this_00,pcVar3);
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e64),*(cRBorder **)(this + 0x8e60));
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e68),*(cRBorder **)(this + 0x8e64));
  if (*(int *)(gOFOData + Game + 0x1ebc) == 1) {
    Rstrcmp("Fluctuosa",gConfig + 0x60);
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
