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
  int iVar4;
  undefined4 uVar5;
  cRSubTrampRingManager *pcVar6;
  undefined4 uVar7;
  cRBod *pcVar8;

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
  iVar4 = 0;
  pcVar6 = this;
  do {
    pcVar1 = pcVar6 + 0x74;
    pcVar6 = pcVar6 + 0x84;
    if (*(int *)pcVar1 == 0) {
      pcVar8 = (cRBod *)(this + iVar4 * 0x84);
      *(undefined4 *)(pcVar8 + 0x78) = 0;
      iVar4 = Game;
      *(undefined4 *)(pcVar8 + 0x74) = 1;
      *(float *)(pcVar8 + 0x7c) = *(float *)(iVar4 + 0x718f4) * 0.041666668;
      tMatrix::Identity((tMatrix *)(pcVar8 + 0x2c));
      iVar4 = Game;
      uVar5 = *(undefined4 *)(pcVar3 + 0x71c);
      uVar7 = *(undefined4 *)(pcVar3 + 0x720);
      *(undefined4 *)(pcVar8 + 0x5c) = *(undefined4 *)(pcVar3 + 0x718);
      *(undefined4 *)(pcVar8 + 0x60) = uVar5;
      *(undefined4 *)(pcVar8 + 100) = uVar7;
      *(float *)(pcVar8 + 0x60) = *(float *)(pcVar8 + 0x60) - 0.2;
      cLinkedList<cRBod>::AddAfter
                ((cLinkedList<cRBod> *)(iVar4 + 0x358),pcVar8,(cRBod *)(iVar4 + 0x744bc));
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 8);
  return;
}
