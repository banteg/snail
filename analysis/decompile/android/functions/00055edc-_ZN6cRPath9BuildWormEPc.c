/*
 * mangled: _ZN6cRPath9BuildWormEPc
 * demangled: cRPath::BuildWorm(char*)
 * address: 00055edc
 * size: 1120
 */

/* cRPath::BuildWorm(char*) */

void cRPath::BuildWorm(char *param_1)

{
  undefined4 uVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  int iVar4;
  tMatrix *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint in_fpscr;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;

  *(undefined4 *)(param_1 + 0x44) = DAT_00056218;
  param_1[0x2c] = '\x1c';
  uVar3 = DAT_0005621c;
  param_1[0x2d] = '\0';
  param_1[0x2e] = '\0';
  param_1[0x2f] = '\0';
  param_1[0x30] = '\0';
  *(undefined4 *)(param_1 + 0x40) = uVar3;
  param_1[0x48] = '\x10';
  param_1[0x49] = '\0';
  param_1[0x4a] = '\0';
  param_1[0x4b] = '\0';
  param_1[0x34] = '\0';
  param_1[0x35] = '\0';
  param_1[0x36] = '\0';
  param_1[0x37] = '\0';
  iVar8 = 0;
  param_1[0x38] = '\x18';
  param_1[0x39] = '\0';
  param_1[0x3a] = '\0';
  param_1[0x3b] = '\0';
  iVar10 = 0;
  GetNodes((cRPath *)param_1);
  iVar4 = *(int *)(param_1 + 0x4c);
  param_1[0x84] = '\0';
  uVar13 = DAT_00056228;
  uVar1 = DAT_00056224;
  uVar3 = DAT_00056220;
  do {
    fVar14 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(undefined4 *)(ptVar5 + 0x90) = uVar1;
    *(undefined4 *)(ptVar5 + 0x98) = uVar1;
    *(undefined4 *)(ptVar5 + 0x94) = uVar1;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar13;
    iVar10 = iVar10 + 1;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar6 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar4 + iVar8 + 0x90);
    iVar8 = iVar8 + 0xa8;
    *(float *)(iVar6 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
  } while (iVar10 != 4);
  iVar10 = 0x14;
  iVar8 = 0xd20;
  do {
    fVar14 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(undefined4 *)(ptVar5 + 0x90) = uVar1;
    *(undefined4 *)(ptVar5 + 0x98) = uVar1;
    *(undefined4 *)(ptVar5 + 0x94) = uVar1;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar13;
    iVar10 = iVar10 + 1;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar6 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar4 + iVar8 + 0x90);
    iVar8 = iVar8 + 0xa8;
    *(float *)(iVar6 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
  } while (iVar8 != 0xfc0);
  iVar10 = 1;
  iVar8 = 0x1f8;
  do {
    iVar9 = iVar8 + 0xa8;
    ptVar5 = (tMatrix *)(iVar4 + iVar9);
    *(undefined4 *)(ptVar5 + 0x90) = uVar1;
    *(undefined4 *)(ptVar5 + 0x98) = uVar1;
    *(undefined4 *)(ptVar5 + 0x94) = uVar1;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
    *(undefined4 *)(ptVar5 + 0x9c) = uVar13;
    tMatrix::Identity(ptVar5);
    fVar14 = (float)VectorSignedToFloat(iVar10 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar6 = *(int *)(param_1 + 0x4c) + iVar9;
    *(undefined4 *)(iVar6 + 0x34) = uVar3;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar6 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar4 + iVar9));
    iVar7 = *(int *)(param_1 + 0x4c);
    iVar4 = *(int *)(param_1 + 0x50) + iVar9;
    *(undefined4 *)(iVar4 + 0x34) = uVar3;
    iVar6 = iVar7 + iVar9;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(float *)(iVar4 + 0x38) = fVar14 * *(float *)(param_1 + 0x44);
    if (iVar10 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar7 + iVar8));
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar8));
    }
    else {
      iVar7 = iVar7 + iVar8;
      fVar12 = *(float *)(iVar6 + 0x38);
      fVar14 = *(float *)(iVar6 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x30);
      *(undefined4 *)(iVar7 + 0x18) = uVar1;
      *(undefined4 *)(iVar7 + 0x14) = uVar13;
      *(undefined4 *)(iVar7 + 0x10) = uVar1;
      *(float *)(iVar7 + 0x24) = fVar14 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x20) = fVar11 - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x28) = fVar12 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar8);
      tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      ptVar2 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar8);
      tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      iVar4 = *(int *)(param_1 + 0x50) + iVar9;
      iVar6 = *(int *)(param_1 + 0x50) + iVar8;
      fVar12 = *(float *)(iVar4 + 0x38);
      fVar14 = *(float *)(iVar4 + 0x34);
      fVar11 = *(float *)(iVar4 + 0x30);
      *(undefined4 *)(iVar6 + 0x18) = uVar1;
      *(undefined4 *)(iVar6 + 0x14) = uVar13;
      *(undefined4 *)(iVar6 + 0x10) = uVar1;
      *(float *)(iVar6 + 0x24) = fVar14 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x20) = fVar11 - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x28) = fVar12 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_1 + 0x50) + iVar8);
      tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      ptVar2 = (tVector *)(*(int *)(param_1 + 0x50) + iVar8);
      tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      if (0xf < iVar10) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar4 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar10 = 0;
          iVar8 = 0;
          do {
            iVar7 = iVar8 + 0xa8;
            iVar10 = iVar10 + 1;
            iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
            iVar4 = *(int *)(param_1 + 0x4c) + iVar7;
            fVar11 = *(float *)(iVar4 + 0x38);
            fVar14 = *(float *)(iVar4 + 0x34);
            *(float *)(iVar6 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar6 + 0x30);
            *(float *)(iVar6 + 0x84) = fVar14 - *(float *)(iVar6 + 0x34);
            *(float *)(iVar6 + 0x88) = fVar11 - *(float *)(iVar6 + 0x38);
            uVar3 = tVector::Normalize((tVector *)(iVar6 + 0x80));
            iVar8 = *(int *)(param_1 + 0x50) + iVar8;
            iVar4 = *(int *)(param_1 + 0x50) + iVar7;
            fVar11 = *(float *)(iVar4 + 0x38);
            fVar14 = *(float *)(iVar4 + 0x34);
            fVar12 = *(float *)(iVar8 + 0x38);
            *(float *)(iVar8 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar8 + 0x30);
            *(float *)(iVar8 + 0x84) = fVar14 - *(float *)(iVar8 + 0x34);
            *(undefined4 *)(iVar6 + 0x8c) = uVar3;
            *(float *)(iVar8 + 0x88) = fVar11 - fVar12;
            uVar3 = tVector::Normalize((tVector *)(iVar8 + 0x80));
            iVar4 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar8 + 0x8c) = uVar3;
            iVar8 = iVar7;
          } while (iVar10 < iVar4);
        }
        uVar1 = DAT_00056228;
        uVar3 = DAT_00056224;
        iVar8 = *(int *)(param_1 + 0x50) + iVar4 * 0xa8;
        iVar4 = *(int *)(param_1 + 0x4c) + iVar4 * 0xa8;
        *(undefined4 *)(iVar4 + 0x88) = DAT_00056228;
        *(undefined4 *)(iVar4 + 0x84) = uVar3;
        *(undefined4 *)(iVar4 + 0x80) = uVar3;
        uVar13 = *(undefined4 *)(param_1 + 0x44);
        *(undefined4 *)(iVar8 + 0x88) = uVar1;
        *(undefined4 *)(iVar4 + 0x8c) = uVar13;
        *(undefined4 *)(iVar8 + 0x80) = uVar3;
        *(undefined4 *)(iVar8 + 0x8c) = uVar13;
        *(undefined4 *)(iVar8 + 0x84) = uVar3;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar10 = iVar10 + 1;
    iVar8 = iVar9;
  } while( true );
}
