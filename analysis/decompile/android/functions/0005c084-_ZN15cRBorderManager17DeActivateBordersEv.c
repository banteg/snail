/*
 * mangled: _ZN15cRBorderManager17DeActivateBordersEv
 * demangled: cRBorderManager::DeActivateBorders()
 * address: 0005c084
 * size: 68
 */

/* cRBorderManager::DeActivateBorders() */

void __thiscall cRBorderManager::DeActivateBorders(cRBorderManager *this)

{
  cRBorderManager *pcVar1;
  int iVar2;
  uint uVar3;

  iVar2 = 0;
  pcVar1 = this + 0x80c;
  do {
    uVar3 = *(uint *)pcVar1;
    iVar2 = iVar2 + 1;
    if (uVar3 != 0) {
      if ((uVar3 & 0x8000) != 0) {
        uVar3 = uVar3 | 0x80000000;
        *(uint *)pcVar1 = uVar3;
      }
      *(uint *)pcVar1 = uVar3 | 0x8000;
    }
    pcVar1 = pcVar1 + 0x71c;
  } while (iVar2 != 0x96);
  return;
}
