/*
 * mangled: _ZN6cRPath11BuildShimmyEfibPcS0_
 * demangled: cRPath::BuildShimmy(float, int, bool, char*, char*)
 * address: 00051f8c
 * size: 964
 */

/* cRPath::BuildShimmy(float, int, bool, char*, char*) */

void cRPath::BuildShimmy(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *this;
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  tMatrix *ptVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  uint in_fpscr;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 uVar18;
  float fVar19;
  float fVar20;
  float fVar21;

  uVar18 = DAT_00052354;
  *(undefined4 *)(param_2 + 0x40) = DAT_00052350;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = uVar18;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar15 = DAT_00052358;
  *(undefined4 *)(param_2 + 0x2c) = 0x36;
  *(undefined4 *)(param_2 + 0x38) = 0x20;
  fVar17 = DAT_0005235c;
  GetNodes((cRPath *)param_2);
  iVar3 = *(int *)(param_2 + 0x48);
  ptVar6 = *(tMatrix **)(param_2 + 0x4c);
  *(float *)(ptVar6 + 0x98) = fVar15;
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(float *)(ptVar6 + 0x94) = fVar15;
  uVar2 = DAT_00052364;
  fVar19 = DAT_00052360;
  if (iVar3 != 1) {
    fVar17 = fVar15;
  }
  iVar8 = DAT_00052374 + 0x5200c;
  *(float *)(ptVar6 + 0x90) = fVar17;
  tMatrix::Identity(ptVar6);
  iVar3 = *(int *)(param_2 + 0x4c);
  ptVar6 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x8c) = uVar18;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(float *)(iVar3 + 0x34) = fVar15;
  *(float *)(iVar3 + 0x38) = fVar15;
  tMatrix::Identity(ptVar6);
  iVar3 = *(int *)(param_2 + 0x4c);
  iVar4 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar4 + 0x8c) = uVar18;
  *(float *)(iVar4 + 0x34) = fVar19;
  *(float *)(iVar4 + 0x38) = fVar15;
  *(float *)(iVar3 + 0x14f0) = fVar15;
  *(float *)(iVar3 + 0x14ec) = fVar15;
  *(float *)(iVar3 + 0x14e8) = fVar17;
  tMatrix::Identity((tMatrix *)(iVar3 + 0x1458));
  iVar4 = *(int *)(param_2 + 0x4c);
  iVar3 = *(int *)(param_2 + 0x50);
  *(float *)(iVar4 + 0x148c) = fVar15;
  *(undefined4 *)(iVar4 + 0x1488) = *(undefined4 *)(iVar4 + 0x14e8);
  *(undefined4 *)(iVar4 + 0x14e4) = uVar18;
  *(undefined4 *)(iVar4 + 0x1490) = uVar2;
  fVar14 = (float)tMatrix::Identity((tMatrix *)(iVar3 + 0x1458));
  iVar3 = *(int *)(param_2 + 0x50);
  uVar1 = *(int *)(param_2 + 0x48) - 1;
  iVar4 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar3 + 0x14e4) = uVar18;
  uVar18 = *(undefined4 *)(iVar4 + 0x14e8);
  *(float *)(iVar3 + 0x148c) = fVar19;
  *(undefined4 *)(iVar3 + 0x1490) = uVar2;
  *(undefined4 *)(iVar3 + 0x1488) = uVar18;
  fVar17 = DAT_00052360;
  fVar15 = DAT_00052358;
  uVar18 = DAT_00052354;
  fVar19 = DAT_00052368;
  if (uVar1 < 8) {
    fVar19 = *(float *)(iVar8 + DAT_00052378 + uVar1 * 4);
  }
  fVar21 = *(float *)(iVar4 + 0x90);
  iVar8 = 0;
  iVar3 = 0;
  do {
    iVar8 = iVar8 + 1;
    iVar9 = iVar3 + 0xa8;
    fVar14 = (float)Sin(fVar14);
    fVar20 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar9);
    *(float *)(ptVar6 + 0x98) = fVar15;
    *(float *)(ptVar6 + 0x94) = fVar15;
    *(float *)(iVar4 + iVar9 + 0x90) = fVar21 + fVar14 * fVar19;
    tMatrix::Identity(ptVar6);
    iVar3 = *(int *)(param_2 + 0x4c) + iVar3;
    iVar4 = *(int *)(param_2 + 0x4c) + iVar9;
    *(float *)(iVar4 + 0x34) = fVar15;
    *(float *)(iVar4 + 0x38) = fVar20;
    fVar14 = *(float *)(iVar3 + 0x34);
    fVar21 = *(float *)(iVar3 + 0x38);
    *(float *)(iVar4 + 0x18) = fVar15;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x14) = uVar18;
    *(float *)(iVar4 + 0x10) = fVar15;
    *(float *)(iVar4 + 0x20) = fVar15;
    *(float *)(iVar4 + 0x24) = fVar15 - fVar14;
    *(float *)(iVar4 + 0x28) = fVar20 - fVar21;
    tVector::Normalize((tVector *)(iVar4 + 0x20));
    this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar9);
    fVar14 = (float)tVector::Cross(this,this + 0x10,this + 0x20);
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar13 = *(int *)(param_2 + 0x50);
    puVar11 = (undefined4 *)(iVar4 + iVar9);
    puVar10 = (undefined4 *)(iVar13 + iVar9);
    uVar2 = puVar11[1];
    uVar5 = puVar11[2];
    uVar7 = puVar11[3];
    *puVar10 = *puVar11;
    puVar10[1] = uVar2;
    puVar10[2] = uVar5;
    puVar10[3] = uVar7;
    uVar2 = puVar11[5];
    uVar5 = puVar11[6];
    uVar7 = puVar11[7];
    puVar10[4] = puVar11[4];
    puVar10[5] = uVar2;
    puVar10[6] = uVar5;
    puVar10[7] = uVar7;
    uVar2 = puVar11[9];
    uVar5 = puVar11[10];
    uVar7 = puVar11[0xb];
    puVar10[8] = puVar11[8];
    puVar10[9] = uVar2;
    puVar10[10] = uVar5;
    puVar10[0xb] = uVar7;
    uVar2 = puVar11[0xd];
    uVar5 = puVar11[0xe];
    uVar7 = puVar11[0xf];
    puVar10[0xc] = puVar11[0xc];
    puVar10[0xd] = uVar2;
    puVar10[0xe] = uVar5;
    puVar10[0xf] = uVar7;
    fVar20 = (float)puVar11[6];
    fVar16 = (float)puVar11[5];
    fVar21 = *(float *)(iVar4 + 0x90);
    puVar10[0xc] = fVar21;
    puVar10[0xe] = (float)puVar10[0xe] + fVar17 * fVar20;
    puVar10[0xd] = (float)puVar10[0xd] + fVar17 * fVar16;
    iVar3 = iVar9;
  } while (iVar8 != 0x1e);
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar3 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar9 = 0;
    iVar8 = 0;
    while( true ) {
      iVar12 = iVar8 + 0xa8;
      iVar13 = iVar4 + iVar8;
      iVar4 = iVar4 + iVar12;
      fVar17 = *(float *)(iVar4 + 0x38);
      fVar15 = *(float *)(iVar4 + 0x34);
      iVar9 = iVar9 + 1;
      *(float *)(iVar13 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar13 + 0x30);
      *(float *)(iVar13 + 0x84) = fVar15 - *(float *)(iVar13 + 0x34);
      *(float *)(iVar13 + 0x88) = fVar17 - *(float *)(iVar13 + 0x38);
      uVar18 = tVector::Normalize((tVector *)(iVar13 + 0x80));
      iVar8 = *(int *)(param_2 + 0x50) + iVar8;
      iVar3 = *(int *)(param_2 + 0x50) + iVar12;
      fVar17 = *(float *)(iVar3 + 0x38);
      fVar15 = *(float *)(iVar3 + 0x34);
      fVar19 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar15 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar13 + 0x8c) = uVar18;
      *(float *)(iVar8 + 0x88) = fVar17 - fVar19;
      uVar18 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar3 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar18;
      if (iVar3 <= iVar9) break;
      iVar4 = *(int *)(param_2 + 0x4c);
      iVar8 = iVar12;
    }
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar13 = *(int *)(param_2 + 0x50);
  }
  fVar15 = DAT_00052358;
  uVar18 = DAT_00052354;
  iVar13 = iVar13 + iVar3 * 0xa8;
  iVar4 = iVar4 + iVar3 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = DAT_00052354;
  *(undefined4 *)(iVar4 + 0x88) = uVar18;
  *(float *)(iVar4 + 0x84) = fVar15;
  *(float *)(iVar4 + 0x80) = fVar15;
  *(undefined4 *)(iVar13 + 0x8c) = uVar18;
  *(float *)(iVar13 + 0x80) = fVar15;
  *(undefined4 *)(iVar13 + 0x88) = uVar18;
  *(float *)(iVar13 + 0x84) = fVar15;
  CalcLengthZ((cRPath *)param_2);
  return;
}
