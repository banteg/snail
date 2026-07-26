/*
 * mangled: _ZN9cRSubGame4InitEv
 * demangled: cRSubGame::Init()
 * address: 0001cd58
 * size: 2748
 */

/* cRSubGame::Init() */

void __thiscall cRSubGame::Init(cRSubGame *this)

{
  undefined *puVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  cRSubGame *pcVar7;
  undefined4 uVar8;
  uint in_fpscr;
  float fVar9;
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

  iVar3 = 0;
  *(undefined4 *)(this + 0x74) = 0;
  this[0x10] = (cRSubGame)0x0;
  do {
    pcVar7 = this + (int)(&PTR_caseD_6_00013458 + iVar3 * 0x88);
    iVar5 = 0;
    do {
      iVar5 = iVar5 + 1;
      *(undefined4 *)(pcVar7 + 0x34) = 0;
      *(undefined4 *)(pcVar7 + 0x38) = 0;
      *(undefined4 *)(pcVar7 + 0x3c) = 0;
      *(undefined4 *)(pcVar7 + 0x40) = 0;
      pcVar7 = pcVar7 + 0x44;
    } while (iVar5 != 8);
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xdac);
  if (*(int *)(this + 0x303aa8) - 1U < 2) {
    RShellMusicPlay("mainmenu.mp4",0,"");
    puVar1 = PTR__Game_001b60b8;
    iVar3 = cRLandscapeManager::Import
                      ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),
                       "Menubg.txt");
    iVar5 = *(int *)puVar1;
    cRBackdrop::Change((cRBackdrop *)(iVar5 + 0x4d2e0),
                       (cRLandscape *)(&DAT_003593dc + iVar5 + iVar3 * 0x1ac),false);
    cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),25.0);
  }
  iVar3 = *(int *)(this + 0x58);
  if (iVar3 == 1) {
    pcVar7 = this + 0x2a0418;
    *(cRSubGame **)(this + 0x2a01a8) = pcVar7;
    *(undefined4 *)(this + 0x27b4) = *(undefined4 *)(this + 0x2a0434);
LAB_0001ce4c:
    uVar4 = *(undefined4 *)(pcVar7 + 8);
    uVar6 = *(undefined4 *)(pcVar7 + 0xc);
    uVar8 = *(undefined4 *)(pcVar7 + 0x10);
    *(undefined4 *)(this + 0x27b8) = *(undefined4 *)(pcVar7 + 4);
    *(undefined4 *)(this + 0x27bc) = uVar4;
    *(undefined4 *)(this + 0x27c0) = uVar6;
    *(undefined4 *)(this + 0x27c4) = uVar8;
    uVar4 = *(undefined4 *)(pcVar7 + 0x18);
    *(undefined4 *)(this + 0x27c8) = *(undefined4 *)(pcVar7 + 0x14);
    *(undefined4 *)(this + 0x27cc) = uVar4;
  }
  else {
    if (iVar3 == 4) {
      pcVar7 = this + 0x2a0680;
      *(cRSubGame **)(this + 0x2a01a8) = pcVar7;
      *(undefined4 *)(this + 0x27b4) = *(undefined4 *)(this + 0x2a069c);
      goto LAB_0001ce4c;
    }
    if (iVar3 == 0) {
      if (*(int *)(this + 0x2f1dcc) == 0) {
        *(cRSubGame **)(this + 0x2a01a8) = this + 0x2a01b0;
      }
      else if (*(int *)(this + 0x2f1dcc) == 1) {
        *(cRSubGame **)(this + 0x2a01a8) = this + 0x2a11e0;
      }
      pcVar7 = *(cRSubGame **)(this + 0x2a01a8);
      *(undefined4 *)(this + 0x27b4) = *(undefined4 *)(pcVar7 + 0x1c);
      goto LAB_0001ce4c;
    }
  }
  puVar1 = PTR__Game_001b60b8;
  uVar4 = 0;
  if (this[0x2e09cd] != (cRSubGame)0x0) {
    uVar4 = *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x48);
  }
  *(undefined4 *)(this + 0x14) = 0;
  this[0x12] = (cRSubGame)0x0;
  if (this[0x2e09cd] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 0x44) = uVar4;
  }
  this[0x11] = (cRSubGame)0x0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x18) = 0x3d088889;
  *(undefined4 *)(this + 0x305304) = 0;
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0x85e0) = uVar4;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,0.03);
  cRBorder::Init(uVar4,&DAT_00400002,"0",0x14,0x43c80000,0x41600000,local_30,uStack_2c,uStack_28,
                 uStack_24,3,0x439b0000);
  *(undefined4 *)(*(int *)(this + 0x85e0) + 0x6e8) = 0x3f99999a;
  *(undefined4 *)(*(int *)(this + 0x85e0) + 0x26c) = 1;
  *(undefined1 *)(*(int *)(this + 0x85e0) + 0x2c4) = 0;
  if (*(int *)(this + 0x58) == 0) {
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
    *(undefined4 *)(this + 0x85e8) = uVar4;
    tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar4,&DAT_00400800,0x6e,0,0x42680000,local_40,uStack_3c,uStack_38,uStack_34,0,1)
    ;
    cRBorder::Scale(*(cRBorder **)(this + 0x85e8),1.25);
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e8));
    puVar1 = PTR__Game_001b60b8;
    *(undefined4 *)(*(int *)(this + 0x85e8) + 0x16c) = 0;
    uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0x85ec) = uVar4;
    tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,0.03);
    cRBorder::Init(uVar4,&DAT_00400002,"0",0x14,0x42780000,0x42b20000,local_50,uStack_4c,uStack_48,
                   uStack_44,0,0);
    cRBorder::HideInit(*(cRBorder **)(this + 0x85ec));
    *(undefined4 *)(*(int *)(this + 0x85ec) + 0x6e8) = 0x3f59999a;
    iVar3 = 0;
    pcVar7 = this + 0x85f0;
    do {
      uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
      *(undefined4 *)pcVar7 = uVar4;
      tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
      fVar9 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
      iVar3 = iVar3 + 1;
      cRBorder::Init(uVar4,&DAT_00400800,0x6f,fVar9 * 24.0 + 13.0,0x43d70000,local_60,uStack_5c,
                     uStack_58,uStack_54,0,1);
      *(undefined4 *)(*(int *)pcVar7 + 0x16c) = 0;
      cRBorder::HideInit(*(cRBorder **)pcVar7);
      pcVar7 = pcVar7 + 4;
    } while (iVar3 != 9);
  }
  wprintf("***TODO*** Score last\n");
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x85e4) = uVar4;
  tColour::tColour((tColour *)&local_70,1.0,1.0,1.0,0.03);
  cRBorder::Init(uVar4,&DAT_00400002,"0",0x14,0x42a00000,0x41600000,local_70,uStack_6c,uStack_68,
                 uStack_64,3,0x41f00000);
  *(undefined4 *)(*(int *)(this + 0x85e4) + 0x6e8) = 0x3f99999a;
  *(undefined4 *)(*(int *)(this + 0x85e4) + 0x26c) = 1;
  *(undefined1 *)(*(int *)(this + 0x85e4) + 0x2c4) = 0;
  switch(*(undefined4 *)(this + 0x58)) {
  case 0:
  case 1:
    cRBorder::AddTextNumber(*(cRBorder **)(this + 0x85e4),*(int *)(this + 0x27b4));
    break;
  case 2:
  case 3:
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e0));
    break;
  case 4:
    iVar3 = *(int *)(this + 0x85e4);
    pcVar2 = (char *)cRTimeTrial::TimeString
                               ((cRTimeTrial *)(this + 0x2e09dc),(cRTime *)(this + 0x27b8));
    Rstrcpy((char *)(iVar3 + 0x2c4),pcVar2);
  }
  if ((*(char *)(*(int *)PTR__Game_001b60b8 + 0x4e6b4) != '\0') || (*(int *)(this + 0x58) == 7)) {
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e4));
    cRBorder::HideInit(*(cRBorder **)(this + 0x85e0));
  }
  puVar1 = PTR__Game_001b60b8;
  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x2c1) != '\0') {
    return;
  }
  *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x2c1) = 0;
  *(undefined4 *)(*(int *)puVar1 + 0x2c4) = 0;
  tMatrix::Identity((tMatrix *)(this + 0xf474));
  *(undefined4 *)(this + 0xf844) = 0;
  *(cRSubGame **)(this + 0xf840) = this;
  *(undefined4 *)(this + 0xf83c) = 0;
  *(undefined4 *)(this + 0x11c20) = *(undefined4 *)(this + 0xf4a4);
  *(undefined4 *)(this + 0x11c24) = *(undefined4 *)(this + 0xf4a8);
  *(undefined4 *)(this + 0x11c28) = *(undefined4 *)(this + 0xf4ac);
  *(uint *)(this + 0xf44c) = *(uint *)(this + 0xf44c) & 0xffffffdf;
  this[0xf855] = (cRSubGame)0x0;
  this[0xf854] = (cRSubGame)0x0;
  uVar4 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
  *(undefined4 *)(this + 0xf838) = uVar4;
  tColour::tColour((tColour *)&local_80,1.0,1.0,1.0,0.999);
  cRBorder::Init(uVar4,&DAT_00400802,0x51,0x43900000,0x42800000,local_80,uStack_7c,uStack_78,
                 uStack_74,0,1);
  *(undefined4 *)(*(int *)(this + 0xf838) + 0x16c) = 0;
  cRBorder::HideInit(*(cRBorder **)(this + 0xf838));
  *(undefined4 *)(this + 0xf82c) = 0;
  *(undefined4 *)(this + 0xf834) = 0x3daaaaab;
  *(undefined4 *)(this + 0xf830) = 0;
  iVar3 = *(int *)(this + 0x303aa8);
  if (iVar3 == 3 || iVar3 == 0) goto LAB_0001d494;
  if (this[0x2e09cd] != (cRSubGame)0x0) {
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(*(int *)(this + 0x2e09d0) + 0x48);
    goto LAB_0001d494;
  }
  switch(*(undefined4 *)(this + 0x58)) {
  case 0:
    if (iVar3 == 1) {
      if (*(int *)(this + 0x2f1dcc) == 0) {
        iVar3 = *(int *)(this + 0x5c) + 1;
        *(int *)(this + 0x5c) = iVar3;
        puVar1 = PTR__gConfig_001b60d4;
        iVar5 = *(int *)(this + 0x2f1de8);
        if (iVar5 < iVar3) {
          *(int *)(this + 0x5c) = iVar5;
          iVar3 = iVar5;
        }
        if (*(int *)(puVar1 + 0xa0) < iVar3) {
          *(int *)(puVar1 + 0xa0) = iVar3;
          gRegisterSaveFile("ism.cfg",puVar1,0xf0);
          iVar3 = *(int *)(this + 0x5c);
        }
        *(int *)(puVar1 + 0xa4) = iVar3;
      }
      else if (*(int *)(this + 0x2f1dcc) == 1) {
        iVar3 = *(int *)(this + 0x5c) + 1;
        *(int *)(this + 0x5c) = iVar3;
        puVar1 = PTR__gConfig_001b60d4;
        iVar5 = *(int *)(this + 0x2fac54);
        if (iVar5 < iVar3) {
          *(int *)(this + 0x5c) = iVar5;
          iVar3 = iVar5;
        }
        if (*(int *)(puVar1 + 0xe8) < iVar3) {
          *(int *)(puVar1 + 0xe8) = iVar3;
          gRegisterSaveFile("ism.cfg",puVar1,0xf0);
          iVar3 = *(int *)(this + 0x5c);
        }
        *(int *)(puVar1 + 0xec) = iVar3;
      }
    }
    iVar3 = *(int *)(this + 0x2f1dcc);
    goto LAB_0001d47c;
  case 1:
    cRGUI::Init((cRGUI *)(this + 0x2f1d84));
    break;
  default:
    RShellError("Unknown game mode");
    break;
  case 4:
    iVar3 = *(int *)(this + 0x2f1dcc);
LAB_0001d47c:
    cRGalaxy::Init((cRGalaxy *)(this + iVar3 * 0x8e6c + 0x2f1dd0));
    break;
  case 7:
    *(undefined4 *)(this + 0x54) = 0;
  }
