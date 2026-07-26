/*
 * mangled: _Z25ObjectProcLandScapeUpdateP8cRObjectffP9cRTextureb
 * demangled: ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool)
 * address: 00033a6c
 * size: 488
 */

/* ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool) */

void ObjectProcLandScapeUpdate
               (cRObject *param_1,float param_2,float param_3,cRTexture *param_4,bool param_5)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  ushort uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int in_r3;
  int iVar9;
  uint in_fpscr;
  uint uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  char in_stack_00000000;

  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x10),(byte)(in_fpscr >> 0x16) & 3);
  iVar9 = *(int *)(in_r3 + 0x98);
  iVar8 = *(int *)(param_1 + 0xa4);
  uVar3 = *(ushort *)(iVar9 + 0xc);
  uVar4 = *(ushort *)(iVar9 + 0xe);
  fVar11 = (float)VectorSignedToFloat((int)((fVar15 * *(float *)(param_1 + 0x1c)) /
                                           *(float *)(param_1 + 0x18)),(byte)(in_fpscr >> 0x16) & 3)
  ;
  fVar16 = (float)VectorUnsignedToFloat((uint)uVar3,(byte)(in_fpscr >> 0x16) & 3);
  fVar18 = (float)VectorUnsignedToFloat((uint)uVar4,(byte)(in_fpscr >> 0x16) & 3);
  fVar16 = fVar16 / (fVar15 + 1.0);
  if (NAN(fVar11)) {
    return;
  }
  uVar10 = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
  fVar12 = 0.0;
  if (SUB41(uVar10 >> 0x1f,0) == NAN(fVar15)) {
    bVar5 = true;
  }
  else {
    bVar5 = false;
  }
  do {
    while (!bVar5) {
LAB_00033ba8:
      fVar12 = fVar12 + 1.0;
      uVar10 = uVar10 & 0xfffffff | (uint)(fVar11 < fVar12) << 0x1f;
      if (SUB41(uVar10 >> 0x1f,0) != (NAN(fVar11) || NAN(fVar12))) {
        return;
      }
    }
    uVar1 = (uint)(*(byte *)(iVar9 + 0x10) >> 3);
    iVar6 = (uint)uVar3 * ((uVar4 - 1) - (int)((fVar18 / (fVar11 + 1.0)) * fVar12 + 0.0));
    if (in_stack_00000000 == '\0') {
      fVar19 = 0.0;
      do {
        fVar13 = fVar19 * fVar16;
        fVar19 = fVar19 + 1.0;
        iVar7 = uVar1 * ((int)(fVar13 + 0.0) + iVar6) + iVar9;
        fVar13 = (float)VectorUnsignedToFloat
                                  ((uint)*(byte *)(iVar7 + 0x12),(byte)(uVar10 >> 0x16) & 3);
        fVar17 = (float)VectorUnsignedToFloat
                                  ((uint)*(byte *)(iVar7 + 0x13),(byte)(uVar10 >> 0x16) & 3);
        fVar14 = (float)VectorUnsignedToFloat
                                  ((uint)*(byte *)(iVar7 + 0x14),(byte)(uVar10 >> 0x16) & 3);
        uVar10 = uVar10 & 0xfffffff | (uint)(fVar15 < fVar19) << 0x1f;
        *(float *)(iVar8 + 4) =
             (float)param_4 +
             (float)(uint)param_5 * ((fVar13 / 255.0 + fVar17 / 255.0 + fVar14 / 255.0) / 3.0);
        iVar8 = iVar8 + 0xc;
      } while (SUB41(uVar10 >> 0x1f,0) == (NAN(fVar15) || NAN(fVar19)));
      goto LAB_00033ba8;
    }
    fVar19 = 0.0;
    do {
      fVar13 = fVar19 * fVar16;
      fVar19 = fVar19 + 1.0;
      iVar7 = uVar1 * ((int)(fVar13 + 0.0) + iVar6) + iVar9;
      fVar13 = (float)VectorUnsignedToFloat
                                ((uint)*(byte *)(iVar7 + 0x12),(byte)(uVar10 >> 0x16) & 3);
      fVar17 = (float)VectorUnsignedToFloat
                                ((uint)*(byte *)(iVar7 + 0x13),(byte)(uVar10 >> 0x16) & 3);
      fVar14 = (float)VectorUnsignedToFloat
                                ((uint)*(byte *)(iVar7 + 0x14),(byte)(uVar10 >> 0x16) & 3);
      fVar13 = (fVar13 / 255.0 + fVar17 / 255.0 + fVar14 / 255.0) / 3.0;
      uVar2 = uVar10 & 0xfffffff;
      uVar10 = uVar2 | (uint)(fVar15 < fVar19) << 0x1f;
      *(float *)(iVar8 + 4) = (float)param_4 + fVar13 * fVar13 * fVar13 * (float)(uint)param_5;
      iVar8 = iVar8 + 0xc;
    } while (SUB41(uVar10 >> 0x1f,0) == (NAN(fVar15) || NAN(fVar19)));
    fVar12 = fVar12 + 1.0;
    uVar10 = uVar2 | (uint)(fVar11 < fVar12) << 0x1f;
    if (SUB41(uVar10 >> 0x1f,0) != (NAN(fVar11) || NAN(fVar12))) {
      return;
    }
  } while( true );
}
