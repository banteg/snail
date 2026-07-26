/*
 * mangled: _ZN8cRBorder13AddTextNumberEi
 * demangled: cRBorder::AddTextNumber(int)
 * address: 0005bcf0
 * size: 252
 */

/* cRBorder::AddTextNumber(int) */

void cRBorder::AddTextNumber(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int in_r1;
  int extraout_r1;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;

  pcVar4 = (char *)(param_1 + 0x2c4);
  cVar1 = *(char *)(param_1 + 0x2c4);
  while (cVar1 != '\0') {
    pcVar4 = pcVar4 + 1;
    cVar1 = *pcVar4;
  }
  if (in_r1 == 0) {
    pcVar4[1] = '\0';
    *pcVar4 = '0';
    return;
  }
  iVar7 = 0;
  bVar2 = false;
  iVar6 = 10000000;
  do {
    pcVar5 = pcVar4;
    if ((iVar6 <= in_r1) || (bVar2)) {
      if (iVar6 == 1) {
        pcVar5 = pcVar4 + 1;
        *pcVar4 = (char)in_r1 + '0';
LAB_0005bde0:
        *pcVar5 = '\0';
        return;
      }
      iVar3 = __divsi3(in_r1,iVar6);
      if (iVar3 == 0) {
        if (bVar2) {
          pcVar5 = pcVar4 + 1;
          *pcVar4 = '0';
        }
      }
      else {
        bVar2 = true;
        *pcVar4 = (char)iVar3 + '0';
        pcVar5 = pcVar4 + 1;
      }
    }
    iVar3 = iVar6 / 10;
    if (iVar7 == 7) goto LAB_0005bde0;
    pcVar4 = pcVar5;
    if ((bVar2) && (iVar3 == 100 || iVar3 == 100000)) {
      pcVar4 = pcVar5 + 1;
      *pcVar5 = ',';
    }
    __aeabi_idivmod(in_r1,iVar6);
    iVar7 = iVar7 + 1;
    iVar6 = iVar3;
    in_r1 = extraout_r1;
  } while( true );
}
