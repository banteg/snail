/*
 * mangled: _ZN6cRPath14BuildTwister2AEfibPcS0_
 * demangled: cRPath::BuildTwister2A(float, int, bool, char*, char*)
 * address: 00050268
 * size: 1240
 */

/* cRPath::BuildTwister2A(float, int, bool, char*, char*) */

void cRPath::BuildTwister2A(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  float fVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float extraout_s0;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;

  *(undefined4 *)(param_2 + 0x2c) = 0x3d;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = 0x42840000;
  *(undefined4 *)(param_2 + 0x38) = 0x42;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  GetNodes((cRPath *)param_2);
  fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  ptVar4 = *(tMatrix **)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  *(undefined4 *)(ptVar4 + 0x98) = 0;
  *(undefined4 *)(ptVar4 + 0x94) = 0;
  *(undefined4 *)(ptVar4 + 0xa0) = 0;
  fVar10 = fVar10 * 0.5 - 4.0;
  iVar8 = 0;
  *(float *)(ptVar4 + 0x90) = fVar10;
  if (((uint)param_5 ^ 1) != 0) {
    *(float *)(ptVar4 + 0x90) = -fVar10;
  }
  *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
  tMatrix::Identity(ptVar4);
  iVar5 = *(int *)(param_2 + 0x4c);
  ptVar4 = *(tMatrix **)(param_2 + 0x50);
  *(undefined4 *)(iVar5 + 0x38) = 0;
  *(undefined4 *)(iVar5 + 0x34) = 0;
  *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  tMatrix::Identity(ptVar4);
  fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3);
  iVar3 = *(int *)(param_2 + 0x50);
  iVar5 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar5 + 0x2b40) = 0;
  fVar10 = fVar10 * 0.5 - 4.0;
  *(undefined4 *)(iVar5 + 0x2b3c) = 0;
  *(undefined4 *)(iVar5 + 0x2b48) = 0;
  *(undefined4 *)(iVar5 + 0x2b44) = 0x3f800000;
  *(float *)(iVar5 + 0x2b38) = fVar10;
  if (((uint)param_5 ^ 1) != 0) {
    *(float *)(iVar5 + 0x2b38) = -fVar10;
  }
  tMatrix::Identity((tMatrix *)(iVar5 + 0x2aa8));
  iVar3 = *(int *)(param_2 + 0x4c);
  iVar5 = *(int *)(param_2 + 0x50);
  *(undefined4 *)(iVar3 + 0x2ae0) = 0x42820000;
  *(undefined4 *)(iVar3 + 0x2ad8) = *(undefined4 *)(iVar3 + 0x2b38);
  *(undefined4 *)(iVar3 + 0x2adc) = 0;
  fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar5 + 0x2aa8));
  iVar5 = *(int *)(param_2 + 0x50);
  iVar3 = *(int *)(param_2 + 0x4c);
  *(undefined4 *)(iVar5 + 0x2ae0) = 0x42820000;
  uVar12 = *(undefined4 *)(iVar3 + 0x2b38);
  *(undefined4 *)(iVar5 + 0x2adc) = 0x3efae148;
  *(undefined4 *)(iVar5 + 0x2ad8) = uVar12;
  iVar5 = 0;
  do {
    iVar8 = iVar8 + 1;
    iVar7 = iVar5 + 0xa8;
    fVar10 = (float)Cos(fVar10);
    ptVar4 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7);
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    uVar13 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    *(float *)(iVar3 + iVar7 + 0x90) = (fVar10 * 0.5 + 0.5) * -5.0 + 2.5;
    fVar10 = (float)tMatrix::Identity(ptVar4);
    iVar9 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    fVar10 = (float)Sin(fVar10);
    fVar2 = (float)Sin(extraout_s0);
    iVar3 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar7 + 0x38) = uVar13;
    *(float *)(iVar9 + 0x34) = fVar10 * fVar2 * (float)(uint)param_3;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar9 = iVar6 + iVar7;
    fVar10 = *(float *)(iVar9 + 0x34);
    iVar3 = *(int *)(param_2 + 0x50) + iVar7;
    uVar12 = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    *(undefined4 *)(iVar3 + 0x30) = uVar12;
    *(float *)(iVar3 + 0x34) = fVar10 + 0.49;
    if (iVar8 == 1) {
      tMatrix::RotIdentity((tMatrix *)(iVar6 + iVar5));
      fVar10 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar5));
    }
    else {
      iVar6 = iVar6 + iVar5;
      fVar11 = *(float *)(iVar9 + 0x38);
      fVar10 = *(float *)(iVar9 + 0x34);
      fVar2 = *(float *)(iVar9 + 0x30);
      *(undefined4 *)(iVar6 + 0x18) = 0;
      *(undefined4 *)(iVar6 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(float *)(iVar6 + 0x24) = fVar10 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x20) = fVar2 - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x28) = fVar11 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar5);
      tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar5);
      tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      tMatrix::Orthoganalize((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5));
      iVar3 = *(int *)(param_2 + 0x50) + iVar7;
      iVar9 = *(int *)(param_2 + 0x50) + iVar5;
      fVar11 = *(float *)(iVar3 + 0x38);
      fVar10 = *(float *)(iVar3 + 0x34);
      fVar2 = *(float *)(iVar3 + 0x30);
      *(undefined4 *)(iVar9 + 0x18) = 0;
      *(undefined4 *)(iVar9 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar9 + 0x10) = 0;
      *(float *)(iVar9 + 0x24) = fVar10 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x20) = fVar2 - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x28) = fVar11 - *(float *)(iVar9 + 0x38);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar5);
      tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      ptVar1 = (tVector *)(*(int *)(param_2 + 0x50) + iVar5);
      tVector::Cross(ptVar1 + 0x10,ptVar1 + 0x20,ptVar1);
      fVar10 = (float)tMatrix::Orthoganalize((tMatrix *)(*(int *)(param_2 + 0x50) + iVar5));
      if (iVar8 == 0x40) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar8 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar3 = 0;
          iVar5 = 0;
          do {
            iVar6 = iVar5 + 0xa8;
            iVar3 = iVar3 + 1;
            iVar9 = *(int *)(param_2 + 0x4c) + iVar5;
            iVar8 = *(int *)(param_2 + 0x4c) + iVar6;
            fVar2 = *(float *)(iVar8 + 0x38);
            fVar10 = *(float *)(iVar8 + 0x34);
            *(float *)(iVar9 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar9 + 0x30);
            *(float *)(iVar9 + 0x84) = fVar10 - *(float *)(iVar9 + 0x34);
            *(float *)(iVar9 + 0x88) = fVar2 - *(float *)(iVar9 + 0x38);
            uVar12 = tVector::Normalize((tVector *)(iVar9 + 0x80));
            iVar5 = *(int *)(param_2 + 0x50) + iVar5;
            iVar8 = *(int *)(param_2 + 0x50) + iVar6;
            fVar2 = *(float *)(iVar8 + 0x38);
            fVar10 = *(float *)(iVar8 + 0x34);
            fVar11 = *(float *)(iVar5 + 0x38);
            *(float *)(iVar5 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar10 - *(float *)(iVar5 + 0x34);
            *(undefined4 *)(iVar9 + 0x8c) = uVar12;
            *(float *)(iVar5 + 0x88) = fVar2 - fVar11;
            uVar12 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar8 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar5 + 0x8c) = uVar12;
            iVar5 = iVar6;
          } while (iVar3 < iVar8);
        }
        iVar5 = *(int *)(param_2 + 0x50) + iVar8 * 0xa8;
        iVar8 = *(int *)(param_2 + 0x4c) + iVar8 * 0xa8;
        *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x84) = 0;
        *(undefined4 *)(iVar8 + 0x80) = 0;
        *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x80) = 0;
        *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar3 = *(int *)(param_2 + 0x4c);
    iVar5 = iVar7;
  } while( true );
}
