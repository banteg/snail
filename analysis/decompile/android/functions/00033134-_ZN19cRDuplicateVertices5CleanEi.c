/*
 * mangled: _ZN19cRDuplicateVertices5CleanEi
 * demangled: cRDuplicateVertices::Clean(int)
 * address: 00033134
 * size: 108
 */

/* cRDuplicateVertices::Clean(int) */

void cRDuplicateVertices::Clean(int param_1)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar7 = *(int *)param_1;
  if (0 < iVar7) {
    iVar5 = 0;
    iVar6 = *(int *)(param_1 + 4);
    iVar4 = 0;
    do {
      sVar1 = *(short *)(iVar6 + iVar5 + 2);
      psVar3 = (short *)(iVar6 + iVar4 * 10);
      iVar2 = iVar4;
      do {
        iVar2 = iVar2 + 1;
        if (*psVar3 == sVar1) {
          psVar3[4] = 0;
        }
        psVar3 = psVar3 + 5;
      } while (iVar2 < iVar7);
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 10;
    } while (iVar4 != iVar7);
  }
  return;
}
