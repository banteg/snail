/*
 * mangled: _ZN6cRPath9BuildWormEPc
 * demangled: cRPath::BuildWorm(char*)
 * address: 00055edc
 * size: 1120
 */

/* cRPath::BuildWorm(char*) */

void cRPath::BuildWorm(char *param_1)

{
  tVector *ptVar1;
  undefined4 uVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;

  param_1[0x44] = '\0';
  param_1[0x45] = '\0';
  param_1[0x46] = -0x80;
  param_1[0x47] = '@';
  param_1[0x2c] = '\x1c';
  param_1[0x2d] = '\0';
  param_1[0x2e] = '\0';
  param_1[0x2f] = '\0';
  param_1[0x30] = '\0';
  param_1[0x40] = '\0';
  param_1[0x41] = '\0';
  param_1[0x42] = -0x40;
  param_1[0x43] = 'B';
  param_1[0x48] = '\x10';
  param_1[0x49] = '\0';
  param_1[0x4a] = '\0';
  param_1[0x4b] = '\0';
  param_1[0x34] = '\0';
  param_1[0x35] = '\0';
  param_1[0x36] = '\0';
  param_1[0x37] = '\0';
  iVar7 = 0;
  param_1[0x38] = '\x18';
  param_1[0x39] = '\0';
  param_1[0x3a] = '\0';
  param_1[0x3b] = '\0';
  iVar9 = 0;
  GetNodes((cRPath *)param_1);
  iVar3 = *(int *)(param_1 + 0x4c);
  param_1[0x84] = '\0';
  do {
    fVar12 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar5 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_1 + 0x4c);
    iVar5 = *(int *)(param_1 + 0x50) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar3 + iVar7 + 0x90);
    iVar7 = iVar7 + 0xa8;
    *(float *)(iVar5 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
  } while (iVar9 != 4);
  iVar9 = 0x14;
  iVar7 = 0xd20;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar5 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_1 + 0x4c);
    iVar5 = *(int *)(param_1 + 0x50) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar3 + iVar7 + 0x90);
    iVar7 = iVar7 + 0xa8;
    *(float *)(iVar5 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
  } while (iVar7 != 0xfc0);
  iVar9 = 1;
  iVar7 = 0x1f8;
  do {
    iVar8 = iVar7 + 0xa8;
    ptVar4 = (tMatrix *)(iVar3 + iVar8);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    tMatrix::Identity(ptVar4);
    fVar12 = (float)VectorSignedToFloat(iVar9 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar5 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar3 + iVar8));
    iVar6 = *(int *)(param_1 + 0x4c);
    iVar3 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar5 = iVar6 + iVar8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar3 + 0x38) = fVar12 * *(float *)(param_1 + 0x44);
    if (iVar9 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar6 + iVar7));
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar7));
    }
    else {
      iVar6 = iVar6 + iVar7;
      fVar11 = *(float *)(iVar5 + 0x38);
      fVar12 = *(float *)(iVar5 + 0x34);
      fVar10 = *(float *)(iVar5 + 0x30);
      *(undefined4 *)(iVar6 + 0x18) = 0;
      *(undefined4 *)(iVar6 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(float *)(iVar6 + 0x24) = fVar12 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x20) = fVar10 - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x28) = fVar11 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar7);
      tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar7);
      tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      iVar3 = *(int *)(param_1 + 0x50) + iVar8;
      iVar5 = *(int *)(param_1 + 0x50) + iVar7;
      fVar11 = *(float *)(iVar3 + 0x38);
      fVar12 = *(float *)(iVar3 + 0x34);
      fVar10 = *(float *)(iVar3 + 0x30);
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar5 + 0x10) = 0;
      *(float *)(iVar5 + 0x24) = fVar12 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x20) = fVar10 - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x28) = fVar11 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar5 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar7);
      tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar7);
      tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      if (0xf < iVar9) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar3 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar9 = 0;
          iVar7 = 0;
          do {
            iVar6 = iVar7 + 0xa8;
            iVar9 = iVar9 + 1;
            iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
            iVar3 = *(int *)(param_1 + 0x4c) + iVar6;
            fVar10 = *(float *)(iVar3 + 0x38);
            fVar12 = *(float *)(iVar3 + 0x34);
            *(float *)(iVar5 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar12 - *(float *)(iVar5 + 0x34);
            *(float *)(iVar5 + 0x88) = fVar10 - *(float *)(iVar5 + 0x38);
            uVar2 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar7 = *(int *)(param_1 + 0x50) + iVar7;
            iVar3 = *(int *)(param_1 + 0x50) + iVar6;
            fVar10 = *(float *)(iVar3 + 0x38);
            fVar12 = *(float *)(iVar3 + 0x34);
            fVar11 = *(float *)(iVar7 + 0x38);
            *(float *)(iVar7 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar7 + 0x30);
            *(float *)(iVar7 + 0x84) = fVar12 - *(float *)(iVar7 + 0x34);
            *(undefined4 *)(iVar5 + 0x8c) = uVar2;
            *(float *)(iVar7 + 0x88) = fVar10 - fVar11;
            uVar2 = tVector::Normalize((tVector *)(iVar7 + 0x80));
            iVar3 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar7 + 0x8c) = uVar2;
            iVar7 = iVar6;
          } while (iVar9 < iVar3);
        }
        iVar7 = *(int *)(param_1 + 0x50) + iVar3 * 0xa8;
        iVar3 = *(int *)(param_1 + 0x4c) + iVar3 * 0xa8;
        *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar3 + 0x84) = 0;
        *(undefined4 *)(iVar3 + 0x80) = 0;
        uVar2 = *(undefined4 *)(param_1 + 0x44);
        *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar3 + 0x8c) = uVar2;
        *(undefined4 *)(iVar7 + 0x80) = 0;
        *(undefined4 *)(iVar7 + 0x8c) = uVar2;
        *(undefined4 *)(iVar7 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar3 = *(int *)(param_1 + 0x4c);
    iVar9 = iVar9 + 1;
    iVar7 = iVar8;
  } while( true );
}
