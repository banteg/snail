/*
 * mangled: _ZN6cRPath13BuildHalfPipeEfibPcS0_
 * demangled: cRPath::BuildHalfPipe(float, int, bool, char*, char*)
 * address: 0005ad70
 * size: 1716
 */

/* cRPath::BuildHalfPipe(float, int, bool, char*, char*) */

void cRPath::BuildHalfPipe(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x39;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x42;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42840000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x2b50,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar1;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  iVar4 = 0;
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  do {
    fVar12 = 16.0;
    fVar13 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    iVar4 = iVar4 + 1;
    fVar3 = (float)Sin((fVar13 / 16.0) * 3.1415927 + 1.5707964);
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar3 = ((fVar3 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) = fVar11 * 0.5 - 4.0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) =
         (fVar12 + fVar3 * fVar3) / (fVar3 + fVar3);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = fVar13;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(float *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = fVar13;
    iVar5 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
  } while (iVar4 != 0x10);
  iVar2 = 0;
  puVar8 = &UNK_000020d0;
  do {
    fVar12 = 16.0;
    uVar14 = 0x3f800000;
    fVar3 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    fVar3 = (float)Sin((1.0 - fVar3 / 16.0) * 3.1415927 + 1.5707964);
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar3 = ((fVar3 * -0.5 + 0.5) * 0.95 + 0.05) * 4.0;
    *(float *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x90) = fVar11 * -0.5 + 4.0;
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(float *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0xa0) =
         (fVar12 + fVar3 * fVar3) / (fVar3 + fVar3);
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x9c) = uVar14;
    tMatrix::Identity((tMatrix *)(puVar8 + *(int *)((int)param_1 + 0x4c)));
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x30) =
         *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar4 = iVar2 + 0x32;
    iVar2 = iVar2 + 1;
    uVar1 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar1;
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x8c) = uVar14;
    tMatrix::Identity((tMatrix *)(puVar8 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x50) + 0x30) =
         *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar1;
    *(undefined4 *)(puVar8 + *(int *)((int)param_1 + 0x50) + 0x8c) = uVar14;
    puVar8 = puVar8 + 0xa8;
  } while (iVar2 != 0x10);
  iVar4 = 0;
  iVar2 = 0xa80;
  do {
    iVar5 = *(int *)((int)param_1 + 0x4c);
    fVar3 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar2 + iVar5 + 0x90) =
         *(float *)(iVar5 + 0x90) +
         (fVar3 * (*(float *)(&DAT_00002160 + iVar5) - *(float *)(iVar5 + 0x90))) / 34.0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined1 **)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa0) = &DAT_40800000;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x30) = 0;
    iVar5 = iVar4 + 0x10;
    iVar4 = iVar4 + 1;
    uVar1 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar1;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x10) = 0;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    fVar3 = *(float *)(iVar6 + 0x34);
    fVar11 = *(float *)(iVar6 + 0x38);
    *(float *)(iVar5 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
    *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x34) - fVar3;
    *(float *)(iVar5 + 0x28) = *(float *)(iVar5 + 0x38) - fVar11;
    tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x20));
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    tVector::Cross((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar5 + 0x10),
                   (tVector *)(iVar5 + 0x20));
    puVar9 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c));
    puVar10 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50));
    uVar1 = puVar9[1];
    uVar14 = puVar9[2];
    uVar7 = puVar9[3];
    *puVar10 = *puVar9;
    puVar10[1] = uVar1;
    puVar10[2] = uVar14;
    puVar10[3] = uVar7;
    uVar1 = puVar9[5];
    uVar14 = puVar9[6];
    uVar7 = puVar9[7];
    puVar10[4] = puVar9[4];
    puVar10[5] = uVar1;
    puVar10[6] = uVar14;
    puVar10[7] = uVar7;
    uVar1 = puVar9[9];
    uVar14 = puVar9[10];
    uVar7 = puVar9[0xb];
    puVar10[8] = puVar9[8];
    puVar10[9] = uVar1;
    puVar10[10] = uVar14;
    puVar10[0xb] = uVar7;
    uVar1 = puVar9[0xd];
    uVar14 = puVar9[0xe];
    uVar7 = puVar9[0xf];
    puVar10[0xc] = puVar9[0xc];
    puVar10[0xd] = uVar1;
    puVar10[0xe] = uVar14;
    puVar10[0xf] = uVar7;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x50);
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar2 = iVar2 + 0xa8;
    fVar11 = *(float *)(iVar6 + 0x14);
    fVar3 = *(float *)(iVar6 + 0x18);
    *(float *)(iVar5 + 0x30) = *(float *)(iVar5 + 0x30) + *(float *)(iVar6 + 0x10) * 0.49;
    *(float *)(iVar5 + 0x34) = *(float *)(iVar5 + 0x34) + fVar11 * 0.49;
    *(float *)(iVar5 + 0x38) = *(float *)(iVar5 + 0x38) + fVar3 * 0.49;
  } while (iVar4 != 0x22);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar5 = 0;
    iVar4 = 0;
    do {
      iVar5 = iVar5 + 1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar6 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar3 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar3 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar6 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar3 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar3 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar5 < iVar2 + -1);
  }
  iVar2 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar2 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
