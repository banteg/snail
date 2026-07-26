/*
 * mangled: _ZN10cRMainMenu2AIEv
 * demangled: cRMainMenu::AI()
 * address: 00069c20
 * size: 388
 */

/* cRMainMenu::AI() */

void __thiscall cRMainMenu::AI(cRMainMenu *this)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar2 = DAT_00069da8;
  iVar4 = DAT_00069da4 + 0x69c38;
  if (*(float *)(**(int **)(iVar4 + DAT_00069da8) + 0x3c) ==
      *(float *)(**(int **)(iVar4 + DAT_00069da8) + 0x44)) {
    iVar3 = *(int *)this;
    uVar1 = *(uint *)(iVar3 + 0x194);
  }
  else {
    UnInit();
    Init();
    iVar3 = *(int *)this;
    uVar1 = *(uint *)(iVar3 + 0x194);
  }
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(iVar3 + 0x194) = uVar1 & 0xffffffdf;
    UnInit();
    iVar2 = **(int **)(iVar4 + iVar2);
    *(undefined1 *)(iVar2 + 0x2c0) = 1;
    *(undefined4 *)(iVar2 + 0x15c) = 2;
    OFGetHighScore();
    return;
  }
  uVar1 = *(uint *)(*(int *)(this + 0xc) + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0xc) + 0x194) = uVar1 & 0xffffffdf;
    UnInit();
    iVar2 = **(int **)(iVar4 + iVar2);
    *(undefined1 *)(iVar2 + 0x2c0) = 1;
    *(undefined4 *)(iVar2 + 0x15c) = 0xe;
    return;
  }
  uVar1 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar1 & 0x20) == 0) {
    if ((*(uint *)(*(int *)(this + 8) + 0x194) & 0x20) != 0) {
      UnInit();
      iVar3 = *(int *)(this + 8);
      iVar2 = **(int **)(iVar4 + iVar2);
      uVar1 = *(uint *)(iVar3 + 0x194);
      *(undefined1 *)(iVar2 + 0x4d484) = 1;
      *(uint *)(iVar3 + 0x194) = uVar1 & 0xffffffdf;
      *(undefined4 *)(iVar2 + 0x4d480) = 4;
      *(undefined4 *)(iVar2 + 0x15c) = 6;
      return;
    }
    uVar1 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar1 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar1 & 0xffffffdf;
      UnInit();
      iVar2 = **(int **)(iVar4 + iVar2);
      *(undefined4 *)(iVar2 + 0x15c) = 0x12;
      *(undefined4 *)(&DAT_003a62d4 + iVar2) = 0;
      return;
    }
    return;
  }
  *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar1 & 0xffffffdf;
  OFOpen();
  return;
}
