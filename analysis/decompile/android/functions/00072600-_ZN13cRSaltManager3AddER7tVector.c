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
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  cRSaltManager *pcVar6;
  cRBod *pcVar7;
  int *piVar8;
  uint in_fpscr;
  float extraout_s0;

  iVar4 = 0;
  pcVar6 = this;
  do {
    pcVar1 = pcVar6 + 0x74;
    pcVar6 = pcVar6 + 0x8c;
    if (*(int *)pcVar1 == 0) {
      piVar8 = *(int **)(DAT_000726fc + 0x72618 + DAT_00072700);
      pcVar7 = (cRBod *)(this + iVar4 * 0x8c);
      *(undefined4 *)(pcVar7 + 0x80) = DAT_000726e8;
      fVar2 = DAT_000726ec;
      iVar4 = *piVar8;
      *(undefined4 *)(pcVar7 + 0x74) = 1;
      *(float *)(pcVar7 + 0x84) = *(float *)(iVar4 + 0x718f4) * fVar2;
      uVar3 = *(undefined4 *)(param_1 + 4);
      uVar5 = *(undefined4 *)(param_1 + 8);
      *(undefined4 *)(pcVar7 + 0x5c) = *(undefined4 *)param_1;
      *(undefined4 *)(pcVar7 + 0x60) = uVar3;
      *(undefined4 *)(pcVar7 + 100) = uVar5;
      tMatrix::RotIdentity((tMatrix *)(pcVar7 + 0x2c));
      uVar3 = gRMathRand2();
      VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      tMatrix::RotLocalY((tMatrix *)(pcVar7 + 0x2c),extraout_s0);
      iVar4 = *piVar8;
      pcVar7[0x88] = (cRBod)0x1;
      cLinkedList<cRBod>::AddAfter
                ((cLinkedList<cRBod> *)(iVar4 + 0x358),pcVar7,(cRBod *)(iVar4 + 0x74598));
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x28);
  return;
}
