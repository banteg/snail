/*
 * mangled: _ZN6cRPath10BuildScrewEiibPcS0_
 * demangled: cRPath::BuildScrew(int, int, bool, char*, char*)
 * address: 0005681c
 * size: 1244
 */

/* cRPath::BuildScrew(int, int, bool, char*, char*) */

void cRPath::BuildScrew(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  uint uVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  tMatrix *ptVar11;
  uint in_fpscr;
  float fVar12;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  float fVar24;

  iVar7 = param_2 + 8;
  uVar17 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  uVar4 = DAT_00056c04;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x44) = uVar4;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(int *)(param_1 + 0x38) = iVar7;
  iVar8 = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x19;
  iVar9 = 0;
  *(undefined4 *)(param_1 + 0x40) = uVar17;
  fVar13 = DAT_00056bf0;
  GetNodes((cRPath *)param_1);
  uVar17 = DAT_00056c08;
  fVar15 = DAT_00056bf4;
  iVar10 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  do {
    uVar22 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(float *)(ptVar11 + 0x90) = fVar13;
    *(undefined4 *)(ptVar11 + 0x98) = uVar17;
    *(undefined4 *)(ptVar11 + 0x94) = uVar17;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar17;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar4;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x34) = uVar17;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar22;
    tMatrix::Identity((tMatrix *)(iVar10 + iVar8));
    iVar10 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar22;
    iVar5 = iVar10 + iVar8;
    *(float *)(iVar6 + 0x34) = fVar15;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    uVar22 = DAT_00056bf8;
  } while (iVar9 != 3);
  iVar9 = param_2 + 3;
  iVar8 = iVar9 * 0xa8;
  do {
    uVar23 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(undefined4 *)(ptVar11 + 0x90) = uVar22;
    *(undefined4 *)(ptVar11 + 0x98) = uVar17;
    *(undefined4 *)(ptVar11 + 0x94) = uVar17;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar17;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar4;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x34) = uVar17;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar23;
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar10 + iVar8));
    iVar10 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar23;
    iVar5 = iVar10 + iVar8;
    *(float *)(iVar6 + 0x34) = fVar15;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    fVar1 = DAT_00056c00;
    fVar21 = DAT_00056bfc;
    fVar13 = DAT_00056bf0;
  } while (iVar9 != iVar7);
  if (0 < param_2) {
    fVar24 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = 0;
    iVar7 = 0x150;
    do {
      fVar20 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = iVar7 + 0xa8;
      fVar12 = (float)Cos(fVar12);
      ptVar11 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar5);
      *(undefined4 *)(ptVar11 + 0x98) = uVar17;
      *(float *)(ptVar11 + 0x94) = (fVar20 * fVar21) / fVar24;
      *(undefined4 *)(ptVar11 + 0xa0) = uVar17;
      *(undefined4 *)(ptVar11 + 0x9c) = uVar4;
      *(float *)(iVar10 + iVar5 + 0x90) = fVar12 * fVar13;
      tMatrix::Identity(ptVar11);
      uVar22 = VectorSignedToFloat(iVar8 + 3,(byte)(in_fpscr >> 0x16) & 3);
      iVar9 = *(int *)(param_1 + 0x50);
      iVar10 = *(int *)(param_1 + 0x4c) + iVar5;
      *(undefined4 *)(iVar10 + 0x34) = uVar17;
      *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
      *(undefined4 *)(iVar10 + 0x38) = uVar22;
      fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar9 + iVar5));
      iVar9 = *(int *)(param_1 + 0x50);
      fVar20 = *(float *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90);
      fVar12 = (float)Sin(fVar12);
      iVar10 = *(int *)(param_1 + 0x50);
      *(float *)(iVar9 + iVar5 + 0x30) = fVar20 + fVar12 * fVar1;
      fVar12 = (float)Cos(extraout_s0_01);
      *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar5 + 0x38) = uVar22;
      *(float *)(iVar10 + iVar5 + 0x34) = fVar12 * fVar15;
      if (iVar8 == 0) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar7));
        fVar12 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar7));
        if (param_2 < 2) goto LAB_00056bd0;
      }
      else {
        iVar6 = *(int *)(param_1 + 0x4c);
        uVar2 = Sin(extraout_s0_02);
        iVar6 = iVar6 + iVar7;
        uVar22 = Cos(extraout_s0);
        iVar9 = *(int *)(param_1 + 0x4c);
        *(undefined4 *)(iVar6 + 0x18) = uVar17;
        iVar10 = iVar9 + iVar7;
        iVar9 = iVar9 + iVar5;
        fVar18 = *(float *)(iVar10 + 0x30);
        fVar14 = *(float *)(iVar9 + 0x38);
        fVar12 = *(float *)(iVar9 + 0x34);
        fVar16 = *(float *)(iVar10 + 0x34);
        fVar20 = *(float *)(iVar9 + 0x30);
        *(uint *)(iVar6 + 0x10) = uVar2 ^ 0x80000000;
        fVar19 = *(float *)(iVar10 + 0x38);
        *(float *)(iVar10 + 0x24) = fVar12 - fVar16;
        *(float *)(iVar10 + 0x20) = fVar20 - fVar18;
        *(undefined4 *)(iVar6 + 0x14) = uVar22;
        *(float *)(iVar10 + 0x28) = fVar14 - fVar19;
        tVector::Normalize((tVector *)(iVar10 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar7);
        fVar12 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
        iVar6 = *(int *)(param_1 + 0x50);
        uVar2 = Sin(fVar12);
        iVar6 = iVar6 + iVar7;
        uVar22 = Cos(extraout_s0_00);
        iVar9 = *(int *)(param_1 + 0x50);
        *(undefined4 *)(iVar6 + 0x18) = uVar17;
        iVar10 = iVar9 + iVar7;
        iVar9 = iVar9 + iVar5;
        fVar18 = *(float *)(iVar10 + 0x30);
        fVar14 = *(float *)(iVar9 + 0x38);
        fVar12 = *(float *)(iVar9 + 0x34);
        fVar20 = *(float *)(iVar9 + 0x30);
        fVar16 = *(float *)(iVar10 + 0x34);
        fVar19 = *(float *)(iVar10 + 0x38);
        *(uint *)(iVar6 + 0x10) = uVar2 ^ 0x80000000;
        *(float *)(iVar10 + 0x20) = fVar20 - fVar18;
        *(float *)(iVar10 + 0x24) = fVar12 - fVar16;
        *(undefined4 *)(iVar6 + 0x14) = uVar22;
        *(float *)(iVar10 + 0x28) = fVar14 - fVar19;
        tVector::Normalize((tVector *)(iVar10 + 0x20));
        ptVar3 = (tVector *)(*(int *)(param_1 + 0x50) + iVar7);
        fVar12 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
        if (param_2 <= iVar8 + 1) goto LAB_00056bd0;
      }
      iVar8 = iVar8 + 1;
      iVar10 = *(int *)(param_1 + 0x4c);
      iVar7 = iVar5;
    } while( true );
  }
