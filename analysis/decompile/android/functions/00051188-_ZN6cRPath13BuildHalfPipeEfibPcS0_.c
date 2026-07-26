/*
 * mangled: _ZN6cRPath13BuildHalfPipeEfibPcS0_
 * demangled: cRPath::BuildHalfPipe(float, int, bool, char*, char*)
 * address: 00051188
 * size: 1248
 */

/* cRPath::BuildHalfPipe(float, int, bool, char*, char*) */

void cRPath::BuildHalfPipe(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  tVector *this;
  undefined4 uVar2;
  tMatrix *ptVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  uint in_fpscr;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;

  iVar6 = 0;
  iVar8 = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0x39;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x40) = 0x42840000;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0x42;
  fVar12 = (float)GetNodes((cRPath *)param_2);
  *(undefined1 *)(param_2 + 0x84) = 0;
  do {
    uVar16 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = iVar8 + 1;
    fVar12 = (float)Sin(fVar12);
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    *(float *)(ptVar3 + 0x90) = fVar13 * 0.5 - 4.0;
    fVar12 = ((fVar12 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)(ptVar3 + 0xa0) = (fVar12 * fVar12 + 16.0) / (fVar12 + fVar12);
    tMatrix::Identity(ptVar3);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = uVar16;
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar6));
    iVar1 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar4 + 0x38) = uVar16;
    uVar16 = *(undefined4 *)(iVar1 + iVar6 + 0x90);
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar16;
  } while (iVar8 != 0x10);
  iVar6 = 0x20d0;
  iVar8 = 0;
  do {
    VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    fVar12 = (float)Sin(fVar12);
    fVar13 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar6);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    *(float *)(ptVar3 + 0x90) = fVar13 * -0.5 + 4.0;
    fVar12 = ((fVar12 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)(ptVar3 + 0xa0) = (fVar12 * fVar12 + 16.0) / (fVar12 + fVar12);
    tMatrix::Identity(ptVar3);
    uVar16 = VectorSignedToFloat(iVar8 + 0x32,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = iVar8 + 1;
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = uVar16;
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar6));
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar1 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar1 + 0x38) = uVar16;
    *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
    uVar16 = *(undefined4 *)(iVar4 + iVar6 + 0x90);
    *(undefined4 *)(iVar1 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar1 + 0x30) = uVar16;
  } while (iVar8 != 0x10);
  iVar6 = 0xa80;
  iVar8 = 0;
  do {
    fVar14 = *(float *)(iVar4 + 0x90);
    fVar12 = *(float *)(iVar4 + 0x2160);
    ptVar3 = (tMatrix *)(iVar4 + iVar6);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0x40800000;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    fVar13 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = fVar14 + ((fVar12 - fVar14) * fVar13) / 34.0;
    tMatrix::Identity(ptVar3);
    fVar15 = (float)VectorSignedToFloat(iVar8 + 0x10,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = iVar8 + 1;
    iVar1 = *(int *)(param_2 + 0x4c) + iVar6 + -0xa8;
    iVar4 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar4 + 0x30) = 0;
    *(undefined4 *)(iVar4 + 0x34) = 0;
    fVar13 = *(float *)(iVar1 + 0x30);
    fVar14 = *(float *)(iVar1 + 0x34);
    *(undefined4 *)(iVar4 + 0x18) = 0;
    *(float *)(iVar4 + 0x38) = fVar15;
    fVar12 = *(float *)(iVar1 + 0x38);
    *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x10) = 0;
    *(float *)(iVar4 + 0x20) = 0.0 - fVar13;
    *(float *)(iVar4 + 0x28) = fVar15 - fVar12;
    *(float *)(iVar4 + 0x24) = 0.0 - fVar14;
    tVector::Normalize((tVector *)(iVar4 + 0x20));
    this = (tVector *)(*(int *)(param_2 + 0x4c) + iVar6);
    tVector::Cross(this,this + 0x10,this + 0x20);
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar1 = *(int *)(param_2 + 0x50);
    puVar10 = (undefined4 *)(iVar4 + iVar6);
    puVar7 = (undefined4 *)(iVar1 + iVar6);
    iVar6 = iVar6 + 0xa8;
    uVar16 = puVar10[1];
    uVar2 = puVar10[2];
    uVar5 = puVar10[3];
    *puVar7 = *puVar10;
    puVar7[1] = uVar16;
    puVar7[2] = uVar2;
    puVar7[3] = uVar5;
    uVar16 = puVar10[5];
    uVar2 = puVar10[6];
    uVar5 = puVar10[7];
    puVar7[4] = puVar10[4];
    puVar7[5] = uVar16;
    puVar7[6] = uVar2;
    puVar7[7] = uVar5;
    uVar16 = puVar10[9];
    uVar2 = puVar10[10];
    uVar5 = puVar10[0xb];
    puVar7[8] = puVar10[8];
    puVar7[9] = uVar16;
    puVar7[10] = uVar2;
    puVar7[0xb] = uVar5;
    uVar16 = puVar10[0xd];
    uVar2 = puVar10[0xe];
    uVar5 = puVar10[0xf];
    puVar7[0xc] = puVar10[0xc];
    puVar7[0xd] = uVar16;
    puVar7[0xe] = uVar2;
    puVar7[0xf] = uVar5;
    fVar12 = (float)puVar10[5];
    fVar13 = (float)puVar10[6];
    puVar7[0xc] = (float)puVar7[0xc] + (float)puVar10[4] * 0.49;
    puVar7[0xd] = (float)puVar7[0xd] + fVar12 * 0.49;
    puVar7[0xe] = (float)puVar7[0xe] + fVar13 * 0.49;
  } while (iVar8 != 0x22);
  if (*(int *)(param_2 + 0x38) < 2) {
    iVar6 = *(int *)(param_2 + 0x38) + -1;
  }
  else {
    iVar1 = 0;
    iVar8 = 0;
    while( true ) {
      iVar11 = iVar8 + 0xa8;
      iVar9 = iVar4 + iVar8;
      iVar4 = iVar4 + iVar11;
      fVar13 = *(float *)(iVar4 + 0x38);
      fVar12 = *(float *)(iVar4 + 0x34);
      iVar1 = iVar1 + 1;
      *(float *)(iVar9 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x84) = fVar12 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x88) = fVar13 - *(float *)(iVar9 + 0x38);
      uVar16 = tVector::Normalize((tVector *)(iVar9 + 0x80));
      iVar8 = *(int *)(param_2 + 0x50) + iVar8;
      iVar6 = *(int *)(param_2 + 0x50) + iVar11;
      fVar13 = *(float *)(iVar6 + 0x38);
      fVar12 = *(float *)(iVar6 + 0x34);
      fVar14 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar12 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar9 + 0x8c) = uVar16;
      *(float *)(iVar8 + 0x88) = fVar13 - fVar14;
      uVar16 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar6 = *(int *)(param_2 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar16;
      if (iVar6 <= iVar1) break;
      iVar4 = *(int *)(param_2 + 0x4c);
      iVar8 = iVar11;
    }
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar1 = *(int *)(param_2 + 0x50);
  }
  iVar1 = iVar1 + iVar6 * 0xa8;
  iVar4 = iVar4 + iVar6 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x80) = 0;
  *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_2);
  return;
}
