/*
 * mangled: _ZN12cRSubGarbage4KillEv
 * demangled: cRSubGarbage::Kill()
 * address: 0006e518
 * size: 148
 */

/* cRSubGarbage::Kill() */

void __thiscall cRSubGarbage::Kill(cRSubGarbage *this)

{
  int iVar1;
  cRSubGarbage *pcVar2;
  cRSubGarbage *pcVar3;

  iVar1 = DAT_0006e5ac;
  *(undefined4 *)(this + 0x78) = 0;
  cLinkedList<cRBod>::Remove
            ((cLinkedList<cRBod> *)(**(int **)(iVar1 + 0x6e534 + DAT_0006e5b0) + 0x358),
             (cRBod *)this);
  cRSprite::Kill(*(cRSprite **)(this + 0xa8));
  pcVar3 = *(cRSubGarbage **)(*(int *)(this + 0x80) + 0x6500);
  if (pcVar3 == this) {
    *(undefined4 *)(*(int *)(this + 0x80) + 0x6500) = *(undefined4 *)(pcVar3 + 0x74);
    return;
  }
  if (pcVar3 == (cRSubGarbage *)0x0) {
    return;
  }
  do {
    pcVar2 = *(cRSubGarbage **)(pcVar3 + 0x74);
    if (pcVar2 == this) {
      *(undefined4 *)(pcVar3 + 0x74) = *(undefined4 *)(this + 0x74);
      *(undefined4 *)(this + 0x74) = 0;
      return;
    }
    pcVar3 = pcVar2;
  } while (pcVar2 != (cRSubGarbage *)0x0);
  return;
}
