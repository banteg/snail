/*
 * mangled: _ZN11cLinkedListI5cRBodE8AddAfterERS0_S2_
 * demangled: cLinkedList<cRBod>::AddAfter(cRBod&, cRBod&)
 * address: 0003f690
 * size: 64
 */

/* cLinkedList<cRBod>::AddAfter(cRBod&, cRBod&) */

void __thiscall cLinkedList<cRBod>::AddAfter(cLinkedList<cRBod> *this,cRBod *param_1,cRBod *param_2)

{
  undefined4 uVar1;

  if ((*(uint *)(param_1 + 4) & 0x200) == 0) {
    uVar1 = *(undefined4 *)(param_2 + 0xc);
    *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x200;
    *(cRBod **)(param_1 + 8) = param_2;
    *(undefined4 *)(param_1 + 0xc) = uVar1;
    *(cRBod **)(param_2 + 0xc) = param_1;
    if (*(int *)(param_1 + 0xc) != 0) {
      *(cRBod **)(*(int *)(param_1 + 0xc) + 8) = param_1;
    }
    return;
  }
  RShellError((char *)(DAT_0003f6d0 + 0x3f6a4 + DAT_0003f6d4));
  return;
}
