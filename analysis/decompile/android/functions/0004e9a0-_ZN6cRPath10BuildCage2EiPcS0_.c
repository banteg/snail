/*
 * mangled: _ZN6cRPath10BuildCage2EiPcS0_
 * demangled: cRPath::BuildCage2(int, char*, char*)
 * address: 0004e9a0
 * size: 1188
 */

/* cRPath::BuildCage2(int, char*, char*) */

void cRPath::BuildCage2(int param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  tVector *ptVar3;
  int iVar4;
  tMatrix *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint in_fpscr;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;

  uVar13 = DAT_0004ed24;
  *(char **)(param_1 + 0x48) = param_2;
  uVar1 = DAT_0004ed4c;
  *(undefined4 *)(param_1 + 0x40) = uVar13;
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x13;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0x1e;
  fVar11 = DAT_0004ed28;
  GetNodes((cRPath *)param_1);
  uVar2 = DAT_0004ed50;
  fVar15 = DAT_0004ed2c;
  fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  ptVar5 = *(tMatrix **)(param_1 + 0x4c);
  *(undefined4 *)(ptVar5 + 0x9c) = uVar1;
  *(undefined4 *)(ptVar5 + 0x98) = uVar2;
  *(undefined4 *)(ptVar5 + 0x94) = uVar2;
  *(undefined4 *)(ptVar5 + 0xa0) = uVar2;
  *(undefined1 *)(param_1 + 0x84) = 0;
  uVar13 = DAT_0004ed34;
  fVar16 = DAT_0004ed30;
  iVar10 = 0;
  *(float *)(ptVar5 + 0x90) = fVar14 * fVar15 - fVar11;
  tMatrix::Identity(ptVar5);
  iVar6 = *(int *)(param_1 + 0x4c);
  ptVar5 = *(tMatrix **)(param_1 + 0x50);
  *(undefined4 *)(iVar6 + 0x38) = uVar2;
  *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  *(undefined4 *)(iVar6 + 0x34) = uVar2;
  tMatrix::Identity(ptVar5);
  uVar12 = *(undefined4 *)(param_1 + 0x48);
  iVar4 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar4 + 0x38) = uVar2;
  iVar6 = *(int *)(param_1 + 0x4c);
  fVar14 = (float)VectorSignedToFloat(uVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  fVar15 = DAT_0004ed48;
  *(float *)(iVar4 + 0x34) = fVar16;
  *(undefined4 *)(iVar6 + 0x13a0) = uVar2;
  *(undefined4 *)(iVar6 + 0x139c) = uVar2;
  *(undefined4 *)(iVar6 + 0x13a8) = uVar2;
  *(undefined4 *)(iVar6 + 0x13a4) = uVar1;
  *(float *)(iVar6 + 0x1398) = fVar11 + fVar14 * fVar15;
  tMatrix::Identity((tMatrix *)(iVar6 + 0x1308));
  iVar4 = *(int *)(param_1 + 0x4c);
  iVar6 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar4 + 0x1340) = uVar13;
  *(undefined4 *)(iVar4 + 0x1338) = *(undefined4 *)(iVar4 + 0x1398);
  *(undefined4 *)(iVar4 + 0x133c) = uVar2;
  fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar6 + 0x1308));
  iVar6 = *(int *)(param_1 + 0x50);
  iVar4 = *(int *)(param_1 + 0x4c);
  uVar12 = *(undefined4 *)(iVar4 + 0x1398);
  *(undefined4 *)(iVar6 + 0x1340) = uVar13;
  *(float *)(iVar6 + 0x133c) = fVar16;
  *(undefined4 *)(iVar6 + 0x1338) = uVar12;
  iVar6 = 0;
  do {
    iVar10 = iVar10 + 1;
    iVar9 = iVar6 + 0xa8;
    fVar11 = (float)Cos(fVar11);
    fVar15 = *(float *)(*(int *)(param_1 + 0x4c) + 0x90);
    ptVar5 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar9);
    *(undefined4 *)(ptVar5 + 0x98) = uVar2;
    *(undefined4 *)(ptVar5 + 0x94) = uVar2;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar2;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar1;
    uVar12 = VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar4 + iVar9 + 0x90) = fVar11 * fVar15;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar7 = *(int *)(param_1 + 0x4c) + iVar9;
    *(undefined4 *)(iVar7 + 0x34) = uVar2;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x38) = uVar12;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar9));
    iVar8 = *(int *)(param_1 + 0x4c);
    iVar7 = iVar8 + iVar9;
    fVar11 = *(float *)(iVar7 + 0x34);
    iVar4 = *(int *)(param_1 + 0x50) + iVar9;
    uVar13 = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar4 + 0x38) = uVar12;
    *(undefined4 *)(iVar4 + 0x30) = uVar13;
    *(float *)(iVar4 + 0x34) = fVar11 + fVar16;
    if (iVar10 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar8 + iVar6));
      fVar11 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar6));
    }
    else {
      iVar8 = iVar8 + iVar6;
      fVar14 = *(float *)(iVar7 + 0x38);
      fVar11 = *(float *)(iVar7 + 0x30);
      fVar15 = *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar8 + 0x18) = uVar2;
      *(undefined4 *)(iVar8 + 0x14) = uVar1;
      *(undefined4 *)(iVar8 + 0x10) = uVar2;
      *(float *)(iVar8 + 0x20) = fVar11 - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x24) = fVar15 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x28) = fVar14 - *(float *)(iVar8 + 0x38);
      tVector::Normalize((tVector *)(iVar8 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar6);
      fVar11 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      iVar4 = *(int *)(param_1 + 0x4c);
      fVar11 = (float)Cos(fVar11);
      tMatrix::RotLocalZ((tMatrix *)(iVar4 + iVar6),fVar11);
      iVar4 = *(int *)(param_1 + 0x50) + iVar9;
      iVar7 = *(int *)(param_1 + 0x50) + iVar6;
      fVar14 = *(float *)(iVar4 + 0x38);
      fVar11 = *(float *)(iVar4 + 0x30);
      fVar15 = *(float *)(iVar4 + 0x34);
      *(undefined4 *)(iVar7 + 0x18) = uVar2;
      *(undefined4 *)(iVar7 + 0x14) = uVar1;
      *(undefined4 *)(iVar7 + 0x10) = uVar2;
      *(float *)(iVar7 + 0x20) = fVar11 - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x24) = fVar15 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x28) = fVar14 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_1 + 0x50) + iVar6);
      fVar11 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      iVar4 = *(int *)(param_1 + 0x50);
      fVar11 = (float)Cos(fVar11);
      fVar11 = (float)tMatrix::RotLocalZ((tMatrix *)(iVar4 + iVar6),fVar11);
      if (iVar10 == 0x1c) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar6 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar10 = 0;
          iVar4 = 0;
          do {
            iVar8 = iVar4 + 0xa8;
            iVar10 = iVar10 + 1;
            iVar7 = *(int *)(param_1 + 0x4c) + iVar4;
            iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
            fVar15 = *(float *)(iVar6 + 0x38);
            fVar11 = *(float *)(iVar6 + 0x34);
            *(float *)(iVar7 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar7 + 0x30);
            *(float *)(iVar7 + 0x84) = fVar11 - *(float *)(iVar7 + 0x34);
            *(float *)(iVar7 + 0x88) = fVar15 - *(float *)(iVar7 + 0x38);
            uVar13 = tVector::Normalize((tVector *)(iVar7 + 0x80));
            iVar4 = *(int *)(param_1 + 0x50) + iVar4;
            iVar6 = *(int *)(param_1 + 0x50) + iVar8;
            fVar15 = *(float *)(iVar6 + 0x38);
            fVar11 = *(float *)(iVar6 + 0x34);
            fVar16 = *(float *)(iVar4 + 0x38);
            *(float *)(iVar4 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar4 + 0x30);
            *(float *)(iVar4 + 0x84) = fVar11 - *(float *)(iVar4 + 0x34);
            *(undefined4 *)(iVar7 + 0x8c) = uVar13;
            *(float *)(iVar4 + 0x88) = fVar15 - fVar16;
            uVar13 = tVector::Normalize((tVector *)(iVar4 + 0x80));
            iVar6 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar4 + 0x8c) = uVar13;
            iVar4 = iVar8;
          } while (iVar10 < iVar6);
        }
        uVar1 = DAT_0004ed50;
        uVar13 = DAT_0004ed4c;
        iVar4 = *(int *)(param_1 + 0x50) + iVar6 * 0xa8;
        iVar6 = *(int *)(param_1 + 0x4c) + iVar6 * 0xa8;
        *(undefined4 *)(iVar6 + 0x8c) = DAT_0004ed4c;
        *(undefined4 *)(iVar6 + 0x88) = uVar13;
        *(undefined4 *)(iVar6 + 0x84) = uVar1;
        *(undefined4 *)(iVar6 + 0x80) = uVar1;
        *(undefined4 *)(iVar4 + 0x8c) = uVar13;
        *(undefined4 *)(iVar4 + 0x80) = uVar1;
        *(undefined4 *)(iVar4 + 0x88) = uVar13;
        *(undefined4 *)(iVar4 + 0x84) = uVar1;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar6 = iVar9;
  } while( true );
}
