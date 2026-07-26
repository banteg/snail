/*
 * mangled: _ZN6cRPath10BuildSBendEiffbPcS0_
 * demangled: cRPath::BuildSBend(int, float, float, bool, char*, char*)
 * address: 0004ee74
 * size: 948
 */

/* cRPath::BuildSBend(int, float, float, bool, char*, char*) */

void cRPath::BuildSBend(int param_1,float param_2,float param_3,bool param_4,char *param_5,
                       char *param_6)

{
  tVector *ptVar1;
  undefined4 uVar2;
  tMatrix *ptVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  bool bVar12;
  uint in_fpscr;
  int iVar13;
  undefined4 uVar14;
  float extraout_s15;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  char in_stack_00000000;

  *(undefined4 *)(param_1 + 0x2c) = 0x12;
  *(uint *)(param_1 + 0x48) = (uint)param_4;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x34) = 0;
  fVar16 = 0.0;
  iVar13 = (int)((float)param_5 * 6.2831855 * 0.5);
  uVar14 = VectorSignedToFloat(iVar13 + 1,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_1 + 0x38) = iVar13 + 1;
  *(undefined4 *)(param_1 + 0x40) = uVar14;
  fVar18 = fVar16;
  if (param_4 == 1) {
    fVar18 = 0.5;
  }
  GetNodes((cRPath *)param_1);
  bVar12 = in_stack_00000000 == '\0';
  fVar15 = extraout_s15;
  if (bVar12) {
    fVar15 = 4.0;
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if (bVar12) {
    ptVar3 = *(tMatrix **)(param_1 + 0x4c);
    fVar18 = fVar18 - fVar15;
    fVar15 = *(float *)(param_1 + 0x48);
  }
  else {
    ptVar3 = *(tMatrix **)(param_1 + 0x4c);
    fVar16 = fVar18 + 0.0;
  }
  if (!bVar12) {
    *(float *)(ptVar3 + 0x90) = fVar16;
  }
  *(undefined4 *)(ptVar3 + 0x98) = 0;
  *(undefined4 *)(ptVar3 + 0x94) = 0;
  *(undefined4 *)(ptVar3 + 0xa0) = 0;
  if (bVar12) {
    fVar16 = (float)VectorSignedToFloat(fVar15,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = fVar18 + fVar16 * 0.5;
  }
  *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
  tMatrix::Identity(ptVar3);
  iVar4 = *(int *)(param_1 + 0x4c);
  ptVar3 = *(tMatrix **)(param_1 + 0x50);
  *(undefined4 *)(iVar4 + 0x38) = 0;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar4 + 0x34) = 0;
  tMatrix::Identity(ptVar3);
  iVar11 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar11 + 0x38) = 0;
  iVar4 = *(int *)(param_1 + 0x4c);
  *(undefined4 *)(iVar11 + 0x34) = 0x3efae148;
  uVar14 = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar11 + 0x30) = uVar14;
  if (0 < iVar13) {
    iVar10 = 0;
    VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = 0;
    while( true ) {
      iVar7 = iVar11 + 0xa8;
      ptVar3 = (tMatrix *)(iVar4 + iVar7);
      *(undefined4 *)(ptVar3 + 0x90) = uVar14;
      *(undefined4 *)(ptVar3 + 0x98) = 0;
      *(undefined4 *)(ptVar3 + 0x94) = 0;
      *(undefined4 *)(ptVar3 + 0xa0) = 0;
      *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
      iVar10 = iVar10 + 1;
      fVar18 = (float)tMatrix::Identity(ptVar3);
      iVar6 = *(int *)(param_1 + 0x4c) + iVar7;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      fVar18 = (float)Cos(fVar18);
      fVar17 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
      iVar11 = *(int *)(param_1 + 0x4c) + iVar11;
      iVar4 = *(int *)(param_1 + 0x4c) + iVar7;
      fVar15 = *(float *)(iVar11 + 0x30);
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0;
      *(undefined4 *)(iVar4 + 0x10) = 0x3f800000;
      *(float *)(iVar4 + 0x38) = fVar17;
      fVar16 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar4 + 0x30) - fVar15;
      *(float *)(iVar4 + 0x28) = fVar17 - fVar16;
      *(float *)(iVar6 + 0x34) = (1.0 - fVar18) * 0.5 * (float)param_5;
      *(float *)(iVar4 + 0x24) = *(float *)(iVar4 + 0x34) - *(float *)(iVar11 + 0x34);
      tVector::Normalize((tVector *)(iVar4 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar7);
      tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      iVar4 = *(int *)(param_1 + 0x4c);
      puVar9 = (undefined4 *)(iVar4 + iVar7);
      iVar11 = *(int *)(param_1 + 0x50);
      puVar8 = (undefined4 *)(iVar11 + iVar7);
      uVar14 = puVar9[1];
      uVar2 = puVar9[2];
      uVar5 = puVar9[3];
      *puVar8 = *puVar9;
      puVar8[1] = uVar14;
      puVar8[2] = uVar2;
      puVar8[3] = uVar5;
      uVar14 = puVar9[5];
      uVar2 = puVar9[6];
      uVar5 = puVar9[7];
      puVar8[4] = puVar9[4];
      puVar8[5] = uVar14;
      puVar8[6] = uVar2;
      puVar8[7] = uVar5;
      uVar14 = puVar9[9];
      uVar2 = puVar9[10];
      uVar5 = puVar9[0xb];
      puVar8[8] = puVar9[8];
      puVar8[9] = uVar14;
      puVar8[10] = uVar2;
      puVar8[0xb] = uVar5;
      uVar14 = puVar9[0xd];
      uVar2 = puVar9[0xe];
      uVar5 = puVar9[0xf];
      puVar8[0xc] = puVar9[0xc];
      puVar8[0xd] = uVar14;
      puVar8[0xe] = uVar2;
      puVar8[0xf] = uVar5;
      fVar18 = (float)puVar9[5];
      fVar16 = (float)puVar9[6];
      puVar8[0xc] = (float)puVar8[0xc] + (float)puVar9[4] * 0.49;
      puVar8[0xd] = (float)puVar8[0xd] + fVar18 * 0.49;
      puVar8[0xe] = (float)puVar8[0xe] + fVar16 * 0.49;
      if (iVar13 <= iVar10) break;
      uVar14 = *(undefined4 *)(iVar4 + 0x90);
      iVar11 = iVar7;
    }
  }
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar13 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar10 = 0;
    iVar11 = 0;
    while( true ) {
      iVar7 = iVar11 + 0xa8;
      iVar6 = iVar4 + iVar11;
      iVar4 = iVar4 + iVar7;
      fVar16 = *(float *)(iVar4 + 0x38);
      fVar18 = *(float *)(iVar4 + 0x34);
      iVar10 = iVar10 + 1;
      *(float *)(iVar6 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar18 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x88) = fVar16 - *(float *)(iVar6 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar11 = *(int *)(param_1 + 0x50) + iVar11;
      iVar13 = *(int *)(param_1 + 0x50) + iVar7;
      fVar16 = *(float *)(iVar13 + 0x38);
      fVar18 = *(float *)(iVar13 + 0x34);
      fVar15 = *(float *)(iVar11 + 0x38);
      *(float *)(iVar11 + 0x80) = *(float *)(iVar13 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar18 - *(float *)(iVar11 + 0x34);
      *(undefined4 *)(iVar6 + 0x8c) = uVar14;
      *(float *)(iVar11 + 0x88) = fVar16 - fVar15;
      uVar14 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar13 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar11 + 0x8c) = uVar14;
      if (iVar13 <= iVar10) break;
      iVar4 = *(int *)(param_1 + 0x4c);
      iVar11 = iVar7;
    }
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar11 = *(int *)(param_1 + 0x50);
  }
  iVar11 = iVar11 + iVar13 * 0xa8;
  iVar4 = iVar4 + iVar13 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x80) = 0;
  *(undefined4 *)(iVar11 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar11 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_1);
  return;
}
