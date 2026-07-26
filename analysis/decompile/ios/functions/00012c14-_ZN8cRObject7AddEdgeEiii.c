/*
 * mangled: _ZN8cRObject7AddEdgeEiii
 * demangled: cRObject::AddEdge(int, int, int)
 * address: 00012c14
 * size: 552
 */

/* cRObject::AddEdge(int, int, int) */

void __thiscall cRObject::AddEdge(cRObject *this,int param_1,int param_2,int param_3)

{
  float fVar1;
  int iVar2;
  ushort *puVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;

  fVar1 = (float)tVector::Magnitude(*(tVector **)(*(int *)(this + 0xcc) + param_3 * 4));
  if (0.9 <= fVar1) {
    if (0 < _gEdgeCount) {
      iVar2 = *(int *)(this + 0xa4);
      pfVar5 = (float *)(param_2 * 0xc + iVar2);
      pfVar6 = (float *)(param_1 * 0xc + iVar2);
      iVar7 = 0;
      puVar3 = _gEdgeStore;
      do {
        iVar8 = (int)puVar3 - (int)_gEdgeStore;
        pfVar4 = (float *)((uint)puVar3[1] * 0xc + iVar2);
        if ((((*pfVar4 == *pfVar5) && (pfVar4[1] == pfVar5[1])) && (pfVar4[2] == pfVar5[2])) &&
           (((pfVar4 = (float *)((uint)puVar3[2] * 0xc + iVar2), *pfVar4 == *pfVar6 &&
             (pfVar4[1] == pfVar6[1])) && (pfVar4[2] == pfVar6[2])))) {
          if ((*puVar3 & 1) == 0) {
            return;
          }
          *puVar3 = *puVar3 & 0xfffe;
          *(ushort *)(iVar8 + (int)_gEdgeStore) = *(ushort *)(iVar8 + (int)_gEdgeStore) | 2;
          *(ushort *)((int)_gEdgeStore + iVar8 + 8) = (ushort)param_3;
          return;
        }
        iVar7 = iVar7 + 1;
        puVar3 = puVar3 + 5;
      } while (iVar7 != _gEdgeCount);
    }
    _gEdgeStore[_gEdgeCount * 5] = 1;
    _gEdgeStore[_gEdgeCount * 5 + 1] = (ushort)param_1;
    _gEdgeStore[_gEdgeCount * 5 + 2] = (ushort)param_2;
    _gEdgeStore[_gEdgeCount * 5 + 3] = (ushort)param_3;
    _gEdgeStore[_gEdgeCount * 5 + 4] = 0;
    _gEdgeCount = _gEdgeCount + 1;
  }
  return;
}
