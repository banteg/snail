/*
 * mangled: _Z20ObjectProcLandScape1P8cRObjectffffifPcS1_b
 * demangled: ObjectProcLandScape1(cRObject*, float, float, float, float, int, float, char*, char*, bool)
 * address: 0003b180
 * size: 1680
 */

/* ObjectProcLandScape1(cRObject*, float, float, float, float, int, float, char*, char*, bool) */

void ObjectProcLandScape1
               (cRObject *param_1,float param_2,float param_3,float param_4,float param_5,
               int param_6,float param_7,char *param_8,char *param_9,bool param_10)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  ushort uVar4;
  ushort uVar5;
  undefined2 *puVar6;
  short sVar7;
  short sVar8;
  void *pvVar9;
  undefined4 uVar10;
  float *pfVar11;
  undefined2 *puVar12;
  uint uVar13;
  uint in_fpscr;
  uint uVar14;
  float fVar15;
  int iVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  int iVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  int iVar27;
  undefined3 in_stack_00000001;
  int in_stack_00000004;
  float in_stack_00000008;
  char *in_stack_0000000c;
  char *in_stack_00000010;
  char in_stack_00000014;

  fVar26 = (float)VectorSignedToFloat(in_stack_00000004,(byte)(in_fpscr >> 0x16) & 3);
  pvVar9 = (void *)RShellLoadFile(in_stack_00000010,(int *)0x0);
  iVar27 = (int)((fVar26 * _param_10) / (float)param_9);
  fVar25 = (float)VectorSignedToFloat(iVar27,(byte)(in_fpscr >> 0x16) & 3);
  uVar14 = in_fpscr & 0xfffffff | (uint)(fVar25 == 0.0) << 0x1e;
  if (SUB41(uVar14 >> 0x1e,0)) {
    bVar1 = true;
    fVar25 = 1.0;
  }
  else {
    uVar13 = in_fpscr & 0xfffffff | (uint)(fVar25 < 0.0) << 0x1f;
    uVar14 = uVar13 | (uint)NAN(fVar25) << 0x1c;
    bVar1 = (byte)(uVar13 >> 0x1f) == ((byte)(uVar14 >> 0x1c) & 1);
  }
  uVar4 = *(ushort *)((int)pvVar9 + 0xc);
  uVar5 = *(ushort *)((int)pvVar9 + 0xe);
  *(char **)(param_1 + 0x18) = param_9;
  *(float *)(param_1 + 0x1c) = _param_10;
  *(int *)(param_1 + 0x10) = in_stack_00000004;
  fVar21 = (float)VectorUnsignedToFloat((uint)uVar4,(byte)(uVar14 >> 0x16) & 3);
  fVar19 = (float)VectorUnsignedToFloat((uint)uVar5,(byte)(uVar14 >> 0x16) & 3);
  fVar21 = fVar21 / (fVar26 + 1.0);
  fVar24 = (float)param_9 * -0.5;
  RShellMemoryFree(pvVar9);
  cRObject::RequestVertices(param_1,iVar27 * (in_stack_00000004 + 1) + in_stack_00000004 + 1);
  cRObject::RequestFaceQuads(param_1,in_stack_00000004 * iVar27);
  cRObject::RequestColours(param_1);
  *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  pvVar9 = (void *)RShellLoadFile(in_stack_00000010,(int *)0x0);
  puVar12 = *(undefined2 **)(param_1 + 200);
  fVar18 = (float)param_9 / fVar26;
  pfVar11 = *(float **)(param_1 + 0xa4);
  if (bVar1) {
    uVar14 = uVar14 & 0xfffffff | (uint)(fVar26 < 0.0) << 0x1f;
    fVar17 = 0.0;
    if (SUB41(uVar14 >> 0x1f,0) == NAN(fVar26)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
LAB_0003b2cc:
    do {
      if (bVar1) {
        uVar13 = (uint)*(ushort *)((int)pvVar9 + 0xc);
        iVar27 = uVar13 - 1;
        iVar22 = (int)((fVar19 / (fVar25 + 1.0)) * fVar17 + 0.0);
        fVar20 = _param_10 * -0.5 + (_param_10 / fVar25) * fVar17;
        if (in_stack_00000014 == '\0') {
          if (iVar22 < 0) {
            fVar23 = 0.0;
            do {
              iVar22 = (int)(fVar23 * fVar21 + 0.0);
              if (iVar22 < 0) {
                iVar22 = 0;
              }
              else if ((int)uVar13 <= iVar22) {
                iVar22 = iVar27;
              }
              *pfVar11 = fVar24 + fVar18 * fVar23;
              fVar23 = fVar23 + 1.0;
              bVar3 = *(byte *)((int)pvVar9 +
                               (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) * (iVar27 - iVar22) + 0x12
                               );
              pfVar11[2] = fVar20;
              fVar15 = (float)VectorUnsignedToFloat((uint)bVar3,(byte)(uVar14 >> 0x16) & 3);
              uVar2 = uVar14 & 0xfffffff;
              uVar14 = uVar2 | (uint)(fVar26 < fVar23) << 0x1f;
              pfVar11[1] = (float)param_6 + (float)param_8 * (fVar15 / 255.0);
              pfVar11 = pfVar11 + 3;
            } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
            fVar17 = fVar17 + 1.0;
            uVar14 = uVar2 | (uint)(fVar25 < fVar17) << 0x1f;
            if (SUB41(uVar14 >> 0x1f,0) != (NAN(fVar25) || NAN(fVar17))) break;
          }
          else {
            uVar4 = *(ushort *)((int)pvVar9 + 0xe);
            fVar23 = 0.0;
            if (iVar22 < (int)(uint)uVar4) {
              do {
                iVar16 = (int)(fVar23 * fVar21 + 0.0);
                if (iVar16 < 0) {
                  iVar16 = 0;
                }
                else if ((int)uVar13 <= iVar16) {
                  iVar16 = iVar27;
                }
                *pfVar11 = fVar24 + fVar18 * fVar23;
                fVar23 = fVar23 + 1.0;
                bVar3 = *(byte *)((int)pvVar9 +
                                 (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) *
                                 (uVar13 * iVar22 + (iVar27 - iVar16)) + 0x12);
                pfVar11[2] = fVar20;
                fVar15 = (float)VectorUnsignedToFloat((uint)bVar3,(byte)(uVar14 >> 0x16) & 3);
                uVar2 = uVar14 & 0xfffffff;
                uVar14 = uVar2 | (uint)(fVar26 < fVar23) << 0x1f;
                pfVar11[1] = (float)param_6 + (float)param_8 * (fVar15 / 255.0);
                pfVar11 = pfVar11 + 3;
              } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
              fVar17 = fVar17 + 1.0;
              uVar14 = uVar2 | (uint)(fVar25 < fVar17) << 0x1f;
              if (SUB41(uVar14 >> 0x1f,0) != (NAN(fVar25) || NAN(fVar17))) break;
            }
            else {
              do {
                iVar22 = (int)(fVar23 * fVar21 + 0.0);
                if (iVar22 < 0) {
                  iVar22 = 0;
                }
                else if ((int)uVar13 <= iVar22) {
                  iVar22 = iVar27;
                }
                *pfVar11 = fVar24 + fVar18 * fVar23;
                fVar23 = fVar23 + 1.0;
                bVar3 = *(byte *)((int)pvVar9 +
                                 (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) *
                                 (uVar13 * (uVar4 - 1) + (iVar27 - iVar22)) + 0x12);
                pfVar11[2] = fVar20;
                fVar15 = (float)VectorUnsignedToFloat((uint)bVar3,(byte)(uVar14 >> 0x16) & 3);
                uVar2 = uVar14 & 0xfffffff;
                uVar14 = uVar2 | (uint)(fVar26 < fVar23) << 0x1f;
                pfVar11[1] = (float)param_6 + (float)param_8 * (fVar15 / 255.0);
                pfVar11 = pfVar11 + 3;
              } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
              fVar17 = fVar17 + 1.0;
              uVar14 = uVar2 | (uint)(fVar25 < fVar17) << 0x1f;
              if (SUB41(uVar14 >> 0x1f,0) != (NAN(fVar25) || NAN(fVar17))) break;
            }
          }
          goto LAB_0003b2cc;
        }
        if (iVar22 < 0) {
          fVar23 = 0.0;
          do {
            iVar22 = (int)(fVar23 * fVar21 + 0.0);
            if (iVar22 < 0) {
              iVar22 = 0;
            }
            else if ((int)uVar13 <= iVar22) {
              iVar22 = iVar27;
            }
            *pfVar11 = fVar24 + fVar18 * fVar23;
            fVar23 = fVar23 + 1.0;
            fVar15 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 +
                                                      (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) *
                                                      (iVar27 - iVar22) + 0x12),
                                       (byte)(uVar14 >> 0x16) & 3);
            pfVar11[2] = fVar20;
            fVar15 = fVar15 / 255.0;
            uVar2 = uVar14 & 0xfffffff;
            uVar14 = uVar2 | (uint)(fVar26 < fVar23) << 0x1f;
            pfVar11[1] = (float)param_6 + (float)param_8 * fVar15 * fVar15 * fVar15;
            pfVar11 = pfVar11 + 3;
          } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
          fVar17 = fVar17 + 1.0;
          uVar14 = uVar2 | (uint)(fVar25 < fVar17) << 0x1f;
          if (SUB41(uVar14 >> 0x1f,0) != (NAN(fVar25) || NAN(fVar17))) break;
          goto LAB_0003b2cc;
        }
        uVar4 = *(ushort *)((int)pvVar9 + 0xe);
        fVar23 = 0.0;
        if (iVar22 < (int)(uint)uVar4) {
          do {
            iVar16 = (int)(fVar23 * fVar21 + 0.0);
            if (iVar16 < 0) {
              iVar16 = 0;
            }
            else if ((int)uVar13 <= iVar16) {
              iVar16 = iVar27;
            }
            *pfVar11 = fVar24 + fVar18 * fVar23;
            fVar23 = fVar23 + 1.0;
            fVar15 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 +
                                                      (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) *
                                                      (uVar13 * iVar22 + (iVar27 - iVar16)) + 0x12),
                                       (byte)(uVar14 >> 0x16) & 3);
            pfVar11[2] = fVar20;
            fVar15 = fVar15 / 255.0;
            uVar2 = uVar14 & 0xfffffff;
            uVar14 = uVar2 | (uint)(fVar26 < fVar23) << 0x1f;
            pfVar11[1] = (float)param_6 + fVar15 * fVar15 * fVar15 * (float)param_8;
            pfVar11 = pfVar11 + 3;
          } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
          fVar17 = fVar17 + 1.0;
          uVar14 = uVar2 | (uint)(fVar25 < fVar17) << 0x1f;
          if (SUB41(uVar14 >> 0x1f,0) != (NAN(fVar25) || NAN(fVar17))) break;
          goto LAB_0003b2cc;
        }
        do {
          iVar22 = (int)(fVar23 * fVar21 + 0.0);
          if (iVar22 < 0) {
            iVar22 = 0;
          }
          else if ((int)uVar13 <= iVar22) {
            iVar22 = iVar27;
          }
          *pfVar11 = fVar24 + fVar18 * fVar23;
          fVar23 = fVar23 + 1.0;
          fVar15 = (float)VectorUnsignedToFloat
                                    ((uint)*(byte *)((int)pvVar9 +
                                                    (uint)(*(byte *)((int)pvVar9 + 0x10) >> 3) *
                                                    (uVar13 * (uVar4 - 1) + (iVar27 - iVar22)) +
                                                    0x12),(byte)(uVar14 >> 0x16) & 3);
          pfVar11[2] = fVar20;
          fVar15 = fVar15 / 255.0;
          uVar14 = uVar14 & 0xfffffff | (uint)(fVar26 < fVar23) << 0x1f;
          pfVar11[1] = (float)param_6 + fVar15 * fVar15 * fVar15 * (float)param_8;
          pfVar11 = pfVar11 + 3;
        } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar26) || NAN(fVar23)));
      }
      fVar17 = fVar17 + 1.0;
      uVar14 = uVar14 & 0xfffffff | (uint)(fVar25 < fVar17) << 0x1f;
    } while (SUB41(uVar14 >> 0x1f,0) == (NAN(fVar25) || NAN(fVar17)));
  }
  if (0.0 < fVar26) {
    fVar18 = 0.0;
    if (fVar25 <= 0.0) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    do {
      if (bVar1) {
        fVar19 = 0.0;
        fVar21 = ((fVar26 - (fVar18 + 0.0)) * (1.0 / fVar26) + 0.0) * in_stack_00000008;
        fVar24 = ((fVar26 - (fVar18 + 1.0)) * (1.0 / fVar26) + 0.0) * in_stack_00000008;
        puVar6 = puVar12;
        do {
          puVar12 = puVar6 + 0x18;
          *(float *)(puVar6 + 8) = fVar21;
          *puVar6 = 0;
          *(float *)(puVar6 + 0xc) = fVar24;
          *(float *)(puVar6 + 0x10) = fVar24;
          *(float *)(puVar6 + 0x14) = fVar21;
          fVar17 = fVar19 * (fVar26 + 1.0);
          fVar20 = fVar19 + 0.0;
          fVar19 = fVar19 + 1.0;
          fVar20 = (1.0 - (fVar25 - fVar20) * (1.0 / fVar25)) * in_stack_00000008;
          fVar23 = (1.0 - (fVar25 - fVar19) * (1.0 / fVar25)) * in_stack_00000008;
          *(float *)(puVar6 + 0xe) = fVar20;
          *(float *)(puVar6 + 10) = fVar20;
          *(float *)(puVar6 + 0x16) = fVar23;
          *(float *)(puVar6 + 0x12) = fVar23;
          sVar8 = (short)(int)(fVar18 + fVar17);
          sVar7 = sVar8 + (short)in_stack_00000004;
          puVar6[1] = sVar8;
          puVar6[2] = sVar8 + 1;
          puVar6[4] = sVar7 + 1;
          puVar6[3] = sVar7 + 2;
          uVar10 = cRTextures::Add((cRTextures *)gTextureList,in_stack_0000000c,(cTgaHeader *)0x0,0)
          ;
          *(undefined4 *)(puVar6 + 6) = uVar10;
          puVar6 = puVar12;
        } while (fVar19 < fVar25);
      }
      fVar18 = fVar18 + 1.0;
    } while (fVar18 < fVar26);
  }
  RShellMemoryFree(pvVar9);
  return;
}
