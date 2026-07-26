/*
 * mangled: _ZN6cRPath10BuildSnakeEfibPcS0_
 * demangled: cRPath::BuildSnake(float, int, bool, char*, char*)
 * address: 00060d58
 * size: 2552
 */

/* cRPath::BuildSnake(float, int, bool, char*, char*) */

void cRPath::BuildSnake(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  tVector *ptVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  undefined1 *puVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x24;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x1b;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x41d80000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar2 = RShellMemoryMalloc(0x11b8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar2;
  uVar2 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar2;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar3 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      iVar6 = *(int *)((int)param_1 + 0x4c) + iVar3;
      iVar3 = iVar3 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90) = 0;
  puVar10 = &DAT_40800000;
  fVar11 = -0.5;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  iVar4 = 1;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x13c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x148) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xd8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xdc) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xe0) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xd8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e4) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1f0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x180) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x184) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x188) = 0x40000000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x180) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x184) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x290) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x28c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x298) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x294) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x228) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x22c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x230) = 0x40400000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x228) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x22c) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x230) = 0x40400000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x338) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x334) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x340) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x33c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d4) = 0;
  *(undefined1 **)(*(int *)((int)param_1 + 0x4c) + 0x2d8) = puVar10;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d4) = 0x3efae148;
  *(undefined1 **)(*(int *)((int)param_1 + 0x50) + 0x2d8) = puVar10;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3d8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3e0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3dc) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 1000) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x3e4) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x348));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x378) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x37c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x380) = 0x40a00000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x348));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x378) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x37c) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x380) = 0x40a00000;
  fVar9 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(segment_command_0000101c.segname + *(int *)((int)param_1 + 0x4c) + 0x2c) =
       (float)puVar10 + fVar9 * fVar11;
  pcVar1 = segment_command_00001054.segname + *(int *)((int)param_1 + 0x4c) + -4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001054.segname + *(int *)((int)param_1 + 0x4c) + -8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001054.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001054.segname + *(int *)((int)param_1 + 0x4c);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0xfc0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xff0) =
       *(undefined4 *)(segment_command_0000101c.segname + *(int *)((int)param_1 + 0x4c) + 0x2c);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xff4) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xff8) = 0x41c00000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0xfc0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xff0) =
       *(undefined4 *)(segment_command_0000101c.segname + *(int *)((int)param_1 + 0x4c) + 0x2c);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xff4) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xff8) = 0x41c00000;
  fVar9 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x18) =
       (float)puVar10 + fVar9 * fVar11;
  pcVar1 = section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x1c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x28;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)
                    (segment_command_00001054.segname + *(int *)((int)param_1 + 0x4c) + 0xc));
  *(undefined4 *)(section_0000108c.sectname + *(int *)((int)param_1 + 0x4c) + 0xc) =
       *(undefined4 *)(section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  pcVar1 = section_0000108c.segname + *(int *)((int)param_1 + 0x4c);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000108c.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x38;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)
                    (segment_command_00001054.segname + *(int *)((int)param_1 + 0x50) + 0xc));
  *(undefined4 *)(section_0000108c.sectname + *(int *)((int)param_1 + 0x50) + 0xc) =
       *(undefined4 *)(section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  pcVar1 = section_0000108c.segname + *(int *)((int)param_1 + 0x50);
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_0000108c.segname + *(int *)((int)param_1 + 0x50) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x38;
  pcVar1[3] = 'A';
  iVar3 = 0x3f0;
  fVar9 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_0000119c.sectname + *(int *)((int)param_1 + 0x4c) + 4) =
       (float)puVar10 + fVar9 * fVar11;
  pcVar1 = section_0000119c.sectname + *(int *)((int)param_1 + 0x4c) + 0xc;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000119c.sectname + *(int *)((int)param_1 + 0x4c) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000119c.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000119c.segname + *(int *)((int)param_1 + 0x4c);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(section_000010d0.segname + *(int *)((int)param_1 + 0x4c) + 0x30));
  *(undefined4 *)(section_00001114.segname + *(int *)((int)param_1 + 0x4c) + 0x1c) =
       *(undefined4 *)(section_0000119c.sectname + *(int *)((int)param_1 + 0x4c) + 4);
  pcVar1 = section_00001114.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_00001114.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x30;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)(section_000010d0.segname + *(int *)((int)param_1 + 0x50) + 0x30));
  *(undefined4 *)(section_00001114.segname + *(int *)((int)param_1 + 0x50) + 0x1c) =
       *(undefined4 *)(section_0000119c.sectname + *(int *)((int)param_1 + 0x4c) + 4);
  pcVar1 = section_00001114.segname + *(int *)((int)param_1 + 0x50) + 0x20;
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_00001114.segname + *(int *)((int)param_1 + 0x50) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x30;
  pcVar1[3] = 'A';
  do {
    fVar11 = 0.5;
    iVar6 = *(int *)((int)param_1 + 0x4c);
    fVar9 = (float)VectorSignedToFloat(iVar4 + -1,(byte)(in_fpscr >> 0x16) & 3);
    fVar12 = *(float *)(segment_command_0000101c.segname + iVar6 + 0x2c);
    fVar14 = (fVar9 * 6.2831855) / 18.0;
    fVar9 = (float)Cos(fVar14 * 0.5);
    fVar13 = 1.0;
    *(float *)(iVar6 + iVar3 + 0x90) = fVar12 * (fVar11 + fVar9 * -0.5);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar3 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    iVar6 = *(int *)((int)param_1 + 0x4c);
    fVar9 = (float)Cos(fVar14);
    *(float *)(iVar3 + iVar6 + 0x34) = -(fVar13 - fVar9);
    uVar2 = VectorSignedToFloat(iVar4 + 5,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x38) = uVar2;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x30) =
         *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x90);
    iVar6 = *(int *)((int)param_1 + 0x50);
    fVar9 = (float)Cos(fVar14);
    *(float *)(iVar3 + iVar6 + 0x34) = 0.49 - (fVar13 - fVar9);
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar2;
    if (iVar4 + -1 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8));
    }
    else {
      pfVar7 = (float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      *pfVar7 = fVar13;
      pfVar7[2] = 0.0;
      pfVar7[1] = 0.0;
      iVar6 = iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar8 = iVar3 + *(int *)((int)param_1 + 0x4c);
      fVar9 = *(float *)(iVar8 + 0x34);
      fVar11 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar6 + 0x20) = *(float *)(iVar8 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x24) = fVar9 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x28) = fVar11 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0x88));
      ptVar5 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
      pfVar7 = (float *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8);
      *pfVar7 = fVar13;
      pfVar7[2] = 0.0;
      pfVar7[1] = 0.0;
      iVar6 = iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar8 = iVar3 + *(int *)((int)param_1 + 0x50);
      fVar9 = *(float *)(iVar8 + 0x34);
      fVar11 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar6 + 0x20) = *(float *)(iVar8 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x24) = fVar9 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x28) = fVar11 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0x88));
      ptVar5 = (tVector *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8);
      tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
      if (0x11 < iVar4) {
        iVar3 = *(int *)((int)param_1 + 0x38);
        if (0 < iVar3 + -1) {
          iVar6 = 0;
          iVar4 = 0;
          do {
            iVar6 = iVar6 + 1;
            iVar3 = *(int *)((int)param_1 + 0x4c) + iVar4;
            iVar8 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar4;
            fVar9 = *(float *)(iVar8 + 0x34);
            fVar11 = *(float *)(iVar8 + 0x38);
            *(float *)(iVar3 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar3 + 0x30);
            *(float *)(iVar3 + 0x84) = fVar9 - *(float *)(iVar3 + 0x34);
            *(float *)(iVar3 + 0x88) = fVar11 - *(float *)(iVar3 + 0x38);
            iVar3 = iVar4 + *(int *)((int)param_1 + 0x4c);
            uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
            *(undefined4 *)(iVar3 + 0x8c) = uVar2;
            iVar3 = *(int *)((int)param_1 + 0x50) + iVar4;
            iVar8 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar4;
            fVar9 = *(float *)(iVar8 + 0x34);
            fVar11 = *(float *)(iVar8 + 0x38);
            *(float *)(iVar3 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar3 + 0x30);
            *(float *)(iVar3 + 0x84) = fVar9 - *(float *)(iVar3 + 0x34);
            *(float *)(iVar3 + 0x88) = fVar11 - *(float *)(iVar3 + 0x38);
            iVar3 = iVar4 + *(int *)((int)param_1 + 0x50);
            uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
            iVar4 = iVar4 + 0xa8;
            *(undefined4 *)(iVar3 + 0x8c) = uVar2;
            iVar3 = *(int *)((int)param_1 + 0x38);
          } while (iVar6 < iVar3 + -1);
        }
        iVar3 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar3 * 0xa8;
        *(undefined4 *)(iVar3 + 0x84) = 0;
        *(undefined4 *)(iVar3 + 0x80) = 0;
        *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) = 0x3f800000
        ;
        iVar3 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
        *(undefined4 *)(iVar3 + 0x84) = 0;
        *(undefined4 *)(iVar3 + 0x80) = 0;
        *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) = 0x3f800000
        ;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar3 = iVar3 + 0xa8;
    iVar4 = iVar4 + 1;
  } while( true );
}
