/*
 * mangled: _ZN10cRMainMenu2AIEv
 * demangled: cRMainMenu::AI()
 * address: 00069c20
 * size: 388
 */

/* cRMainMenu::AI() */

void __thiscall cRMainMenu::AI(cRMainMenu *this)

{
  int iVar1;
  uint uVar2;
  int iVar3;

  if (*(float *)(Game + 0x3c) == *(float *)(Game + 0x44)) {
    iVar3 = *(int *)this;
    uVar2 = *(uint *)(iVar3 + 0x194);
  }
  else {
    UnInit();
    Init();
    iVar3 = *(int *)this;
    uVar2 = *(uint *)(iVar3 + 0x194);
  }
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(iVar3 + 0x194) = uVar2 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined1 *)(Game + 0x2c0) = 1;
    *(undefined4 *)(iVar3 + 0x15c) = 2;
    OFGetHighScore();
    return;
  }
  uVar2 = *(uint *)(*(int *)(this + 0xc) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0xc) + 0x194) = uVar2 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined1 *)(Game + 0x2c0) = 1;
    *(undefined4 *)(iVar3 + 0x15c) = 0xe;
    return;
  }
  uVar2 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar2 & 0x20) == 0) {
    if ((*(uint *)(*(int *)(this + 8) + 0x194) & 0x20) != 0) {
      UnInit();
      iVar3 = Game;
      iVar1 = *(int *)(this + 8);
      uVar2 = *(uint *)(iVar1 + 0x194);
      *(undefined1 *)(Game + 0x4d484) = 1;
      *(uint *)(iVar1 + 0x194) = uVar2 & 0xffffffdf;
      *(undefined4 *)(iVar3 + 0x4d480) = 4;
      *(undefined4 *)(iVar3 + 0x15c) = 6;
      return;
    }
    uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
      UnInit();
      iVar3 = Game;
      *(undefined4 *)(Game + 0x15c) = 0x12;
      *(undefined4 *)(&DAT_003a62d4 + iVar3) = 0;
      return;
    }
    return;
  }
  *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar2 & 0xffffffdf;
  OFOpen();
  return;
}
