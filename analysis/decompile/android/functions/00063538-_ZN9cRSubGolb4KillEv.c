/*
 * mangled: _ZN9cRSubGolb4KillEv
 * demangled: cRSubGolb::Kill()
 * address: 00063538
 * size: 148
 */

/* cRSubGolb::Kill() */

void __thiscall cRSubGolb::Kill(cRSubGolb *this)

{
  int iVar1;
  int *piVar2;

  piVar2 = *(int **)(DAT_000635cc + 0x6354c + DAT_000635d0);
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)this);
  iVar1 = *(int *)(this + 0x1a0);
  *(undefined4 *)(this + 0x224) = 0;
  if (iVar1 == 1) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x74));
    return;
  }
  if (iVar1 == 2) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(*piVar2 + 0x358),(cRBod *)(this + 0x100));
    iVar1 = *(int *)(this + 0x174);
    if (iVar1 != 0) {
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xffffefff;
    }
    return;
  }
  if (iVar1 == 0) {
    cRSprite::Kill(*(cRSprite **)(this + 0x228));
    return;
  }
  return;
}
