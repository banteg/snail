/*
 * mangled: _ZN11cLinkedListI5cRBodE6RemoveEPS0_
 * demangled: cLinkedList<cRBod>::Remove(cRBod*)
 * address: 0005d1a8
 * size: 108
 */

/* cLinkedList<cRBod>::Remove(cRBod*) */

void __thiscall cLinkedList<cRBod>::Remove(cLinkedList<cRBod> *this,cRBod *param_1)

{
  uint uVar1;
  int iVar2;

  uVar1 = *(uint *)(param_1 + 4);
  if ((uVar1 & 0x200) == 0) {
    RShellError((char *)(DAT_0005d214 + 0x5d1bc + DAT_0005d218));
    return;
  }
  if ((uVar1 & 0x40) != 0) {
    RShellError((char *)(DAT_0005d214 + 0x5d1bc + DAT_0005d21c));
    return;
  }
  iVar2 = *(int *)(param_1 + 0xc);
  *(uint *)(param_1 + 4) = uVar1 & 0xfffffdff;
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(param_1 + 8);
  }
  if (*(int *)(param_1 + 8) == 0) {
    *(int *)(this + 4) = iVar2;
  }
  else {
    *(int *)(*(int *)(param_1 + 8) + 0xc) = iVar2;
  }
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(this + 8);
  *(cRBod **)(this + 8) = param_1;
  return;
}
