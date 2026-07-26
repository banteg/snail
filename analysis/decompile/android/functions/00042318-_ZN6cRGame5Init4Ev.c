/*
 * mangled: _ZN6cRGame5Init4Ev
 * demangled: cRGame::Init4()
 * address: 00042318
 * size: 776
 */

/* cRGame::Init4() */

void __thiscall cRGame::Init4(cRGame *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  cRGame *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  float extraout_s0;
  float fVar11;
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

  iVar10 = DAT_0004264c + 0x42334;
  wprintf((char *)(iVar10 + DAT_00042650));
  iVar3 = DAT_00042654;
  uVar2 = DAT_00042620;
  if (0 < *(int *)(this + 100)) {
    iVar7 = 0;
    pcVar6 = this;
    do {
      iVar1 = iVar7 * 0x1fc;
      tMatrix::Identity((tMatrix *)(this + iVar1 + 0x100));
      tMatrix::Identity((tMatrix *)(this + iVar1 + 0x194));
      *(undefined4 *)(pcVar6 + 0x21c) = uVar2;
      *(cRGame **)(pcVar6 + 0x224) = this + iVar7 * 0x6c + 0x68;
      tMatrix::tMatrix((tMatrix *)&local_88,extraout_s0,extraout_s1,extraout_s2,extraout_s3,
                       extraout_s4,extraout_s5,extraout_s6,extraout_s7,extraout_s8,extraout_s9,
                       extraout_s10,extraout_s11,extraout_s12,extraout_s13,extraout_s14,DAT_00042648
                      );
      *(undefined4 *)(pcVar6 + 0x100) = local_88;
      *(undefined4 *)(pcVar6 + 0x104) = uStack_84;
      *(undefined4 *)(pcVar6 + 0x108) = uStack_80;
      *(undefined4 *)(pcVar6 + 0x10c) = uStack_7c;
      *(undefined4 *)(pcVar6 + 0x110) = local_78;
      *(undefined4 *)(pcVar6 + 0x114) = uStack_74;
      *(undefined4 *)(pcVar6 + 0x118) = uStack_70;
      *(undefined4 *)(pcVar6 + 0x11c) = uStack_6c;
      *(undefined4 *)(pcVar6 + 0x120) = local_68;
      *(undefined4 *)(pcVar6 + 0x124) = uStack_64;
      *(undefined4 *)(pcVar6 + 0x128) = uStack_60;
      *(undefined4 *)(pcVar6 + 300) = uStack_5c;
      *(undefined4 *)(pcVar6 + 0x130) = local_58;
      *(undefined4 *)(pcVar6 + 0x134) = uStack_54;
      *(undefined4 *)(pcVar6 + 0x138) = uStack_50;
      *(undefined4 *)(pcVar6 + 0x13c) = uStack_4c;
      cRFlash::Init((int)(this + iVar1 + 0x25c));
      cRMouse::SetInActive((cRMouse *)(this + iVar1 + 0x228));
      if (iVar7 == 0) {
        *(undefined4 *)(this + 0x15c) = 0xc;
      }
      pcVar6[0x23c] = (cRGame)0x0;
      iVar7 = iVar7 + 1;
      *(undefined4 *)(pcVar6 + 0x2c4) = 0;
      iVar4 = *(int *)(iVar10 + iVar3);
      pcVar6[0x2c1] = (cRGame)0x0;
      pcVar6 = pcVar6 + 0x1fc;
      Rstrcpy((char *)(this + iVar1 + 0x148),(char *)(iVar4 + 0x60));
    } while (iVar7 < *(int *)(this + 100));
  }
  cRSubHighScore::Init();
  cRSubHighScore::MiniInit((cRSubHighScore *)(this + 0x340d3c));
  this[0x381561] = (cRGame)0x0;
  this[0x381560] = (cRGame)0x0;
  cRTipManager::Init((cRTipManager *)(this + 0x3a63d8));
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(this + 0x358),(cRBod *)(this + 0x3a63d8));
  cLinkedList<cRBod>::Add
            ((cLinkedList<cRBod> *)(**(int **)(iVar10 + DAT_00042658) + 0x358),
             (cRBod *)(this + 0x4d440));
  cRStarManager::Open((int)(this + 0x4d440));
  uVar5 = *(uint *)(this + 0xd18);
  *(undefined4 *)(this + 0x7a4f8) = 0;
  *(undefined4 *)(this + 0x7a4fc) = 0;
  if ((uVar5 & 0x200) == 0) {
    iVar3 = *(int *)(this + 0x35c);
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0xd14;
      *(undefined4 *)(this + 0xd20) = 0;
      *(undefined4 *)(this + 0xd1c) = 0;
    }
    else {
      do {
        iVar10 = iVar3;
        iVar3 = *(int *)(iVar10 + 0xc);
      } while (*(int *)(iVar10 + 0xc) != 0);
      *(cRGame **)(iVar10 + 0xc) = this + 0xd14;
      *(int *)(this + 0xd1c) = iVar10;
      *(undefined4 *)(this + 0xd20) = 0;
    }
    *(uint *)(this + 0xd18) = uVar5 | 0x200;
  }
  else {
    RShellError((char *)(iVar10 + DAT_0004265c));
  }
  fVar11 = (float)cRBorderStack::Init((cRBorderStack *)(this + 0xd40));
  *(cRBorderManager **)(this + 5000) = (cRBorderManager *)(this + 0xd14);
  this[0x43df8] = (cRGame)0x0;
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(this + 0xd14),fVar11);
  puVar8 = (undefined4 *)0x0;
  do {
    puVar9 = puVar8 + 0x1c7;
    *(undefined4 *)(this + (int)(puVar8 + 0x548)) = 0;
    puVar8 = puVar9;
  } while (puVar9 != &DAT_00042a68);
  return;
}
