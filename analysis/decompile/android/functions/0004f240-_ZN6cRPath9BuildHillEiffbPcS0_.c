/*
 * mangled: _ZN6cRPath9BuildHillEiffbPcS0_
 * demangled: cRPath::BuildHill(int, float, float, bool, char*, char*)
 * address: 0004f240
 * size: 1220
 */

/* cRPath::BuildHill(int, float, float, bool, char*, char*) */

void cRPath::BuildHill(int param_1,float param_2,float param_3,bool param_4,char *param_5,
                      char *param_6)

{
  tVector *ptVar1;
  tMatrix *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float extraout_s13;
  float fVar13;
  float fVar14;
  float fVar15;
  int iVar16;
  float extraout_s14;
  float fVar17;
  undefined4 uVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  char in_stack_00000000;

  iVar16 = (int)(float)param_6;
  *(float *)(param_1 + 0x44) = DAT_0004f5dc;
  *(undefined4 *)(param_1 + 0x2c) = 0x14;
  *(uint *)(param_1 + 0x48) = (uint)param_4;
  *(undefined1 *)(param_1 + 0x30) = 0;
  iVar6 = iVar16 + 1;
  uVar18 = VectorSignedToFloat(iVar16 + 2,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_1 + 0x38) = iVar16 + 2;
  *(undefined4 *)(param_1 + 0x34) = 0;
  fVar11 = DAT_0004f5e0;
  *(undefined4 *)(param_1 + 0x40) = uVar18;
  GetNodes((cRPath *)param_1);
  bVar9 = in_stack_00000000 == '\0';
  if (bVar9) {
    fVar13 = *(float *)(param_1 + 0x48);
    ptVar2 = *(tMatrix **)(param_1 + 0x4c);
    fVar19 = DAT_0004f5e4;
    fVar15 = DAT_0004f5e8;
  }
  else {
    ptVar2 = *(tMatrix **)(param_1 + 0x4c);
    fVar19 = DAT_0004f5e0;
    fVar15 = extraout_s14;
    fVar13 = extraout_s13;
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if (bVar9) {
    fVar13 = (float)VectorSignedToFloat(fVar13,(byte)(in_fpscr >> 0x16) & 3);
  }
  else {
    *(float *)(ptVar2 + 0x90) = fVar19;
  }
  *(float *)(ptVar2 + 0x98) = fVar11;
  *(float *)(ptVar2 + 0x94) = fVar11;
  *(float *)(ptVar2 + 0xa0) = fVar11;
  if (bVar9) {
    *(float *)(ptVar2 + 0x90) = fVar13 * fVar15 - fVar19;
  }
  *(float *)(ptVar2 + 0x9c) = DAT_0004f5dc;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x4c);
  ptVar2 = *(tMatrix **)(param_1 + 0x50);
  *(float *)(iVar3 + 0x38) = fVar11;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(float *)(iVar3 + 0x34) = fVar11;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x50);
  iVar4 = *(int *)(param_1 + 0x4c);
  *(float *)(iVar3 + 0x34) = DAT_0004f5d4;
  *(float *)(iVar3 + 0x38) = fVar11;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  if (in_stack_00000000 == '\0') {
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar2 = (tMatrix *)(iVar4 + iVar6 * 0xa8);
    *(float *)(ptVar2 + 0x90) = fVar11 * DAT_0004f5e8 - DAT_0004f5e4;
  }
  else {
    ptVar2 = (tMatrix *)(iVar4 + iVar6 * 0xa8);
    *(float *)(ptVar2 + 0x90) = fVar11;
  }
  fVar13 = DAT_0004f5e0;
  iVar4 = iVar6 * 0xa8;
  uVar18 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(ptVar2 + 0x98) = DAT_0004f5e0;
  *(float *)(ptVar2 + 0x94) = fVar13;
  *(float *)(ptVar2 + 0xa0) = fVar13;
  fVar15 = DAT_0004f5dc;
  *(float *)(ptVar2 + 0x9c) = DAT_0004f5dc;
  fVar11 = DAT_0004f5d4;
  tMatrix::Identity(ptVar2);
  iVar6 = *(int *)(param_1 + 0x50);
  iVar3 = *(int *)(param_1 + 0x4c) + iVar4;
  *(float *)(iVar3 + 0x34) = fVar13;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar3 + 0x38) = uVar18;
  tMatrix::Identity((tMatrix *)(iVar6 + iVar4));
  iVar3 = *(int *)(param_1 + 0x4c);
  iVar6 = *(int *)(param_1 + 0x50) + iVar4;
  *(undefined4 *)(iVar6 + 0x38) = uVar18;
  *(float *)(iVar6 + 0x34) = fVar11;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar3 + iVar4 + 0x90);
  fVar19 = DAT_0004f5e8;
  if (0 < iVar16) {
    VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = 0;
    iVar4 = 0;
    while( true ) {
      iVar5 = iVar6 + 0xa8;
      ptVar2 = (tMatrix *)(iVar3 + iVar5);
      *(undefined4 *)(ptVar2 + 0x90) = *(undefined4 *)(iVar3 + 0x90);
      *(float *)(ptVar2 + 0x98) = fVar13;
      *(float *)(ptVar2 + 0x94) = fVar13;
      *(float *)(ptVar2 + 0xa0) = fVar13;
      *(float *)(ptVar2 + 0x9c) = fVar15;
      iVar7 = iVar4 + 1;
      fVar10 = (float)tMatrix::Identity(ptVar2);
      iVar8 = *(int *)(param_1 + 0x4c) + iVar5;
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
      uVar18 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar10 = (float)Cos(fVar10);
      iVar3 = *(int *)(param_1 + 0x50);
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x38) = uVar18;
      *(float *)(iVar8 + 0x34) = (fVar15 - fVar10) * fVar19 * (float)param_5;
      fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar5));
      iVar3 = *(int *)(param_1 + 0x50) + iVar5;
      *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90);
      fVar10 = (float)Cos(fVar10);
      *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar5 + 0x38) = uVar18;
      *(float *)(iVar3 + 0x34) = fVar11 + (fVar15 - fVar10) * fVar19 * (float)param_5;
      if (iVar4 < 1) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar6));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar6));
      }
      else {
        iVar4 = *(int *)(param_1 + 0x4c);
        iVar8 = iVar4 + iVar6;
        iVar3 = iVar4 + iVar5;
        fVar20 = *(float *)(iVar8 + 0x30);
        fVar14 = *(float *)(iVar3 + 0x38);
        fVar10 = *(float *)(iVar3 + 0x34);
        fVar17 = *(float *)(iVar8 + 0x34);
        fVar12 = *(float *)(iVar3 + 0x30);
        *(float *)(iVar8 + 8) = fVar13;
        *(float *)(iVar8 + 4) = fVar13;
        *(float *)(iVar4 + iVar6) = fVar15;
        *(float *)(iVar8 + 0x24) = fVar10 - fVar17;
        *(float *)(iVar8 + 0x20) = fVar12 - fVar20;
        *(float *)(iVar8 + 0x28) = fVar14 - *(float *)(iVar8 + 0x38);
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar6);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
        iVar4 = *(int *)(param_1 + 0x50);
        iVar8 = iVar4 + iVar6;
        iVar3 = iVar4 + iVar5;
        fVar20 = *(float *)(iVar8 + 0x30);
        fVar14 = *(float *)(iVar3 + 0x38);
        fVar10 = *(float *)(iVar3 + 0x34);
        fVar12 = *(float *)(iVar3 + 0x30);
        fVar17 = *(float *)(iVar8 + 0x34);
        fVar21 = *(float *)(iVar8 + 0x38);
        *(float *)(iVar8 + 8) = fVar13;
        *(float *)(iVar4 + iVar6) = fVar15;
        *(float *)(iVar8 + 4) = fVar13;
        *(float *)(iVar8 + 0x20) = fVar12 - fVar20;
        *(float *)(iVar8 + 0x24) = fVar10 - fVar17;
        *(float *)(iVar8 + 0x28) = fVar14 - fVar21;
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar6);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      }
      if (iVar16 <= iVar7) break;
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar6 = iVar5;
      iVar4 = iVar7;
    }
    iVar3 = *(int *)(param_1 + 0x4c);
  }
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar6 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar4 = 0;
    iVar16 = 0;
    while( true ) {
      iVar7 = iVar16 + 0xa8;
      iVar5 = iVar3 + iVar16;
      iVar3 = iVar3 + iVar7;
      fVar15 = *(float *)(iVar3 + 0x38);
      fVar11 = *(float *)(iVar3 + 0x34);
      iVar4 = iVar4 + 1;
      *(float *)(iVar5 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar11 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar15 - *(float *)(iVar5 + 0x38);
      uVar18 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar16 = *(int *)(param_1 + 0x50) + iVar16;
      iVar6 = *(int *)(param_1 + 0x50) + iVar7;
      fVar15 = *(float *)(iVar6 + 0x38);
      fVar11 = *(float *)(iVar6 + 0x34);
      fVar13 = *(float *)(iVar16 + 0x38);
      *(float *)(iVar16 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar16 + 0x30);
      *(float *)(iVar16 + 0x84) = fVar11 - *(float *)(iVar16 + 0x34);
      *(undefined4 *)(iVar5 + 0x8c) = uVar18;
      *(float *)(iVar16 + 0x88) = fVar15 - fVar13;
      uVar18 = tVector::Normalize((tVector *)(iVar16 + 0x80));
      iVar6 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar16 + 0x8c) = uVar18;
      if (iVar6 <= iVar4) break;
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar16 = iVar7;
    }
    iVar3 = *(int *)(param_1 + 0x4c);
  }
  fVar15 = DAT_0004f5e0;
  fVar11 = DAT_0004f5dc;
  iVar16 = *(int *)(param_1 + 0x50) + iVar6 * 0xa8;
  iVar3 = iVar3 + iVar6 * 0xa8;
  *(float *)(iVar3 + 0x8c) = DAT_0004f5dc;
  *(float *)(iVar3 + 0x88) = fVar11;
  *(float *)(iVar3 + 0x84) = fVar15;
  *(float *)(iVar3 + 0x80) = fVar15;
  *(float *)(iVar16 + 0x8c) = fVar11;
  *(float *)(iVar16 + 0x80) = fVar15;
  *(float *)(iVar16 + 0x88) = fVar11;
  *(float *)(iVar16 + 0x84) = fVar15;
  CalcLengthZ((cRPath *)param_1);
  return;
}
