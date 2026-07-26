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
  int iVar3;
  cRSubGame *pcVar4;
  bool bVar5;
  float fVar6;

  OFSaveHighScores();
  fVar6 = (float)wprintf("-SubGame::UnInit()\n");
  cRBackdrop::SetZoom((cRBackdrop *)(Game + 0x4d2e0),fVar6);
  cRQuit::UnInit((cRQuit *)(this + 8));
  *(undefined4 *)(Game + 0x4d364) = 1;
  if (*(int *)(this + 0x60) == 7) {
    cRTutorial::UnInit();
  }
  cRWarning::UnInit((cRWarning *)(this + 0xfea8));
  cRLandscapeManager::UnInit();
  cRTimesUp::UnInit((cRTimesUp *)(this + 0x334600));
  RemoveBods(this);
  if (*(int *)(this + 0x5c) != 1) {
    uVar2 = *(uint *)(this + 0x60);
    bVar5 = 3 < uVar2;
    if (uVar2 != 4) {
      bVar5 = uVar2 != 0;
    }
    if (!bVar5 || (uVar2 == 4 || uVar2 == 1)) {
      cRCompletion::UnInit((cRCompletion *)(this + 0x3345ac));
    }
    iVar3 = 0;
    pcVar4 = this + 0x41ac;
    do {
      while (uVar2 = *(uint *)pcVar4, pcVar4 = pcVar4 + 0xa4, (uVar2 & 0x200) == 0) {
        iVar3 = iVar3 + 1;
        if (iVar3 == 0x14) goto LAB_0007a5cc;
      }
      iVar1 = iVar3 * 0xa4;
      iVar3 = iVar3 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar1 + 0x41a8));
    } while (iVar3 != 0x14);
LAB_0007a5cc:
    iVar3 = 0;
    pcVar4 = this + 0x4e7c;
    do {
      while (uVar2 = *(uint *)pcVar4, pcVar4 = pcVar4 + 0x8c, (uVar2 & 0x200) == 0) {
        iVar3 = iVar3 + 1;
        if (iVar3 == 0x28) goto LAB_0007a628;
      }
      iVar1 = iVar3 * 0x8c;
      iVar3 = iVar3 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar1 + 0x4e78));
    } while (iVar3 != 0x28);
LAB_0007a628:
    pcVar4 = this + 0x334614;
    iVar3 = 0;
    do {
      while ((*(uint *)pcVar4 & 0x200) == 0) {
        iVar3 = iVar3 + 1;
        pcVar4 = pcVar4 + 0x84;
        if (iVar3 == 8) goto LAB_0007a694;
      }
      iVar1 = iVar3 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar3 * 0x84 + 0x334610));
      *(undefined4 *)(pcVar4 + 0x70) = 0;
      pcVar4 = pcVar4 + 0x84;
      iVar3 = iVar1;
    } while (iVar1 != 8);
LAB_0007a694:
    if ((*(uint *)(this + 0x645c) & 0x200) != 0) {
      cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x6458));
    }
    if ((*(uint *)(this + 0x64b0) & 0x200) != 0) {
      cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x64ac));
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
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x315b24));
    uVar2 = *(uint *)(this + 0xf9f4);
  }
  if ((uVar2 & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xf9f0));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xfa1c));
  }
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8c58));
  cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8c5c));
  iVar3 = Game;
  if (this[0x30fcc1] != (cRSubGame)0x0) {
    this[0x30fcc1] = (cRSubGame)0x0;
    *(undefined4 *)(iVar3 + 0x160) = 0x12;
  }
  iVar3 = *(int *)(this + 0x60);
  if (iVar3 == 3) {
    *(undefined4 *)(Game + 0x71900) = 2;
    iVar3 = *(int *)(this + 0x60);
  }
  if (iVar3 == 0) {
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8c60));
    cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x8c64));
    iVar3 = 0;
    do {
      iVar1 = iVar3 + 4;
      cRBorderManager::Kill((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + iVar3 + 0x8c68))
      ;
      iVar3 = iVar1;
    } while (iVar1 != 0x24);
    *(undefined4 *)(this + 0x5c) = 8;
    return;
  }
  *(undefined4 *)(this + 0x5c) = 8;
  return;
}
