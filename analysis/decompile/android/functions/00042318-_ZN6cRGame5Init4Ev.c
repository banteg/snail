/*
 * mangled: _ZN6cRGame5Init4Ev
 * demangled: cRGame::Init4()
 * address: 00042318
 * size: 776
 */

/* cRGame::Init4() */

void __thiscall cRGame::Init4(cRGame *this)

{
  uint uVar1;
  int iVar2;
  cRGame *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float extraout_s0;
  float fVar7;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;
  float extraout_s6;
  float extraout_s7;
  float extraout_s8;
  float extraout_s9;
  float extraout_s10;
  float extraout_s11;
  float extraout_s12;
  float extraout_s13;
  float extraout_s14;
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

  wprintf("GameInit4\n");
  if (0 < *(int *)(this + 100)) {
    iVar4 = 0;
    pcVar3 = this;
    do {
      iVar2 = iVar4 * 0x1fc;
      tMatrix::Identity((tMatrix *)(this + iVar2 + 0x100));
      tMatrix::Identity((tMatrix *)(this + iVar2 + 0x194));
      *(undefined4 *)(pcVar3 + 0x21c) = 0x42f00000;
      *(cRGame **)(pcVar3 + 0x224) = this + iVar4 * 0x6c + 0x68;
      tMatrix::tMatrix((tMatrix *)&local_88,extraout_s0,extraout_s1,extraout_s2,extraout_s3,
                       extraout_s4,extraout_s5,extraout_s6,extraout_s7,extraout_s8,extraout_s9,
                       extraout_s10,extraout_s11,extraout_s12,extraout_s13,extraout_s14,1.0);
      *(undefined4 *)(pcVar3 + 0x100) = local_88;
      *(undefined4 *)(pcVar3 + 0x104) = uStack_84;
      *(undefined4 *)(pcVar3 + 0x108) = uStack_80;
      *(undefined4 *)(pcVar3 + 0x10c) = uStack_7c;
      *(undefined4 *)(pcVar3 + 0x110) = local_78;
      *(undefined4 *)(pcVar3 + 0x114) = uStack_74;
      *(undefined4 *)(pcVar3 + 0x118) = uStack_70;
      *(undefined4 *)(pcVar3 + 0x11c) = uStack_6c;
      *(undefined4 *)(pcVar3 + 0x120) = local_68;
      *(undefined4 *)(pcVar3 + 0x124) = uStack_64;
      *(undefined4 *)(pcVar3 + 0x128) = uStack_60;
      *(undefined4 *)(pcVar3 + 300) = uStack_5c;
      *(undefined4 *)(pcVar3 + 0x130) = local_58;
      *(undefined4 *)(pcVar3 + 0x134) = uStack_54;
      *(undefined4 *)(pcVar3 + 0x138) = uStack_50;
      *(undefined4 *)(pcVar3 + 0x13c) = uStack_4c;
      cRFlash::Init((int)(this + iVar2 + 0x25c));
      cRMouse::SetInActive((cRMouse *)(this + iVar2 + 0x228));
      if (iVar4 == 0) {
        *(undefined4 *)(this + 0x15c) = 0xc;
      }
      pcVar3[0x23c] = (cRGame)0x0;
      iVar4 = iVar4 + 1;
      *(undefined4 *)(pcVar3 + 0x2c4) = 0;
      pcVar3[0x2c1] = (cRGame)0x0;
      pcVar3 = pcVar3 + 0x1fc;
      Rstrcpy((char *)(this + iVar2 + 0x148),gConfig + 0x60);
    } while (iVar4 < *(int *)(this + 100));
  }
  cRSubHighScore::Init();
  cRSubHighScore::MiniInit((cRSubHighScore *)(this + 0x340d3c));
  this[0x381561] = (cRGame)0x0;
  this[0x381560] = (cRGame)0x0;
  cRTipManager::Init((cRTipManager *)(this + 0x3a63d8));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(this + 0x358),(cRBod *)(this + 0x3a63d8));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x4d440));
  cRStarManager::Open((int)(this + 0x4d440));
  uVar1 = *(uint *)(this + 0xd18);
  *(undefined4 *)(this + 0x7a4f8) = 0;
  *(undefined4 *)(this + 0x7a4fc) = 0;
  if ((uVar1 & 0x200) == 0) {
    iVar4 = *(int *)(this + 0x35c);
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0xd14;
      *(undefined4 *)(this + 0xd20) = 0;
      *(undefined4 *)(this + 0xd1c) = 0;
    }
    else {
      do {
        iVar2 = iVar4;
        iVar4 = *(int *)(iVar2 + 0xc);
      } while (*(int *)(iVar2 + 0xc) != 0);
      *(cRGame **)(iVar2 + 0xc) = this + 0xd14;
      *(int *)(this + 0xd1c) = iVar2;
      *(undefined4 *)(this + 0xd20) = 0;
    }
    *(uint *)(this + 0xd18) = uVar1 | 0x200;
  }
  else {
    RShellError("List ADDend");
  }
  fVar7 = (float)cRBorderStack::Init((cRBorderStack *)(this + 0xd40));
  *(cRBorderManager **)(this + 5000) = (cRBorderManager *)(this + 0xd14);
  this[0x43df8] = (cRGame)0x0;
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(this + 0xd14),fVar7);
  puVar5 = (undefined4 *)0x0;
  do {
    puVar6 = puVar5 + 0x1c7;
    *(undefined4 *)(this + (int)(puVar5 + 0x548)) = 0;
    puVar5 = puVar6;
  } while (puVar6 != &DAT_00042a68);
  return;
}