LAB_00056bd4:
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar7 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar9 = 0;
    iVar8 = 0;
    while( true ) {
      iVar6 = iVar8 + 0xa8;
      iVar5 = iVar10 + iVar8;
      iVar10 = iVar10 + iVar6;
      fVar15 = *(float *)(iVar10 + 0x38);
      fVar13 = *(float *)(iVar10 + 0x34);
      iVar9 = iVar9 + 1;
      *(float *)(iVar5 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar13 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar15 - *(float *)(iVar5 + 0x38);
      uVar4 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar8 = *(int *)(param_1 + 0x50) + iVar8;
      iVar7 = *(int *)(param_1 + 0x50) + iVar6;
      fVar15 = *(float *)(iVar7 + 0x38);
      fVar13 = *(float *)(iVar7 + 0x34);
      fVar21 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar13 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar5 + 0x8c) = uVar4;
      *(float *)(iVar8 + 0x88) = fVar15 - fVar21;
      uVar4 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar7 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar4;
      if (iVar7 <= iVar9) break;
      iVar10 = *(int *)(param_1 + 0x4c);
      iVar8 = iVar6;
    }
    iVar10 = *(int *)(param_1 + 0x4c);
  }
  uVar17 = DAT_00056c08;
  uVar4 = DAT_00056c04;
  iVar8 = *(int *)(param_1 + 0x50) + iVar7 * 0xa8;
  iVar10 = iVar10 + iVar7 * 0xa8;
  *(undefined4 *)(iVar10 + 0x8c) = DAT_00056c04;
  *(undefined4 *)(iVar10 + 0x88) = uVar4;
  *(undefined4 *)(iVar10 + 0x84) = uVar17;
  *(undefined4 *)(iVar10 + 0x80) = uVar17;
  *(undefined4 *)(iVar8 + 0x8c) = uVar4;
  *(undefined4 *)(iVar8 + 0x80) = uVar17;
  *(undefined4 *)(iVar8 + 0x88) = uVar4;
  *(undefined4 *)(iVar8 + 0x84) = uVar17;
  CalcLengthZ((cRPath *)param_1);
  return;
LAB_00056bd0:
  iVar10 = *(int *)(param_1 + 0x4c);
  goto LAB_00056bd4;
}
