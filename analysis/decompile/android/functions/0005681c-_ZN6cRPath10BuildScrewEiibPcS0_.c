/*
 * mangled: _ZN6cRPath10BuildScrewEiibPcS0_
 * demangled: cRPath::BuildScrew(int, int, bool, char*, char*)
 * address: 0005681c
 * size: 1244
 */

/* cRPath::BuildScrew(int, int, bool, char*, char*) */

void cRPath::BuildScrew(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  uint uVar1;
  tVector *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  tMatrix *ptVar9;
  uint in_fpscr;
  float fVar10;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;

  iVar5 = param_2 + 8;
  uVar13 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(int *)(param_1 + 0x38) = iVar5;
  iVar6 = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x19;
  iVar7 = 0;
  *(undefined4 *)(param_1 + 0x40) = uVar13;
  GetNodes((cRPath *)param_1);
  iVar8 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  do {
    uVar13 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    ptVar9 = (tMatrix *)(iVar8 + iVar6);
    *(undefined4 *)(ptVar9 + 0x90) = 0x3f000000;
    *(undefined4 *)(ptVar9 + 0x98) = 0;
    *(undefined4 *)(ptVar9 + 0x94) = 0;
    *(undefined4 *)(ptVar9 + 0xa0) = 0;
    *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
    iVar7 = iVar7 + 1;
    tMatrix::Identity(ptVar9);
    iVar8 = *(int *)(param_1 + 0x50);
    iVar3 = *(int *)(param_1 + 0x4c) + iVar6;
    *(undefined4 *)(iVar3 + 0x34) = 0;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    tMatrix::Identity((tMatrix *)(iVar8 + iVar6));
    iVar8 = *(int *)(param_1 + 0x4c);
    iVar4 = *(int *)(param_1 + 0x50) + iVar6;
    *(undefined4 *)(iVar4 + 0x38) = uVar13;
    iVar3 = iVar8 + iVar6;
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  } while (iVar7 != 3);
  iVar7 = param_2 + 3;
  iVar6 = iVar7 * 0xa8;
  do {
    uVar13 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    ptVar9 = (tMatrix *)(iVar8 + iVar6);
    *(undefined4 *)(ptVar9 + 0x90) = 0xbf000000;
    *(undefined4 *)(ptVar9 + 0x98) = 0;
    *(undefined4 *)(ptVar9 + 0x94) = 0;
    *(undefined4 *)(ptVar9 + 0xa0) = 0;
    *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
    iVar7 = iVar7 + 1;
    tMatrix::Identity(ptVar9);
    iVar8 = *(int *)(param_1 + 0x50);
    iVar3 = *(int *)(param_1 + 0x4c) + iVar6;
    *(undefined4 *)(iVar3 + 0x34) = 0;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar8 + iVar6));
    iVar8 = *(int *)(param_1 + 0x4c);
    iVar4 = *(int *)(param_1 + 0x50) + iVar6;
    *(undefined4 *)(iVar4 + 0x38) = uVar13;
    iVar3 = iVar8 + iVar6;
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  } while (iVar7 != iVar5);
  if (0 < param_2) {
    fVar17 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = 0;
    iVar5 = 0x150;
    do {
      fVar16 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      iVar3 = iVar5 + 0xa8;
      fVar10 = (float)Cos(fVar10);
      ptVar9 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar3);
      *(undefined4 *)(ptVar9 + 0x98) = 0;
      *(float *)(ptVar9 + 0x94) = (fVar16 * 6.2831855) / fVar17;
      *(undefined4 *)(ptVar9 + 0xa0) = 0;
      *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
      *(float *)(iVar8 + iVar3 + 0x90) = fVar10 * 0.5;
      tMatrix::Identity(ptVar9);
      uVar13 = VectorSignedToFloat(iVar6 + 3,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = *(int *)(param_1 + 0x50);
      iVar8 = *(int *)(param_1 + 0x4c) + iVar3;
      *(undefined4 *)(iVar8 + 0x34) = 0;
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
      *(undefined4 *)(iVar8 + 0x38) = uVar13;
      fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar7 + iVar3));
      iVar7 = *(int *)(param_1 + 0x50);
      fVar16 = *(float *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x90);
      fVar10 = (float)Sin(fVar10);
      iVar8 = *(int *)(param_1 + 0x50);
      *(float *)(iVar7 + iVar3 + 0x30) = fVar16 + fVar10 * -0.49;
      fVar10 = (float)Cos(extraout_s0_01);
      *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar3 + 0x38) = uVar13;
      *(float *)(iVar8 + iVar3 + 0x34) = fVar10 * 0.49;
      if (iVar6 == 0) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar5));
        fVar10 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar5));
        if (param_2 < 2) goto LAB_00056bd0;
      }
      else {
        iVar4 = *(int *)(param_1 + 0x4c);
        uVar1 = Sin(extraout_s0_02);
        iVar4 = iVar4 + iVar5;
        uVar13 = Cos(extraout_s0);
        iVar7 = *(int *)(param_1 + 0x4c);
        *(undefined4 *)(iVar4 + 0x18) = 0;
        iVar8 = iVar7 + iVar5;
        iVar7 = iVar7 + iVar3;
        fVar14 = *(float *)(iVar8 + 0x30);
        fVar11 = *(float *)(iVar7 + 0x38);
        fVar10 = *(float *)(iVar7 + 0x34);
        fVar12 = *(float *)(iVar8 + 0x34);
        fVar16 = *(float *)(iVar7 + 0x30);
        *(uint *)(iVar4 + 0x10) = uVar1 ^ 0x80000000;
        fVar15 = *(float *)(iVar8 + 0x38);
        *(float *)(iVar8 + 0x24) = fVar10 - fVar12;
        *(float *)(iVar8 + 0x20) = fVar16 - fVar14;
        *(undefined4 *)(iVar4 + 0x14) = uVar13;
        *(float *)(iVar8 + 0x28) = fVar11 - fVar15;
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar5);
        fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
        iVar4 = *(int *)(param_1 + 0x50);
        uVar1 = Sin(fVar10);
        iVar4 = iVar4 + iVar5;
        uVar13 = Cos(extraout_s0_00);
        iVar7 = *(int *)(param_1 + 0x50);
        *(undefined4 *)(iVar4 + 0x18) = 0;
        iVar8 = iVar7 + iVar5;
        iVar7 = iVar7 + iVar3;
        fVar14 = *(float *)(iVar8 + 0x30);
        fVar11 = *(float *)(iVar7 + 0x38);
        fVar10 = *(float *)(iVar7 + 0x34);
        fVar16 = *(float *)(iVar7 + 0x30);
        fVar12 = *(float *)(iVar8 + 0x34);
        fVar15 = *(float *)(iVar8 + 0x38);
        *(uint *)(iVar4 + 0x10) = uVar1 ^ 0x80000000;
        *(float *)(iVar8 + 0x20) = fVar16 - fVar14;
        *(float *)(iVar8 + 0x24) = fVar10 - fVar12;
        *(undefined4 *)(iVar4 + 0x14) = uVar13;
        *(float *)(iVar8 + 0x28) = fVar11 - fVar15;
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_1 + 0x50) + iVar5);
        fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
        if (param_2 <= iVar6 + 1) goto LAB_00056bd0;
      }
      iVar6 = iVar6 + 1;
      iVar8 = *(int *)(param_1 + 0x4c);
      iVar5 = iVar3;
    } while( true );
  }
