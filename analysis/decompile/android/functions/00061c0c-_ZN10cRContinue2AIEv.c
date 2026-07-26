/*
 * mangled: _ZN10cRContinue2AIEv
 * demangled: cRContinue::AI()
 * address: 00061c0c
 * size: 428
 */

/* cRContinue::AI() */

void __thiscall cRContinue::AI(cRContinue *this)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;

  iVar2 = DAT_00061dbc;
  iVar4 = DAT_00061db8 + 0x61c24;
  if (*(float *)(**(int **)(iVar4 + DAT_00061dbc) + 0x3c) !=
      *(float *)(**(int **)(iVar4 + DAT_00061dbc) + 0x44)) {
    UnInit();
    Init(this);
  }
  uVar1 = *(uint *)(*(int *)this + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar1 & 0xffffffdf;
    UnInit();
    iVar3 = **(int **)(iVar4 + iVar2);
    *(undefined4 *)(iVar3 + 0x15c) = 10;
    iVar2 = *(int *)(gOFOData + iVar3 + 0x1ebc);
    *(undefined4 *)(iVar3 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar3) = 4;
    *(undefined1 *)(iVar3 + 0x2c0) = 1;
    if (iVar2 == 0) {
      iVar2 = *(int *)(iVar4 + DAT_00061dc0);
      uVar5 = *(undefined4 *)(iVar2 + 0xd8);
      *(undefined4 *)(iVar3 + 0x71904) = uVar5;
      *(undefined4 *)(iVar2 + 0xa4) = uVar5;
      *(undefined4 *)(iVar3 + 0x81630) = *(undefined4 *)(iVar2 + 0xd0);
      *(undefined4 *)(iVar3 + 0x85358) = *(undefined4 *)(iVar2 + 0xd4);
      return;
    }
    if (iVar2 != 1) {
      return;
    }
    iVar2 = *(int *)(iVar4 + DAT_00061dc0);
    uVar5 = *(undefined4 *)(iVar2 + 0xdc);
    *(undefined4 *)(iVar3 + 0x71904) = uVar5;
    *(undefined4 *)(iVar2 + 0xec) = uVar5;
    *(undefined4 *)(iVar3 + 0x81630) = *(undefined4 *)(iVar2 + 0xe0);
    *(undefined4 *)(iVar3 + 0x85358) = *(undefined4 *)(iVar2 + 0xe4);
    return;
  }
  uVar1 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar1 & 0xffffffdf;
    UnInit();
    iVar2 = **(int **)(iVar4 + iVar2);
    *(undefined1 *)(iVar2 + 0x2c0) = 1;
    *(undefined4 *)(iVar2 + 0x15c) = 0x23;
    return;
  }
  uVar1 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar1 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar1 & 0xffffffdf;
  UnInit();
  iVar2 = **(int **)(iVar4 + iVar2);
  *(undefined1 *)(iVar2 + 0x2c0) = 1;
  *(undefined4 *)(iVar2 + 0x15c) = 2;
  return;
}
