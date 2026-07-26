/*
 * mangled: _ZN6cRPath19BuildTurnoverDoubleEfibPcS0_
 * demangled: cRPath::BuildTurnoverDouble(float, int, bool, char*, char*)
 * address: 0005d844
 * size: 2696
 */

/* cRPath::BuildTurnoverDouble(float, int, bool, char*, char*) */

void cRPath::BuildTurnoverDouble(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint in_fpscr;
  undefined4 uVar10;
  float fVar11;
  undefined1 *puVar12;
  float fVar13;
  float fVar15;
  undefined8 uVar14;
  float fVar16;
  int iVar17;
  undefined8 uVar18;

  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x30;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar17 = (int)((float)param_2 * 9.424778);
  fVar15 = (float)VectorSignedToFloat(iVar17,(byte)(in_fpscr >> 0x16) & 3);
  iVar5 = iVar17 + 8;
  *(int *)((int)param_1 + 0x38) = iVar5;
  uVar10 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar10;
  uVar18 = CONCAT44(fVar15 / 12.566371,iVar17);
  uVar10 = RShellMemoryMalloc(iVar5 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar10;
  uVar10 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar10;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar5 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0xa0) = 0;
      iVar6 = *(int *)((int)param_1 + 0x4c) + iVar5;
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  puVar12 = &DAT_40800000;
  uVar14 = CONCAT44(fVar15,0x3f000000);
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar15 * 0.5 - 4.0;
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
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x138) = fVar15 * (float)uVar14 - (float)puVar12;
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
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = fVar15 * (float)uVar14 - (float)puVar12;
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
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x288) = fVar15 * (float)uVar14 - (float)puVar12;
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
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x330) = fVar15 * (float)uVar14 - (float)puVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x338) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x334) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x340) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x33c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d4) = 0;
  *(undefined1 **)(*(int *)((int)param_1 + 0x4c) + 0x2d8) = puVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x32c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d4) = 0x3efae148;
  *(undefined1 **)(*(int *)((int)param_1 + 0x50) + 0x2d8) = puVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x32c) = 0x3f800000;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x3d8) = fVar15 * (float)uVar14 - (float)puVar12;
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
  iVar5 = (iVar17 + 6) * 0xa8;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x90) = fVar15 * (float)uVar14 - (float)puVar12
  ;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x4c)));
  iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
  uVar10 = VectorSignedToFloat(iVar17 + 6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar10;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar10;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  iVar5 = (iVar17 + 7) * 0xa8;
  fVar15 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x90) = fVar15 * (float)uVar14 - (float)puVar12
  ;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x4c)));
  iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
  uVar10 = VectorSignedToFloat(iVar17 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar10;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar10;
  *(undefined4 *)(iVar5 + *(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  if (0 < (int)uVar18) {
    iVar17 = 0;
    iVar5 = 0x3f0;
    do {
      iVar4 = *(int *)((int)param_1 + 0x4c);
      fVar15 = (float)VectorSignedToFloat(iVar17,(byte)(in_fpscr >> 0x16) & 3);
      fVar11 = *(float *)(iVar4 + 0x90);
      fVar16 = (float)((ulonglong)uVar14 >> 0x20);
      fVar13 = (fVar15 * 12.566371) / fVar16;
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar13 < 6.2831855) << 0x1f |
              (uint)(fVar13 == 6.2831855) << 0x1e;
      in_fpscr = uVar1 | (uint)NAN(fVar13) << 0x1c;
      bVar2 = (byte)(uVar1 >> 0x18);
      if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
        fVar13 = 12.566371 - fVar13;
      }
      fVar15 = (float)Sin((fVar15 * 6.2831855) / fVar16 + 1.5707964);
      *(float *)(iVar4 + iVar5 + 0x90) = fVar11 * fVar15;
      *(float *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x98) = -fVar13;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x94) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0xa0) = 0;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar5 + *(int *)((int)param_1 + 0x4c)));
      iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
      fVar11 = *(float *)(iVar4 + 0x90);
      uVar10 = Sin(fVar13);
      uVar14 = CONCAT44(fVar16,uVar10);
      fVar15 = (float)Sin(fVar13 * 0.5);
      *(float *)(iVar4 + 0x30) = fVar11 + (float)uVar14 * fVar15 * -2.0;
      iVar4 = iVar17 + 6;
      iVar17 = iVar17 + 1;
      uVar10 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5 + 0x38) = uVar10;
      iVar4 = *(int *)((int)param_1 + 0x4c);
      fVar15 = (float)Cos(fVar13);
      fVar11 = (float)((ulonglong)uVar18 >> 0x20);
      *(float *)(iVar5 + iVar4 + 0x34) = (fVar11 - fVar15 * fVar11) * 0.4;
      iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
      uVar10 = Sin(fVar13);
      uVar3 = Cos(fVar13);
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x10) = uVar10;
      *(undefined4 *)(iVar4 + 0x14) = uVar3;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar5;
      iVar6 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar5;
      fVar15 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar4 + 0x24) = *(float *)(iVar4 + 0x34) - fVar15;
      *(float *)(iVar4 + 0x28) = *(float *)(iVar4 + 0x38) - fVar11;
      tVector::Normalize((tVector *)(iVar5 + *(int *)((int)param_1 + 0x4c) + 0x20));
      iVar4 = iVar5 + *(int *)((int)param_1 + 0x4c);
      tVector::Cross((tVector *)(iVar5 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar4 + 0x10),
                     (tVector *)(iVar4 + 0x20));
      puVar8 = (undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar5);
      puVar9 = (undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar5);
      uVar10 = puVar8[1];
      uVar3 = puVar8[2];
      uVar7 = puVar8[3];
      *puVar9 = *puVar8;
      puVar9[1] = uVar10;
      puVar9[2] = uVar3;
      puVar9[3] = uVar7;
      uVar10 = puVar8[5];
      uVar3 = puVar8[6];
      uVar7 = puVar8[7];
      puVar9[4] = puVar8[4];
      puVar9[5] = uVar10;
      puVar9[6] = uVar3;
      puVar9[7] = uVar7;
      uVar10 = puVar8[9];
      uVar3 = puVar8[10];
      uVar7 = puVar8[0xb];
      puVar9[8] = puVar8[8];
      puVar9[9] = uVar10;
      puVar9[10] = uVar3;
      puVar9[0xb] = uVar7;
      uVar10 = puVar8[0xd];
      uVar3 = puVar8[0xe];
      uVar7 = puVar8[0xf];
      puVar9[0xc] = puVar8[0xc];
      puVar9[0xd] = uVar10;
      puVar9[0xe] = uVar3;
      puVar9[0xf] = uVar7;
      iVar4 = iVar5 + *(int *)((int)param_1 + 0x50);
      iVar6 = iVar5 + *(int *)((int)param_1 + 0x4c);
      iVar5 = iVar5 + 0xa8;
      fVar11 = *(float *)(iVar6 + 0x14);
      fVar15 = *(float *)(iVar6 + 0x18);
      *(float *)(iVar4 + 0x30) = *(float *)(iVar4 + 0x30) + *(float *)(iVar6 + 0x10) * 0.49;
      *(float *)(iVar4 + 0x34) = *(float *)(iVar4 + 0x34) + fVar11 * 0.49;
      *(float *)(iVar4 + 0x38) = *(float *)(iVar4 + 0x38) + fVar15 * 0.49;
    } while (iVar17 != (int)uVar18);
  }
  iVar5 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar5 + -1) {
    iVar4 = 0;
    iVar17 = 0;
    do {
      iVar4 = iVar4 + 1;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar17;
      iVar6 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar17;
      fVar15 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar15 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar11 - *(float *)(iVar5 + 0x38);
      iVar5 = iVar17 + *(int *)((int)param_1 + 0x4c);
      uVar10 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      *(undefined4 *)(iVar5 + 0x8c) = uVar10;
      iVar5 = *(int *)((int)param_1 + 0x50) + iVar17;
      iVar6 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar17;
      fVar15 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x84) = fVar15 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x88) = fVar11 - *(float *)(iVar5 + 0x38);
      iVar5 = iVar17 + *(int *)((int)param_1 + 0x50);
      uVar10 = tVector::Normalize((tVector *)(iVar5 + 0x80));
      iVar17 = iVar17 + 0xa8;
      *(undefined4 *)(iVar5 + 0x8c) = uVar10;
      iVar5 = *(int *)((int)param_1 + 0x38);
    } while (iVar4 < iVar5 + -1);
  }
  iVar5 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar5 * 0xa8;
  *(undefined4 *)(iVar5 + 0x84) = 0;
  *(undefined4 *)(iVar5 + 0x80) = 0;
  *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar5 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar5 + 0x84) = 0;
  *(undefined4 *)(iVar5 + 0x80) = 0;
  *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
