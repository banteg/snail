/*
 * mangled: _Z25ObjectProcLandScapeUpdateP8cRObjectffP9cRTextureb
 * demangled: ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool)
 * address: 000156b8
 * size: 504
 */

/* ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool) */

void ObjectProcLandScapeUpdate
               (cRObject *param_1,float param_2,float param_3,cRTexture *param_4,bool param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  uint in_fpscr;
  uint uVar5;
  float fVar6;
  float in_s7;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  iVar3 = *(int *)(param_4 + 0x98);
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  iVar1 = *(int *)(param_1 + 0xa4);
  fVar6 = (float)VectorSignedToFloat((int)((fVar7 * *(float *)(param_1 + 0x1c)) /
                                          *(float *)(param_1 + 0x18)),(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = (float)VectorUnsignedToFloat((uint)*(ushort *)(iVar3 + 0xc),(byte)(in_fpscr >> 0x16) & 3);
  uVar5 = in_fpscr & 0xfffffff | (uint)(fVar6 < 0.0) << 0x1f;
  bVar4 = SUB41(uVar5 >> 0x1f,0);
  fVar9 = fVar9 / (fVar7 + 1.0);
  fVar10 = (float)VectorUnsignedToFloat((uint)*(ushort *)(iVar3 + 0xe),(byte)(uVar5 >> 0x16) & 3);
  if (bVar4 == NAN(fVar6)) {
    in_s7 = 0.0;
  }
  if (bVar4 == NAN(fVar6)) {
    do {
      uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 < 0.0) << 0x1f;
      if (SUB41(uVar5 >> 0x1f,0) == NAN(fVar7)) {
        fVar8 = 0.0;
        iVar11 = (int)((fVar10 / (fVar6 + 1.0)) * in_s7 + 0.0);
        if (param_5) {
          do {
            iVar2 = (uint)(*(byte *)(iVar3 + 0x10) >> 3) *
                    ((uint)*(ushort *)(iVar3 + 0xc) * ((*(ushort *)(iVar3 + 0xe) - 1) - iVar11) +
                    (int)(fVar8 * fVar9 + 0.0)) + iVar3;
            fVar12 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x12),(byte)(uVar5 >> 0x16) & 3);
            fVar13 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x13),(byte)(uVar5 >> 0x16) & 3);
            fVar14 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x14),(byte)(uVar5 >> 0x16) & 3);
            fVar12 = (fVar12 / 255.0 + fVar13 / 255.0 + fVar14 / 255.0) / 3.0;
            fVar8 = fVar8 + 1.0;
            *(float *)(iVar1 + 4) = param_2 + param_3 * fVar12 * fVar12 * fVar12;
            iVar1 = iVar1 + 0xc;
            uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 < fVar8) << 0x1f;
          } while (SUB41(uVar5 >> 0x1f,0) == (NAN(fVar7) || NAN(fVar8)));
        }
        else {
          do {
            iVar2 = (uint)(*(byte *)(iVar3 + 0x10) >> 3) *
                    ((uint)*(ushort *)(iVar3 + 0xc) * ((*(ushort *)(iVar3 + 0xe) - 1) - iVar11) +
                    (int)(fVar8 * fVar9 + 0.0)) + iVar3;
            fVar12 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x12),(byte)(uVar5 >> 0x16) & 3);
            fVar13 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x13),(byte)(uVar5 >> 0x16) & 3);
            fVar14 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)(iVar2 + 0x14),(byte)(uVar5 >> 0x16) & 3);
            fVar8 = fVar8 + 1.0;
            *(float *)(iVar1 + 4) =
                 param_2 + param_3 * ((fVar12 / 255.0 + fVar13 / 255.0 + fVar14 / 255.0) / 3.0);
            iVar1 = iVar1 + 0xc;
            uVar5 = uVar5 & 0xfffffff | (uint)(fVar7 < fVar8) << 0x1f;
          } while (SUB41(uVar5 >> 0x1f,0) == (NAN(fVar7) || NAN(fVar8)));
        }
      }
      in_s7 = in_s7 + 1.0;
      uVar5 = uVar5 & 0xfffffff | (uint)(fVar6 < in_s7) << 0x1f;
    } while (SUB41(uVar5 >> 0x1f,0) == (NAN(fVar6) || NAN(in_s7)));
    return;
  }
  return;
}
