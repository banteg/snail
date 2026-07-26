/*
 * mangled: _ZN15cRBorderManager22DeActivateOtherBordersEP8cRBorder
 * demangled: cRBorderManager::DeActivateOtherBorders(cRBorder*)
 * address: 0005c234
 * size: 104
 */

/* cRBorderManager::DeActivateOtherBorders(cRBorder*) */

void __thiscall cRBorderManager::DeActivateOtherBorders(cRBorderManager *this,cRBorder *param_1)

{
  int iVar1;
  cRBorderManager *pcVar2;
  int iVar3;
  uint uVar4;

  iVar1 = 0;
  pcVar2 = this + 0x80c;
  do {
    iVar3 = iVar1 * 0x71c;
    iVar1 = iVar1 + 1;
    if ((param_1 != (cRBorder *)(this + iVar3 + 0x678)) && (uVar4 = *(uint *)pcVar2, uVar4 != 0)) {
      if ((uVar4 & 0x8000) != 0) {
        uVar4 = uVar4 | 0x80000000;
        *(uint *)pcVar2 = uVar4;
      }
      *(uint *)pcVar2 = uVar4 | 0x8000;
    }
    pcVar2 = pcVar2 + 0x71c;
  } while (iVar1 != 0x96);
  return;
}
