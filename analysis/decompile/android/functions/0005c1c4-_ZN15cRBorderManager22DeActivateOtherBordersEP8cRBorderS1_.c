/*
 * mangled: _ZN15cRBorderManager22DeActivateOtherBordersEP8cRBorderS1_
 * demangled: cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*)
 * address: 0005c1c4
 * size: 112
 */

/* cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*) */

void __thiscall
cRBorderManager::DeActivateOtherBorders(cRBorderManager *this,cRBorder *param_1,cRBorder *param_2)

{
  cRBorderManager *pcVar1;
  int iVar2;
  uint uVar3;
  int iVar4;

  iVar4 = 0;
  pcVar1 = this + 0x80c;
  do {
    iVar2 = iVar4 * 0x71c;
    iVar4 = iVar4 + 1;
    if (((this + iVar2 + 0x678 != (cRBorderManager *)param_1) &&
        (this + iVar2 + 0x678 != (cRBorderManager *)param_2)) &&
       (uVar3 = *(uint *)pcVar1, uVar3 != 0)) {
      if ((uVar3 & 0x8000) != 0) {
        uVar3 = uVar3 | 0x80000000;
        *(uint *)pcVar1 = uVar3;
      }
      *(uint *)pcVar1 = uVar3 | 0x8000;
    }
    pcVar1 = pcVar1 + 0x71c;
  } while (iVar4 != 0x96);
  return;
}
