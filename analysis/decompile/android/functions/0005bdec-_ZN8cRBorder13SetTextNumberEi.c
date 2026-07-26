/*
 * mangled: _ZN8cRBorder13SetTextNumberEi
 * demangled: cRBorder::SetTextNumber(int)
 * address: 0005bdec
 * size: 168
 */

/* cRBorder::SetTextNumber(int) */

void __thiscall cRBorder::SetTextNumber(cRBorder *this,int param_1)

{
  cRBorder cVar1;
  bool bVar2;
  cRBorder *pcVar3;
  int iVar4;

  pcVar3 = this + 0x2c4;
  cVar1 = this[0x2c4];
  while (9 < (byte)((char)cVar1 - 0x30U)) {
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
  } while ((byte)((char)pcVar3[iVar4] - 0x30U) < 10);
  pcVar3 = pcVar3 + iVar4;
  bVar2 = false;
  do {
    if (bVar2) {
      pcVar3[-1] = (cRBorder)0x20;
    }
    else {
      pcVar3[-1] = (cRBorder)((char)param_1 + (char)(param_1 / 10) * -10 + '0');
    }
    iVar4 = iVar4 + -1;
    pcVar3 = pcVar3 + -1;
    param_1 = param_1 / 10;
    if (param_1 == 0) {
      bVar2 = true;
    }
  } while (iVar4 != 0);
  return;
}
