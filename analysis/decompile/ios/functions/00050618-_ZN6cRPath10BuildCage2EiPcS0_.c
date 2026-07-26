/*
 * mangled: _ZN6cRPath10BuildCage2EiPcS0_
 * demangled: cRPath::BuildCage2(int, char*, char*)
 * address: 00050618
 * size: 1696
 */

/* cRPath::BuildCage2(int, char*, char*) */

void cRPath::BuildCage2(int param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  tMatrix *ptVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined1 *puVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  *(undefined4 *)(param_1 + 0x2c) = 0x13;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x38) = 0x1e;
  *(char **)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x40) = 0x41f00000;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  uVar2 = RShellMemoryMalloc(0x13b0,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar2;
  uVar2 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar2;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar4 = 0;
    iVar3 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar3;
      iVar3 = iVar3 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)(param_1 + 0x38));
  }
  puVar11 = &DAT_40800000;
  iVar4 = 0;
  *(undefined1 *)(param_1 + 0x84) = 0;
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  fVar9 = 0.0;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x90) = fVar8 * 0.5 - 4.0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x4c));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x38) = 0;
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x1c) =
       (float)puVar11 + fVar8 * -0.5;
  pcVar1 = section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x20;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x2c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x28;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(section_000012e4.segname + *(int *)(param_1 + 0x4c) + 0x14));
  *(undefined4 *)(section_00001328.segname + *(int *)(param_1 + 0x4c)) =
       *(undefined4 *)(section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x1c);
  pcVar1 = section_00001328.segname + *(int *)(param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_00001328.segname + *(int *)(param_1 + 0x4c) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x18;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)(section_000012e4.segname + *(int *)(param_1 + 0x50) + 0x14));
  *(undefined4 *)(section_00001328.segname + *(int *)(param_1 + 0x50)) =
       *(undefined4 *)(section_0000136c.segname + *(int *)(param_1 + 0x4c) + 0x1c);
  pcVar1 = section_00001328.segname + *(int *)(param_1 + 0x50) + 4;
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_00001328.segname + *(int *)(param_1 + 0x50) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x18;
  pcVar1[3] = 'A';
  iVar3 = 0xa8;
  do {
    while( true ) {
      fVar13 = 28.0;
      iVar5 = *(int *)(param_1 + 0x4c);
      fVar12 = 1.0;
      iVar4 = iVar4 + 1;
      fVar8 = (float)Cos((fVar9 * 9.424778) / 28.0);
      *(float *)(iVar3 + iVar5 + 0x90) = fVar8 * *(float *)(*(int *)(param_1 + 0x4c) + 0x90);
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x98) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x94) = 0;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      *(float *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x9c) = fVar12;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)(param_1 + 0x4c)));
      iVar5 = iVar3 + *(int *)(param_1 + 0x4c);
      fVar8 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x34) = 0;
      *(float *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x38) = fVar8;
      tMatrix::Identity((tMatrix *)(iVar3 + *(int *)(param_1 + 0x50)));
      *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar3 + 0x30) =
           *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x90);
      *(float *)(*(int *)(param_1 + 0x50) + iVar3 + 0x34) =
           *(float *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x34) + 0.49;
      *(float *)(*(int *)(param_1 + 0x50) + iVar3 + 0x38) = fVar8;
      if (iVar4 != 1) break;
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)(param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)(param_1 + 0x50) + -0xa8));
      iVar3 = iVar3 + 0xa8;
      fVar9 = fVar8;
    }
    fVar15 = 0.3926991;
    iVar5 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar3;
    *(float *)(iVar5 + 0x14) = fVar12;
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x10) = 0;
    fVar14 = 0.5;
    iVar5 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar3;
    iVar6 = *(int *)(param_1 + 0x4c) + iVar3;
    fVar13 = (fVar9 * 6.2831855) / fVar13;
    fVar9 = *(float *)(iVar6 + 0x34);
    fVar10 = *(float *)(iVar6 + 0x38);
    *(float *)(iVar5 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
    *(float *)(iVar5 + 0x24) = fVar9 - *(float *)(iVar5 + 0x34);
    *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
    fVar9 = fVar8;
    tVector::Normalize((tVector *)(iVar3 + *(int *)(param_1 + 0x4c) + -0x88));
    iVar5 = *(int *)(param_1 + 0x4c) + -0xa8;
    iVar6 = iVar5 + iVar3;
    tVector::Cross((tVector *)(iVar5 + iVar3),(tVector *)(iVar6 + 0x10),(tVector *)(iVar6 + 0x20));
    ptVar7 = (tMatrix *)(iVar3 + *(int *)(param_1 + 0x4c) + -0xa8);
    fVar10 = *(float *)(ptVar7 + 0x90) * fVar15;
    fVar8 = (float)Cos(fVar13);
    tMatrix::RotLocalZ(ptVar7,fVar10 * (fVar12 - fVar8) * fVar14);
    iVar5 = iVar3 + *(int *)(param_1 + 0x50) + -0xa8;
    *(float *)(iVar5 + 0x14) = fVar12;
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x10) = 0;
    iVar5 = iVar3 + *(int *)(param_1 + 0x50) + -0xa8;
    iVar6 = iVar3 + *(int *)(param_1 + 0x50);
    fVar8 = *(float *)(iVar6 + 0x34);
    fVar10 = *(float *)(iVar6 + 0x38);
    *(float *)(iVar5 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
    *(float *)(iVar5 + 0x24) = fVar8 - *(float *)(iVar5 + 0x34);
    *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
    tVector::Normalize((tVector *)(iVar3 + *(int *)(param_1 + 0x50) + -0x88));
    iVar5 = *(int *)(param_1 + 0x50) + -0xa8;
    iVar6 = iVar3 + iVar5;
    tVector::Cross((tVector *)(iVar3 + iVar5),(tVector *)(iVar6 + 0x10),(tVector *)(iVar6 + 0x20));
    ptVar7 = (tMatrix *)(iVar3 + *(int *)(param_1 + 0x50) + -0xa8);
    iVar5 = iVar3 + *(int *)(param_1 + 0x4c);
    iVar3 = iVar3 + 0xa8;
    fVar15 = *(float *)(iVar5 + -0x18) * fVar15;
    fVar8 = (float)Cos(fVar13);
    tMatrix::RotLocalZ(ptVar7,fVar15 * (fVar12 - fVar8) * fVar14);
  } while (iVar4 != 0x1c);
  iVar3 = *(int *)(param_1 + 0x38);
  if (0 < iVar3 + -1) {
    iVar5 = 0;
    iVar4 = 0;
    do {
      iVar5 = iVar5 + 1;
      iVar3 = iVar4 + *(int *)(param_1 + 0x4c);
      iVar6 = iVar4 + *(int *)(param_1 + 0x4c) + 0xa8;
      fVar9 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar9 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar8 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar4 + *(int *)(param_1 + 0x4c);
      uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      *(undefined4 *)(iVar3 + 0x8c) = uVar2;
      iVar3 = iVar4 + *(int *)(param_1 + 0x50);
      iVar6 = iVar4 + *(int *)(param_1 + 0x50) + 0xa8;
      fVar9 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar9 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar8 - *(float *)(iVar3 + 0x38);
      iVar3 = iVar4 + *(int *)(param_1 + 0x50);
      uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar3 + 0x8c) = uVar2;
      iVar3 = *(int *)(param_1 + 0x38);
    } while (iVar5 < iVar3 + -1);
  }
  iVar3 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar3 * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) = 0x3f800000;
  iVar3 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
