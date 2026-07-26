/*
 * mangled: _ZN6cRQuit2AIEv
 * demangled: cRQuit::AI()
 * address: 0006f50c
 * size: 316
 */

/* cRQuit::AI() */

void __thiscall cRQuit::AI(cRQuit *this)

{
  int iVar1;
  cRBorder *this_00;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;

  iVar1 = DAT_0006f650;
  this_00 = *(cRBorder **)(this + 4);
  iVar4 = DAT_0006f64c + 0x6f528;
  if (this_00 == (cRBorder *)0x0) {
    return;
  }
  piVar5 = *(int **)(iVar4 + DAT_0006f650);
  if (*(char *)(*piVar5 + 0x718b9) != '\0') {
    cRBorder::HideInit(this_00);
    *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffffffdf;
    return;
  }
  cRBorder::UnHideInit(this_00);
  uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
  if ((uVar2 & 0x20) == 0) {
    iVar3 = *piVar5;
  }
  else {
    iVar3 = *piVar5;
    *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
    if ((*(int *)(iVar3 + 0x71900) != 0) ||
       (((*(char *)(iVar3 + 0x81779) == '\0' || (DAT_0006f648 <= *(float *)(iVar3 + 0x813c4))) &&
        (*(char *)(iVar3 + 0x81624) == '\0')))) {
      wprintf((char *)(iVar4 + DAT_0006f658));
      KeySet('\x01');
      iVar3 = **(int **)(iVar4 + iVar1);
      if (*(int *)(iVar3 + 0x718b4) < 1) {
        return;
      }
      goto LAB_0006f574;
    }
  }
  if (*(int *)(iVar3 + 0x718b4) < 1) {
    return;
  }
LAB_0006f574:
  iVar1 = DAT_0006f654;
  *(undefined4 *)(iVar3 + 0x718b4) = 0;
  wprintf((char *)(iVar4 + iVar1));
  KeySet('\x01');
  return;
}
