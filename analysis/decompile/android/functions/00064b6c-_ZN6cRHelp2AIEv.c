/*
 * mangled: _ZN6cRHelp2AIEv
 * demangled: cRHelp::AI()
 * address: 00064b6c
 * size: 180
 */

/* cRHelp::AI() */

void __thiscall cRHelp::AI(cRHelp *this)

{
  int iVar1;

  if (((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) == 0) || (*(int *)(Game + 0x24) != 0)) {
    if (this[4] == (cRHelp)0x0) {
      return;
    }
    iVar1 = *(int *)(Game + 0x24);
  }
  else {
    if (this[4] != (cRHelp)0x0) {
      return;
    }
    cRSound::Play((int)&gRSound);
    cRFade::Start((cRFade *)(Game + 0x24),(_func_void *)0x0);
    iVar1 = Game;
    this[4] = (cRHelp)0x1;
    iVar1 = *(int *)(iVar1 + 0x24);
  }
  if (iVar1 != 4) {
    return;
  }
  UnInit();
  iVar1 = Game;
  *(undefined1 *)(Game + 0x2c0) = 1;
  *(undefined4 *)(iVar1 + 0x15c) = 2;
  return;
}
