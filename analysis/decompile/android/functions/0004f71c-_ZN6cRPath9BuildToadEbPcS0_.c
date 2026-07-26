/*
 * mangled: _ZN6cRPath9BuildToadEbPcS0_
 * demangled: cRPath::BuildToad(bool, char*, char*)
 * address: 0004f71c
 * size: 1176
 */

/* cRPath::BuildToad(bool, char*, char*) */

void cRPath::BuildToad(bool param_1,char *param_2,char *param_3)

{
  cRPath *this;
  tVector *this_00;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  bool bVar13;
  uint in_fpscr;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;
  int local_58;

  this = (cRPath *)(uint)param_1;
  bVar13 = param_2 != (char *)0x0;
  uVar17 = 0x41e80000;
  if (bVar13) {
    uVar2 = 0x1e;
    uVar17 = 0x41f00000;
  }
  else {
    uVar2 = 0x1d;
  }
  this[0x30] = (cRPath)0x0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x40) = uVar17;
  *(undefined4 *)(this + 0x38) = uVar2;
  *(undefined4 *)(this + 0x44) = 0x3f800000;
  *(undefined4 *)(this + 0x2c) = 0x31;
  *(undefined4 *)(this + 0x48) = 4;
  if (bVar13) {
    iVar1 = 1;
  }
  else {
    iVar1 = 2;
  }
  iVar7 = 0;
  if (bVar13) {
    iVar10 = 0x1b;
    iVar11 = 3;
  }
  else {
    iVar10 = 0x1c;
    iVar11 = 1;
  }
  iVar9 = 0;
  fVar15 = -2.0;
  if (!bVar13) {
    fVar15 = 2.0;
  }
  GetNodes(this);
  this[0x84] = (cRPath)0x0;
  iVar3 = *(int *)(this + 0x4c);
  do {
    uVar17 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(float *)(ptVar4 + 0x90) = fVar15;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(this + 0x50);
    iVar5 = *(int *)(this + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(this + 0x4c);
    iVar5 = *(int *)(this + 0x50) + iVar7;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    uVar17 = *(undefined4 *)(iVar3 + iVar7 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar17;
  } while (iVar9 < iVar1);
  iVar9 = 0;
  iVar7 = iVar10 * 0xa8;
  do {
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(float *)(ptVar4 + 0x90) = fVar15;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    tMatrix::Identity(ptVar4);
    uVar17 = VectorSignedToFloat(iVar10 + iVar9,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = iVar9 + 1;
    iVar3 = *(int *)(this + 0x50);
    iVar5 = *(int *)(this + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    fVar14 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(this + 0x4c);
    iVar5 = *(int *)(this + 0x50) + iVar7;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
    uVar17 = *(undefined4 *)(iVar3 + iVar7 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar17;
  } while (iVar9 < iVar11);
  iVar11 = 0;
  iVar10 = (iVar1 + -1) * 0xa8;
  iVar7 = iVar1 * 0xa8;
  do {
    VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    Cos(fVar14);
    ptVar4 = (tMatrix *)(*(int *)(this + 0x4c) + iVar7);
    *(float *)(ptVar4 + 0x90) = fVar15;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    fVar14 = (float)tMatrix::Identity(ptVar4);
    iVar5 = *(int *)(this + 0x4c);
    fVar14 = (float)Sin(fVar14);
    fVar18 = (float)VectorSignedToFloat(iVar1 + iVar11,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = *(int *)(this + 0x4c) + iVar10;
    iVar3 = *(int *)(this + 0x4c) + iVar7;
    *(undefined4 *)(iVar3 + 0x34) = 0;
    fVar16 = *(float *)(iVar9 + 0x34);
    *(undefined4 *)(iVar3 + 0x18) = 0;
    *(undefined4 *)(iVar3 + 0x14) = 0x3f800000;
    *(undefined4 *)(iVar3 + 0x10) = 0;
    iVar11 = iVar11 + 1;
    iVar10 = iVar10 + 0xa8;
    *(float *)(iVar3 + 0x38) = fVar18;
    *(float *)(iVar3 + 0x28) = fVar18 - *(float *)(iVar9 + 0x38);
    *(float *)(iVar3 + 0x24) = 0.0 - fVar16;
    *(float *)(iVar5 + iVar7 + 0x30) = fVar14 + fVar14 + fVar15;
    *(float *)(iVar3 + 0x20) = *(float *)(iVar3 + 0x30) - *(float *)(iVar9 + 0x30);
    tVector::Normalize((tVector *)(iVar3 + 0x20));
    this_00 = (tVector *)(*(int *)(this + 0x4c) + iVar7);
    fVar14 = (float)tVector::Cross(this_00,this_00 + 0x10,this_00 + 0x20);
    fVar14 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(this + 0x4c) + iVar7),fVar14);
    iVar9 = *(int *)(this + 0x4c);
    local_58 = *(int *)(this + 0x50);
    puVar12 = (undefined4 *)(iVar9 + iVar7);
    puVar8 = (undefined4 *)(local_58 + iVar7);
    uVar17 = puVar12[1];
    uVar2 = puVar12[2];
    uVar6 = puVar12[3];
    iVar7 = iVar7 + 0xa8;
    *puVar8 = *puVar12;
    puVar8[1] = uVar17;
    puVar8[2] = uVar2;
    puVar8[3] = uVar6;
    uVar17 = puVar12[5];
    uVar2 = puVar12[6];
    uVar6 = puVar12[7];
    puVar8[4] = puVar12[4];
    puVar8[5] = uVar17;
    puVar8[6] = uVar2;
    puVar8[7] = uVar6;
    uVar17 = puVar12[9];
    uVar2 = puVar12[10];
    uVar6 = puVar12[0xb];
    puVar8[8] = puVar12[8];
    puVar8[9] = uVar17;
    puVar8[10] = uVar2;
    puVar8[0xb] = uVar6;
    uVar17 = puVar12[0xd];
    uVar2 = puVar12[0xe];
    uVar6 = puVar12[0xf];
    puVar8[0xc] = puVar12[0xc];
    puVar8[0xd] = uVar17;
    puVar8[0xe] = uVar2;
    puVar8[0xf] = uVar6;
    fVar16 = (float)puVar12[5];
    fVar18 = (float)puVar12[6];
    puVar8[0xc] = (float)puVar8[0xc] + (float)puVar12[4] * 0.49;
    puVar8[0xd] = (float)puVar8[0xd] + fVar16 * 0.49;
    puVar8[0xe] = (float)puVar8[0xe] + fVar18 * 0.49;
  } while (iVar11 != 0x1a);
  if (*(int *)(this + 0x38) < 2) {
    iVar1 = *(int *)(this + 0x38) + -1;
  }
  else {
    iVar11 = 0;
    iVar7 = 0;
    while( true ) {
      iVar3 = iVar7 + 0xa8;
      iVar10 = iVar9 + iVar7;
      iVar9 = iVar9 + iVar3;
      fVar14 = *(float *)(iVar9 + 0x38);
      fVar15 = *(float *)(iVar9 + 0x34);
      iVar11 = iVar11 + 1;
      *(float *)(iVar10 + 0x80) = *(float *)(iVar9 + 0x30) - *(float *)(iVar10 + 0x30);
      *(float *)(iVar10 + 0x84) = fVar15 - *(float *)(iVar10 + 0x34);
      *(float *)(iVar10 + 0x88) = fVar14 - *(float *)(iVar10 + 0x38);
      uVar17 = tVector::Normalize((tVector *)(iVar10 + 0x80));
      iVar7 = *(int *)(this + 0x50) + iVar7;
      iVar1 = *(int *)(this + 0x50) + iVar3;
      fVar14 = *(float *)(iVar1 + 0x38);
      fVar15 = *(float *)(iVar1 + 0x34);
      fVar16 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar15 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar10 + 0x8c) = uVar17;
      *(float *)(iVar7 + 0x88) = fVar14 - fVar16;
      uVar17 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar1 = *(int *)(this + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar17;
      if (iVar1 <= iVar11) break;
      iVar9 = *(int *)(this + 0x4c);
      iVar7 = iVar3;
    }
    local_58 = *(int *)(this + 0x50);
    iVar9 = *(int *)(this + 0x4c);
  }
  local_58 = local_58 + iVar1 * 0xa8;
  iVar9 = iVar9 + iVar1 * 0xa8;
  *(undefined4 *)(iVar9 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar9 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar9 + 0x84) = 0;
  *(undefined4 *)(iVar9 + 0x80) = 0;
  *(undefined4 *)(local_58 + 0x8c) = 0x3f800000;
  *(undefined4 *)(local_58 + 0x80) = 0;
  *(undefined4 *)(local_58 + 0x88) = 0x3f800000;
  *(undefined4 *)(local_58 + 0x84) = 0;
  CalcLengthZ(this);
  return;
}
