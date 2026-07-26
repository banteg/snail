/*
 * mangled: _ZN5cRBod8ApplyPosER7tMatrix
 * demangled: cRBod::ApplyPos(tMatrix&)
 * address: 00012e48
 * size: 120
 */

/* cRBod::ApplyPos(tMatrix&) */

void cRBod::ApplyPos(tMatrix *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  iVar1 = *(int *)(param_1 + 0x24);
  if (0 < *(int *)(iVar1 + 0xa0)) {
    iVar4 = 0;
    iVar3 = 0;
    do {
      puVar2 = (undefined4 *)(iVar3 + *(int *)(iVar1 + 0xa4));
      tVector::operator*((tVector *)&local_2c,(tMatrix *)(iVar3 + *(int *)(iVar1 + 0xa4)));
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0xc;
      *puVar2 = local_2c;
      puVar2[1] = uStack_28;
      puVar2[2] = uStack_24;
      iVar1 = *(int *)(param_1 + 0x24);
    } while (iVar4 < *(int *)(iVar1 + 0xa0));
  }
  return;
}
