/*
 * mangled: _ZN6cRQuit2AIEv
 * demangled: cRQuit::AI()
 * address: 0006f50c
 * size: 316
 */

/* cRQuit::AI() */

void __thiscall cRQuit::AI(cRQuit *this)

{
  cRBorder *this_00;
  uint uVar1;
  int iVar2;

  this_00 = *(cRBorder **)(this + 4);
  if (this_00 == (cRBorder *)0x0) {
    return;
  }
  if (*(char *)(Game + 0x718b9) == '\0') {
    cRBorder::UnHideInit(this_00);
    iVar2 = Game;
    uVar1 = *(uint *)(*(int *)(this + 4) + 0x194);
    if (((uVar1 & 0x20) == 0) ||
       ((*(uint *)(*(int *)(this + 4) + 0x194) = uVar1 & 0xffffffdf, *(int *)(iVar2 + 0x71900) == 0
        && (((*(char *)(iVar2 + 0x81779) != '\0' && (*(float *)(iVar2 + 0x813c4) < -0.1)) ||
            (*(char *)(iVar2 + 0x81624) != '\0')))))) {
      if (*(int *)(iVar2 + 0x718b4) < 1) {
        return;
      }
    }
    else {
      wprintf("Border Quit");
      KeySet('\x01');
      iVar2 = Game;
      if (*(int *)(Game + 0x718b4) < 1) {
        return;
      }
    }
    *(undefined4 *)(iVar2 + 0x718b4) = 0;
    wprintf("Border Auto Quit");
    KeySet('\x01');
    return;
  }
  cRBorder::HideInit(this_00);
  *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffffffdf;
  return;
}
