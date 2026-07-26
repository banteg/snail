/*
 * mangled: _ZN13cRSaltManager3AddER7tVector
 * demangled: cRSaltManager::Add(tVector&)
 * address: 00072600
 * size: 232
 */

/* cRSaltManager::Add(tVector&) */

void __thiscall cRSaltManager::Add(cRSaltManager *this,tVector *param_1)

{
  cRSaltManager *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  cRSaltManager *pcVar5;
  cRBod *pcVar6;
  uint in_fpscr;
  float extraout_s0;

  iVar3 = 0;
  pcVar5 = this;
  do {
    pcVar1 = pcVar5 + 0x74;
    pcVar5 = pcVar5 + 0x8c;
    if (*(int *)pcVar1 == 0) {
      pcVar6 = (cRBod *)(this + iVar3 * 0x8c);
      *(undefined4 *)(pcVar6 + 0x80) = 0;
      iVar3 = Game;
      *(undefined4 *)(pcVar6 + 0x74) = 1;
      *(float *)(pcVar6 + 0x84) = *(float *)(iVar3 + 0x718f4) * 0.033333335;
      uVar2 = *(undefined4 *)(param_1 + 4);
      uVar4 = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(pcVar6 + 0x5c) = *(undefined4 *)param_1;
      *(undefined4 *)(pcVar6 + 0x60) = uVar2;
      *(undefined4 *)(pcVar6 + 100) = uVar4;
      tMatrix::RotIdentity((tMatrix *)(pcVar6 + 0x2c));
      uVar2 = gRMathRand2();
      VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      tMatrix::RotLocalY((tMatrix *)(pcVar6 + 0x2c),extraout_s0);
      iVar3 = Game;
      pcVar6[0x88] = (cRBod)0x1;
      cLinkedList<cRBod>::AddAfter
                ((cLinkedList<cRBod> *)(iVar3 + 0x358),pcVar6,(cRBod *)(iVar3 + 0x74598));
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x28);
  return;
}
