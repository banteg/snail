/*
 * mangled: _ZN8cRGalaxy5Init2Ev
 * demangled: cRGalaxy::Init2()
 * address: 00069280
 * size: 2368
 */

/* cRGalaxy::Init2() */

void __thiscall cRGalaxy::Init2(cRGalaxy *this)

{
  undefined4 uVar1;
  int iVar2;
  cRGalaxy *pcVar3;
  undefined4 local_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 local_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  *(undefined4 *)this = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e2c) = uVar1;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x400000,"Intergalactic Delivery Route",0x14,0x41700000,0x41700000,local_30,
                 uStack_2c,uStack_28,uStack_24,0,0);
  *(undefined4 *)(*(int *)(this + 0x8e2c) + 0x6e8) = 0x3f547ae1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e30) = uVar1;
  tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20400802,0x7d,0x43b90000,0x41200000,local_40,uStack_3c,uStack_38,uStack_34,
                 0,1);
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e28) = uVar1;
  tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x60000014,"Back",0x14,0x41a00000,0x43d20000,local_50,uStack_4c,uStack_48,
                 uStack_44,0,0);
  if (0 < *(int *)(this + 0x18) + 1) {
    iVar2 = 0;
    pcVar3 = this;
    do {
      *(undefined4 *)(pcVar3 + 0x21c) = 0;
      *(undefined4 *)(pcVar3 + 0x220) = 0;
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 0x2a0;
    } while (iVar2 < *(int *)(this + 0x18) + 1);
  }
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e40) = uVar1;
  tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20010002,"",0x14,0x41f00000,0x42a00000,local_60,uStack_5c,uStack_58,
                 uStack_54,0,0);
  tColour::Set((tColour *)(*(int *)(this + 0x8e40) + 0x1c0),1.0,1.0,1.0,1.0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e40));
  if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x7f;
  }
  else if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
    *(undefined4 *)(*(int *)(this + 0x8e40) + 0x3c) = 0x82;
  }
  *(undefined4 *)(*(int *)(this + 0x8e40) + 0x40) = 0x43a00000;
  *(undefined4 *)(*(int *)(this + 0x8e40) + 0x44) = 0x43700000;
  *(undefined4 *)(*(int *)(this + 0x8e40) + 0x48) = 0x43480000;
  *(undefined4 *)(*(int *)(this + 0x8e40) + 0x4c) = 0x42c80000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e44) = uVar1;
  tColour::tColour((tColour *)&local_70,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x42c80000,0x42a00000,local_70,uStack_6c,uStack_68,
                 uStack_64,0,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e44));
  *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6e8) = 0x3f99999a;
  *(undefined4 *)(*(int *)(this + 0x8e44) + 0x264) = 0;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e48) = uVar1;
  tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x43960000,0x43dc0000,local_80,uStack_7c,uStack_78,
                 uStack_74,0,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e48));
  *(undefined4 *)(*(int *)(this + 0x8e48) + 0x6e8) = 0x3f8ccccd;
  *(undefined4 *)(*(int *)(this + 0x8e48) + 0x264) = 0;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e4c) = uVar1;
  tColour::tColour((tColour *)&local_90,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20400002,"",0x14,0x43960000,0x43dc0000,local_90,uStack_8c,uStack_88,
                 uStack_84,0,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e4c));
  *(undefined4 *)(*(int *)(this + 0x8e4c) + 0x6e8) = 0x3f800000;
  *(undefined4 *)(*(int *)(this + 0x8e4c) + 0x264) = 0;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e50) = uVar1;
  if (*(int *)(*(int *)(this + 0x8e24) + 0x58) == 0) {
    tColour::tColour((tColour *)&local_a0,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x60000014,"Deliver!",0x14,0x43960000,0x43dc0000,local_a0,uStack_9c,
                   uStack_98,uStack_94,2,0x42c80000);
  }
  else {
    tColour::tColour((tColour *)&local_b0,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar1,0x60000014,"Play",0x14,0x43960000,0x43dc0000,local_b0,uStack_ac,uStack_a8,
                   uStack_a4,2,0x42c80000);
  }
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e50));
  *(undefined4 *)(*(int *)(this + 0x8e50) + 0x264) = 0x41a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e54) = uVar1;
  tColour::tColour((tColour *)&local_c0,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x60000014,"Watch Best Trial",0x14,0x43960000,0x43dc0000,local_c0,uStack_bc,
                 uStack_b8,uStack_b4,2,0);
  cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
  *(undefined4 *)(*(int *)(this + 0x8e54) + 0x264) = 0x41200000;
  *(undefined4 *)(*(int *)(this + 0x8e54) + 0x6e8) = 0x3f4ccccd;
  *(undefined1 **)(*(int *)(this + 0x8e54) + 0x208) = &DAT_40800000;
  *(undefined4 *)(*(int *)(this + 0x8e54) + 0x208) = 0x41000000;
  *(undefined4 *)PTR__RFontTypeSet_001b61f8 = 1;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e5c) = uVar1;
  tColour::tColour((tColour *)&local_d0,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20000014,"{",0x14,0x437a0000,0x43d20000,local_d0,uStack_cc,uStack_c8,
                 uStack_c4,2,0xc2a00000);
  *(undefined4 *)(*(int *)(this + 0x8e5c) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e60) = uVar1;
  tColour::tColour((tColour *)&local_e0,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20000014,"[",0x14,0x43960000,0x43d20000,local_e0,uStack_dc,uStack_d8,
                 uStack_d4,2,0);
  *(undefined4 *)(*(int *)(this + 0x8e60) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e64) = uVar1;
  tColour::tColour((tColour *)&local_f0,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20000014,"]",0x14,0x43960000,0x43d20000,local_f0,uStack_ec,uStack_e8,
                 uStack_e4,2,0);
  *(undefined4 *)(*(int *)(this + 0x8e64) + 0x264) = 0x40a00000;
  uVar1 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x8e68) = uVar1;
  tColour::tColour((tColour *)&local_100,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar1,0x20000014,"}",0x14,0x43960000,0x43d20000,local_100,uStack_fc,uStack_f8,
                 uStack_f4,2,0);
  *(undefined4 *)(*(int *)(this + 0x8e68) + 0x264) = 0x40a00000;
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e60),*(cRBorder **)(this + 0x8e5c));
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e64),*(cRBorder **)(this + 0x8e60));
  cRBorder::SetRight(*(cRBorder **)(this + 0x8e68),*(cRBorder **)(this + 0x8e64));
  if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
    Rstrcmp("Fluctuosa",PTR__gConfig_001b60d4 + 0x60);
  }
  if (*(int *)(this + 0xc) != 0 && *(int *)(this + 0xc) != 2) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e5c));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e60));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e64));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e68));
    cRBorder::HideInit(*(cRBorder **)(this + 0x8e28));
  }
  BoxOn(this,*(int *)(this + 0x8e34));
  return;
}
