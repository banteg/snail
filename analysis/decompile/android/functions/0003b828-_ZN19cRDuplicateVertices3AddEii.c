/*
 * mangled: _ZN19cRDuplicateVertices3AddEii
 * demangled: cRDuplicateVertices::Add(int, int)
 * address: 0003b828
 * size: 172
 */

/* cRDuplicateVertices::Add(int, int) */

void __thiscall cRDuplicateVertices::Add(cRDuplicateVertices *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  short *psVar5;

  iVar3 = *(int *)this;
  iVar1 = DAT_0003b8d4 + 0x3b840;
  if (iVar3 < 1) {
    psVar4 = *(short **)(this + 4);
  }
  else {
    psVar4 = *(short **)(this + 4);
    iVar2 = 0;
    psVar5 = psVar4;
    do {
      iVar2 = iVar2 + 1;
      if ((*psVar5 == param_1) && (psVar5[1] == param_2)) {
        psVar5[4] = psVar5[4] + 1;
        return;
      }
      psVar5 = psVar5 + 5;
    } while (iVar2 < iVar3);
  }
  *(int *)this = iVar3 + 1;
  psVar4[iVar3 * 5] = (short)param_1;
  psVar4[iVar3 * 5 + 1] = (short)param_2;
  psVar4[iVar3 * 5 + 4] = 1;
  if (iVar3 + 1 != 2000) {
    return;
  }
  RShellError((char *)(iVar1 + DAT_0003b8d8),2000);
  return;
}
