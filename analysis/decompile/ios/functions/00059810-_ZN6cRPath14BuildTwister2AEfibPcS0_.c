/*
 * mangled: _ZN6cRPath14BuildTwister2AEfibPcS0_
 * demangled: cRPath::BuildTwister2A(float, int, bool, char*, char*)
 * address: 00059810
 * size: 1804
 */

/* cRPath::BuildTwister2A(float, int, bool, char*, char*) */

void cRPath::BuildTwister2A(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  tVector *ptVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  undefined1 *puVar12;
  ulonglong uVar11;
  float fVar13;
  float fVar14;

  uVar6 = (uint)param_4 & 0xff;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x3d;
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
      iVar7 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar7 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  puVar12 = &DAT_40800000;
  fVar13 = 0.5;
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar10 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar10 * 0.5 - 4.0;
  uVar8 = uVar6;
  if (uVar6 == 0) {
    uVar8 = *(uint *)((int)param_1 + 0x4c);
  }
  if (uVar6 == 0) {
    *(float *)(uVar8 + 0x90) = -*(float *)(uVar8 + 0x90);
  }
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  fVar10 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(&DAT_00002b38 + *(int *)((int)param_1 + 0x4c)) = fVar10 * fVar13 - (float)puVar12;
  if (uVar6 == 0) {
    *(float *)(&DAT_00002b38 + *(int *)((int)param_1 + 0x4c)) =
         -*(float *)(&DAT_00002b38 + *(int *)((int)param_1 + 0x4c));
  }
  uVar11 = 0;
  *(undefined4 *)(&DAT_00002b40 + *(int *)((int)param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002b3c + *(int *)((int)param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002b48 + *(int *)((int)param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002b44 + *(int *)((int)param_1 + 0x4c)) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(&UNK_00002aa8 + *(int *)((int)param_1 + 0x4c)));
  *(undefined4 *)(&DAT_00002ad8 + *(int *)((int)param_1 + 0x4c)) =
       *(undefined4 *)(&DAT_00002b38 + *(int *)((int)param_1 + 0x4c));
  *(undefined4 *)(&DAT_00002adc + *(int *)((int)param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002ae0 + *(int *)((int)param_1 + 0x4c)) = 0x42820000;
  tMatrix::Identity((tMatrix *)(&UNK_00002aa8 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(&DAT_00002ad8 + *(int *)((int)param_1 + 0x50)) =
       *(undefined4 *)(&DAT_00002b38 + *(int *)((int)param_1 + 0x4c));
  *(undefined4 *)(&DAT_00002adc + *(int *)((int)param_1 + 0x50)) = 0x3efae148;
  *(undefined4 *)(&DAT_00002ae0 + *(int *)((int)param_1 + 0x50)) = 0x42820000;
  iVar4 = 0xa8;
  do {
    while( true ) {
      fVar14 = 0.5;
      iVar7 = *(int *)((int)param_1 + 0x4c);
      iVar2 = iVar2 + 1;
      fVar13 = (float)uVar11 * 12.566371 * 0.015625;
      fVar10 = fVar13;
      if (uVar6 == 0) {
        fVar10 = fVar13 + 3.1415927;
      }
      fVar3 = (float)Cos(fVar10);
      *(float *)(iVar4 + iVar7 + 0x90) = (fVar14 + fVar3 * fVar14) * -5.0 + 2.5;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
      iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c);
      *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
      iVar7 = *(int *)((int)param_1 + 0x4c);
      fVar13 = (float)Sin(fVar13 * fVar14);
      fVar10 = (float)Sin(fVar10);
      *(float *)(iVar4 + iVar7 + 0x34) = fVar13 * fVar10 * (float)param_2;
      uVar8 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
      uVar11 = (ulonglong)uVar8;
      *(uint *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar8;
      tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
      *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x30) =
           *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90);
      *(float *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x34) =
           *(float *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x34) + 0.49;
      *(int *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x38) = (int)uVar11;
      if (iVar2 != 1) break;
      tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8));
      iVar4 = iVar4 + 0xa8;
    }
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x10) = 0;
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    iVar9 = iVar4 + *(int *)((int)param_1 + 0x4c);
    fVar10 = *(float *)(iVar9 + 0x34);
    fVar13 = *(float *)(iVar9 + 0x38);
    *(float *)(iVar7 + 0x20) = *(float *)(iVar9 + 0x30) - *(float *)(iVar7 + 0x30);
    *(float *)(iVar7 + 0x24) = fVar10 - *(float *)(iVar7 + 0x34);
    *(float *)(iVar7 + 0x28) = fVar13 - *(float *)(iVar7 + 0x38);
    tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0x88));
    iVar7 = *(int *)((int)param_1 + 0x4c) + -0xa8;
    iVar9 = iVar4 + iVar7;
    tVector::Cross((tVector *)(iVar4 + iVar7),(tVector *)(iVar9 + 0x10),(tVector *)(iVar9 + 0x20));
    ptVar5 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8);
    tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
    tMatrix::Orthoganalize((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8));
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar7 + 0x10) = 0;
    iVar7 = iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8;
    iVar9 = iVar4 + *(int *)((int)param_1 + 0x50);
    fVar10 = *(float *)(iVar9 + 0x34);
    fVar13 = *(float *)(iVar9 + 0x38);
    *(float *)(iVar7 + 0x20) = *(float *)(iVar9 + 0x30) - *(float *)(iVar7 + 0x30);
    *(float *)(iVar7 + 0x24) = fVar10 - *(float *)(iVar7 + 0x34);
    *(float *)(iVar7 + 0x28) = fVar13 - *(float *)(iVar7 + 0x38);
    tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0x88));
    iVar7 = *(int *)((int)param_1 + 0x50) + -0xa8;
    iVar9 = iVar4 + iVar7;
    tVector::Cross((tVector *)(iVar4 + iVar7),(tVector *)(iVar9 + 0x10),(tVector *)(iVar9 + 0x20));
    ptVar5 = (tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8);
    tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
    tMatrix::Orthoganalize((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8));
    iVar4 = iVar4 + 0xa8;
  } while (iVar2 != 0x40);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar7 = 0;
    iVar4 = 0;
    do {
      iVar7 = iVar7 + 1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar9 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar10 = *(float *)(iVar9 + 0x34);
      fVar13 = *(float *)(iVar9 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar10 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar9 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar10 = *(float *)(iVar9 + 0x34);
      fVar13 = *(float *)(iVar9 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar10 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar7 < iVar2 + -1);
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
