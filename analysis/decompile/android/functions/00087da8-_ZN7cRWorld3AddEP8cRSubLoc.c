/*
 * mangled: _ZN7cRWorld3AddEP8cRSubLoc
 * demangled: cRWorld::Add(cRSubLoc*)
 * address: 00087da8
 * size: 1608
 */

/* cRWorld::Add(cRSubLoc*) */

void __thiscall cRWorld::Add(cRWorld *this,cRSubLoc *param_1)

{
  cRSubLoc *pcVar1;
  uint uVar2;
  cRSubLoc cVar3;
  byte bVar4;
  int iVar5;
  cGLVertexArray *this_00;
  int iVar6;
  int extraout_r1;
  undefined4 extraout_r1_00;
  int extraout_r1_01;
  undefined4 extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  uint extraout_r1_07;
  int extraout_r1_08;
  int extraout_r1_09;
  uint extraout_r1_10;
  int extraout_r1_11;
  int extraout_r1_12;
  int iVar7;
  int iVar8;
  int *piVar9;
  char *pcVar10;
  char *pcVar11;
  int iVar12;
  cRSubLoc *pcVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint in_fpscr;
  uint uVar19;
  uint uVar20;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float fVar21;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s2;
  float extraout_s2_00;
  float fVar22;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s3;
  float extraout_s3_00;
  float fVar23;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float fVar24;
  float fVar25;
  float fVar26;
  int local_48;

  fVar24 = DAT_0008819c + *(float *)(this + 0x18);
  fVar25 = *(float *)(param_1 + 0x18);
  iVar5 = DAT_000881ac + 0x87dd8;
  uVar20 = in_fpscr & 0xfffffff | (uint)(fVar25 < fVar24) << 0x1f | (uint)(fVar25 == fVar24) << 0x1e
  ;
  uVar19 = uVar20 | (uint)(NAN(fVar25) || NAN(fVar24)) << 0x1c;
  bVar4 = (byte)(uVar20 >> 0x18);
  if (!(bool)(bVar4 >> 6 & 1) && bVar4 >> 7 == ((byte)(uVar19 >> 0x1c) & 1)) {
    *(float *)(this + 0x18) = fVar24;
    fVar24 = DAT_000881a0;
    iVar18 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x3c);
    if (0 < iVar18) {
      iVar12 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 8);
      iVar8 = 0;
      iVar7 = 0;
      do {
        iVar6 = iVar12 + iVar8;
        iVar7 = iVar7 + 1;
        iVar8 = iVar8 + 10;
        fVar25 = (float)VectorSignedToFloat((int)*(short *)(iVar6 + 4),(byte)(uVar19 >> 0x16) & 3);
        *(short *)(iVar6 + 4) = (short)(int)(fVar25 - fVar24);
      } while (iVar7 != iVar18);
    }
    fVar25 = *(float *)(param_1 + 0x18);
  }
  uVar20 = in_fpscr & 0xfffffff | (uint)(DAT_0008819c + *(float *)(this + 0x44) < fVar25) << 0x1f;
  if (SUB41(uVar20 >> 0x1f,0)) {
    *(float *)(this + 0x44) = DAT_0008819c + *(float *)(this + 0x44);
    fVar24 = DAT_000881a0;
    iVar18 = *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x3c);
    if (0 < iVar18) {
      iVar12 = *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 8);
      iVar8 = 0;
      iVar7 = 0;
      do {
        iVar6 = iVar12 + iVar8;
        iVar7 = iVar7 + 1;
        iVar8 = iVar8 + 10;
        fVar25 = (float)VectorSignedToFloat((int)*(short *)(iVar6 + 4),(byte)(uVar20 >> 0x16) & 3);
        *(short *)(iVar6 + 4) = (short)(int)(fVar25 - fVar24);
      } while (iVar7 != iVar18);
    }
  }
  iVar7 = DAT_000881b0;
  cRSubGame::GetSkirtColour((tColourSmall *)(**(int **)(iVar5 + DAT_000881b0) + 0x718a0));
  iVar8 = cRSubLoc::Yi(param_1);
  iVar16 = *(int *)(this + 0x5c);
  iVar6 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  __aeabi_idivmod(iVar8,iVar16);
  local_48 = *(undefined4 *)(iVar6 + 0x28);
  iVar17 = *(int *)(iVar6 + 0x1c);
  __aeabi_idivmod(*(undefined4 *)(iVar6 + 0x24),local_48);
  piVar9 = (int *)(iVar17 + extraout_r1 * 8);
  iVar12 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  piVar9[1] = 0;
  *(undefined4 *)(iVar17 + extraout_r1 * 8) = extraout_r1_00;
  iVar15 = *(int *)(this + 0x60);
  __aeabi_idivmod(iVar8,iVar15);
  iVar18 = extraout_r1_01 * 8;
  fVar25 = (float)__aeabi_idivmod(*(undefined4 *)(iVar12 + 0x24),*(undefined4 *)(iVar12 + 0x28));
  iVar14 = *(int *)(iVar12 + 0x1c);
  *(undefined4 *)(iVar14 + iVar18 + 4) = 0;
  *(undefined4 *)(iVar14 + extraout_r1_01 * 8) = extraout_r1_02;
  fVar24 = DAT_000881a4;
  if (0 < *(int *)(this + 100)) {
    local_48 = 0;
    pcVar10 = (char *)(iVar5 + DAT_000881b4);
    pcVar11 = (char *)(iVar5 + DAT_000881b8);
    fVar21 = extraout_s1;
    fVar22 = extraout_s2;
    fVar23 = extraout_s3;
    do {
      if ((((((((*(uint *)(param_1 + 4) & 0x200) != 0) && (((byte)param_1[0x35] & 0x40) != 0)) &&
             (cVar3 = param_1[0x30], cVar3 != (cRSubLoc)0x1d)) &&
            (((cVar3 != (cRSubLoc)0x1e && (cVar3 != (cRSubLoc)0xe)) &&
             ((cVar3 != (cRSubLoc)0x2 && ((cVar3 != (cRSubLoc)0x3 && (cVar3 != (cRSubLoc)0x4))))))))
           && ((cVar3 != (cRSubLoc)0x8 &&
               (((cVar3 != (cRSubLoc)0x9 && (cVar3 != (cRSubLoc)0xa)) && (cVar3 != (cRSubLoc)0xb))))
              )) && (((cVar3 != (cRSubLoc)0xc && (cVar3 != (cRSubLoc)0xd)) &&
                     (((cVar3 != (cRSubLoc)0x5 &&
                       ((cVar3 != (cRSubLoc)0x6 && (cVar3 != (cRSubLoc)0x7)))) &&
                      (cVar3 != (cRSubLoc)0x0)))))) &&
         ((((cVar3 != (cRSubLoc)0x16 && (cVar3 != (cRSubLoc)0x1c)) && (cVar3 != (cRSubLoc)0x1f)) &&
          (cVar3 != (cRSubLoc)0x20)))) {
        fVar26 = *(float *)(param_1 + 0x18);
        uVar19 = uVar20 & 0xfffffff;
        uVar2 = uVar19 | (uint)(fVar26 < fVar24) << 0x1f | (uint)(fVar26 == fVar24) << 0x1e;
        uVar20 = uVar2 | (uint)(NAN(fVar26) || NAN(fVar24)) << 0x1c;
        this_00 = *(cGLVertexArray **)(*(int *)(this + 0x24) + 0x10c);
        bVar4 = (byte)(uVar2 >> 0x18);
        *(undefined4 *)this_00 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 200) + 0xc);
        if (!(bool)(bVar4 >> 6 & 1) && bVar4 >> 7 == ((byte)(uVar20 >> 0x1c) & 1)) {
          VectorSignedToFloat(*(undefined4 *)(**(int **)(iVar5 + iVar7) + 0x71918),
                              (byte)(uVar20 >> 0x16) & 3);
          uVar20 = uVar19;
        }
        cGLVertexArray::WorldAdd
                  (this_00,(tVector *)(param_1 + 0x10),fVar25,fVar21,*(cRObject **)(param_1 + 0x1c),
                   fVar22,fVar23);
        iVar18 = *(int *)(*(int *)(this + 0x24) + 0x10c);
        fVar25 = (float)__aeabi_idivmod(iVar8,*(undefined4 *)(this + 0x5c));
        piVar9 = *(int **)(iVar5 + iVar7);
        iVar18 = *(int *)(iVar18 + 0x1c) + extraout_r1_03 * 8;
        *(int *)(iVar18 + 4) = *(int *)(iVar18 + 4) + 6;
        uVar19 = *(uint *)(param_1 + 4);
        *(uint *)(param_1 + 4) = uVar19 & 0xffffffdf;
        param_1[0x35] = (cRSubLoc)((byte)param_1[0x35] & 0xbf);
        iVar18 = *piVar9;
        if ((uVar19 & 0x200) == 0) {
          RShellError(pcVar11);
          fVar25 = extraout_s0_00;
          fVar21 = extraout_s1_03;
          fVar22 = extraout_s2_03;
          fVar23 = extraout_s3_03;
        }
        else if ((uVar19 & 0x40) == 0) {
          iVar12 = *(int *)(param_1 + 0xc);
          *(uint *)(param_1 + 4) = uVar19 & 0xfffffddf;
          if (iVar12 != 0) {
            *(undefined4 *)(iVar12 + 8) = *(undefined4 *)(param_1 + 8);
          }
          if (*(int *)(param_1 + 8) == 0) {
            *(int *)(iVar18 + 0x35c) = iVar12;
          }
          else {
            *(int *)(*(int *)(param_1 + 8) + 0xc) = iVar12;
          }
          *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar18 + 0x360);
          *(cRSubLoc **)(iVar18 + 0x360) = param_1;
          fVar21 = extraout_s1_00;
          fVar22 = extraout_s2_00;
          fVar23 = extraout_s3_00;
        }
        else {
          RShellError(pcVar10);
          fVar25 = extraout_s0;
          fVar21 = extraout_s1_02;
          fVar22 = extraout_s2_02;
          fVar23 = extraout_s3_02;
        }
      }
      iVar18 = 0;
      pcVar13 = param_1;
      do {
        pcVar1 = pcVar13 + 0x38;
        iVar18 = iVar18 + 1;
        pcVar13 = pcVar13 + 4;
        if (*(int *)pcVar1 != 0) {
          cGLVertexArray::WorldAdd
                    (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10)
                     ,fVar25,fVar21,(cRObject *)0x0,fVar22,fVar23);
          iVar12 = *(int *)(*(int *)(this + 0x50) + 0x10c);
          fVar25 = (float)__aeabi_idivmod(iVar8,*(undefined4 *)(this + 0x60));
          iVar12 = *(int *)(iVar12 + 0x1c) + extraout_r1_04 * 8;
          *(int *)(iVar12 + 4) = *(int *)(iVar12 + 4) + 6;
          fVar21 = extraout_s1_01;
          fVar22 = extraout_s2_01;
          fVar23 = extraout_s3_01;
        }
      } while (iVar18 != 4);
      param_1 = param_1 + 0x48;
      local_48 = local_48 + 1;
    } while (local_48 < *(int *)(this + 100));
    iVar16 = *(int *)(this + 0x5c);
    __aeabi_idivmod(iVar8,iVar16);
    iVar15 = *(int *)(this + 0x60);
    iVar6 = *(int *)(*(int *)(this + 0x24) + 0x10c);
    local_48 = *(undefined4 *)(iVar6 + 0x28);
    iVar17 = *(int *)(iVar6 + 0x1c);
    piVar9 = (int *)(iVar17 + extraout_r1_05 * 8);
    __aeabi_idivmod(iVar8,iVar15);
    iVar12 = *(int *)(*(int *)(this + 0x50) + 0x10c);
    iVar14 = *(int *)(iVar12 + 0x1c);
    iVar18 = extraout_r1_06 << 3;
  }
  if (iVar8 < iVar16) {
    iVar5 = 0;
    __aeabi_idivmod(piVar9[1] + *piVar9,local_48);
    uVar20 = extraout_r1_07;
    if (extraout_r1_07 < 0x80000000) goto LAB_000882d8;
LAB_0008837c:
    *(uint *)(iVar6 + 0x38) = uVar20;
    *(undefined4 *)(iVar6 + 0x34) = 0;
    *(int *)(iVar6 + 0x30) = *(int *)(iVar6 + 0x28) - iVar5;
    *(int *)(iVar6 + 0x2c) = iVar5;
  }
  else {
    __aeabi_idivmod((iVar8 + 10) - iVar16,iVar16);
    iVar5 = *(int *)(iVar17 + extraout_r1_09 * 8);
    __aeabi_idivmod(piVar9[1] + *piVar9,local_48);
    uVar20 = extraout_r1_10;
    if ((int)extraout_r1_10 < iVar5) goto LAB_0008837c;
LAB_000882d8:
    *(uint *)(iVar6 + 0x30) = uVar20 - iVar5;
    *(int *)(iVar6 + 0x2c) = iVar5;
    *(undefined4 *)(iVar6 + 0x38) = 0;
  }
  if (iVar8 < iVar15) {
    iVar7 = 0;
    __aeabi_idivmod(*(int *)(iVar14 + iVar18 + 4) + *(int *)(iVar14 + iVar18),
                    *(undefined4 *)(iVar12 + 0x28));
    iVar5 = extraout_r1_08;
    if (-1 < extraout_r1_08) {
LAB_000883dc:
      *(int *)(iVar12 + 0x30) = iVar5 - iVar7;
      *(int *)(iVar12 + 0x2c) = iVar7;
      *(undefined4 *)(iVar12 + 0x38) = 0;
      return;
    }
  }
  else {
    __aeabi_idivmod((iVar8 + 10) - iVar15,iVar15);
    iVar7 = *(int *)(iVar14 + extraout_r1_11 * 8);
    __aeabi_idivmod(*(int *)(iVar14 + iVar18 + 4) + *(int *)(iVar14 + iVar18),
                    *(undefined4 *)(iVar12 + 0x28));
    iVar5 = extraout_r1_12;
    if (iVar7 <= extraout_r1_12) goto LAB_000883dc;
  }
  *(int *)(iVar12 + 0x38) = iVar5;
  *(undefined4 *)(iVar12 + 0x34) = 0;
  *(int *)(iVar12 + 0x30) = *(int *)(iVar12 + 0x28) - iVar7;
  *(int *)(iVar12 + 0x2c) = iVar7;
  return;
}
