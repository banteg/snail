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
  int *piVar2;
  int iVar3;
  cRSubGame *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;

  iVar5 = DAT_00076ff0;
  pcVar4 = this + 0x20dee4;
  iVar3 = 0;
  iVar6 = DAT_00076fec + 0x76bd0;
  do {
    if ((*(uint *)pcVar4 & 0x200) != 0) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar6 + iVar5) + 0x358),
                 (cRBod *)(this + iVar3 * 0xdc + 0x20dee0));
    }
    iVar7 = 0;
    do {
      iVar8 = iVar7 + 1;
      cRSubLoc::Remove((cRSubLoc *)(this + iVar3 * 0x240 + iVar7 * 0x48 + 0x13adc));
      iVar1 = DAT_00076ff0;
      iVar7 = iVar8;
    } while (iVar8 != 8);
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 0xdc;
  } while (iVar3 != 0xe10);
  iVar5 = 0;
  pcVar4 = this + 0x306c;
  do {
    while ((*(uint *)pcVar4 & 0x200) != 0) {
      iVar3 = iVar5 * 0x68;
      iVar5 = iVar5 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar6 + iVar1) + 0x358),
                 (cRBod *)(this + iVar3 + 0x3068));
      *(undefined4 *)(pcVar4 + 0x28) = 0;
      pcVar4 = pcVar4 + 0x68;
      if (iVar5 == 8) goto LAB_00076c84;
    }
    iVar5 = iVar5 + 1;
    pcVar4 = pcVar4 + 0x68;
  } while (iVar5 != 8);
LAB_00076c84:
  if ((*(uint *)(this + 0x2e4c) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00076ff0) + 0x358),
               (cRBod *)(this + 0x2e48));
    *(undefined4 *)(this + 0x2ebc) = 0;
  }
  if ((*(uint *)(this + 0x2ef4) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00076ff0) + 0x358),
               (cRBod *)(this + 0x2ef0));
    *(undefined4 *)(this + 0x2f1c) = 0;
  }
  iVar5 = DAT_00076ff0;
  iVar3 = 0;
  pcVar4 = this + 0x6508;
  do {
    while ((*(uint *)pcVar4 & 0x200) != 0) {
      iVar7 = iVar3 * 0xb8;
      piVar2 = *(int **)(iVar6 + iVar5);
      *(undefined4 *)(pcVar4 + 0x74) = 0;
      iVar3 = iVar3 + 1;
      pcVar4 = pcVar4 + 0xb8;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + iVar7 + 0x6504));
      if (iVar3 == 0x32) goto LAB_00076d5c;
    }
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 0xb8;
  } while (iVar3 != 0x32);
LAB_00076d5c:
  iVar5 = DAT_00076ff0;
  iVar3 = 0;
  pcVar4 = this + 0x33ac;
  do {
    while ((*(uint *)pcVar4 & 0x200) != 0) {
      piVar2 = *(int **)(iVar6 + iVar5);
      *(undefined4 *)(pcVar4 + 0x70) = 0;
      pcVar4 = pcVar4 + 0xe0;
      iVar7 = iVar3 * 0xe0;
      iVar3 = iVar3 + 1;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + iVar7 + 0x33a8));
      if (iVar3 == 0x10) goto LAB_00076dc8;
    }
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 0xe0;
  } while (iVar3 != 0x10);
LAB_00076dc8:
  if (*(int *)(this + 0x8968) != 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00076ff0) + 0x358),
               (cRBod *)(this + 0x88f4));
  }
  *(undefined4 *)(this + 0x8968) = 0;
  if (*(int *)(this + 0x8b14) != 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00076ff0) + 0x358),
               (cRBod *)(this + 0x8aa0));
  }
  *(undefined4 *)(this + 0x8b14) = 0;
  if ((*(uint *)(this + 0xfac8) & 0x200) != 0) {
    piVar2 = *(int **)(iVar6 + DAT_00076ff0);
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0xfac4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x122c4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x13348));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x1288c));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x12c20));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x12fb4));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x1399c));
    *(undefined4 *)(this + 0xfec8) = 0;
    cRSubGoldy::UnInit();
  }
  iVar5 = 0;
  pcVar4 = this + 0x10134;
  do {
    while (iVar3 = *(int *)pcVar4, pcVar4 = pcVar4 + 0x2c8, iVar3 == 1) {
      iVar3 = iVar5 * 0x2c8;
      iVar5 = iVar5 + 1;
      cRSubGolb::Kill((cRSubGolb *)(this + iVar3 + 0xff10));
      if (iVar5 == 0xc) goto LAB_00076f3c;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 0xc);
LAB_00076f3c:
  if ((*(uint *)(this + 0xfb5c) & 0x200) != 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00076ff0) + 0x358),
               (cRBod *)(this + 0xfb58));
    *(undefined4 *)(this + 0xfbcc) = 0;
  }
  if ((*(uint *)(this + 0xf9f4) & 0x200) != 0) {
    piVar2 = *(int **)(iVar6 + DAT_00076ff0);
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0xf9f0));
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0xfa1c));
  }
  cRSpriteManager::KillGame();
  return;
}
