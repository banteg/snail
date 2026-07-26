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
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  tMatrix *ptVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;
  float fVar17;
  float fVar18;

  *(undefined4 *)(param_2 + 0x40) = 0x42000000;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0x36;
  *(undefined4 *)(param_2 + 0x38) = 0x20;
  GetNodes((cRPath *)param_2);
  iVar2 = *(int *)(param_2 + 0x48);
  ptVar5 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined4 *)(ptVar5 + 0x98) = 0;
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(undefined4 *)(ptVar5 + 0x94) = 0;
  uVar15 = 0xbf000000;
  if (iVar2 != 1) {
    uVar15 = 0;
  }
  *(undefined4 *)(ptVar5 + 0x90) = uVar15;
  tMatrix::Identity(ptVar5);
  iVar2 = *(int *)(param_2 + 0x4c);
  ptVar5 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(undefined4 *)(iVar2 + 0x38) = 0;
  tMatrix::Identity(ptVar5);
  iVar2 = *(int *)(param_2 + 0x4c);
  iVar3 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
  *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar2 + 0x14f0) = 0;
  *(undefined4 *)(iVar2 + 0x14ec) = 0;
  *(undefined4 *)(iVar2 + 0x14e8) = uVar15;
  tMatrix::Identity((tMatrix *)(iVar2 + 0x1458));
  iVar3 = *(int *)(param_2 + 0x4c);
  iVar2 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x148c) = 0;
  *(undefined4 *)(iVar3 + 0x1488) = *(undefined4 *)(iVar3 + 0x14e8);
  *(undefined4 *)(iVar3 + 0x14e4) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x1490) = 0x41f80000;
  fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar2 + 0x1458));
  iVar2 = *(int *)(param_2 + 0x50);
  uVar1 = *(int *)(param_2 + 0x48) - 1;
  iVar3 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar2 + 0x14e4) = 0x3f800000;
  uVar15 = *(undefined4 *)(iVar3 + 0x14e8);
  *(undefined4 *)(iVar2 + 0x148c) = 0x3efae148;
  *(undefined4 *)(iVar2 + 0x1490) = 0x41f80000;
  *(undefined4 *)(iVar2 + 0x1488) = uVar15;
  if (uVar1 < 8) {
    fVar18 = *(float *)(&CSWTCH_686 + uVar1 * 4);
  }
  else {
    fVar18 = 0.3;
  }
  fVar17 = *(float *)(iVar3 + 0x90);
  iVar10 = 0;
  iVar2 = 0;
  do {
    iVar10 = iVar10 + 1;
    iVar7 = iVar2 + 0xa8;
    fVar13 = (float)Sin(fVar13);
    fVar16 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7);
    *(undefined4 *)(ptVar5 + 0x98) = 0;
    *(undefined4 *)(ptVar5 + 0x94) = 0;
    *(float *)(iVar3 + iVar7 + 0x90) = fVar17 + fVar13 * fVar18;
    tMatrix::Identity(ptVar5);
    iVar2 = *(int *)(param_2 + 0x4c) + iVar2;
    iVar3 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar3 + 0x34) = 0;
    *(float *)(iVar3 + 0x38) = fVar16;
    fVar13 = *(float *)(iVar2 + 0x34);
    fVar17 = *(float *)(iVar2 + 0x38);
    *(undefined4 *)(iVar3 + 0x18) = 0;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar3 + 0x10) = 0;
    *(undefined4 *)(iVar3 + 0x20) = 0;
    *(float *)(iVar3 + 0x24) = 0.0 - fVar13;
    *(float *)(iVar3 + 0x28) = fVar16 - fVar17;
    tVector::Normalize((tVector *)(iVar3 + 0x20));
    this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
    fVar13 = (float)tVector::Cross(this,this + 0x10,this + 0x20);
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar12 = *(int *)(param_2 + 0x50);
    puVar9 = (undefined4 *)(iVar3 + iVar7);
    puVar8 = (undefined4 *)(iVar12 + iVar7);
    uVar15 = puVar9[1];
    uVar4 = puVar9[2];
    uVar6 = puVar9[3];
    *puVar8 = *puVar9;
    puVar8[1] = uVar15;
    puVar8[2] = uVar4;
    puVar8[3] = uVar6;
    uVar15 = puVar9[5];
    uVar4 = puVar9[6];
    uVar6 = puVar9[7];
    puVar8[4] = puVar9[4];
    puVar8[5] = uVar15;
    puVar8[6] = uVar4;
    puVar8[7] = uVar6;
    uVar15 = puVar9[9];
    uVar4 = puVar9[10];
    uVar6 = puVar9[0xb];
    puVar8[8] = puVar9[8];
    puVar8[9] = uVar15;
    puVar8[10] = uVar4;
    puVar8[0xb] = uVar6;
    uVar15 = puVar9[0xd];
    uVar4 = puVar9[0xe];
    uVar6 = puVar9[0xf];
    puVar8[0xc] = puVar9[0xc];
    puVar8[0xd] = uVar15;
    puVar8[0xe] = uVar4;
    puVar8[0xf] = uVar6;
    fVar16 = (float)puVar9[6];
    fVar14 = (float)puVar9[5];
    fVar17 = *(float *)(iVar3 + 0x90);
    puVar8[0xc] = fVar17;
    puVar8[0xe] = (float)puVar8[0xe] + fVar16 * 0.49;
    puVar8[0xd] = (float)puVar8[0xd] + fVar14 * 0.49;
    iVar2 = iVar7;
  } while (iVar10 != 0x1e);
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar2 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar7 = 0;
    iVar10 = 0;
    while( true ) {
      iVar11 = iVar10 + 0xa8;
      iVar12 = iVar3 + iVar10;
      iVar3 = iVar3 + iVar11;
      fVar18 = *(float *)(iVar3 + 0x38);
      fVar13 = *(float *)(iVar3 + 0x34);
      iVar7 = iVar7 + 1;
      *(float *)(iVar12 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar12 + 0x30);
      *(float *)(iVar12 + 0x84) = fVar13 - *(float *)(iVar12 + 0x34);
      *(float *)(iVar12 + 0x88) = fVar18 - *(float *)(iVar12 + 0x38);
      uVar15 = tVector::Normalize((tVector *)(iVar12 + 0x80));
      iVar10 = *(int *)(param_2 + 0x50) + iVar10;
      iVar2 = *(int *)(param_2 + 0x50) + iVar11;
      fVar18 = *(float *)(iVar2 + 0x38);
      fVar13 = *(float *)(iVar2 + 0x34);
      fVar17 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar10 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar10 + 0x30);
      *(float *)(iVar10 + 0x84) = fVar13 - *(float *)(iVar10 + 0x34);
      *(undefined4 *)(iVar12 + 0x8c) = uVar15;
      *(float *)(iVar10 + 0x88) = fVar18 - fVar17;
      uVar15 = tVector::Normalize((tVector *)(iVar10 + 0x80));
      iVar2 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar10 + 0x8c) = uVar15;
      if (iVar2 <= iVar7) break;
      iVar3 = *(int *)(param_2 + 0x4c);
      iVar10 = iVar11;
    }
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar12 = *(int *)(param_2 + 0x50);
  }
  iVar12 = iVar12 + iVar2 * 0xa8;
  iVar3 = iVar3 + iVar2 * 0xa8;
  *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar12 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar12 + 0x80) = 0;
  *(undefined4 *)(iVar12 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar12 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
