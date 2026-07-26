/*
 * mangled: _Z21ObjectProcTileUVWorldP8cRObjectii
 * demangled: ObjectProcTileUVWorld(cRObject*, int, int)
 * address: 000336e0
 * size: 284
 */

/* ObjectProcTileUVWorld(cRObject*, int, int) */

void ObjectProcTileUVWorld(cRObject *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;

  if (*(int *)(param_1 + 0xa0) != 0) {
    iVar4 = *(int *)(param_1 + 0xc0);
    iVar2 = *(int *)(param_1 + 0xa4);
    if (0 < iVar4) {
      pfVar3 = (float *)(*(int *)(param_1 + 200) + 0x10);
      iVar1 = 0;
      do {
        iVar1 = iVar1 + 1;
        if (((uint)pfVar3[-4] & 0x20) != 0) {
          fVar9 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
          pfVar5 = (float *)(iVar2 + (uint)*(ushort *)((int)pfVar3 + -0xe) * 0xc);
          pfVar7 = (float *)(iVar2 + (uint)*(ushort *)(pfVar3 + -3) * 0xc);
          pfVar8 = (float *)(iVar2 + (uint)*(ushort *)((int)pfVar3 + -10) * 0xc);
          pfVar6 = (float *)(iVar2 + (uint)*(ushort *)(pfVar3 + -2) * 0xc);
          fVar10 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
          *pfVar3 = *pfVar5 / fVar9 + 0.5;
          pfVar3[1] = pfVar5[2] / fVar10 + 0.5;
          pfVar3[2] = *pfVar7 / fVar9 + 0.5;
          pfVar3[3] = pfVar7[2] / fVar10 + 0.5;
          pfVar3[4] = *pfVar8 / fVar9 + 0.5;
          pfVar3[5] = pfVar8[2] / fVar10 + 0.5;
          pfVar3[6] = *pfVar6 / fVar9 + 0.5;
          pfVar3[7] = pfVar6[2] / fVar10 + 0.5;
        }
        pfVar3 = pfVar3 + 0xc;
      } while (iVar1 != iVar4);
    }
  }
  return;
}
