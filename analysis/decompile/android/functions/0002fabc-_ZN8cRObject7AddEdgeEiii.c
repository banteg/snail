/*
 * mangled: _ZN8cRObject7AddEdgeEiii
 * demangled: cRObject::AddEdge(int, int, int)
 * address: 0002fabc
 * size: 384
 */

/* cRObject::AddEdge(int, int, int) */

void __thiscall cRObject::AddEdge(cRObject *this,int param_1,int param_2,int param_3)

{
  float fVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;

  iVar5 = DAT_0002fc40;
  fVar1 = (float)tVector::Magnitude(*(tVector **)(*(int *)(this + 0xcc) + param_3 * 4));
  iVar5 = iVar5 + 0x2faec;
  if (fVar1 < DAT_0002fc3c) {
    return;
  }
  iVar8 = **(int **)(iVar5 + DAT_0002fc44);
  if (iVar8 < 1) {
    puVar6 = (ushort *)**(undefined4 **)(iVar5 + DAT_0002fc48);
  }
  else {
    iVar2 = *(int *)(this + 0xa4);
    iVar3 = 0;
    pfVar9 = (float *)(iVar2 + param_2 * 0xc);
    pfVar7 = (float *)(iVar2 + param_1 * 0xc);
    puVar6 = (ushort *)**(undefined4 **)(iVar5 + DAT_0002fc48);
    puVar4 = puVar6;
    do {
      iVar3 = iVar3 + 1;
      pfVar10 = (float *)(iVar2 + (uint)puVar4[1] * 0xc);
      if ((((*pfVar10 == *pfVar9) && (pfVar10[1] == pfVar9[1])) && (pfVar10[2] == pfVar9[2])) &&
         (((pfVar10 = (float *)(iVar2 + (uint)puVar4[2] * 0xc), *pfVar10 == *pfVar7 &&
           (pfVar10[1] == pfVar7[1])) && (pfVar10[2] == pfVar7[2])))) {
        if ((*puVar4 & 1) != 0) {
          puVar4[4] = (ushort)param_3;
          *puVar4 = *puVar4 & 0xfffe | 2;
        }
        return;
      }
      puVar4 = puVar4 + 5;
    } while (iVar3 < iVar8);
  }
  **(int **)(iVar5 + DAT_0002fc44) = iVar8 + 1;
  puVar6[iVar8 * 5] = 1;
  puVar6[iVar8 * 5 + 1] = (ushort)param_1;
  puVar6[iVar8 * 5 + 4] = 0;
  puVar6[iVar8 * 5 + 2] = (ushort)param_2;
  puVar6[iVar8 * 5 + 3] = (ushort)param_3;
  return;
}
