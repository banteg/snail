/*
 * mangled: _ZN6cRPath9BuildToadEbPcS0_
 * demangled: cRPath::BuildToad(bool, char*, char*)
 * address: 0004f71c
 * size: 1176
 */

/* cRPath::BuildToad(bool, char*, char*) */

void cRPath::BuildToad(bool param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  cRPath *this;
  tVector *this_00;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  tMatrix *ptVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  bool bVar14;
  uint in_fpscr;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  undefined4 uVar21;
  int local_58;

  this = (cRPath *)(uint)param_1;
  bVar14 = param_2 != (char *)0x0;
  if (bVar14) {
    uVar3 = 0x1e;
    uVar21 = DAT_0004faa0;
  }
  else {
    uVar3 = 0x1d;
    uVar21 = DAT_0004faa4;
  }
  this[0x30] = (cRPath)0x0;
  uVar1 = DAT_0004fac8;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x40) = uVar21;
  *(undefined4 *)(this + 0x38) = uVar3;
  *(undefined4 *)(this + 0x44) = uVar1;
  *(undefined4 *)(this + 0x2c) = 0x31;
  *(undefined4 *)(this + 0x48) = 4;
  fVar17 = DAT_0004facc;
  fVar16 = DAT_0004fab4;
  if (bVar14) {
    iVar2 = 1;
  }
  else {
    iVar2 = 2;
  }
  iVar8 = 0;
  if (bVar14) {
    iVar11 = 0x1b;
    iVar12 = 3;
  }
  else {
    iVar11 = 0x1c;
    iVar12 = 1;
  }
  iVar10 = 0;
  fVar20 = DAT_0004fab0;
  if (!bVar14) {
    fVar20 = DAT_0004faa8;
  }
  GetNodes(this);
  this[0x84] = (cRPath)0x0;
  iVar4 = *(int *)(this + 0x4c);
  do {
    uVar21 = VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(float *)(ptVar5 + 0x90) = fVar20;
    *(float *)(ptVar5 + 0x98) = fVar17;
    *(float *)(ptVar5 + 0x94) = fVar17;
    *(float *)(ptVar5 + 0xa0) = fVar17;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar1;
    iVar10 = iVar10 + 1;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(this + 0x50);
    iVar6 = *(int *)(this + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x8c) = uVar1;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar17;
    *(undefined4 *)(iVar6 + 0x38) = uVar21;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(this + 0x4c);
    iVar6 = *(int *)(this + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar21;
    *(undefined4 *)(iVar6 + 0x8c) = uVar1;
    uVar21 = *(undefined4 *)(iVar4 + iVar8 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar16;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = uVar21;
  } while (iVar10 < iVar2);
  iVar10 = 0;
  iVar8 = iVar11 * 0xa8;
  do {
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(float *)(ptVar5 + 0x90) = fVar20;
    *(float *)(ptVar5 + 0x98) = fVar17;
    *(float *)(ptVar5 + 0x94) = fVar17;
    *(float *)(ptVar5 + 0xa0) = fVar17;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar1;
    tMatrix::Identity(ptVar5);
    uVar21 = VectorSignedToFloat(iVar11 + iVar10,(byte)(in_fpscr >> 0x16) & 3);
    iVar10 = iVar10 + 1;
    iVar4 = *(int *)(this + 0x50);
    iVar6 = *(int *)(this + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x8c) = uVar1;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar17;
    *(undefined4 *)(iVar6 + 0x38) = uVar21;
    fVar15 = (float)tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(this + 0x4c);
    iVar6 = *(int *)(this + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar21;
    *(undefined4 *)(iVar6 + 0x8c) = uVar1;
    uVar21 = *(undefined4 *)(iVar4 + iVar8 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar16;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = uVar21;
  } while (iVar10 < iVar12);
  iVar12 = 0;
  iVar11 = (iVar2 + -1) * 0xa8;
  iVar8 = iVar2 * 0xa8;
  do {
    VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
    Cos(fVar15);
    ptVar5 = (tMatrix *)(*(int *)(this + 0x4c) + iVar8);
    *(float *)(ptVar5 + 0x90) = fVar20;
    *(float *)(ptVar5 + 0x98) = fVar17;
    *(float *)(ptVar5 + 0x94) = fVar17;
    *(float *)(ptVar5 + 0xa0) = fVar17;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar1;
    fVar15 = (float)tMatrix::Identity(ptVar5);
    iVar6 = *(int *)(this + 0x4c);
    fVar15 = (float)Sin(fVar15);
    fVar19 = (float)VectorSignedToFloat(iVar2 + iVar12,(byte)(in_fpscr >> 0x16) & 3);
    iVar10 = *(int *)(this + 0x4c) + iVar11;
    iVar4 = *(int *)(this + 0x4c) + iVar8;
    *(float *)(iVar4 + 0x34) = fVar17;
    fVar18 = *(float *)(iVar10 + 0x34);
    *(float *)(iVar4 + 0x18) = fVar17;
    *(undefined4 *)(iVar4 + 0x14) = uVar1;
    *(float *)(iVar4 + 0x10) = fVar17;
    iVar12 = iVar12 + 1;
    iVar11 = iVar11 + 0xa8;
    *(float *)(iVar4 + 0x38) = fVar19;
    *(float *)(iVar4 + 0x28) = fVar19 - *(float *)(iVar10 + 0x38);
    *(float *)(iVar4 + 0x24) = fVar17 - fVar18;
    *(float *)(iVar6 + iVar8 + 0x30) = fVar15 + fVar15 + fVar20;
    *(float *)(iVar4 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar10 + 0x30);
    tVector::Normalize((tVector *)(iVar4 + 0x20));
    this_00 = (tVector *)(*(int *)(this + 0x4c) + iVar8);
    fVar15 = (float)tVector::Cross(this_00,this_00 + 0x10,this_00 + 0x20);
    fVar15 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(this + 0x4c) + iVar8),fVar15);
    iVar10 = *(int *)(this + 0x4c);
    local_58 = *(int *)(this + 0x50);
    puVar13 = (undefined4 *)(iVar10 + iVar8);
    puVar9 = (undefined4 *)(local_58 + iVar8);
    uVar21 = puVar13[1];
    uVar3 = puVar13[2];
    uVar7 = puVar13[3];
    iVar8 = iVar8 + 0xa8;
    *puVar9 = *puVar13;
    puVar9[1] = uVar21;
    puVar9[2] = uVar3;
    puVar9[3] = uVar7;
    uVar21 = puVar13[5];
    uVar3 = puVar13[6];
    uVar7 = puVar13[7];
    puVar9[4] = puVar13[4];
    puVar9[5] = uVar21;
    puVar9[6] = uVar3;
    puVar9[7] = uVar7;
    uVar21 = puVar13[9];
    uVar3 = puVar13[10];
    uVar7 = puVar13[0xb];
    puVar9[8] = puVar13[8];
    puVar9[9] = uVar21;
    puVar9[10] = uVar3;
    puVar9[0xb] = uVar7;
    uVar21 = puVar13[0xd];
    uVar3 = puVar13[0xe];
    uVar7 = puVar13[0xf];
    puVar9[0xc] = puVar13[0xc];
    puVar9[0xd] = uVar21;
    puVar9[0xe] = uVar3;
    puVar9[0xf] = uVar7;
    fVar18 = (float)puVar13[5];
    fVar19 = (float)puVar13[6];
    puVar9[0xc] = (float)puVar9[0xc] + fVar16 * (float)puVar13[4];
    puVar9[0xd] = (float)puVar9[0xd] + fVar16 * fVar18;
    puVar9[0xe] = (float)puVar9[0xe] + fVar16 * fVar19;
  } while (iVar12 != 0x1a);
  if (*(int *)(this + 0x38) < 2) {
    iVar2 = *(int *)(this + 0x38) + -1;
  }
  else {
    iVar12 = 0;
    iVar8 = 0;
    while( true ) {
      iVar4 = iVar8 + 0xa8;
      iVar11 = iVar10 + iVar8;
      iVar10 = iVar10 + iVar4;
      fVar17 = *(float *)(iVar10 + 0x38);
      fVar16 = *(float *)(iVar10 + 0x34);
      iVar12 = iVar12 + 1;
      *(float *)(iVar11 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar11 + 0x30);
      *(float *)(iVar11 + 0x84) = fVar16 - *(float *)(iVar11 + 0x34);
      *(float *)(iVar11 + 0x88) = fVar17 - *(float *)(iVar11 + 0x38);
      uVar21 = tVector::Normalize((tVector *)(iVar11 + 0x80));
      iVar8 = *(int *)(this + 0x50) + iVar8;
      iVar2 = *(int *)(this + 0x50) + iVar4;
      fVar17 = *(float *)(iVar2 + 0x38);
      fVar16 = *(float *)(iVar2 + 0x34);
      fVar20 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar16 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar11 + 0x8c) = uVar21;
      *(float *)(iVar8 + 0x88) = fVar17 - fVar20;
      uVar21 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar2 = *(int *)(this + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar21;
      if (iVar2 <= iVar12) break;
      iVar10 = *(int *)(this + 0x4c);
      iVar8 = iVar4;
    }
    local_58 = *(int *)(this + 0x50);
    iVar10 = *(int *)(this + 0x4c);
  }
  fVar16 = DAT_0004facc;
  uVar21 = DAT_0004fac8;
  local_58 = local_58 + iVar2 * 0xa8;
  iVar10 = iVar10 + iVar2 * 0xa8;
  *(undefined4 *)(iVar10 + 0x8c) = DAT_0004fac8;
  *(undefined4 *)(iVar10 + 0x88) = uVar21;
  *(float *)(iVar10 + 0x84) = fVar16;
  *(float *)(iVar10 + 0x80) = fVar16;
  *(undefined4 *)(local_58 + 0x8c) = uVar21;
  *(float *)(local_58 + 0x80) = fVar16;
  *(undefined4 *)(local_58 + 0x88) = uVar21;
  *(float *)(local_58 + 0x84) = fVar16;
  CalcLengthZ(this);
  return;
}
