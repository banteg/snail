/*
 * mangled: _ZN12cRSubSpeedUp2AIEv
 * demangled: cRSubSpeedUp::AI()
 * address: 0006e6e4
 * size: 128
 */

/* cRSubSpeedUp::AI() */

void __thiscall cRSubSpeedUp::AI(cRSubSpeedUp *this)

{
  int iVar1;

  iVar1 = DAT_0006e764 + 0x6e6fc;
  if (*(char *)(*(int *)(this + 0x80) + 0x19) != '\0') {
    return;
  }
  if (*(int *)(this + 0x74) == 1) {
    if (*(float *)(*(int *)(this + 0x78) + 0x27fc) <= *(float *)(this + 100)) {
      return;
    }
  }
  else if (*(int *)(this + 0x74) != 2) {
    return;
  }
  *(undefined4 *)(this + 0x74) = 0;
  cLinkedList<cRBod>::Remove
            ((cLinkedList<cRBod> *)(**(int **)(iVar1 + DAT_0006e768) + 0x358),(cRBod *)this);
  cRSprite::Kill(*(cRSprite **)(this + 0xa0));
  return;
}
