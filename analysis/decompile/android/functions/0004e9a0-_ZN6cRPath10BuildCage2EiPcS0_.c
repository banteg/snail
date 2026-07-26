/*
 * mangled: _ZN6cRPath10BuildCage2EiPcS0_
 * demangled: cRPath::BuildCage2(int, char*, char*)
 * address: 0004e9a0
 * size: 1188
 */

/* cRPath::BuildCage2(int, char*, char*) */

void cRPath::BuildCage2(int param_1,char *param_2,char *param_3)

{
  tVector *ptVar1;
  int iVar2;
  tMatrix *ptVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;

  *(char **)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x40) = 0x41f00000;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0x13;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0x1e;
  GetNodes((cRPath *)param_1);
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  ptVar3 = *(tMatrix **)(param_1 + 0x4c);
  *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
  *(undefined4 *)(ptVar3 + 0x98) = 0;
  *(undefined4 *)(ptVar3 + 0x94) = 0;
  *(undefined4 *)(ptVar3 + 0xa0) = 0;
  *(undefined1 *)(param_1 + 0x84) = 0;
  iVar8 = 0;
  *(float *)(ptVar3 + 0x90) = fVar11 * 0.5 - 4.0;
  tMatrix::Identity(ptVar3);
  iVar4 = *(int *)(param_1 + 0x4c);
  ptVar3 = *(tMatrix **)(param_1 + 0x50);
  *(undefined4 *)(iVar4 + 0x38) = 0;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar4 + 0x34) = 0;
  tMatrix::Identity(ptVar3);
  uVar10 = *(undefined4 *)(param_1 + 0x48);
  iVar2 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar2 + 0x38) = 0;
  iVar4 = *(int *)(param_1 + 0x4c);
  fVar11 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar2 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar4 + 0x13a0) = 0;
  *(undefined4 *)(iVar4 + 0x139c) = 0;
  *(undefined4 *)(iVar4 + 0x13a8) = 0;
  *(undefined4 *)(iVar4 + 0x13a4) = 0x3f800000;
  *(float *)(iVar4 + 0x1398) = fVar11 * -0.5 + 4.0;
  tMatrix::Identity((tMatrix *)(iVar4 + 0x1308));
  iVar2 = *(int *)(param_1 + 0x4c);
  iVar4 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar2 + 0x1340) = 0x41e80000;
  *(undefined4 *)(iVar2 + 0x1338) = *(undefined4 *)(iVar2 + 0x1398);
  *(undefined4 *)(iVar2 + 0x133c) = 0;
  fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar4 + 0x1308));
  iVar4 = *(int *)(param_1 + 0x50);
  iVar2 = *(int *)(param_1 + 0x4c);
  uVar10 = *(undefined4 *)(iVar2 + 0x1398);
  *(undefined4 *)(iVar4 + 0x1340) = 0x41e80000;
  *(undefined4 *)(iVar4 + 0x133c) = 0x3efae148;
  *(undefined4 *)(iVar4 + 0x1338) = uVar10;
  iVar4 = 0;
  do {
    iVar8 = iVar8 + 1;
    iVar7 = iVar4 + 0xa8;
    fVar11 = (float)Cos(fVar11);
    fVar12 = *(float *)(*(int *)(param_1 + 0x4c) + 0x90);
    ptVar3 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar7);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    uVar13 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar2 + iVar7 + 0x90) = fVar11 * fVar12;
    tMatrix::Identity(ptVar3);
    iVar2 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar13;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar7));
    iVar6 = *(int *)(param_1 + 0x4c);
    iVar5 = iVar6 + iVar7;
    fVar11 = *(float *)(iVar5 + 0x34);
    iVar2 = *(int *)(param_1 + 0x50) + iVar7;
    uVar10 = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar2 + 0x38) = uVar13;
    *(undefined4 *)(iVar2 + 0x30) = uVar10;
    *(float *)(iVar2 + 0x34) = fVar11 + 0.49;
    if (iVar8 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar6 + iVar4));
      fVar11 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar4));
    }
    else {
      iVar6 = iVar6 + iVar4;
      fVar9 = *(float *)(iVar5 + 0x38);
      fVar11 = *(float *)(iVar5 + 0x30);
      fVar12 = *(float *)(iVar5 + 0x34);
      *(undefined4 *)(iVar6 + 0x18) = 0;
      *(undefined4 *)(iVar6 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(float *)(iVar6 + 0x20) = fVar11 - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x24) = fVar12 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x28) = fVar9 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar4);
      fVar11 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      iVar2 = *(int *)(param_1 + 0x4c);
      fVar11 = (float)Cos(fVar11);
      tMatrix::RotLocalZ((tMatrix *)(iVar2 + iVar4),fVar11);
      iVar2 = *(int *)(param_1 + 0x50) + iVar7;
      iVar5 = *(int *)(param_1 + 0x50) + iVar4;
      fVar9 = *(float *)(iVar2 + 0x38);
      fVar11 = *(float *)(iVar2 + 0x30);
      fVar12 = *(float *)(iVar2 + 0x34);
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar5 + 0x10) = 0;
      *(float *)(iVar5 + 0x20) = fVar11 - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar12 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar9 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar5 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar4);
      fVar11 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      iVar2 = *(int *)(param_1 + 0x50);
      fVar11 = (float)Cos(fVar11);
      fVar11 = (float)tMatrix::RotLocalZ((tMatrix *)(iVar2 + iVar4),fVar11);
      if (iVar8 == 0x1c) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar4 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar8 = 0;
          iVar2 = 0;
          do {
            iVar6 = iVar2 + 0xa8;
            iVar8 = iVar8 + 1;
            iVar5 = *(int *)(param_1 + 0x4c) + iVar2;
            iVar4 = *(int *)(param_1 + 0x4c) + iVar6;
            fVar12 = *(float *)(iVar4 + 0x38);
            fVar11 = *(float *)(iVar4 + 0x34);
            *(float *)(iVar5 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar11 - *(float *)(iVar5 + 0x34);
            *(float *)(iVar5 + 0x88) = fVar12 - *(float *)(iVar5 + 0x38);
            uVar10 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar2 = *(int *)(param_1 + 0x50) + iVar2;
            iVar4 = *(int *)(param_1 + 0x50) + iVar6;
            fVar12 = *(float *)(iVar4 + 0x38);
            fVar11 = *(float *)(iVar4 + 0x34);
            fVar9 = *(float *)(iVar2 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
            *(undefined4 *)(iVar5 + 0x8c) = uVar10;
            *(float *)(iVar2 + 0x88) = fVar12 - fVar9;
            uVar10 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            iVar4 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar2 + 0x8c) = uVar10;
            iVar2 = iVar6;
          } while (iVar8 < iVar4);
        }
        iVar2 = *(int *)(param_1 + 0x50) + iVar4 * 0xa8;
        iVar4 = *(int *)(param_1 + 0x4c) + iVar4 * 0xa8;
        *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar4 + 0x84) = 0;
        *(undefined4 *)(iVar4 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar2 = *(int *)(param_1 + 0x4c);
    iVar4 = iVar7;
  } while( true );
}
