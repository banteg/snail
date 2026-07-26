/*
 * mangled: _ZN6cRPath11BuildWibbleEfibPcS0_
 * demangled: cRPath::BuildWibble(float, int, bool, char*, char*)
 * address: 0005c6e0
 * size: 1548
 */

/* cRPath::BuildWibble(float, int, bool, char*, char*) */

void cRPath::BuildWibble(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint in_fpscr;
  float fVar11;
  undefined1 *puVar12;
  float fVar13;
  float fVar14;
  uint uVar15;
  ulonglong uVar16;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x32;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x20;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42000000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x1500,"Path Tile Nodes");
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
  puVar12 = &DAT_40800000;
  iVar4 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  uVar16 = 0;
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar11 * 0.5 - 4.0;
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
  *(float *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18) =
       (float)puVar12 + fVar11 * -0.5;
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = '\0';
  pcVar6[3] = '\0';
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x1c;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = '\0';
  pcVar6[3] = '\0';
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x28;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = '\0';
  pcVar6[3] = '\0';
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = -0x80;
  pcVar6[3] = '?';
  tMatrix::Identity((tMatrix *)(section_00001438.segname + *(int *)((int)param_1 + 0x4c) + 0x10));
  *(undefined4 *)(section_0000147c.sectname + *(int *)((int)param_1 + 0x4c) + 0xc) =
       *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  pcVar6 = section_0000147c.segname + *(int *)((int)param_1 + 0x4c);
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = '\0';
  pcVar6[3] = '\0';
  pcVar6 = section_0000147c.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = -8;
  pcVar6[3] = 'A';
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x14;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = -0x80;
  pcVar6[3] = '?';
  tMatrix::Identity((tMatrix *)(section_00001438.segname + *(int *)((int)param_1 + 0x50) + 0x10));
  *(undefined4 *)(section_0000147c.sectname + *(int *)((int)param_1 + 0x50) + 0xc) =
       *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  pcVar6 = section_0000147c.segname + *(int *)((int)param_1 + 0x50);
  pcVar6[0] = 'H';
  pcVar6[1] = -0x1f;
  pcVar6[2] = -6;
  pcVar6[3] = '>';
  pcVar6 = section_0000147c.segname + *(int *)((int)param_1 + 0x50) + 4;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = -8;
  pcVar6[3] = 'A';
  pcVar6 = section_000014c0.segname + *(int *)((int)param_1 + 0x50) + 0x14;
  pcVar6[0] = '\0';
  pcVar6[1] = '\0';
  pcVar6[2] = -0x80;
  pcVar6[3] = '?';
  iVar2 = 0xa8;
  do {
    iVar5 = *(int *)((int)param_1 + 0x4c);
    fVar13 = 30.0;
    fVar11 = (float)uVar16;
    iVar4 = iVar4 + 1;
    *(float *)(iVar2 + iVar5 + 0x90) =
         *(float *)(iVar5 + 0x90) +
         (fVar11 * (*(float *)(section_000014c0.segname + iVar5 + 0x18) - *(float *)(iVar5 + 0x90)))
         / 30.0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    uVar15 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    uVar16 = (ulonglong)uVar15;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x30) = 0;
    fVar14 = 0.3;
    *(uint *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar15;
    *(undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    fVar13 = ((fVar11 * 6.2831855) / fVar13) * 3.0;
    fVar11 = (float)Sin(fVar13);
    uVar1 = Sin(fVar11 * fVar14);
    fVar11 = (float)Sin(fVar13);
    uVar3 = Cos(fVar11 * fVar14);
    *(undefined4 *)(iVar5 + 0x18) = 0;
    *(undefined4 *)(iVar5 + 0x10) = uVar1;
    *(undefined4 *)(iVar5 + 0x14) = uVar3;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar7 = iVar2 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    fVar11 = *(float *)(iVar7 + 0x34);
    fVar13 = *(float *)(iVar7 + 0x38);
    *(float *)(iVar5 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar7 + 0x30);
    *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x34) - fVar11;
    *(float *)(iVar5 + 0x28) = *(float *)(iVar5 + 0x38) - fVar13;
    tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c) + 0x20));
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x4c);
    tVector::Cross((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar5 + 0x10),
                   (tVector *)(iVar5 + 0x20));
    puVar9 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x4c));
    puVar10 = (undefined4 *)(iVar2 + *(int *)((int)param_1 + 0x50));
    uVar1 = puVar9[1];
    uVar3 = puVar9[2];
    uVar8 = puVar9[3];
    *puVar10 = *puVar9;
    puVar10[1] = uVar1;
    puVar10[2] = uVar3;
    puVar10[3] = uVar8;
    uVar1 = puVar9[5];
    uVar3 = puVar9[6];
    uVar8 = puVar9[7];
    puVar10[4] = puVar9[4];
    puVar10[5] = uVar1;
    puVar10[6] = uVar3;
    puVar10[7] = uVar8;
    uVar1 = puVar9[9];
    uVar3 = puVar9[10];
    uVar8 = puVar9[0xb];
    puVar10[8] = puVar9[8];
    puVar10[9] = uVar1;
    puVar10[10] = uVar3;
    puVar10[0xb] = uVar8;
    uVar1 = puVar9[0xd];
    uVar3 = puVar9[0xe];
    uVar8 = puVar9[0xf];
    puVar10[0xc] = puVar9[0xc];
    puVar10[0xd] = uVar1;
    puVar10[0xe] = uVar3;
    puVar10[0xf] = uVar8;
    iVar5 = iVar2 + *(int *)((int)param_1 + 0x50);
    iVar7 = iVar2 + *(int *)((int)param_1 + 0x4c);
    iVar2 = iVar2 + 0xa8;
    fVar13 = *(float *)(iVar7 + 0x14);
    fVar11 = *(float *)(iVar7 + 0x18);
    *(float *)(iVar5 + 0x30) = *(float *)(iVar5 + 0x30) + *(float *)(iVar7 + 0x10) * 0.49;
    *(float *)(iVar5 + 0x34) = *(float *)(iVar5 + 0x34) + fVar13 * 0.49;
    *(float *)(iVar5 + 0x38) = *(float *)(iVar5 + 0x38) + fVar11 * 0.49;
  } while (iVar4 != 0x1e);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar5 = 0;
    iVar4 = 0;
    do {
      iVar5 = iVar5 + 1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      iVar7 = iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar11 = *(float *)(iVar7 + 0x34);
      fVar13 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar4 + *(int *)((int)param_1 + 0x50);
      iVar7 = iVar4 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar11 = *(float *)(iVar7 + 0x34);
      fVar13 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
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
