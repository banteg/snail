/*
 * mangled: _ZN15cRBorderManager22DeActivateOtherBordersEP8cRBorderS1_S1_
 * demangled: cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*, cRBorder*)
 * address: 0005c14c
 * size: 120
 */

/* cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*, cRBorder*) */

void __thiscall
cRBorderManager::DeActivateOtherBorders
          (cRBorderManager *this,cRBorder *param_1,cRBorder *param_2,cRBorder *param_3)

{
  int iVar1;
  int iVar2;
  cRBorderManager *pcVar3;
  uint uVar4;
  cRBorderManager *pcVar5;

  pcVar5 = this + 0x80c;
  iVar1 = 0;
  do {
    iVar2 = iVar1 * 0x71c;
    iVar1 = iVar1 + 1;
    pcVar3 = this + iVar2 + 0x678;
    if ((((pcVar3 != (cRBorderManager *)param_1) && (pcVar3 != (cRBorderManager *)param_2)) &&
        (pcVar3 != (cRBorderManager *)param_3)) && (uVar4 = *(uint *)pcVar5, uVar4 != 0)) {
      if ((uVar4 & 0x8000) != 0) {
        uVar4 = uVar4 | 0x80000000;
        *(uint *)pcVar5 = uVar4;
      }
      *(uint *)pcVar5 = uVar4 | 0x8000;
    }
    pcVar5 = pcVar5 + 0x71c;
  } while (iVar1 != 0x96);
  return;
}
