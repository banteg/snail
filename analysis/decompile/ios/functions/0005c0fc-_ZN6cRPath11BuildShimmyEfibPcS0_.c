/*
 * mangled: _ZN6cRPath11BuildShimmyEfibPcS0_
 * demangled: cRPath::BuildShimmy(float, int, bool, char*, char*)
 * address: 0005c0fc
 * size: 1456
 */

/* cRPath::BuildShimmy(float, int, bool, char*, char*) */

void cRPath::BuildShimmy(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint in_fpscr;
  float fVar11;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x36;
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
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  uVar12 = 0;
  uVar1 = 0xbf000000;
  if (*(int *)((int)param_1 + 0x48) != 1) {
    uVar1 = uVar12;
  }
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90) = uVar1;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = uVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = uVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = uVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18) = uVar1;
  *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x20) = uVar12;
  *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x1c) = uVar12;
  tMatrix::Identity((tMatrix *)(section_00001438.segname + *(int *)((int)param_1 + 0x4c) + 0x10));
  *(undefined4 *)(section_0000147c.sectname + *(int *)((int)param_1 + 0x4c) + 0xc) =
       *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  *(undefined4 *)(section_0000147c.segname + *(int *)((int)param_1 + 0x4c)) = uVar12;
  pcVar5 = section_0000147c.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar5[0] = '\0';
  pcVar5[1] = '\0';
  pcVar5[2] = -8;
  pcVar5[3] = 'A';
  pcVar5 = section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x14;
  pcVar5[0] = '\0';
  pcVar5[1] = '\0';
  pcVar5[2] = -0x80;
  pcVar5[3] = '?';
  tMatrix::Identity((tMatrix *)(section_00001438.segname + *(int *)((int)param_1 + 0x50) + 0x10));
  *(undefined4 *)(section_0000147c.sectname + *(int *)((int)param_1 + 0x50) + 0xc) =
       *(undefined4 *)(section_000014c0.segname + *(int *)((int)param_1 + 0x4c) + 0x18);
  pcVar5 = section_0000147c.segname + *(int *)((int)param_1 + 0x50);
  pcVar5[0] = 'H';
  pcVar5[1] = -0x1f;
  pcVar5[2] = -6;
  pcVar5[3] = '>';
  pcVar5 = section_0000147c.segname + *(int *)((int)param_1 + 0x50) + 4;
  pcVar5[0] = '\0';
  pcVar5[1] = '\0';
  pcVar5[2] = -8;
  pcVar5[3] = 'A';
  pcVar5 = section_000014c0.segname + *(int *)((int)param_1 + 0x50) + 0x14;
  pcVar5[0] = '\0';
  pcVar5[1] = '\0';
  pcVar5[2] = -0x80;
  pcVar5[3] = '?';
  iVar2 = *(int *)((int)param_1 + 0x48);
  if (iVar2 == 2) {
    fVar15 = 0.15;
  }
  else if (iVar2 == 4) {
    fVar15 = 0.2;
  }
  else if (iVar2 == 1) {
    fVar15 = 0.1;
  }
  else {
    fVar15 = 0.3;
  }
  fVar13 = 0.0;
  iVar3 = 0xa8;
  iVar2 = 0;
  do {
    iVar8 = iVar2;
    iVar4 = *(int *)((int)param_1 + 0x4c);
    iVar2 = iVar8 + 1;
    fVar14 = *(float *)(iVar4 + 0x90);
    fVar13 = (float)Sin((fVar13 * 25.132742) / 30.0);
    *(float *)(iVar3 + iVar4 + 0x90) = fVar14 + fVar13 * fVar15;
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    fVar13 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x38) = fVar13;
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x18) = 0;
    *(undefined4 *)(iVar4 + 0x10) = 0;
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    iVar6 = iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8;
    fVar14 = *(float *)(iVar6 + 0x34);
    fVar11 = *(float *)(iVar6 + 0x38);
    *(float *)(iVar4 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
    *(float *)(iVar4 + 0x24) = *(float *)(iVar4 + 0x34) - fVar14;
    *(float *)(iVar4 + 0x28) = *(float *)(iVar4 + 0x38) - fVar11;
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x20) = 0;
    tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x20));
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    tVector::Cross((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c)),(tVector *)(iVar4 + 0x10),
                   (tVector *)(iVar4 + 0x20));
    puVar9 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c));
    puVar10 = (undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50));
    uVar1 = puVar9[1];
    uVar12 = puVar9[2];
    uVar7 = puVar9[3];
    *puVar10 = *puVar9;
    puVar10[1] = uVar1;
    puVar10[2] = uVar12;
    puVar10[3] = uVar7;
    uVar1 = puVar9[5];
    uVar12 = puVar9[6];
    uVar7 = puVar9[7];
    puVar10[4] = puVar9[4];
    puVar10[5] = uVar1;
    puVar10[6] = uVar12;
    puVar10[7] = uVar7;
    uVar1 = puVar9[9];
    uVar12 = puVar9[10];
    uVar7 = puVar9[0xb];
    puVar10[8] = puVar9[8];
    puVar10[9] = uVar1;
    puVar10[10] = uVar12;
    puVar10[0xb] = uVar7;
    uVar1 = puVar9[0xd];
    uVar12 = puVar9[0xe];
    uVar7 = puVar9[0xf];
    puVar10[0xc] = puVar9[0xc];
    puVar10[0xd] = uVar1;
    puVar10[0xe] = uVar12;
    puVar10[0xf] = uVar7;
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x50);
    iVar6 = iVar3 + *(int *)((int)param_1 + 0x4c);
    fVar11 = *(float *)(iVar6 + 0x14);
    fVar14 = *(float *)(iVar6 + 0x18);
    *(float *)(iVar4 + 0x30) = *(float *)(iVar4 + 0x30) + *(float *)(iVar6 + 0x10) * 0.49;
    *(float *)(iVar4 + 0x34) = *(float *)(iVar4 + 0x34) + fVar11 * 0.49;
    *(float *)(iVar4 + 0x38) = *(float *)(iVar4 + 0x38) + fVar14 * 0.49;
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x50);
    iVar3 = iVar3 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  } while (iVar2 != 0x1e);
  iVar2 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar8 = iVar8 + -0x1d;
    iVar3 = iVar8;
    do {
      iVar3 = iVar3 + 1;
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x4c);
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar15 = *(float *)(iVar4 + 0x34);
      fVar13 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar15 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x50);
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar15 = *(float *)(iVar4 + 0x34);
      fVar13 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar15 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar13 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar8 + *(int *)((int)param_1 + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar8 = iVar8 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar1;
      iVar2 = *(int *)((int)param_1 + 0x38);
    } while (iVar3 < iVar2 + -1);
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
