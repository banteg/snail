/*
 * mangled: _ZN21cRSubTrampRingManager7AddRingEP8cRSubLoc
 * demangled: cRSubTrampRingManager::AddRing(cRSubLoc*)
 * address: 0006d5b4
 * size: 256
 */

/* cRSubTrampRingManager::AddRing(cRSubLoc*) */

void __thiscall cRSubTrampRingManager::AddRing(cRSubTrampRingManager *this,cRSubLoc *param_1)

{
  cRSubTrampRingManager *pcVar1;
  cRSubLoc cVar2;
  cRSubLoc *pcVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  cRSubTrampRingManager *pcVar7;
  undefined4 uVar8;
  cRBod *pcVar9;
  int *piVar10;

  cVar2 = param_1[0x30];
  while (cVar2 == (cRSubLoc)0x16) {
    cVar2 = param_1[-0x18];
    param_1 = param_1 + -0x48;
  }
  cVar2 = param_1[0x78];
  pcVar3 = param_1 + 0x48;
  while (cVar2 == (cRSubLoc)0x16) {
    cVar2 = pcVar3[-0x210];
    pcVar3 = pcVar3 + -0x240;
  }
  iVar5 = 0;
  pcVar7 = this;
  do {
    pcVar1 = pcVar7 + 0x74;
    pcVar7 = pcVar7 + 0x84;
    if (*(int *)pcVar1 == 0) {
      piVar10 = *(int **)(DAT_0006d6c0 + 0x6d5cc + DAT_0006d6c4);
      pcVar9 = (cRBod *)(this + iVar5 * 0x84);
      *(undefined4 *)(pcVar9 + 0x78) = DAT_0006d6b4;
      fVar4 = DAT_0006d6b8;
      iVar5 = *piVar10;
      *(undefined4 *)(pcVar9 + 0x74) = 1;
      *(float *)(pcVar9 + 0x7c) = *(float *)(iVar5 + 0x718f4) * fVar4;
      tMatrix::Identity((tMatrix *)(pcVar9 + 0x2c));
      fVar4 = DAT_0006d6bc;
      uVar6 = *(undefined4 *)(pcVar3 + 0x71c);
      uVar8 = *(undefined4 *)(pcVar3 + 0x720);
      iVar5 = *piVar10;
      *(undefined4 *)(pcVar9 + 0x5c) = *(undefined4 *)(pcVar3 + 0x718);
      *(undefined4 *)(pcVar9 + 0x60) = uVar6;
      *(undefined4 *)(pcVar9 + 100) = uVar8;
      *(float *)(pcVar9 + 0x60) = *(float *)(pcVar9 + 0x60) - fVar4;
      cLinkedList<cRBod>::AddAfter
                ((cLinkedList<cRBod> *)(iVar5 + 0x358),pcVar9,(cRBod *)(iVar5 + 0x744bc));
      return;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 != 8);
  return;
}
