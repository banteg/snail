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
  float fVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  tMatrix *ptVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  uint in_fpscr;
  float fVar14;
  float fVar15;
  int iVar16;
  undefined4 uVar17;
  float extraout_s15;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  char in_stack_00000000;

  fVar19 = DAT_0004f22c;
  fVar15 = (float)param_5 * DAT_0004f228;
  *(undefined4 *)(param_1 + 0x2c) = 0x12;
  *(uint *)(param_1 + 0x48) = (uint)param_4;
  fVar22 = DAT_0004f230;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(float *)(param_1 + 0x44) = fVar22;
  *(undefined4 *)(param_1 + 0x34) = 0;
  fVar1 = DAT_0004f238;
  fVar20 = DAT_0004f234;
  iVar16 = (int)(fVar15 * fVar19);
  uVar17 = VectorSignedToFloat(iVar16 + 1,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_1 + 0x38) = iVar16 + 1;
  *(undefined4 *)(param_1 + 0x40) = uVar17;
  fVar22 = fVar20;
  if (param_4 == 1) {
    fVar22 = fVar19;
  }
  GetNodes((cRPath *)param_1);
  bVar13 = in_stack_00000000 == '\0';
  fVar15 = extraout_s15;
  if (bVar13) {
    fVar15 = DAT_0004f23c;
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if (bVar13) {
    ptVar4 = *(tMatrix **)(param_1 + 0x4c);
    fVar22 = fVar22 - fVar15;
    fVar15 = *(float *)(param_1 + 0x48);
  }
  else {
    ptVar4 = *(tMatrix **)(param_1 + 0x4c);
    fVar20 = fVar22 + fVar20;
  }
  if (!bVar13) {
    *(float *)(ptVar4 + 0x90) = fVar20;
  }
  fVar20 = DAT_0004f234;
  *(float *)(ptVar4 + 0x98) = DAT_0004f234;
  *(float *)(ptVar4 + 0x94) = fVar20;
  *(float *)(ptVar4 + 0xa0) = fVar20;
  if (bVar13) {
    fVar15 = (float)VectorSignedToFloat(fVar15,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar4 + 0x90) = fVar22 + fVar15 * fVar19;
  }
  fVar19 = DAT_0004f230;
  *(float *)(ptVar4 + 0x9c) = DAT_0004f230;
  tMatrix::Identity(ptVar4);
  iVar5 = *(int *)(param_1 + 0x4c);
  ptVar4 = *(tMatrix **)(param_1 + 0x50);
  *(float *)(iVar5 + 0x38) = fVar20;
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  *(float *)(iVar5 + 0x34) = fVar20;
  tMatrix::Identity(ptVar4);
  iVar12 = *(int *)(param_1 + 0x50);
  *(float *)(iVar12 + 0x38) = fVar20;
  iVar5 = *(int *)(param_1 + 0x4c);
  *(float *)(iVar12 + 0x34) = fVar1;
  uVar17 = *(undefined4 *)(iVar5 + 0x90);
  *(undefined4 *)(iVar12 + 0x30) = uVar17;
  fVar22 = DAT_0004f22c;
  if (0 < iVar16) {
    iVar11 = 0;
    VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
    iVar12 = 0;
    while( true ) {
      iVar8 = iVar12 + 0xa8;
      ptVar4 = (tMatrix *)(iVar5 + iVar8);
      *(undefined4 *)(ptVar4 + 0x90) = uVar17;
      *(float *)(ptVar4 + 0x98) = fVar20;
      *(float *)(ptVar4 + 0x94) = fVar20;
      *(float *)(ptVar4 + 0xa0) = fVar20;
      *(float *)(ptVar4 + 0x9c) = fVar19;
      iVar11 = iVar11 + 1;
      fVar15 = (float)tMatrix::Identity(ptVar4);
      iVar7 = *(int *)(param_1 + 0x4c) + iVar8;
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      fVar15 = (float)Cos(fVar15);
      fVar21 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
      iVar12 = *(int *)(param_1 + 0x4c) + iVar12;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
      fVar18 = *(float *)(iVar12 + 0x30);
      *(float *)(iVar5 + 0x18) = fVar20;
      *(float *)(iVar5 + 0x14) = fVar20;
      *(float *)(iVar5 + 0x10) = fVar19;
      *(float *)(iVar5 + 0x38) = fVar21;
      fVar14 = *(float *)(iVar12 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar5 + 0x30) - fVar18;
      *(float *)(iVar5 + 0x28) = fVar21 - fVar14;
      *(float *)(iVar7 + 0x34) = (fVar19 - fVar15) * fVar22 * (float)param_5;
      *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x34) - *(float *)(iVar12 + 0x34);
      tVector::Normalize((tVector *)(iVar5 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar8);
      tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      iVar5 = *(int *)(param_1 + 0x4c);
      puVar10 = (undefined4 *)(iVar5 + iVar8);
      iVar12 = *(int *)(param_1 + 0x50);
      puVar9 = (undefined4 *)(iVar12 + iVar8);
      uVar17 = puVar10[1];
      uVar3 = puVar10[2];
      uVar6 = puVar10[3];
      *puVar9 = *puVar10;
      puVar9[1] = uVar17;
      puVar9[2] = uVar3;
      puVar9[3] = uVar6;
      uVar17 = puVar10[5];
      uVar3 = puVar10[6];
      uVar6 = puVar10[7];
      puVar9[4] = puVar10[4];
      puVar9[5] = uVar17;
      puVar9[6] = uVar3;
      puVar9[7] = uVar6;
      uVar17 = puVar10[9];
      uVar3 = puVar10[10];
      uVar6 = puVar10[0xb];
      puVar9[8] = puVar10[8];
      puVar9[9] = uVar17;
      puVar9[10] = uVar3;
      puVar9[0xb] = uVar6;
      uVar17 = puVar10[0xd];
      uVar3 = puVar10[0xe];
      uVar6 = puVar10[0xf];
      puVar9[0xc] = puVar10[0xc];
      puVar9[0xd] = uVar17;
      puVar9[0xe] = uVar3;
      puVar9[0xf] = uVar6;
      fVar15 = (float)puVar10[5];
      fVar14 = (float)puVar10[6];
      puVar9[0xc] = (float)puVar9[0xc] + fVar1 * (float)puVar10[4];
      puVar9[0xd] = (float)puVar9[0xd] + fVar1 * fVar15;
      puVar9[0xe] = (float)puVar9[0xe] + fVar1 * fVar14;
      if (iVar16 <= iVar11) break;
      uVar17 = *(undefined4 *)(iVar5 + 0x90);
      iVar12 = iVar8;
    }
  }
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar16 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar11 = 0;
    iVar12 = 0;
    while( true ) {
      iVar8 = iVar12 + 0xa8;
      iVar7 = iVar5 + iVar12;
      iVar5 = iVar5 + iVar8;
      fVar20 = *(float *)(iVar5 + 0x38);
      fVar22 = *(float *)(iVar5 + 0x34);
      iVar11 = iVar11 + 1;
      *(float *)(iVar7 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar22 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar20 - *(float *)(iVar7 + 0x38);
      uVar17 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar12 = *(int *)(param_1 + 0x50) + iVar12;
      iVar16 = *(int *)(param_1 + 0x50) + iVar8;
      fVar20 = *(float *)(iVar16 + 0x38);
      fVar22 = *(float *)(iVar16 + 0x34);
      fVar19 = *(float *)(iVar12 + 0x38);
      *(float *)(iVar12 + 0x80) = *(float *)(iVar16 + 0x30) - *(float *)(iVar12 + 0x30);
      *(float *)(iVar12 + 0x84) = fVar22 - *(float *)(iVar12 + 0x34);
      *(undefined4 *)(iVar7 + 0x8c) = uVar17;
      *(float *)(iVar12 + 0x88) = fVar20 - fVar19;
      uVar17 = tVector::Normalize((tVector *)(iVar12 + 0x80));
      iVar16 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar12 + 0x8c) = uVar17;
      if (iVar16 <= iVar11) break;
      iVar5 = *(int *)(param_1 + 0x4c);
      iVar12 = iVar8;
    }
    iVar5 = *(int *)(param_1 + 0x4c);
    iVar12 = *(int *)(param_1 + 0x50);
  }
  fVar20 = DAT_0004f234;
  fVar22 = DAT_0004f230;
  iVar12 = iVar12 + iVar16 * 0xa8;
  iVar5 = iVar5 + iVar16 * 0xa8;
  *(float *)(iVar5 + 0x8c) = DAT_0004f230;
  *(float *)(iVar5 + 0x88) = fVar22;
  *(float *)(iVar5 + 0x84) = fVar20;
  *(float *)(iVar5 + 0x80) = fVar20;
  *(float *)(iVar12 + 0x8c) = fVar22;
  *(float *)(iVar12 + 0x80) = fVar20;
  *(float *)(iVar12 + 0x88) = fVar22;
  *(float *)(iVar12 + 0x84) = fVar20;
  CalcLengthZ((cRPath *)param_1);
  return;
}
