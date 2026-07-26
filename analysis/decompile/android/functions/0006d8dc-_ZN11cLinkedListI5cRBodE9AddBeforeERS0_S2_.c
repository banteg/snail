/*
 * mangled: _ZN11cLinkedListI5cRBodE9AddBeforeERS0_S2_
 * demangled: cLinkedList<cRBod>::AddBefore(cRBod&, cRBod&)
 * address: 0006d8dc
 * size: 100
 */

/* cLinkedList<cRBod>::AddBefore(cRBod&, cRBod&) */

void __thiscall
cLinkedList<cRBod>::AddBefore(cLinkedList<cRBod> *this,cRBod *param_1,cRBod *param_2)

{
  cRBod *pcVar1;

  if ((*(uint *)(param_1 + 4) & 0x200) != 0) {
    RShellError("List ADDbefore");
    return;
  }
  *(cRBod **)(param_1 + 0xc) = param_2;
  pcVar1 = *(cRBod **)(this + 4);
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 0x200;
  if (pcVar1 == param_2) {
    *(cRBod **)(pcVar1 + 8) = param_1;
    *(cRBod **)(this + 4) = param_1;
    *(undefined4 *)(param_1 + 8) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
    *(cRBod **)(param_2 + 8) = param_1;
    *(cRBod **)(*(int *)(param_1 + 8) + 0xc) = param_1;
  }
  return;
}
