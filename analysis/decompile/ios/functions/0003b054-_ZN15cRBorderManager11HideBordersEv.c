/*
 * mangled: _ZN15cRBorderManager11HideBordersEv
 * demangled: cRBorderManager::HideBorders()
 * address: 0003b054
 * size: 176
 */

/* cRBorderManager::HideBorders() */

void __thiscall cRBorderManager::HideBorders(cRBorderManager *this)

{
  int iVar1;
  uint uVar2;
  int iVar3;

  iVar3 = 0;
  do {
    iVar1 = iVar3 * 0x71c + *(int *)(this + 0x674);
    uVar2 = *(uint *)(iVar1 + 0x80c);
    if ((((uVar2 != 0) && ((uVar2 & 0x400) == 0)) && ((uVar2 & 0x10000000) == 0)) &&
       ((uVar2 & 0x1000) == 0)) {
      *(uint *)(iVar1 + 0x80c) = uVar2 | 0x1000;
      *(int *)(this + *(int *)(this + 0x30) * 8 + 0x38) =
           *(int *)(this + 0x674) + iVar3 * 0x71c + 0x678;
      *(undefined4 *)(this + (*(int *)(this + 0x30) + 1) * 8 + 0x2c) = *(undefined4 *)(this + 0x2c);
      *(int *)(this + 0x30) = *(int *)(this + 0x30) + 1;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x96);
  *(int *)(this + 0x2c) = *(int *)(this + 0x2c) + 1;
  return;
}
