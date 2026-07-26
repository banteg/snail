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
  cGLVertexArray *this_00;
  int iVar5;
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
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  cRSubLoc *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint in_fpscr;
  uint uVar15;
  uint uVar16;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s1_02;
  float extraout_s1_03;
  float extraout_s2;
  float extraout_s2_00;
  float fVar17;
  float extraout_s2_01;
  float extraout_s2_02;
  float extraout_s2_03;
  float extraout_s3;
  float extraout_s3_00;
  float fVar18;
  float extraout_s3_01;
  float extraout_s3_02;
  float extraout_s3_03;
  float fVar19;
  float fVar20;
  float fVar21;
  int local_48;

  fVar19 = *(float *)(this + 0x18) + 120.0;
  fVar20 = *(float *)(param_1 + 0x18);
  uVar16 = in_fpscr & 0xfffffff | (uint)(fVar20 < fVar19) << 0x1f | (uint)(fVar20 == fVar19) << 0x1e
  ;
  uVar15 = uVar16 | (uint)(NAN(fVar20) || NAN(fVar19)) << 0x1c;
  bVar4 = (byte)(uVar16 >> 0x18);
  if (!(bool)(bVar4 >> 6 & 1) && bVar4 >> 7 == ((byte)(uVar15 >> 0x1c) & 1)) {
    *(float *)(this + 0x18) = fVar19;
    iVar14 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x3c);
    if (0 < iVar14) {
      iVar9 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 8);
      iVar7 = 0;
      iVar6 = 0;
      do {
        iVar5 = iVar9 + iVar7;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 10;
        fVar19 = (float)VectorSignedToFloat((int)*(short *)(iVar5 + 4),(byte)(uVar15 >> 0x16) & 3);
        *(short *)(iVar5 + 4) = (short)(int)(fVar19 - 15360.0);
      } while (iVar6 != iVar14);
    }
    fVar20 = *(float *)(param_1 + 0x18);
  }
  uVar16 = in_fpscr & 0xfffffff | (uint)(*(float *)(this + 0x44) + 120.0 < fVar20) << 0x1f;
  if (SUB41(uVar16 >> 0x1f,0)) {
    *(float *)(this + 0x44) = *(float *)(this + 0x44) + 120.0;
    iVar14 = *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 0x3c);
    if (0 < iVar14) {
      iVar9 = *(int *)(*(int *)(*(int *)(this + 0x50) + 0x10c) + 8);
      iVar7 = 0;
      iVar6 = 0;
      do {
        iVar5 = iVar9 + iVar7;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 10;
        fVar19 = (float)VectorSignedToFloat((int)*(short *)(iVar5 + 4),(byte)(uVar16 >> 0x16) & 3);
        *(short *)(iVar5 + 4) = (short)(int)(fVar19 - 15360.0);
      } while (iVar6 != iVar14);
    }
  }
  cRSubGame::GetSkirtColour((tColourSmall *)(Game + 0x718a0));
  iVar6 = cRSubLoc::Yi(param_1);
  iVar12 = *(int *)(this + 0x5c);
  iVar9 = *(int *)(*(int *)(this + 0x24) + 0x10c);
  __aeabi_idivmod(iVar6,iVar12);
  local_48 = *(undefined4 *)(iVar9 + 0x28);
  iVar13 = *(int *)(iVar9 + 0x1c);
  __aeabi_idivmod(*(undefined4 *)(iVar9 + 0x24),local_48);
  piVar8 = (int *)(iVar13 + extraout_r1 * 8);
  iVar7 = *(int *)(*(int *)(this + 0x50) + 0x10c);
  piVar8[1] = 0;
  *(undefined4 *)(iVar13 + extraout_r1 * 8) = extraout_r1_00;
  iVar11 = *(int *)(this + 0x60);
  __aeabi_idivmod(iVar6,iVar11);
  iVar14 = extraout_r1_01 * 8;
  fVar19 = (float)__aeabi_idivmod(*(undefined4 *)(iVar7 + 0x24),*(undefined4 *)(iVar7 + 0x28));
  iVar5 = *(int *)(iVar7 + 0x1c);
  *(undefined4 *)(iVar5 + iVar14 + 4) = 0;
  *(undefined4 *)(iVar5 + extraout_r1_01 * 8) = extraout_r1_02;
  if (0 < *(int *)(this + 100)) {
    local_48 = 0;
    fVar20 = extraout_s1;
    fVar17 = extraout_s2;
    fVar18 = extraout_s3;
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
        fVar21 = *(float *)(param_1 + 0x18);
        uVar15 = uVar16 & 0xfffffff;
        uVar2 = uVar15 | (uint)(fVar21 < 10.0) << 0x1f | (uint)(fVar21 == 10.0) << 0x1e;
        uVar16 = uVar2 | (uint)NAN(fVar21) << 0x1c;
        this_00 = *(cGLVertexArray **)(*(int *)(this + 0x24) + 0x10c);
        bVar4 = (byte)(uVar2 >> 0x18);
        *(undefined4 *)this_00 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 200) + 0xc);
        if (!(bool)(bVar4 >> 6 & 1) && bVar4 >> 7 == ((byte)(uVar16 >> 0x1c) & 1)) {
          VectorSignedToFloat(*(undefined4 *)(Game + 0x71918),(byte)(uVar16 >> 0x16) & 3);
          uVar16 = uVar15;
        }
        cGLVertexArray::WorldAdd
                  (this_00,(tVector *)(param_1 + 0x10),fVar19,fVar20,*(cRObject **)(param_1 + 0x1c),
                   fVar17,fVar18);
        iVar14 = *(int *)(*(int *)(this + 0x24) + 0x10c);
        fVar19 = (float)__aeabi_idivmod(iVar6,*(undefined4 *)(this + 0x5c));
        iVar14 = *(int *)(iVar14 + 0x1c) + extraout_r1_03 * 8;
        *(int *)(iVar14 + 4) = *(int *)(iVar14 + 4) + 6;
        uVar15 = *(uint *)(param_1 + 4);
        *(uint *)(param_1 + 4) = uVar15 & 0xffffffdf;
        param_1[0x35] = (cRSubLoc)((byte)param_1[0x35] & 0xbf);
        iVar14 = Game;
        if ((uVar15 & 0x200) == 0) {
          RShellError("List remove");
          fVar19 = extraout_s0_00;
          fVar20 = extraout_s1_03;
          fVar17 = extraout_s2_03;
          fVar18 = extraout_s3_03;
        }
        else if ((uVar15 & 0x40) == 0) {
          iVar7 = *(int *)(param_1 + 0xc);
          *(uint *)(param_1 + 4) = uVar15 & 0xfffffddf;
          if (iVar7 != 0) {
            *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(param_1 + 8);
          }
          if (*(int *)(param_1 + 8) == 0) {
            *(int *)(iVar14 + 0x35c) = iVar7;
          }
          else {
            *(int *)(*(int *)(param_1 + 8) + 0xc) = iVar7;
          }
          *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar14 + 0x360);
          *(cRSubLoc **)(iVar14 + 0x360) = param_1;
          fVar20 = extraout_s1_00;
          fVar17 = extraout_s2_00;
          fVar18 = extraout_s3_00;
        }
        else {
          RShellError("List remove NEXTBOD");
          fVar19 = extraout_s0;
          fVar20 = extraout_s1_02;
          fVar17 = extraout_s2_02;
          fVar18 = extraout_s3_02;
        }
      }
      iVar14 = 0;
      pcVar10 = param_1;
      do {
        pcVar1 = pcVar10 + 0x38;
        iVar14 = iVar14 + 1;
        pcVar10 = pcVar10 + 4;
        if (*(int *)pcVar1 != 0) {
          cGLVertexArray::WorldAdd
                    (*(cGLVertexArray **)(*(int *)(this + 0x50) + 0x10c),(tVector *)(param_1 + 0x10)
                     ,fVar19,fVar20,(cRObject *)0x0,fVar17,fVar18);
          iVar7 = *(int *)(*(int *)(this + 0x50) + 0x10c);
          fVar19 = (float)__aeabi_idivmod(iVar6,*(undefined4 *)(this + 0x60));
          iVar7 = *(int *)(iVar7 + 0x1c) + extraout_r1_04 * 8;
          *(int *)(iVar7 + 4) = *(int *)(iVar7 + 4) + 6;
          fVar20 = extraout_s1_01;
          fVar17 = extraout_s2_01;
          fVar18 = extraout_s3_01;
        }
      } while (iVar14 != 4);
      param_1 = param_1 + 0x48;
      local_48 = local_48 + 1;
    } while (local_48 < *(int *)(this + 100));
    iVar12 = *(int *)(this + 0x5c);
    __aeabi_idivmod(iVar6,iVar12);
    iVar11 = *(int *)(this + 0x60);
    iVar9 = *(int *)(*(int *)(this + 0x24) + 0x10c);
    local_48 = *(undefined4 *)(iVar9 + 0x28);
    iVar13 = *(int *)(iVar9 + 0x1c);
    piVar8 = (int *)(iVar13 + extraout_r1_05 * 8);
    __aeabi_idivmod(iVar6,iVar11);
    iVar7 = *(int *)(*(int *)(this + 0x50) + 0x10c);
    iVar5 = *(int *)(iVar7 + 0x1c);
    iVar14 = extraout_r1_06 << 3;
  }
  if (iVar6 < iVar12) {
    iVar12 = 0;
    __aeabi_idivmod(piVar8[1] + *piVar8,local_48);
    uVar16 = extraout_r1_07;
    if (extraout_r1_07 < 0x80000000) goto LAB_000882d8;
LAB_0008837c:
    *(uint *)(iVar9 + 0x38) = uVar16;
    *(undefined4 *)(iVar9 + 0x34) = 0;
    *(int *)(iVar9 + 0x30) = *(int *)(iVar9 + 0x28) - iVar12;
    *(int *)(iVar9 + 0x2c) = iVar12;
  }
  else {
    __aeabi_idivmod((iVar6 + 10) - iVar12,iVar12);
    iVar12 = *(int *)(iVar13 + extraout_r1_09 * 8);
    __aeabi_idivmod(piVar8[1] + *piVar8,local_48);
    uVar16 = extraout_r1_10;
    if ((int)extraout_r1_10 < iVar12) goto LAB_0008837c;
LAB_000882d8:
    *(uint *)(iVar9 + 0x30) = uVar16 - iVar12;
    *(int *)(iVar9 + 0x2c) = iVar12;
    *(undefined4 *)(iVar9 + 0x38) = 0;
  }
  if (iVar6 < iVar11) {
    iVar6 = 0;
    __aeabi_idivmod(*(int *)(iVar5 + iVar14 + 4) + *(int *)(iVar5 + iVar14),
                    *(undefined4 *)(iVar7 + 0x28));
    iVar14 = extraout_r1_08;
    if (-1 < extraout_r1_08) {
LAB_000883dc:
      *(int *)(iVar7 + 0x30) = iVar14 - iVar6;
      *(int *)(iVar7 + 0x2c) = iVar6;
      *(undefined4 *)(iVar7 + 0x38) = 0;
      return;
    }
  }
  else {
    __aeabi_idivmod((iVar6 + 10) - iVar11,iVar11);
    iVar6 = *(int *)(iVar5 + extraout_r1_11 * 8);
    __aeabi_idivmod(*(int *)(iVar5 + iVar14 + 4) + *(int *)(iVar5 + iVar14),
                    *(undefined4 *)(iVar7 + 0x28));
    iVar14 = extraout_r1_12;
    if (iVar6 <= extraout_r1_12) goto LAB_000883dc;
  }
  *(int *)(iVar7 + 0x38) = iVar14;
  *(undefined4 *)(iVar7 + 0x34) = 0;
  *(int *)(iVar7 + 0x30) = *(int *)(iVar7 + 0x28) - iVar6;
  *(int *)(iVar7 + 0x2c) = iVar6;
  return;
}
