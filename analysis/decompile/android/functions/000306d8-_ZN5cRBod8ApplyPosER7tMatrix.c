/*
 * mangled: _ZN5cRBod8ApplyPosER7tMatrix
 * demangled: cRBod::ApplyPos(tMatrix&)
 * address: 000306d8
 * size: 108
 */

/* cRBod::ApplyPos(tMatrix&) */

void cRBod::ApplyPos(tMatrix *param_1)

{
  int iVar1;
  tMatrix *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;

  iVar1 = *(int *)(param_1 + 0x24);
  if (0 < *(int *)(iVar1 + 0xa0)) {
    iVar3 = 0;
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      ptVar2 = (tMatrix *)(*(int *)(iVar1 + 0xa4) + iVar3);
      iVar3 = iVar3 + 0xc;
      tVector::operator*((tVector *)&local_30,ptVar2);
      iVar1 = *(int *)(param_1 + 0x24);
      iVar5 = *(int *)(iVar1 + 0xa0);
      *(undefined4 *)ptVar2 = local_30;
      *(undefined4 *)(ptVar2 + 4) = uStack_2c;
      *(undefined4 *)(ptVar2 + 8) = uStack_28;
    } while (iVar4 < iVar5);
  }
  return;
}
