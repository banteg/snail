/*
 * mangled: _Z16ObjectProcTileUVP8cRObjectii
 * demangled: ObjectProcTileUV(cRObject*, int, int)
 * address: 000335c4
 * size: 276
 */

/* ObjectProcTileUV(cRObject*, int, int) */

void ObjectProcTileUV(cRObject *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  float fVar10;

  fVar9 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  fVar10 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = 1.0 / fVar9;
  fVar10 = 1.0 / fVar10;
  if (*(int *)(param_1 + 0xa0) != 0) {
    iVar2 = *(int *)(param_1 + 200);
    iVar1 = *(int *)(param_1 + 0xa4);
    pfVar3 = (float *)(iVar2 + 0x10);
    do {
      pfVar4 = (float *)(iVar1 + (uint)*(ushort *)((int)pfVar3 + -0xe) * 0xc);
      fVar8 = *pfVar4;
      pfVar7 = (float *)(iVar1 + (uint)*(ushort *)(pfVar3 + -3) * 0xc);
      pfVar6 = (float *)(iVar1 + (uint)*(ushort *)((int)pfVar3 + -10) * 0xc);
      *(ushort *)(pfVar3 + -4) = *(ushort *)(pfVar3 + -4) | 0x20;
      pfVar5 = (float *)(iVar1 + (uint)*(ushort *)(pfVar3 + -2) * 0xc);
      *pfVar3 = (0.5 - fVar8) * fVar9;
      pfVar3[1] = (pfVar4[2] + 0.5) * fVar10;
      pfVar3[2] = (0.5 - *pfVar7) * fVar9;
      pfVar3[3] = (pfVar7[2] + 0.5) * fVar10;
      pfVar3[4] = (0.5 - *pfVar6) * fVar9;
      pfVar3[5] = (pfVar6[2] + 0.5) * fVar10;
      pfVar3[6] = (0.5 - *pfVar5) * fVar9;
      pfVar3[7] = (pfVar5[2] + 0.5) * fVar10;
      pfVar3 = pfVar3 + 0xc;
    } while (pfVar3 != (float *)(iVar2 + 0x100));
  }
  return;
}
