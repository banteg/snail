/*
 * mangled: _ZN11cLinkedListI5cRBodE3AddERS0_
 * demangled: cLinkedList<cRBod>::Add(cRBod&)
 * address: 0003f638
 * size: 80
 */

/* cLinkedList<cRBod>::Add(cRBod&) */

void __thiscall cLinkedList<cRBod>::Add(cLinkedList<cRBod> *this,cRBod *param_1)

{
  int iVar1;

  if ((*(uint *)(param_1 + 4) & 0x200) != 0) {
    RShellError((char *)(DAT_0003f688 + 0x3f64c + DAT_0003f68c));
    return;
  }
  iVar1 = *(int *)(this + 4);
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x200;
  if (iVar1 == 0) {
    *(cRBod **)(this + 4) = param_1;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  else {
    *(cRBod **)(iVar1 + 8) = param_1;
    *(int *)(param_1 + 0xc) = iVar1;
    *(cRBod **)(this + 4) = param_1;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  return;
}
