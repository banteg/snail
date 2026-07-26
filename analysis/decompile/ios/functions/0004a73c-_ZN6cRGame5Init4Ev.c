/*
 * mangled: _ZN6cRGame5Init4Ev
 * demangled: cRGame::Init4()
 * address: 0004a73c
 * size: 936
 */

/* cRGame::Init4() */

void __thiscall cRGame::Init4(cRGame *this)

{
  char *pcVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  cRGame *pcVar5;
  cRTipManager *this_00;
  int iVar6;
  bool bVar7;
  tMatrix atStack_60 [64];

  wprintf("GameInit4\n");
  if (0 < *(int *)(this + 100)) {
    iVar6 = 0;
    pcVar5 = this;
    do {
      iVar4 = iVar6 * 0x1fc;
      tMatrix::Identity((tMatrix *)(this + iVar4 + 0x100));
      tMatrix::Identity((tMatrix *)(this + iVar4 + 0x194));
      *(undefined4 *)(pcVar5 + 0x21c) = 0x42f00000;
      *(cRGame **)(pcVar5 + 0x224) = this + iVar6 * 0x6c + 0x68;
      tMatrix::tMatrix(atStack_60,0.073343,0.0,-0.997311,0.0,0.15213,0.988297,0.011188,0.0,0.985639,
                       -0.15254,0.072484,0.0,-8.626667,3.113528,4.477407,1.0);
      _memcpy(pcVar5 + 0x100,atStack_60,0x40);
      *(undefined4 *)(pcVar5 + 0x25c) = 0x1000000;
      tColour::Set((tColour *)(this + iVar4 + 0x260),1.0,1.0,1.0,0.0);
      uVar2 = 0x3f800000;
      tColour::Set((tColour *)(this + iVar4 + 0x270),1.0,1.0,1.0,0.0);
      cRMouse::SetInActive((cRMouse *)(this + iVar4 + 0x228));
      bVar7 = iVar6 == 0;
      if (bVar7) {
        uVar2 = 0xc;
      }
      pcVar1 = PTR__gConfig_001b60d4 + 0x60;
      pcVar5[0x23c] = (cRGame)0x0;
      pcVar5[0x2c1] = (cRGame)0x0;
      *(undefined4 *)(pcVar5 + 0x2c4) = 0;
      iVar6 = iVar6 + 1;
      pcVar5 = pcVar5 + 0x1fc;
      if (bVar7) {
        *(undefined4 *)(this + 0x15c) = uVar2;
      }
      Rstrcpy((char *)(this + iVar4 + 0x148),pcVar1);
    } while (iVar6 < *(int *)(this + 100));
  }
  cRSubHighScore::Init();
  cRSubHighScore::MiniInit((cRSubHighScore *)(this + 0x312d20));
  this_00 = (cRTipManager *)(this + 0x3783b4);
  this[0x353545] = (cRGame)0x0;
  this[0x353544] = (cRGame)0x0;
  cRTipManager::Init(this_00);
  if ((*(uint *)(this + 0x3783b8) & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRTipManager **)(this + 0x35c) = this_00;
      *(undefined4 *)(this + 0x3783bc) = 0;
      *(undefined4 *)(this + 0x3783c0) = 0;
    }
    else {
      *(cRTipManager **)(*(int *)(this + 0x35c) + 8) = this_00;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar6 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar6;
      *(undefined4 *)(iVar6 + 8) = 0;
    }
    *(uint *)(this + 0x3783b8) = *(uint *)(this + 0x3783b8) | 0x200;
    iVar6 = *(int *)PTR__Game_001b60b8;
    uVar3 = *(uint *)(this + 0x4e71c);
  }
  else {
    RShellError("List ADD");
    iVar6 = *(int *)PTR__Game_001b60b8;
    uVar3 = *(uint *)(this + 0x4e71c);
  }
  if ((uVar3 & 0x200) == 0) {
    if (*(int *)(iVar6 + 0x35c) == 0) {
      *(cRGame **)(iVar6 + 0x35c) = this + 0x4e718;
      *(undefined4 *)(this + 0x4e720) = 0;
      *(undefined4 *)(this + 0x4e724) = 0;
    }
    else {
      *(cRGame **)(*(int *)(iVar6 + 0x35c) + 8) = this + 0x4e718;
      *(int *)(*(int *)(*(int *)(iVar6 + 0x35c) + 8) + 0xc) = *(int *)(iVar6 + 0x35c);
      iVar4 = *(int *)(*(int *)(iVar6 + 0x35c) + 8);
      *(int *)(iVar6 + 0x35c) = iVar4;
      *(undefined4 *)(iVar4 + 8) = 0;
    }
    *(uint *)(this + 0x4e71c) = *(uint *)(this + 0x4e71c) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  cRStarManager::Open((int)(this + 0x4e718));
  uVar3 = *(uint *)(this + 0xd18);
  *(undefined4 *)(this + 0x7b15c) = 0;
  *(undefined4 *)(this + 0x7b158) = 0;
  if ((uVar3 & 0x200) == 0) {
    iVar6 = *(int *)(this + 0x35c);
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0xd14;
      *(undefined4 *)(this + 0xd1c) = 0;
      *(undefined4 *)(this + 0xd20) = 0;
    }
    else {
      do {
        iVar4 = iVar6;
        iVar6 = *(int *)(iVar4 + 0xc);
      } while (*(int *)(iVar4 + 0xc) != 0);
      *(cRGame **)(iVar4 + 0xc) = this + 0xd14;
      *(int *)(this + 0xd1c) = iVar4;
      *(undefined4 *)(this + 0xd20) = 0;
    }
    *(uint *)(this + 0xd18) = uVar3 | 0x200;
  }
  else {
    RShellError("List ADDend");
  }
  cRBorderStack::Init((cRBorderStack *)(this + 0xd40));
  *(cRBorderManager **)(this + 5000) = (cRBorderManager *)(this + 0xd14);
  this[0x43df8] = (cRGame)0x0;
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(this + 0xd14),25.0);
  iVar6 = 0x71c;
  *(undefined4 *)(this + 0x1520) = 0;
  do {
    *(undefined4 *)(this + iVar6 + 0x1520) = 0;
    iVar6 = iVar6 + 0x71c;
  } while (iVar6 != 0x42a68);
  return;
}
