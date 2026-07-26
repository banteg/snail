/*
 * mangled: _ZN10cRSubPause2AIEv
 * demangled: cRSubPause::AI()
 * address: 00077260
 * size: 392
 */

/* cRSubPause::AI() */

void __thiscall cRSubPause::AI(cRSubPause *this)

{
  cRBorder *this_00;
  uint uVar1;
  int iVar2;

  uVar1 = *(uint *)(*(int *)this + 0x194);
  iVar2 = DAT_000773e8 + 0x7727c;
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)this + 0x194) = uVar1 & 0xffffffdf;
    this_00 = *(cRBorder **)(this + 8);
    iVar2 = **(int **)(iVar2 + DAT_000773ec);
    *(undefined1 *)(iVar2 + 0x4d484) = 0;
    *(undefined1 *)(iVar2 + 0x2c0) = 1;
    *(undefined4 *)(iVar2 + 0x4d480) = *(undefined4 *)(iVar2 + 0x15c);
    *(undefined4 *)(iVar2 + 0x15c) = 6;
    cRBorder::HideInit(this_00);
    cRBorder::HideInit(*(cRBorder **)this);
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    return;
  }
  cRBorder::UnHideInit(*(cRBorder **)(this + 8));
  cRBorder::UnHideInit(*(cRBorder **)this);
  cRBorder::UnHideInit(*(cRBorder **)(this + 4));
  uVar1 = *(uint *)(*(int *)(this + 8) + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 8) + 0x194) = uVar1 & 0xffffffdf;
    UnInit(this);
    iVar2 = **(int **)(iVar2 + DAT_000773ec);
    *(undefined1 *)(iVar2 + 0x718b8) = 1;
    *(undefined4 *)(iVar2 + 0x718fc) = 2;
    return;
  }
  uVar1 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar1 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar1 & 0xffffffdf;
    iVar2 = **(int **)(iVar2 + DAT_000773ec);
    *(undefined4 *)(iVar2 + 0x4d4b0) = *(undefined4 *)(iVar2 + 0x15c);
    if (*(int *)(iVar2 + 0x71900) == 7) {
      *(undefined4 *)(iVar2 + 0x4d4a8) = 7;
    }
    else if (gDirectory[iVar2 + 0x2545] == '\0') {
      *(undefined4 *)(iVar2 + 0x4d4a8) = 2;
    }
    else {
      *(undefined4 *)(iVar2 + 0x4d4a8) = 3;
    }
    *(undefined4 *)(&DAT_003a463c + iVar2) = 2;
    *(undefined4 *)(iVar2 + 0x15c) = 8;
    return;
  }
  return;
}
