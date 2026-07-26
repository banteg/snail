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
  short *psVar3;
  short *psVar4;

  iVar2 = *(int *)this;
  if (iVar2 < 1) {
    psVar3 = *(short **)(this + 4);
  }
  else {
    psVar3 = *(short **)(this + 4);
    iVar1 = 0;
    psVar4 = psVar3;
    do {
      iVar1 = iVar1 + 1;
      if ((*psVar4 == param_1) && (psVar4[1] == param_2)) {
        psVar4[4] = psVar4[4] + 1;
        return;
      }
      psVar4 = psVar4 + 5;
    } while (iVar1 < iVar2);
  }
  *(int *)this = iVar2 + 1;
  psVar3[iVar2 * 5] = (short)param_1;
  psVar3[iVar2 * 5 + 1] = (short)param_2;
  psVar3[iVar2 * 5 + 4] = 1;
  if (iVar2 + 1 != 2000) {
    return;
  }
  RShellError("Too many duplicate Vertices increase RDUPLICATE_PAIR_MAX(%i)",2000);
  return;
}
