/*
 * mangled: _ZN15cRBorderManager22DeActivateOtherBordersEP8cRBorderS1_S1_S1_
 * demangled: cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*, cRBorder*, cRBorder*)
 * address: 0005c0c8
 * size: 132
 */

/* cRBorderManager::DeActivateOtherBorders(cRBorder*, cRBorder*, cRBorder*, cRBorder*) */

void __thiscall
cRBorderManager::DeActivateOtherBorders
          (cRBorderManager *this,cRBorder *param_1,cRBorder *param_2,cRBorder *param_3,
          cRBorder *param_4)

{
  int iVar1;
  cRBorderManager *pcVar2;
  uint uVar3;
  int iVar4;
  cRBorderManager *pcVar5;

  pcVar5 = this + 0x80c;
  iVar4 = 0;
  do {
    iVar1 = iVar4 * 0x71c;
    iVar4 = iVar4 + 1;
    pcVar2 = this + iVar1 + 0x678;
    if ((((pcVar2 != (cRBorderManager *)param_1) && (pcVar2 != (cRBorderManager *)param_2)) &&
        (pcVar2 != (cRBorderManager *)param_3)) &&
       ((pcVar2 != (cRBorderManager *)param_4 && (uVar3 = *(uint *)pcVar5, uVar3 != 0)))) {
      if ((uVar3 & 0x8000) != 0) {
        uVar3 = uVar3 | 0x80000000;
        *(uint *)pcVar5 = uVar3;
      }
      *(uint *)pcVar5 = uVar3 | 0x8000;
    }
    pcVar5 = pcVar5 + 0x71c;
  } while (iVar4 != 0x96);
  return;
}
