/*
 * mangled: _ZN6cRExit4InitEv
 * demangled: cRExit::Init()
 * address: 00061dc4
 * size: 1748
 */

/* cRExit::Init() */

void __thiscall cRExit::Init(cRExit *this)

{
  undefined4 uVar1;
  tColour *ptVar2;
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
  float fVar3;
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
  float fVar4;
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
  float fVar5;
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
  float fVar6;
  undefined4 uVar7;
  undefined4 uVar8;
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

  cRBorderManager::HideBorders((cRBorderManager *)(Game + 0xd14));
  switch(*(undefined4 *)this) {
  case 2:
    goto LAB_00061fbc;
  case 3:
    local_168 = atStack_100;
    ptVar2 = atStack_f0;
    local_164 = atStack_110;
    goto LAB_00061fe8;
  case 4:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour((tColour *)&local_120,extraout_s0_05,extraout_s1_05,extraout_s2_05,
                     extraout_s3_05);
    cRBorder::Init(uVar1,0x400002,"Do you really want>to quit?",0x14,0,0x43480000,local_120,
                   uStack_11c,uStack_118,uStack_114,2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_130,extraout_s0_06,extraout_s1_06,extraout_s2_06,
                     extraout_s3_06);
    cRBorder::Init(uVar1,0x40000014,&DAT_000931e8,0x14,0x43ea0000,0x43ba8000,local_130,uStack_12c,
                   uStack_128,uStack_124,2,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_140,extraout_s0_07,extraout_s1_07,extraout_s2_07,
                     extraout_s3_07);
    uVar8 = 0x440e0000;
    uVar7 = 0x43940000;
    goto LAB_00061f7c;
  case 5:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_150,extraout_s0_08,extraout_s1_08,extraout_s2_08,
                     extraout_s3_08);
    cRBorder::Init(uVar1,0x14,&DAT_000931e8,0x14,0x43ec8000,0x42040000,local_150,uStack_14c,
                   uStack_148,uStack_144,0,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_160,extraout_s0_09,extraout_s1_09,extraout_s2_09,
                     extraout_s3_09);
    cRBorder::Init(uVar1,0x14,&DAT_000931ec,0x14,0x440d8000,0x42d80000,local_160,uStack_15c,
                   uStack_158,uStack_154,0,0);
    break;
  case 6:
    break;
  case 7:
LAB_00061fbc:
    ptVar2 = local_c0;
    local_164 = atStack_e0;
    local_168 = local_d0;
LAB_00061fe8:
    uVar7 = 0x43a50000;
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour(ptVar2,extraout_s0_02,extraout_s1_02,extraout_s2_02,extraout_s3_02);
    cRBorder::Init(uVar1,0x400002,"Do you really want>to quit?",0x14,0,0x43480000,
                   *(undefined4 *)ptVar2,*(undefined4 *)(ptVar2 + 4),*(undefined4 *)(ptVar2 + 8),
                   *(undefined4 *)(ptVar2 + 0xc),2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour(local_168,extraout_s0_03,extraout_s1_03,extraout_s2_03,extraout_s3_03);
    cRBorder::Init(uVar1,0x40000014,&DAT_000931e8,0x14,0,0x43a50000,*(undefined4 *)local_168,
                   *(undefined4 *)(local_168 + 4),*(undefined4 *)(local_168 + 8),
                   *(undefined4 *)(local_168 + 0xc),2,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    fVar6 = extraout_s0_04;
    fVar3 = extraout_s1_04;
    fVar4 = extraout_s2_04;
    fVar5 = extraout_s3_04;
LAB_00061f68:
    tColour::tColour(local_164,fVar6,fVar3,fVar4,fVar5);
    local_140 = *(undefined4 *)local_164;
    uStack_13c = *(undefined4 *)(local_164 + 4);
    uStack_138 = *(undefined4 *)(local_164 + 8);
    uStack_134 = *(undefined4 *)(local_164 + 0xc);
    uVar8 = 0;
LAB_00061f7c:
    cRBorder::Init(uVar1,0x14,&DAT_000931ec,0x14,uVar8,uVar7,local_140,uStack_13c,uStack_138,
                   uStack_134,2,0x42a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
    break;
  case 8:
    break;
  case 9:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    fVar6 = *(float *)(this + 0xc);
    *(undefined4 *)(this + 0x14) = uVar1;
    tColour::tColour((tColour *)&local_40,extraout_s0_10,extraout_s1_10,extraout_s2_10,
                     extraout_s3_10);
    cRBorder::Init(uVar1,0x14,&DAT_000931e8,0x14,0,fVar6 - 54.0,local_40,uStack_3c,uStack_38,
                   uStack_34,2,0x430c0000);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    uVar7 = *(undefined4 *)(this + 0xc);
    *(undefined4 *)(this + 0x18) = uVar1;
    tColour::tColour((tColour *)&local_50,extraout_s0_11,extraout_s1_11,extraout_s2_11,
                     extraout_s3_11);
    cRBorder::Init(uVar1,0x14,&DAT_000931ec,0x14,0,uVar7,local_50,uStack_4c,uStack_48,uStack_44,2,
                   0x43860000);
    break;
  case 10:
    local_168 = atStack_70;
    ptVar2 = atStack_60;
    local_164 = atStack_80;
    goto LAB_00061e58;
  case 0xb:
    ptVar2 = local_90;
    local_164 = local_b0;
    local_168 = local_a0;
LAB_00061e58:
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar1;
    tColour::tColour(ptVar2,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    cRBorder::Init(uVar1,0x400002,"Do you really want>to quit?",0x14,0,0x43480000,
                   *(undefined4 *)ptVar2,*(undefined4 *)(ptVar2 + 4),*(undefined4 *)(ptVar2 + 8),
                   *(undefined4 *)(ptVar2 + 0xc),2,0);
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x14) = uVar1;
    uVar7 = *(undefined4 *)(this + 0xc);
    tColour::tColour(local_168,extraout_s0_00,extraout_s1_00,extraout_s2_00,extraout_s3_00);
    cRBorder::Init(uVar1,0x40000014,&DAT_000931e8,0x14,0,uVar7,*(undefined4 *)local_168,
                   *(undefined4 *)(local_168 + 4),*(undefined4 *)(local_168 + 8),
                   *(undefined4 *)(local_168 + 0xc),2,0xc2a00000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x14),*(cRBorder **)(this + 0x10));
    uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(Game + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar1;
    uVar7 = *(undefined4 *)(this + 0xc);
    fVar6 = extraout_s0_01;
    fVar3 = extraout_s1_01;
    fVar4 = extraout_s2_01;
    fVar5 = extraout_s3_01;
    goto LAB_00061f68;
  }
  return;
}