LAB_0001d494:
  *(undefined4 *)(this + 0x2a1c) = 0;
  *(undefined4 *)(this + 0x2a84) = 0;
  *(undefined4 *)(this + 0x2aec) = 0;
  *(undefined4 *)(this + 0x2b54) = 0;
  *(undefined4 *)(this + 0x2bbc) = 0;
  *(undefined4 *)(this + 0x2c24) = 0;
  *(undefined4 *)(this + 0x2c8c) = 0;
  *(undefined4 *)(this + 0x2cf4) = 0;
  *(undefined4 *)(this + 0x2844) = 0;
  *(undefined4 *)(this + 0x28a4) = 0;
  pcVar7 = this + 0x5f04;
  *(cRSubGame **)(this + 0x2a28) = this;
  *(cRSubGame **)(this + 0x2a90) = this;
  *(cRSubGame **)(this + 11000) = this;
  *(cRSubGame **)(this + 0x2b60) = this;
  *(cRSubGame **)(this + 0x2bc8) = this;
  *(cRSubGame **)(this + 0x2c30) = this;
  *(cRSubGame **)(this + 0x2c98) = this;
  *(cRSubGame **)(this + 0x2d00) = this;
  *(cRSubGame **)(this + 0x2850) = this;
  *(cRSubGame **)(this + 0x28b0) = this;
  do {
    *(undefined4 *)pcVar7 = 0;
    *(cRSubGame **)(pcVar7 + 8) = this;
    *(undefined4 *)(pcVar7 + -4) = 0;
    pcVar7 = pcVar7 + 0xb8;
  } while (pcVar7 != this + 0x82f4);
  *(undefined4 *)(this + 0x2da4) = 0;
  *(cRSubGame **)(this + 0x2dac) = this;
  *(undefined4 *)(this + 0x2e84) = 0;
  *(cRSubGame **)(this + 0x2e8c) = this;
  *(undefined4 *)(this + 0x2f64) = 0;
  *(cRSubGame **)(this + 0x2f6c) = this;
  *(undefined4 *)(this + 0x3044) = 0;
  *(cRSubGame **)(this + 0x304c) = this;
  *(undefined4 *)(this + 0x3124) = 0;
  *(cRSubGame **)(this + 0x312c) = this;
  *(undefined4 *)(this + 0x3204) = 0;
  *(cRSubGame **)(this + 0x320c) = this;
  *(undefined4 *)(this + 0x32e4) = 0;
  *(cRSubGame **)(this + 0x32ec) = this;
  *(undefined4 *)(this + 0x33c4) = 0;
  *(cRSubGame **)(this + 0x33cc) = this;
  *(undefined4 *)(this + 0x34a4) = 0;
  *(cRSubGame **)(this + 0x34ac) = this;
  *(undefined4 *)(this + 0x3584) = 0;
  *(cRSubGame **)(this + 0x358c) = this;
  *(undefined4 *)(this + 0x3664) = 0;
  *(cRSubGame **)(this + 0x366c) = this;
  *(undefined4 *)(this + 0x3744) = 0;
  *(cRSubGame **)(this + 0x374c) = this;
  *(undefined4 *)(this + 0x3824) = 0;
  *(cRSubGame **)(this + 0x382c) = this;
  *(undefined4 *)(this + 0x3904) = 0;
  *(cRSubGame **)(this + 0x390c) = this;
  *(undefined4 *)(this + 0x39e4) = 0;
  *(cRSubGame **)(this + 0x39ec) = this;
  *(undefined4 *)(this + 0x3ac4) = 0;
  *(cRSubGame **)(this + 0x3acc) = this;
  *(undefined4 *)(this + 0x82f0) = 0;
  *(cRSubGame **)(this + 0x8400) = this;
  *(undefined4 *)(this + 0x849c) = 0;
  *(cRSubGame **)(this + 0x85ac) = this;
  if ((this[0x2e09cc] == (cRSubGame)0x0) ||
     (iVar3 = *(int *)(this + 0x2e09c8), *(int *)(this + 0x58) != *(int *)(iVar3 + 0x2c))) {
    if (*(int *)(this + 0x303aa8) == 2) {
      *(undefined4 *)(this + 0xf714) = 0;
      *(undefined4 *)(this + 0xf740) = 0;
      iVar3 = 4;
      do {
        iVar5 = iVar3 + 4;
        *(undefined4 *)(this + iVar3 + 0xf740) = 0;
        iVar3 = iVar5;
      } while (iVar5 != 0x1c);
    }
    *(undefined4 *)(this + 0xf718) = 0;
    *(undefined4 *)(this + 0xf72c) = 0;
    *(undefined4 *)(this + 0xf71c) = 0;
    *(undefined4 *)(this + 0xf720) = 0;
    *(undefined4 *)(this + 0xf724) = 0;
    *(undefined4 *)(this + 0xf728) = 0;
    *(undefined4 *)(this + 0xf730) = 0;
    *(undefined4 *)(this + 0xf734) = 0;
  }
  else {
    *(undefined4 *)(this + 0xf714) = *(undefined4 *)(iVar3 + 4);
    uVar4 = *(undefined4 *)(iVar3 + 0xc);
    uVar6 = *(undefined4 *)(iVar3 + 0x10);
    uVar8 = *(undefined4 *)(iVar3 + 0x14);
    *(undefined4 *)(this + 0xf718) = *(undefined4 *)(iVar3 + 8);
    *(undefined4 *)(this + 0xf71c) = uVar4;
    *(undefined4 *)(this + 0xf720) = uVar6;
    *(undefined4 *)(this + 0xf724) = uVar8;
    uVar4 = *(undefined4 *)(iVar3 + 0x1c);
    *(undefined4 *)(this + 0xf728) = *(undefined4 *)(iVar3 + 0x18);
    *(undefined4 *)(this + 0xf72c) = uVar4;
    *(undefined4 *)(this + 0xf730) = *(undefined4 *)(iVar3 + 0x20);
    *(undefined4 *)(this + 0xf734) = *(undefined4 *)(iVar3 + 0x24);
  }
  *(undefined4 *)(this + 0xf7b4) = 0;
  *this = (cRSubGame)0x1;
  this[1] = (cRSubGame)0x1;
  this[0x2e09cc] = (cRSubGame)0x0;
  *(undefined4 *)(this + 0x5e88) = 0;
  return;
}
