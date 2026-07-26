/*
 * mangled: _ZN8cRBorder13AddTextNumberEi
 * demangled: cRBorder::AddTextNumber(int)
 * address: 000380f0
 * size: 920
 */

/* cRBorder::AddTextNumber(int) */

void __thiscall cRBorder::AddTextNumber(cRBorder *this,int param_1)

{
  cRBorder cVar1;
  bool bVar2;
  int iVar3;
  cRBorder *pcVar4;
  cRBorder *pcVar5;

  pcVar4 = this + 0x2c4;
  cVar1 = this[0x2c4];
  while (cVar1 != (cRBorder)0x0) {
    pcVar4 = pcVar4 + 1;
    cVar1 = *pcVar4;
  }
  if (param_1 == 0) {
    *pcVar4 = (cRBorder)0x30;
    pcVar4[1] = (cRBorder)0x0;
    return;
  }
  if ((param_1 < 10000000) || (param_1 / 10000000 == 0)) {
    bVar2 = false;
    pcVar5 = pcVar4;
  }
  else {
    pcVar5 = pcVar4 + 1;
    *pcVar4 = (cRBorder)((char)(param_1 / 10000000) + '0');
    bVar2 = true;
  }
  iVar3 = param_1 % 10000000;
  if ((999999 < iVar3) || (bVar2)) {
    if (iVar3 / 1000000 == 0) {
      if (!bVar2) goto LAB_000381ac;
      *pcVar5 = (cRBorder)0x30;
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 1000000) + '0');
    }
    pcVar4 = pcVar5 + 1;
    bVar2 = true;
    iVar3 = iVar3 % 1000000;
    pcVar5 = pcVar5 + 2;
    *pcVar4 = (cRBorder)0x2c;
  }
  else {
    iVar3 = iVar3 % 1000000;
  }
LAB_000381ac:
  if ((99999 < iVar3) || (bVar2)) {
    if (iVar3 / 100000 == 0) {
      if (!bVar2) goto LAB_000381dc;
      *pcVar5 = (cRBorder)0x30;
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 100000) + '0');
    }
    pcVar5 = pcVar5 + 1;
    bVar2 = true;
  }
LAB_000381dc:
  iVar3 = iVar3 % 100000;
  if ((9999 < iVar3) || (bVar2)) {
    if (iVar3 / 10000 == 0) {
      if (!bVar2) goto LAB_0003820c;
      *pcVar5 = (cRBorder)0x30;
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 10000) + '0');
    }
    pcVar5 = pcVar5 + 1;
    bVar2 = true;
  }
LAB_0003820c:
  iVar3 = iVar3 % 10000;
  if ((999 < iVar3) || (bVar2)) {
    if (iVar3 / 1000 == 0) {
      if (!bVar2) goto LAB_0003823c;
      *pcVar5 = (cRBorder)0x30;
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 1000) + '0');
    }
    pcVar4 = pcVar5 + 1;
    bVar2 = true;
    pcVar5 = pcVar5 + 2;
    *pcVar4 = (cRBorder)0x2c;
  }
LAB_0003823c:
  iVar3 = iVar3 % 1000;
  if ((99 < iVar3) || (bVar2)) {
    if (iVar3 / 100 == 0) {
      if (bVar2) {
        *pcVar5 = (cRBorder)0x30;
        pcVar5 = pcVar5 + 1;
      }
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 100) + '0');
      bVar2 = true;
      pcVar5 = pcVar5 + 1;
    }
  }
  iVar3 = iVar3 % 100;
  if ((9 < iVar3) || (bVar2)) {
    if (iVar3 / 10 == 0) {
      if (bVar2) {
        *pcVar5 = (cRBorder)0x30;
        pcVar5 = pcVar5 + 1;
      }
    }
    else {
      *pcVar5 = (cRBorder)((char)(iVar3 / 10) + '0');
      bVar2 = true;
      pcVar5 = pcVar5 + 1;
    }
  }
  if ((0 < iVar3 % 10) || (pcVar4 = pcVar5, bVar2)) {
    pcVar4 = pcVar5 + 1;
    *pcVar5 = (cRBorder)((char)(iVar3 % 10) + '0');
  }
  *pcVar4 = (cRBorder)0x0;
  return;
}
