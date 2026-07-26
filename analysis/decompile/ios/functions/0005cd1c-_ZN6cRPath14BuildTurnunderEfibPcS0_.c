/*
 * mangled: _ZN6cRPath14BuildTurnunderEfibPcS0_
 * demangled: cRPath::BuildTurnunder(float, int, bool, char*, char*)
 * address: 0005cd1c
 * size: 2792
 */

/* cRPath::BuildTurnunder(float, int, bool, char*, char*) */

void cRPath::BuildTurnunder(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint in_fpscr;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined1 *puVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  int iVar18;
  ulonglong uVar19;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x31;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar18 = (int)((float)param_2 * 6.2831855);
  fVar17 = (float)VectorSignedToFloat(iVar18,(byte)(in_fpscr >> 0x16) & 3);
  iVar4 = iVar18 + 8;
  *(int *)((int)param_1 + 0x38) = iVar4;
  uVar19 = (ulonglong)(uint)(fVar17 / 6.2831855);
  uVar10 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar10;
  iVar3 = iVar18;
  uVar10 = RShellMemoryMalloc(iVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar10;
  uVar10 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar10;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar1 = 0;
    iVar4 = 0;
    do {
      iVar1 = iVar1 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0xa0) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar4;
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar1 < *(int *)((int)param_1 + 0x38));
  }
  puVar13 = &DAT_40800000;
  fVar12 = 0.5;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  fVar15 = -0.5;
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = -(fVar11 * 0.5 - 4.0);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x138) = -(fVar11 * fVar12 - (float)puVar13);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x13c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x148) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xdc) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x134) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x134) = 0x3f800000;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = -(fVar11 * fVar12 - (float)puVar13);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e4) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1f0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x184) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1dc) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x184) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x1dc) = 0x3f800000;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x288) = -(fVar11 * fVar12 - (float)puVar13);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x290) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x28c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x298) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x294) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x228) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x22c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x230) = 0x40400000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x284) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x228) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x22c) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x230) = 0x40400000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x284) = 0x3f800000;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x330) = -(fVar11 * fVar12 - (float)puVar13);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x338) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x334) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x340) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x33c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d4) = 0;
  *(undefined1 **)(*(int *)((int)param_1 + 0x4c) + 0x2d8) = puVar13;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x32c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d4) = 0x3efae148;
  *(undefined1 **)(*(int *)((int)param_1 + 0x50) + 0x2d8) = puVar13;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x32c) = 0x3f800000;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x3d8) = -(fVar11 * fVar12 - (float)puVar13);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3e0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3dc) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 1000) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3e4) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x348));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x378) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3d8);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x37c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x380) = 0x40a00000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3d4) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x348));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x378) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3d8);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x37c) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x380) = 0x40a00000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x3d4) = 0x3f800000;
  iVar4 = (iVar18 + 6) * 0xa8;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90) = -((float)puVar13 + fVar11 * fVar15);
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
  iVar1 = iVar4 + *(int *)((int)param_1 + 0x4c);
  uVar10 = VectorSignedToFloat(iVar18 + 6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar10;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar10;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  iVar1 = (iVar18 + 7) * 0xa8;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x90) = -((float)puVar13 + fVar11 * fVar15);
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
  iVar5 = iVar1 + *(int *)((int)param_1 + 0x4c);
  uVar10 = VectorSignedToFloat(iVar18 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar10;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar10;
  *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  if (0 < iVar3) {
    iVar18 = 0;
    iVar1 = 0x3f0;
    do {
      fVar11 = (float)VectorSignedToFloat(iVar18,(byte)(in_fpscr >> 0x16) & 3);
      iVar5 = *(int *)((int)param_1 + 0x4c);
      fVar16 = (fVar11 * -6.2831855) / fVar17;
      *(float *)(iVar5 + iVar1 + 0x90) =
           *(float *)(iVar5 + 0x90) +
           (fVar11 * (*(float *)(iVar5 + iVar4 + 0x90) - *(float *)(iVar5 + 0x90))) / fVar17;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x98) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x94) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0xa0) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar1 + *(int *)((int)param_1 + 0x4c)));
      iVar5 = iVar1 + *(int *)((int)param_1 + 0x4c);
      fVar15 = *(float *)(iVar5 + 0x90);
      fVar11 = (float)Sin(fVar16);
      fVar12 = (float)Sin(fVar16 * 0.5);
      fVar14 = 3.1415927;
      *(float *)(iVar5 + 0x30) = fVar15 + fVar11 * fVar12 * -2.0;
      fVar15 = 3.0;
      uVar10 = VectorSignedToFloat(iVar18 + 6,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0x38) = uVar10;
      iVar5 = *(int *)((int)param_1 + 0x4c);
      fVar11 = (float)Cos(fVar16);
      *(float *)(iVar1 + iVar5 + 0x34) = ((float)uVar19 - fVar11 * (float)uVar19) * -0.2;
      iVar5 = iVar1 + *(int *)((int)param_1 + 0x4c);
      fVar11 = (float)Sin(fVar16);
      fVar11 = (float)Sin((fVar11 * fVar14) / fVar15);
      fVar12 = (float)Sin(fVar16);
      uVar10 = Cos((fVar12 * fVar14) / fVar15);
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(float *)(iVar5 + 0x10) = -fVar11;
      *(undefined4 *)(iVar5 + 0x14) = uVar10;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar1;
      iVar6 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar1;
      fVar11 = *(float *)(iVar6 + 0x34);
      fVar12 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x34) - fVar11;
      *(float *)(iVar5 + 0x28) = *(float *)(iVar5 + 0x38) - fVar12;
      tVector::Normalize((tVector *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0x20));
      iVar5 = iVar1 + *(int *)((int)param_1 + 0x4c);
      tVector::Cross((tVector *)(iVar1 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar5 + 0x10),
                     (tVector *)(iVar5 + 0x20));
      puVar8 = (undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1);
      puVar9 = (undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar1);
      uVar10 = puVar8[1];
      uVar2 = puVar8[2];
      uVar7 = puVar8[3];
      *puVar9 = *puVar8;
      puVar9[1] = uVar10;
      puVar9[2] = uVar2;
      puVar9[3] = uVar7;
      uVar10 = puVar8[5];
      uVar2 = puVar8[6];
      uVar7 = puVar8[7];
      puVar9[4] = puVar8[4];
      puVar9[5] = uVar10;
      puVar9[6] = uVar2;
      puVar9[7] = uVar7;
      uVar10 = puVar8[9];
      uVar2 = puVar8[10];
      uVar7 = puVar8[0xb];
      puVar9[8] = puVar8[8];
      puVar9[9] = uVar10;
      puVar9[10] = uVar2;
      puVar9[0xb] = uVar7;
      uVar10 = puVar8[0xd];
      uVar2 = puVar8[0xe];
      uVar7 = puVar8[0xf];
      puVar9[0xc] = puVar8[0xc];
      puVar9[0xd] = uVar10;
      puVar9[0xe] = uVar2;
      puVar9[0xf] = uVar7;
      iVar5 = iVar1 + *(int *)((int)param_1 + 0x50);
      iVar18 = iVar18 + 1;
      iVar6 = iVar1 + *(int *)((int)param_1 + 0x4c);
      fVar12 = *(float *)(iVar6 + 0x14);
      fVar11 = *(float *)(iVar6 + 0x18);
      iVar1 = iVar1 + 0xa8;
      *(float *)(iVar5 + 0x30) = *(float *)(iVar5 + 0x30) + *(float *)(iVar6 + 0x10) * 0.49;
      *(float *)(iVar5 + 0x34) = *(float *)(iVar5 + 0x34) + fVar12 * 0.49;
      *(float *)(iVar5 + 0x38) = *(float *)(iVar5 + 0x38) + fVar11 * 0.49;
    } while (iVar18 != iVar3);
  }
  iVar3 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar3 + -1) {
    iVar18 = 0;
    iVar4 = 0;
    do {
      iVar18 = iVar18 + 1;
      iVar3 = *(int *)((int)param_1 + 0x4c) + iVar4;
      iVar1 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar4;
      fVar17 = *(float *)(iVar1 + 0x34);
      fVar11 = *(float *)(iVar1 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar17 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar11 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar10 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      *(undefined4 *)(iVar3 + 0x8c) = uVar10;
      iVar3 = *(int *)((int)param_1 + 0x50) + iVar4;
      iVar1 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar4;
      fVar17 = *(float *)(iVar1 + 0x34);
      fVar11 = *(float *)(iVar1 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar17 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar11 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar10 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar3 + 0x8c) = uVar10;
      iVar3 = *(int *)((int)param_1 + 0x38);
    } while (iVar18 < iVar3 + -1);
  }
  iVar3 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar3 * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar3 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