LAB_00056bd4:
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar5 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar7 = 0;
    iVar6 = 0;
    while( true ) {
      iVar4 = iVar6 + 0xa8;
      iVar3 = iVar8 + iVar6;
      iVar8 = iVar8 + iVar4;
      fVar17 = *(float *)(iVar8 + 0x38);
      fVar10 = *(float *)(iVar8 + 0x34);
      iVar7 = iVar7 + 1;
      *(float *)(iVar3 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar10 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar17 - *(float *)(iVar3 + 0x38);
      uVar13 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar6 = *(int *)(param_1 + 0x50) + iVar6;
      iVar5 = *(int *)(param_1 + 0x50) + iVar4;
      fVar17 = *(float *)(iVar5 + 0x38);
      fVar10 = *(float *)(iVar5 + 0x34);
      fVar16 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar6 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar10 - *(float *)(iVar6 + 0x34);
      *(undefined4 *)(iVar3 + 0x8c) = uVar13;
      *(float *)(iVar6 + 0x88) = fVar17 - fVar16;
      uVar13 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar5 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar6 + 0x8c) = uVar13;
      if (iVar5 <= iVar7) break;
      iVar8 = *(int *)(param_1 + 0x4c);
      iVar6 = iVar4;
    }
    iVar8 = *(int *)(param_1 + 0x4c);
  }
  iVar6 = *(int *)(param_1 + 0x50) + iVar5 * 0xa8;
  iVar8 = iVar8 + iVar5 * 0xa8;
  *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x84) = 0;
  *(undefined4 *)(iVar8 + 0x80) = 0;
  *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x80) = 0;
  *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_1);
  return;
LAB_00056bd0:
  iVar8 = *(int *)(param_1 + 0x4c);
  goto LAB_00056bd4;
}
