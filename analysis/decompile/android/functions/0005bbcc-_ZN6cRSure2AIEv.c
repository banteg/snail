/*
 * mangled: _ZN6cRSure2AIEv
 * demangled: cRSure::AI()
 * address: 0005bbcc
 * size: 280
 */

/* cRSure::AI() */

void __thiscall cRSure::AI(cRSure *this)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  iVar5 = DAT_0005bce8;
  iVar6 = DAT_0005bce4 + 0x5bbe4;
  if (*(float *)(**(int **)(iVar6 + DAT_0005bce8) + 0x3c) !=
      *(float *)(**(int **)(iVar6 + DAT_0005bce8) + 0x44)) {
    UnInit();
    Init(this);
  }
  uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    piVar1 = *(int **)(iVar6 + iVar5);
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
    iVar3 = *(int *)(iVar6 + DAT_0005bcec);
    iVar4 = *piVar1;
    *(undefined4 *)(iVar3 + 0xcc) = 0;
    if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 0) {
      *(undefined4 *)(iVar3 + 0xa4) = 1;
    }
    else if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 1) {
      *(undefined4 *)(iVar3 + 0xec) = 1;
    }
    UnInit();
    iVar5 = **(int **)(iVar6 + iVar5);
    *(undefined4 *)(iVar5 + 0x15c) = 10;
    *(undefined4 *)(&DAT_003a463c + iVar5) = 2;
    *(undefined4 *)(iVar5 + 0x71900) = 0;
    *(undefined1 *)(iVar5 + 0x2c0) = 1;
    return;
  }
  uVar2 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar2 & 0x20) == 0) {
    return;
  }
  *(uint *)(*(int *)(this + 8) + 0x194) = uVar2 & 0xffffffdf;
  UnInit();
  iVar5 = **(int **)(iVar6 + iVar5);
  *(undefined1 *)(iVar5 + 0x2c0) = 1;
  *(undefined4 *)(iVar5 + 0x15c) = 0x21;
  return;
}
