/*
 * mangled: _ZN6cRPath9BuildToadEbPcS0_
 * demangled: cRPath::BuildToad(bool, char*, char*)
 * address: 00054194
 * size: 1728
 */

/* cRPath::BuildToad(bool, char*, char*) */

void cRPath::BuildToad(bool param_1,char *param_2,char *param_3)

{
  cRPath *this;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  bool bVar11;
  uint in_fpscr;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined8 uVar16;

  this = (cRPath *)(uint)param_1;
  bVar11 = ((uint)param_2 & 0xff) != 0;
  if (bVar11) {
    uVar1 = 0xc0000000;
  }
  else {
    uVar1 = 0x40000000;
  }
  uVar12 = 0x41f00000;
  *(undefined4 *)(this + 0x2c) = 0x31;
  if (bVar11) {
    uVar16 = CONCAT44(0xbf800000,uVar1);
  }
  else {
    uVar16 = CONCAT44(0x3f800000,uVar1);
  }
  *(undefined4 *)(this + 0x48) = 4;
  if (bVar11) {
    iVar4 = 0x1b;
  }
  else {
    iVar4 = 0x1c;
    uVar12 = 0x41e80000;
  }
  this[0x30] = (cRPath)0x0;
  *(undefined4 *)(this + 0x34) = 0;
  if (bVar11) {
    iVar5 = 0x1e;
    iVar3 = 3;
  }
  else {
    iVar5 = 0x1d;
    iVar3 = 1;
  }
  *(undefined4 *)(this + 0x44) = 0x3f800000;
  *(int *)(this + 0x38) = iVar5;
  *(undefined4 *)(this + 0x40) = uVar12;
  if (bVar11) {
    iVar8 = 1;
  }
  else {
    iVar8 = 2;
  }
  uVar1 = RShellMemoryMalloc(iVar5 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(this + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)(this + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(this + 0x50) = uVar1;
  if (0 < *(int *)(this + 0x38)) {
    iVar2 = 0;
    iVar5 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar5 + 0xa0) = 0;
      iVar6 = *(int *)(this + 0x4c) + iVar5;
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar2 < *(int *)(this + 0x38));
  }
  this[0x84] = (cRPath)0x0;
  if (iVar8 != 0) {
    iVar2 = 0;
    iVar5 = 0;
    do {
      *(int *)(*(int *)(this + 0x4c) + iVar2 + 0x90) = (int)uVar16;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x98) = 0;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x94) = 0;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0xa0) = 0;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(this + 0x4c)));
      iVar6 = iVar5 + 1;
      uVar1 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar2 + *(int *)(this + 0x4c) + 0x30) =
           *(undefined4 *)(iVar2 + *(int *)(this + 0x4c) + 0x90);
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x34) = 0;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x38) = uVar1;
      *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x8c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(this + 0x50)));
      *(undefined4 *)(*(int *)(this + 0x50) + iVar2 + 0x30) =
           *(undefined4 *)(*(int *)(this + 0x4c) + iVar2 + 0x90);
      *(undefined4 *)(*(int *)(this + 0x50) + iVar2 + 0x34) = 0x3efae148;
      *(undefined4 *)(*(int *)(this + 0x50) + iVar2 + 0x38) = uVar1;
      iVar5 = *(int *)(this + 0x50) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
      iVar5 = iVar6;
    } while (iVar6 != iVar8);
  }
  if (iVar3 != 0) {
    iVar2 = 0;
    iVar5 = iVar4 * 0xa8;
    do {
      *(int *)(iVar5 + *(int *)(this + 0x4c) + 0x90) = (int)uVar16;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x98) = 0;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x94) = 0;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0xa0) = 0;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x9c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(this + 0x4c)));
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x30) =
           *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x90);
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x34) = 0;
      iVar6 = iVar4 + iVar2;
      iVar2 = iVar2 + 1;
      uVar1 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x38) = uVar1;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x8c) = 0x3f800000;
      tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(this + 0x50)));
      *(undefined4 *)(iVar5 + *(int *)(this + 0x50) + 0x30) =
           *(undefined4 *)(iVar5 + *(int *)(this + 0x4c) + 0x90);
      *(undefined4 *)(iVar5 + *(int *)(this + 0x50) + 0x34) = 0x3efae148;
      *(undefined4 *)(iVar5 + *(int *)(this + 0x50) + 0x38) = uVar1;
      iVar6 = iVar5 + *(int *)(this + 0x50);
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
    } while (iVar2 != iVar3);
  }
  iVar5 = 0;
  iVar4 = iVar8 * 0xa8;
  do {
    fVar14 = 1.0;
    fVar13 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar13 = (float)Cos((fVar13 * 6.2831855) / 26.0);
    *(int *)(*(int *)(this + 0x4c) + iVar4 + 0x90) = (int)uVar16;
    *(undefined4 *)(*(int *)(this + 0x4c) + iVar4 + 0x98) = 0;
    *(undefined4 *)(*(int *)(this + 0x4c) + iVar4 + 0x94) = 0;
    *(undefined4 *)(*(int *)(this + 0x4c) + iVar4 + 0xa0) = 0;
    *(float *)(*(int *)(this + 0x4c) + iVar4 + 0x9c) = fVar14;
    fVar15 = (fVar14 - fVar13) * 0.5 * (float)((ulonglong)uVar16 >> 0x20) * 3.1415927 * 0.5;
    tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(this + 0x4c)));
    iVar3 = *(int *)(this + 0x4c);
    fVar13 = (float)Sin(fVar15);
    *(float *)(iVar4 + iVar3 + 0x30) = fVar13 + fVar13 + (float)uVar16;
    iVar3 = iVar5 + iVar8;
    iVar5 = iVar5 + 1;
    uVar1 = VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)(this + 0x4c) + iVar4 + 0x38) = uVar1;
    *(undefined4 *)(*(int *)(this + 0x4c) + iVar4 + 0x34) = 0;
    iVar3 = iVar4 + *(int *)(this + 0x4c);
    *(float *)(iVar3 + 0x14) = fVar14;
    *(undefined4 *)(iVar3 + 0x18) = 0;
    *(undefined4 *)(iVar3 + 0x10) = 0;
    iVar3 = *(int *)(this + 0x4c) + iVar4;
    iVar2 = *(int *)(this + 0x4c) + -0xa8 + iVar4;
    fVar13 = *(float *)(iVar2 + 0x34);
    fVar14 = *(float *)(iVar2 + 0x38);
    *(float *)(iVar3 + 0x20) = *(float *)(iVar3 + 0x30) - *(float *)(iVar2 + 0x30);
    *(float *)(iVar3 + 0x24) = *(float *)(iVar3 + 0x34) - fVar13;
    *(float *)(iVar3 + 0x28) = *(float *)(iVar3 + 0x38) - fVar14;
    tVector::Normalize((tVector *)(iVar4 + *(int *)(this + 0x4c) + 0x20));
    iVar3 = iVar4 + *(int *)(this + 0x4c);
    tVector::Cross((tVector *)(iVar4 + *(int *)(this + 0x4c)),(tVector *)(iVar3 + 0x10),
                   (tVector *)(iVar3 + 0x20));
    tMatrix::RotLocalZ((tMatrix *)(iVar4 + *(int *)(this + 0x4c)),fVar15);
    puVar9 = (undefined4 *)(*(int *)(this + 0x4c) + iVar4);
    puVar10 = (undefined4 *)(*(int *)(this + 0x50) + iVar4);
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
    iVar3 = iVar4 + *(int *)(this + 0x50);
    iVar2 = iVar4 + *(int *)(this + 0x4c);
    iVar4 = iVar4 + 0xa8;
    fVar14 = *(float *)(iVar2 + 0x14);
    fVar13 = *(float *)(iVar2 + 0x18);
    *(float *)(iVar3 + 0x30) = *(float *)(iVar3 + 0x30) + *(float *)(iVar2 + 0x10) * 0.49;
    *(float *)(iVar3 + 0x34) = *(float *)(iVar3 + 0x34) + fVar14 * 0.49;
    *(float *)(iVar3 + 0x38) = *(float *)(iVar3 + 0x38) + fVar13 * 0.49;
  } while (iVar5 != 0x1a);
  iVar4 = *(int *)(this + 0x38);
  if (0 < iVar4 + -1) {
    iVar3 = 0;
    iVar5 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar4 = iVar5 + *(int *)(this + 0x4c);
      iVar8 = iVar5 + *(int *)(this + 0x4c) + 0xa8;
      fVar13 = *(float *)(iVar8 + 0x34);
      fVar14 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar13 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar14 - *(float *)(iVar4 + 0x38);
      iVar4 = *(int *)(this + 0x4c);
      uVar1 = tVector::Normalize((tVector *)(iVar5 + iVar4 + 0x80));
      *(undefined4 *)(iVar5 + iVar4 + 0x8c) = uVar1;
      iVar4 = iVar5 + *(int *)(this + 0x50);
      iVar8 = iVar5 + *(int *)(this + 0x50) + 0xa8;
      fVar13 = *(float *)(iVar8 + 0x34);
      fVar14 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar13 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar14 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar5 + *(int *)(this + 0x50);
      uVar1 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar4 + 0x8c) = uVar1;
      iVar4 = *(int *)(this + 0x38);
    } while (iVar3 < iVar4 + -1);
  }
  iVar4 = *(int *)(this + 0x4c) + -0xa8 + iVar4 * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(this + 0x38) * 0xa8 + *(int *)(this + 0x4c) + -0x1c) = 0x3f800000;
  iVar4 = *(int *)(this + 0x50) + -0xa8 + *(int *)(this + 0x38) * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(this + 0x38) * 0xa8 + *(int *)(this + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ(this);
  return;
}
