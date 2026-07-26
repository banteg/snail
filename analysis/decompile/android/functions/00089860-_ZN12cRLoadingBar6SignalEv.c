/*
 * mangled: _ZN12cRLoadingBar6SignalEv
 * demangled: cRLoadingBar::Signal()
 * address: 00089860
 * size: 176
 */

/* cRLoadingBar::Signal() */

void __thiscall cRLoadingBar::Signal(cRLoadingBar *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  undefined4 uVar4;

  iVar3 = DAT_00089910 + 0x8987c;
  if (this[0x34] == (cRLoadingBar)0x0) {
    return;
  }
  if (this[0xbd] == (cRLoadingBar)0x0) {
    iVar2 = *(int *)(this + 4);
    iVar1 = *(int *)(iVar3 + DAT_00089914);
    *(int *)(this + 4) = iVar2 + 1;
    if (*(int *)(iVar1 + 0xac) == 0) {
      *(undefined4 *)(iVar1 + 0xac) = 1;
    }
    iVar1 = __divsi3(((iVar2 + 1) - *(int *)(this + 8)) * 100,0x4c8 - *(int *)(this + 8));
    iVar3 = *(int *)(iVar3 + DAT_00089918);
    if (99 < iVar1) {
      iVar1 = 100;
    }
    if (*(char *)(iVar3 + 0x45) != '\0') {
      if (0 < iVar1 - *(int *)this) {
        uVar4 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
        *(int *)this = iVar1;
        this[0xd3] = (cRLoadingBar)0x1;
        *(undefined4 *)(iVar3 + 0xa0) = uVar4;
        return;
      }
      return;
    }
    return;
  }
  return;
}
