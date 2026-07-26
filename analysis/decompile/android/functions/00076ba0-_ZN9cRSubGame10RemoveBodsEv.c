/*
 * mangled: _ZN9cRSubGame10RemoveBodsEv
 * demangled: cRSubGame::RemoveBods()
 * address: 00076ba0
 * size: 1100
 */

/* cRSubGame::RemoveBods() */

void __thiscall cRSubGame::RemoveBods(cRSubGame *this)

{
  int iVar1;
  int iVar2;
  cRSubGame *pcVar3;
  int iVar4;

  pcVar3 = this + 0x20dee4;
  iVar2 = 0;
  do {
    if ((*(uint *)pcVar3 & 0x200) != 0) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar2 * 0xdc + 0x20dee0));
    }
    iVar1 = 0;
    do {
      iVar4 = iVar1 + 1;
      cRSubLoc::Remove((cRSubLoc *)(this + iVar2 * 0x240 + iVar1 * 0x48 + 0x13adc));
      iVar1 = iVar4;
    } while (iVar4 != 8);
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0xdc;
  } while (iVar2 != 0xe10);
  iVar2 = 0;
  pcVar3 = this + 0x306c;
  do {
    while ((*(uint *)pcVar3 & 0x200) != 0) {
      iVar1 = iVar2 * 0x68;
      iVar2 = iVar2 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar1 + 0x3068));
      *(undefined4 *)(pcVar3 + 0x28) = 0;
      pcVar3 = pcVar3 + 0x68;
      if (iVar2 == 8) goto LAB_00076c84;
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x68;
  } while (iVar2 != 8);
LAB_00076c84:
  if ((*(uint *)(this + 0x2e4c) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x2e48));
    *(undefined4 *)(this + 0x2ebc) = 0;
  }
  if ((*(uint *)(this + 0x2ef4) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x2ef0));
    *(undefined4 *)(this + 0x2f1c) = 0;
  }
  iVar2 = 0;
  pcVar3 = this + 0x6508;
  do {
    while ((*(uint *)pcVar3 & 0x200) != 0) {
      iVar1 = iVar2 * 0xb8;
      *(undefined4 *)(pcVar3 + 0x74) = 0;
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 0xb8;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar1 + 0x6504));
      if (iVar2 == 0x32) goto LAB_00076d5c;
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0xb8;
  } while (iVar2 != 0x32);
LAB_00076d5c:
  iVar2 = 0;
  pcVar3 = this + 0x33ac;
  do {
    while ((*(uint *)pcVar3 & 0x200) != 0) {
      *(undefined4 *)(pcVar3 + 0x70) = 0;
      pcVar3 = pcVar3 + 0xe0;
      iVar1 = iVar2 * 0xe0;
      iVar2 = iVar2 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + iVar1 + 0x33a8));
      if (iVar2 == 0x10) goto LAB_00076dc8;
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0xe0;
  } while (iVar2 != 0x10);
LAB_00076dc8:
  if (*(int *)(this + 0x8968) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x88f4));
  }
  *(undefined4 *)(this + 0x8968) = 0;
  if (*(int *)(this + 0x8b14) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x8aa0));
  }
  *(undefined4 *)(this + 0x8b14) = 0;
  if ((*(uint *)(this + 0xfac8) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xfac4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x122c4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x13348));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x1288c));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x12c20));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x12fb4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x1399c));
    *(undefined4 *)(this + 0xfec8) = 0;
    cRSubGoldy::UnInit();
  }
  iVar2 = 0;
  pcVar3 = this + 0x10134;
  do {
    while (iVar1 = *(int *)pcVar3, pcVar3 = pcVar3 + 0x2c8, iVar1 == 1) {
      iVar1 = iVar2 * 0x2c8;
      iVar2 = iVar2 + 1;
      cRSubGolb::Kill((cRSubGolb *)(this + iVar1 + 0xff10));
      if (iVar2 == 0xc) goto LAB_00076f3c;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0xc);
LAB_00076f3c:
  if ((*(uint *)(this + 0xfb5c) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xfb58));
    *(undefined4 *)(this + 0xfbcc) = 0;
  }
  if ((*(uint *)(this + 0xf9f4) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xf9f0));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0xfa1c));
  }
  cRSpriteManager::KillGame();
  return;
}
