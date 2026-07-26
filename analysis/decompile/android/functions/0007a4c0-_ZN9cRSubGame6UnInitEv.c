/*
 * mangled: _ZN9cRSubGame6UnInitEv
 * demangled: cRSubGame::UnInit()
 * address: 0007a4c0
 * size: 992
 */

/* cRSubGame::UnInit() */

void __thiscall cRSubGame::UnInit(cRSubGame *this)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  cRSubGame *pcVar6;
  int iVar7;
  bool bVar8;
  float fVar9;

  iVar5 = DAT_0007a8a4;
  iVar7 = DAT_0007a8a0;
  OFSaveHighScores();
  iVar7 = iVar7 + 0x7a4e0;
  fVar9 = (float)wprintf((char *)(iVar7 + DAT_0007a8a8));
  piVar3 = *(int **)(iVar7 + iVar5);
  cRBackdrop::SetZoom((cRBackdrop *)(*piVar3 + 0x4d2e0),fVar9);
  cRQuit::UnInit((cRQuit *)(this + 8));
  *(undefined4 *)(*piVar3 + 0x4d364) = 1;
  if (*(int *)(this + 0x60) == 7) {
    cRTutorial::UnInit();
  }
  cRWarning::UnInit((cRWarning *)(this + 0xfea8));
  cRLandscapeManager::UnInit();
  cRTimesUp::UnInit((cRTimesUp *)(this + 0x334600));
  RemoveBods(this);
  if (*(int *)(this + 0x5c) != 1) {
    uVar2 = *(uint *)(this + 0x60);
    bVar8 = 3 < uVar2;
    if (uVar2 != 4) {
      bVar8 = uVar2 != 0;
    }
    if (!bVar8 || (uVar2 == 4 || uVar2 == 1)) {
      cRCompletion::UnInit((cRCompletion *)(this + 0x3345ac));
    }
    iVar4 = 0;
    pcVar6 = this + 0x41ac;
    do {
      while (uVar2 = *(uint *)pcVar6, pcVar6 = pcVar6 + 0xa4, (uVar2 & 0x200) == 0) {
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x14) goto LAB_0007a5cc;
      }
      iVar1 = iVar4 * 0xa4;
      iVar4 = iVar4 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),
                 (cRBod *)(this + iVar1 + 0x41a8));
    } while (iVar4 != 0x14);
LAB_0007a5cc:
    iVar4 = 0;
    pcVar6 = this + 0x4e7c;
    do {
      while (uVar2 = *(uint *)pcVar6, pcVar6 = pcVar6 + 0x8c, (uVar2 & 0x200) == 0) {
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x28) goto LAB_0007a628;
      }
      iVar1 = iVar4 * 0x8c;
      iVar4 = iVar4 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),
                 (cRBod *)(this + iVar1 + 0x4e78));
    } while (iVar4 != 0x28);
LAB_0007a628:
    pcVar6 = this + 0x334614;
    iVar4 = 0;
    do {
      while ((*(uint *)pcVar6 & 0x200) == 0) {
        iVar4 = iVar4 + 1;
        pcVar6 = pcVar6 + 0x84;
        if (iVar4 == 8) goto LAB_0007a694;
      }
      iVar1 = iVar4 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),
                 (cRBod *)(this + iVar4 * 0x84 + 0x334610));
      *(undefined4 *)(pcVar6 + 0x70) = 0;
      pcVar6 = pcVar6 + 0x84;
      iVar4 = iVar1;
    } while (iVar1 != 8);
LAB_0007a694:
    if ((*(uint *)(this + 0x645c) & 0x200) != 0) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),(cRBod *)(this + 0x6458))
      ;
    }
    if ((*(uint *)(this + 0x64b0) & 0x200) != 0) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),(cRBod *)(this + 0x64ac))
      ;
      uVar2 = *(uint *)(this + 0x315b28);
      goto joined_r0x0007a6c4;
    }
  }
  uVar2 = *(uint *)(this + 0x315b28);
joined_r0x0007a6c4:
  if ((uVar2 & 0x200) == 0) {
    uVar2 = *(uint *)(this + 0xf9f4);
  }
  else {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar7 + iVar5) + 0x358),(cRBod *)(this + 0x315b24))
    ;
    uVar2 = *(uint *)(this + 0xf9f4);
  }
  if ((uVar2 & 0x200) != 0) {
    piVar3 = *(int **)(iVar7 + iVar5);
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar3 + 0x358),(cRBod *)(this + 0xf9f0));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar3 + 0x358),(cRBod *)(this + 0xfa1c));
  }
  piVar3 = *(int **)(iVar7 + iVar5);
  cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0x8c58));
  cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0x8c5c));
  if (this[0x30fcc1] != (cRSubGame)0x0) {
    iVar4 = *piVar3;
    this[0x30fcc1] = (cRSubGame)0x0;
    *(undefined4 *)(iVar4 + 0x160) = 0x12;
  }
  iVar4 = *(int *)(this + 0x60);
  if (iVar4 == 3) {
    *(undefined4 *)(**(int **)(iVar7 + iVar5) + 0x71900) = 2;
    iVar4 = *(int *)(this + 0x60);
  }
  if (iVar4 == 0) {
    piVar3 = *(int **)(iVar7 + iVar5);
    cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0x8c60));
    cRBorderManager::Kill((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + 0x8c64));
    iVar7 = 0;
    do {
      iVar5 = iVar7 + 4;
      cRBorderManager::Kill
                ((cRBorderManager *)(*piVar3 + 0xd14),*(cRBorder **)(this + iVar7 + 0x8c68));
      iVar7 = iVar5;
    } while (iVar5 != 0x24);
    *(undefined4 *)(this + 0x5c) = 8;
    return;
  }
  *(undefined4 *)(this + 0x5c) = 8;
  return;
}
