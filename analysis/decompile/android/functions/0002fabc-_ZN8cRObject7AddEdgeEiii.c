/*
 * mangled: _ZN8cRObject7AddEdgeEiii
 * demangled: cRObject::AddEdge(int, int, int)
 * address: 0002fabc
 * size: 384
 */

/* cRObject::AddEdge(int, int, int) */

void __thiscall cRObject::AddEdge(cRObject *this,int param_1,int param_2,int param_3)

{
  ushort *puVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;

  fVar3 = (float)tVector::Magnitude(*(tVector **)(*(int *)(this + 0xcc) + param_3 * 4));
  iVar2 = gEdgeCount;
  puVar1 = gEdgeStore;
  if (fVar3 < 0.9) {
    return;
  }
  if (0 < gEdgeCount) {
    iVar4 = *(int *)(this + 0xa4);
    iVar5 = 0;
    pfVar8 = (float *)(iVar4 + param_2 * 0xc);
    pfVar7 = (float *)(iVar4 + param_1 * 0xc);
    puVar6 = gEdgeStore;
    do {
      iVar5 = iVar5 + 1;
      pfVar9 = (float *)(iVar4 + (uint)puVar6[1] * 0xc);
      if ((((*pfVar9 == *pfVar8) && (pfVar9[1] == pfVar8[1])) && (pfVar9[2] == pfVar8[2])) &&
         (((pfVar9 = (float *)(iVar4 + (uint)puVar6[2] * 0xc), *pfVar9 == *pfVar7 &&
           (pfVar9[1] == pfVar7[1])) && (pfVar9[2] == pfVar7[2])))) {
        if ((*puVar6 & 1) != 0) {
          puVar6[4] = (ushort)param_3;
          *puVar6 = *puVar6 & 0xfffe | 2;
        }
        return;
      }
      puVar6 = puVar6 + 5;
    } while (iVar5 < gEdgeCount);
  }
  iVar4 = gEdgeCount * 5;
  gEdgeCount = gEdgeCount + 1;
  gEdgeStore[iVar4] = 1;
  puVar1[iVar2 * 5 + 1] = (ushort)param_1;
  puVar1[iVar2 * 5 + 4] = 0;
  puVar1[iVar2 * 5 + 2] = (ushort)param_2;
  puVar1[iVar2 * 5 + 3] = (ushort)param_3;
  return;
}
