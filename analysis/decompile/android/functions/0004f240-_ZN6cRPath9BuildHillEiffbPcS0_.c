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
  float extraout_s13;
  float fVar10;
  int iVar11;
  float extraout_s14;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  char in_stack_00000000;

  iVar11 = (int)(float)param_6;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x2c) = 0x14;
  *(uint *)(param_1 + 0x48) = (uint)param_4;
  *(undefined1 *)(param_1 + 0x30) = 0;
  iVar6 = iVar11 + 1;
  uVar14 = VectorSignedToFloat(iVar11 + 2,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_1 + 0x38) = iVar11 + 2;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x40) = uVar14;
  GetNodes((cRPath *)param_1);
  bVar9 = in_stack_00000000 == '\0';
  if (bVar9) {
    fVar10 = *(float *)(param_1 + 0x48);
    fVar15 = 4.0;
    fVar12 = 0.5;
    ptVar2 = *(tMatrix **)(param_1 + 0x4c);
  }
  else {
    ptVar2 = *(tMatrix **)(param_1 + 0x4c);
    fVar15 = 0.0;
    fVar12 = extraout_s14;
    fVar10 = extraout_s13;
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if (bVar9) {
    fVar10 = (float)VectorSignedToFloat(fVar10,(byte)(in_fpscr >> 0x16) & 3);
  }
  else {
    *(float *)(ptVar2 + 0x90) = fVar15;
  }
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  if (bVar9) {
    *(float *)(ptVar2 + 0x90) = fVar10 * fVar12 - fVar15;
  }
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x4c);
  ptVar2 = *(tMatrix **)(param_1 + 0x50);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar3 + 0x34) = 0;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x50);
  iVar4 = *(int *)(param_1 + 0x4c);
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  if (in_stack_00000000 == '\0') {
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar2 = (tMatrix *)(iVar4 + iVar6 * 0xa8);
    *(float *)(ptVar2 + 0x90) = fVar12 * 0.5 - 4.0;
  }
  else {
    ptVar2 = (tMatrix *)(iVar4 + iVar6 * 0xa8);
    *(undefined4 *)(ptVar2 + 0x90) = 0;
  }
  iVar4 = iVar6 * 0xa8;
  uVar14 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  tMatrix::Identity(ptVar2);
  iVar6 = *(int *)(param_1 + 0x50);
  iVar3 = *(int *)(param_1 + 0x4c) + iVar4;
  *(undefined4 *)(iVar3 + 0x34) = 0;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar3 + 0x38) = uVar14;
  tMatrix::Identity((tMatrix *)(iVar6 + iVar4));
  iVar3 = *(int *)(param_1 + 0x4c);
  iVar6 = *(int *)(param_1 + 0x50) + iVar4;
  *(undefined4 *)(iVar6 + 0x38) = uVar14;
  *(undefined4 *)(iVar6 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar3 + iVar4 + 0x90);
  if (0 < iVar11) {
    VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = 0;
    iVar4 = 0;
    while( true ) {
      iVar5 = iVar6 + 0xa8;
      ptVar2 = (tMatrix *)(iVar3 + iVar5);
      *(undefined4 *)(ptVar2 + 0x90) = *(undefined4 *)(iVar3 + 0x90);
      *(undefined4 *)(ptVar2 + 0x98) = 0;
      *(undefined4 *)(ptVar2 + 0x94) = 0;
      *(undefined4 *)(ptVar2 + 0xa0) = 0;
      *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
      iVar7 = iVar4 + 1;
      fVar12 = (float)tMatrix::Identity(ptVar2);
      iVar8 = *(int *)(param_1 + 0x4c) + iVar5;
      *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
      uVar14 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar12 = (float)Cos(fVar12);
      iVar3 = *(int *)(param_1 + 0x50);
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x38) = uVar14;
      *(float *)(iVar8 + 0x34) = (1.0 - fVar12) * 0.5 * (float)param_5;
      fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar5));
      iVar3 = *(int *)(param_1 + 0x50) + iVar5;
      *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90);
      fVar12 = (float)Cos(fVar12);
      *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar5 + 0x38) = uVar14;
      *(float *)(iVar3 + 0x34) = (1.0 - fVar12) * 0.5 * (float)param_5 + 0.49;
      if (iVar4 < 1) {
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar6));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar6));
      }
      else {
        iVar4 = *(int *)(param_1 + 0x4c);
        iVar8 = iVar4 + iVar6;
        iVar3 = iVar4 + iVar5;
        fVar16 = *(float *)(iVar8 + 0x30);
        fVar15 = *(float *)(iVar3 + 0x38);
        fVar12 = *(float *)(iVar3 + 0x34);
        fVar13 = *(float *)(iVar8 + 0x34);
        fVar10 = *(float *)(iVar3 + 0x30);
        *(undefined4 *)(iVar8 + 8) = 0;
        *(undefined4 *)(iVar8 + 4) = 0;
        *(undefined4 *)(iVar4 + iVar6) = 0x3f800000;
        *(float *)(iVar8 + 0x24) = fVar12 - fVar13;
        *(float *)(iVar8 + 0x20) = fVar10 - fVar16;
        *(float *)(iVar8 + 0x28) = fVar15 - *(float *)(iVar8 + 0x38);
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar6);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
        iVar4 = *(int *)(param_1 + 0x50);
        iVar8 = iVar4 + iVar6;
        iVar3 = iVar4 + iVar5;
        fVar16 = *(float *)(iVar8 + 0x30);
        fVar15 = *(float *)(iVar3 + 0x38);
        fVar12 = *(float *)(iVar3 + 0x34);
        fVar10 = *(float *)(iVar3 + 0x30);
        fVar13 = *(float *)(iVar8 + 0x34);
        fVar17 = *(float *)(iVar8 + 0x38);
        *(undefined4 *)(iVar8 + 8) = 0;
        *(undefined4 *)(iVar4 + iVar6) = 0x3f800000;
        *(undefined4 *)(iVar8 + 4) = 0;
        *(float *)(iVar8 + 0x20) = fVar10 - fVar16;
        *(float *)(iVar8 + 0x24) = fVar12 - fVar13;
        *(float *)(iVar8 + 0x28) = fVar15 - fVar17;
        tVector::Normalize((tVector *)(iVar8 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar6);
        tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      }
      if (iVar11 <= iVar7) break;
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
    iVar11 = 0;
    while( true ) {
      iVar7 = iVar11 + 0xa8;
      iVar5 = iVar3 + iVar11;
      iVar3 = iVar3 + iVar7;
      fVar10 = *(float *)(iVar3 + 0x38);
      fVar12 = *(float *)(iVar3 + 0x34);
      iVar4 = iVar4 + 1;
      *(float *)(iVar5 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar12 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar10 - *(float *)(iVar5 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar11 = *(int *)(param_1 + 0x50) + iVar11;
      iVar6 = *(int *)(param_1 + 0x50) + iVar7;
      fVar10 = *(float *)(iVar6 + 0x38);
      fVar12 = *(float *)(iVar6 + 0x34);
      fVar15 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar12 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar5 + 0x8c) = uVar14;
      *(float *)(iVar11 + 0x88) = fVar10 - fVar15;
      uVar14 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar6 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar14;
      if (iVar6 <= iVar4) break;
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar11 = iVar7;
    }
    iVar3 = *(int *)(param_1 + 0x4c);
  }
  iVar11 = *(int *)(param_1 + 0x50) + iVar6 * 0xa8;
  iVar3 = iVar3 + iVar6 * 0xa8;
  *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_1);
  return;
}
