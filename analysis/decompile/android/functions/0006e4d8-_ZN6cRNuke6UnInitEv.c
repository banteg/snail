/*
 * mangled: _ZN6cRNuke6UnInitEv
 * demangled: cRNuke::UnInit()
 * address: 0006e4d8
 * size: 64
 */

/* cRNuke::UnInit() */

void __thiscall cRNuke::UnInit(cRNuke *this)

{
  int iVar1;
  cRNuke *pcVar2;

  if (*(int *)this != 1) {
    return;
  }
  iVar1 = 0;
  pcVar2 = this;
  do {
    iVar1 = iVar1 + 1;
    cRSprite::Kill(*(cRSprite **)(pcVar2 + 0x18));
    pcVar2 = pcVar2 + 4;
  } while (iVar1 != 0x19);
  *(undefined4 *)this = 0;
  return;
}
