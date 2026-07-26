/*
 * mangled: _Z20ObjectProcTileUVFastP8cRObjectii
 * demangled: ObjectProcTileUVFast(cRObject*, int, int)
 * address: 00033800
 * size: 248
 */

/* ObjectProcTileUVFast(cRObject*, int, int) */

void ObjectProcTileUVFast(cRObject *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;

  if (*(int *)(param_1 + 0xa0) != 0) {
    fVar8 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar2 = *(int *)(param_1 + 200);
    iVar1 = *(int *)(param_1 + 0xa4);
    fVar8 = 1.0 / fVar8;
    pfVar3 = (float *)(iVar1 + (uint)*(ushort *)(iVar2 + 2) * 0xc);
    pfVar6 = (float *)(iVar1 + (uint)*(ushort *)(iVar2 + 4) * 0xc);
    pfVar5 = (float *)(iVar1 + (uint)*(ushort *)(iVar2 + 6) * 0xc);
    pfVar4 = (float *)(iVar1 + (uint)*(ushort *)(iVar2 + 8) * 0xc);
    fVar7 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = 1.0 / fVar7;
    *(float *)(iVar2 + 0x10) = (0.5 - *pfVar3) * fVar8;
    *(float *)(iVar2 + 0x14) = (pfVar3[2] + 0.5) * fVar7;
    *(float *)(iVar2 + 0x18) = (0.5 - *pfVar6) * fVar8;
    *(float *)(iVar2 + 0x1c) = (pfVar6[2] + 0.5) * fVar7;
    *(float *)(iVar2 + 0x20) = (0.5 - *pfVar5) * fVar8;
    *(float *)(iVar2 + 0x24) = (pfVar5[2] + 0.5) * fVar7;
    *(float *)(iVar2 + 0x28) = (0.5 - *pfVar4) * fVar8;
    *(float *)(iVar2 + 0x2c) = (pfVar4[2] + 0.5) * fVar7;
  }
  return;
}
