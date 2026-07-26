/*
 * mangled: _ZN6cRPath12BuildInvert1EfibPcS0_
 * demangled: cRPath::BuildInvert1(float, int, bool, char*, char*)
 * address: 0005b46c
 * size: 1588
 */

/* cRPath::BuildInvert1(float, int, bool, char*, char*) */

void cRPath::BuildInvert1(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  tVector *ptVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  uint in_fpscr;
  float fVar12;
  undefined1 *puVar13;
  float fVar14;
  float fVar15;
  uint uVar16;
  ulonglong uVar17;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x38;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x22;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42080000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x1650,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar1;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar6 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 1;
  puVar13 = &DAT_40800000;
  fVar14 = 0.5;
  fVar12 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  uVar17 = 0;
  iVar4 = 0;
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar12 * 0.5 - 4.0;
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
  fVar12 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14) =
       fVar12 * fVar14 - (float)puVar13;
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x1c;
  pcVar7[0] = -0x25;
  pcVar7[1] = '\x0f';
  pcVar7[2] = 'I';
  pcVar7[3] = '@';
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x18;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\0';
  pcVar7[3] = '\0';
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\0';
  pcVar7[3] = '\0';
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = -0x80;
  pcVar7[3] = '?';
  tMatrix::Identity((tMatrix *)(section_0000158c.segname + *(int *)((int)param_1 + 0x4c) + 0xc));
  *(undefined4 *)(section_000015d0.sectname + *(int *)((int)param_1 + 0x4c) + 8) =
       *(undefined4 *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14);
  pcVar7 = section_000015d0.sectname + *(int *)((int)param_1 + 0x4c) + 0xc;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\0';
  pcVar7[3] = '\0';
  pcVar7 = section_000015d0.segname + *(int *)((int)param_1 + 0x4c);
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\x04';
  pcVar7[3] = 'B';
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x10;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = -0x80;
  pcVar7[3] = '?';
  tMatrix::Identity((tMatrix *)(section_0000158c.segname + *(int *)((int)param_1 + 0x50) + 0xc));
  *(undefined4 *)(section_000015d0.sectname + *(int *)((int)param_1 + 0x50) + 8) =
       *(undefined4 *)(section_00001614.segname + *(int *)((int)param_1 + 0x4c) + 0x14);
  pcVar7 = section_000015d0.sectname + *(int *)((int)param_1 + 0x50) + 0xc;
  pcVar7[0] = 'H';
  pcVar7[1] = -0x1f;
  pcVar7[2] = -6;
  pcVar7[3] = '>';
  pcVar7 = section_000015d0.segname + *(int *)((int)param_1 + 0x50);
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = '\x04';
  pcVar7[3] = 'B';
  pcVar7 = section_00001614.segname + *(int *)((int)param_1 + 0x50) + 0x10;
  pcVar7[0] = '\0';
  pcVar7[1] = '\0';
  pcVar7[2] = -0x80;
  pcVar7[3] = '?';
  iVar2 = 0xa8;
  do {
    iVar6 = *(int *)((int)param_1 + 0x4c);
    iVar4 = iVar4 + 1;
    fVar15 = (float)uVar17 * 6.2831855 * 0.03125;
    *(float *)(iVar2 + iVar6 + 0x90) =
         *(float *)(iVar6 + 0x90) +
         ((float)uVar17 *
         (*(float *)(section_00001614.segname + iVar6 + 0x14) - *(float *)(iVar6 + 0x90))) / 32.0;
    *(float *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x98) = -fVar15;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = *(int *)((int)param_1 + 0x4c);
    fVar14 = *(float *)(iVar6 + 0x90);
    fVar12 = (float)Cos(fVar15);
    *(float *)(iVar2 + iVar6 + 0x30) = fVar14 * fVar12;
    uVar16 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    uVar17 = (ulonglong)uVar16;
    *(uint *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar16;
    iVar6 = *(int *)((int)param_1 + 0x4c);
    fVar14 = -*(float *)(iVar6 + 0x90);
    fVar12 = (float)Sin(fVar15);
    *(float *)(iVar2 + iVar6 + 0x34) = fVar14 * fVar12;
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    uVar1 = Sin(fVar15);
    uVar3 = Cos(fVar15);
    *(undefined4 *)(iVar6 + 0x18) = 0;
    *(undefined4 *)(iVar6 + 0x10) = uVar1;
    *(undefined4 *)(iVar6 + 0x14) = uVar3;
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    fVar12 = *(float *)(iVar8 + 0x34);
    fVar14 = *(float *)(iVar8 + 0x38);
    *(float *)(iVar6 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar8 + 0x30);
    *(float *)(iVar6 + 0x24) = *(float *)(iVar6 + 0x34) - fVar12;
    *(float *)(iVar6 + 0x28) = *(float *)(iVar6 + 0x38) - fVar14;
    tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x20));
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x4c);
    tVector::Cross((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar6 + 0x10),
                   (tVector *)(iVar6 + 0x20));
    ptVar5 = (tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c));
    tVector::Cross(ptVar5 + 0x10,ptVar5 + 0x20,ptVar5);
    tMatrix::Orthoganalize((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    puVar10 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c));
    puVar11 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50));
    uVar1 = puVar10[1];
    uVar3 = puVar10[2];
    uVar9 = puVar10[3];
    *puVar11 = *puVar10;
    puVar11[1] = uVar1;
    puVar11[2] = uVar3;
    puVar11[3] = uVar9;
    uVar1 = puVar10[5];
    uVar3 = puVar10[6];
    uVar9 = puVar10[7];
    puVar11[4] = puVar10[4];
    puVar11[5] = uVar1;
    puVar11[6] = uVar3;
    puVar11[7] = uVar9;
    uVar1 = puVar10[9];
    uVar3 = puVar10[10];
    uVar9 = puVar10[0xb];
    puVar11[8] = puVar10[8];
    puVar11[9] = uVar1;
    puVar11[10] = uVar3;
    puVar11[0xb] = uVar9;
    uVar1 = puVar10[0xd];
    uVar3 = puVar10[0xe];
    uVar9 = puVar10[0xf];
    puVar11[0xc] = puVar10[0xc];
    puVar11[0xd] = uVar1;
    puVar11[0xe] = uVar3;
    puVar11[0xf] = uVar9;
    iVar6 = iVar2 + *(int *)((int)param_1 + 0x50);
    iVar8 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar2 = iVar2 + 0xa8;
    fVar14 = *(float *)(iVar8 + 0x14);
    fVar12 = *(float *)(iVar8 + 0x18);
    *(float *)(iVar6 + 0x30) = *(float *)(iVar6 + 0x30) + *(float *)(iVar8 + 0x10) * 0.49;
    *(float *)(iVar6 + 0x34) = *(float *)(iVar6 + 0x34) + fVar14 * 0.49;
    *(float *)(iVar6 + 0x38) = *(float *)(iVar6 + 0x38) + fVar12 * 0.49;
  } while (iVar4 != 0x20);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar6 = 0;
    iVar4 = 0;
    do {
      iVar6 = iVar6 + 1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar8 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar12 = *(float *)(iVar8 + 0x34);
      fVar14 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar12 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar14 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar8 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar12 = *(float *)(iVar8 + 0x34);
      fVar14 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar12 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar14 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar6 < iVar2 + -1);
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
