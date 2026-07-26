/*
 * mangled: _ZN12cRSubGarbage4KillEv
 * demangled: cRSubGarbage::Kill()
 * address: 0006e518
 * size: 148
 */

/* cRSubGarbage::Kill() */

void __thiscall cRSubGarbage::Kill(cRSubGarbage *this)

{
  cRSubGarbage *pcVar1;
  cRSubGarbage *pcVar2;

  *(undefined4 *)(this + 0x78) = 0;
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
  cRSprite::Kill(*(cRSprite **)(this + 0xa8));
  pcVar2 = *(cRSubGarbage **)(*(int *)(this + 0x80) + 0x6500);
  if (pcVar2 == this) {
    *(undefined4 *)(*(int *)(this + 0x80) + 0x6500) = *(undefined4 *)(pcVar2 + 0x74);
    return;
  }
  if (pcVar2 == (cRSubGarbage *)0x0) {
    return;
  }
  do {
    pcVar1 = *(cRSubGarbage **)(pcVar2 + 0x74);
    if (pcVar1 == this) {
      *(undefined4 *)(pcVar2 + 0x74) = *(undefined4 *)(this + 0x74);
      *(undefined4 *)(this + 0x74) = 0;
      return;
    }
    pcVar2 = pcVar1;
  } while (pcVar1 != (cRSubGarbage *)0x0);
  return;
}
