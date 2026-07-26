/*
 * mangled: _ZN6cRPath10BuildSweepEfibPcS0_
 * demangled: cRPath::BuildSweep(float, int, bool, char*, char*)
 * address: 0005536c
 * size: 1160
 */

/* cRPath::BuildSweep(float, int, bool, char*, char*) */

void cRPath::BuildSweep(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  tVector *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  tMatrix *ptVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;

  *(undefined4 *)(param_2 + 0x2c) = 0x20;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = 0x41f00000;
  *(undefined4 *)(param_2 + 0x38) = 0x1e;
  iVar6 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  GetNodes((cRPath *)param_2);
  iVar8 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar6);
    *(undefined4 *)(ptVar9 + 0x98) = 0;
    *(undefined4 *)(ptVar9 + 0x94) = 0;
    *(undefined4 *)(ptVar9 + 0xa0) = 0;
    *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
    iVar7 = iVar1 + 1;
    uVar13 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = fVar11 * 0.5 - 4.0;
    tMatrix::Identity(ptVar9);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar8 + 0x38) = uVar13;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar8 + 0x34) = 0;
    tMatrix::Identity((tMatrix *)(iVar1 + iVar6));
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    iVar1 = iVar8 + iVar6;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    iVar1 = iVar7;
  } while (iVar7 != 3);
  iVar6 = 0x11b8;
  iVar1 = 0x1b;
  do {
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar9 = (tMatrix *)(iVar8 + iVar6);
    *(undefined4 *)(ptVar9 + 0x98) = 0;
    *(undefined4 *)(ptVar9 + 0x94) = 0;
    *(undefined4 *)(ptVar9 + 0xa0) = 0;
    *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
    uVar13 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar9 + 0x90) = fVar11 * -0.5 + 4.0;
    tMatrix::Identity(ptVar9);
    iVar8 = *(int *)(param_2 + 0x50);
    iVar3 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0;
    fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar8 + iVar6));
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar7 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar7 + 0x38) = uVar13;
    iVar3 = iVar8 + iVar6;
    iVar6 = iVar6 + 0xa8;
    uVar13 = *(undefined4 *)(iVar3 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar7 + 0x30) = uVar13;
    iVar1 = iVar1 + 1;
  } while (iVar6 != 0x13b0);
  iVar3 = 1;
  iVar6 = 0;
  iVar1 = 0x150;
  do {
    VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = iVar1 + 0xa8;
    fVar11 = (float)Cos(fVar11);
    fVar12 = *(float *)(*(int *)(param_2 + 0x4c) + 0x90);
    ptVar9 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5);
    *(undefined4 *)(ptVar9 + 0x98) = 0;
    *(undefined4 *)(ptVar9 + 0x94) = 0;
    *(undefined4 *)(ptVar9 + 0xa0) = 0;
    *(undefined4 *)(ptVar9 + 0x9c) = 0x3f800000;
    *(float *)(iVar8 + iVar5 + 0x90) = fVar11 * fVar12;
    fVar11 = (float)tMatrix::Identity(ptVar9);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    fVar11 = (float)Sin(fVar11);
    uVar14 = VectorSignedToFloat(iVar6 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar5 + 0x38) = uVar14;
    *(float *)(iVar7 + 0x34) = fVar11 * -0.3;
    tMatrix::Identity((tMatrix *)(iVar8 + iVar5));
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar7 = iVar4 + iVar5;
    fVar11 = *(float *)(iVar7 + 0x34);
    iVar8 = *(int *)(param_2 + 0x50) + iVar5;
    uVar13 = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar8 + 0x38) = uVar14;
    *(undefined4 *)(iVar8 + 0x30) = uVar13;
    *(float *)(iVar8 + 0x34) = fVar11 + 0.49;
    if (iVar6 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar4 + iVar1));
      fVar11 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar1));
    }
    else {
      iVar4 = iVar4 + iVar1;
      fVar10 = *(float *)(iVar7 + 0x38);
      fVar11 = *(float *)(iVar7 + 0x34);
      fVar12 = *(float *)(iVar7 + 0x30);
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      *(float *)(iVar4 + 0x24) = fVar11 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x20) = fVar12 - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x28) = fVar10 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar1);
      tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      iVar8 = *(int *)(param_2 + 0x50) + iVar5;
      iVar7 = *(int *)(param_2 + 0x50) + iVar1;
      fVar10 = *(float *)(iVar8 + 0x38);
      fVar11 = *(float *)(iVar8 + 0x34);
      fVar12 = *(float *)(iVar8 + 0x30);
      *(undefined4 *)(iVar7 + 0x18) = 0;
      *(undefined4 *)(iVar7 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar7 + 0x10) = 0;
      *(float *)(iVar7 + 0x20) = fVar12 - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x24) = fVar11 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x28) = fVar10 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar1);
      fVar11 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      if (0x17 < iVar3) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar1 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar8 = 0;
          iVar6 = 0;
          do {
            iVar7 = iVar6 + 0xa8;
            iVar8 = iVar8 + 1;
            iVar3 = *(int *)(param_2 + 0x4c) + iVar6;
            iVar1 = *(int *)(param_2 + 0x4c) + iVar7;
            fVar12 = *(float *)(iVar1 + 0x38);
            fVar11 = *(float *)(iVar1 + 0x34);
            *(float *)(iVar3 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar3 + 0x30);
            *(float *)(iVar3 + 0x84) = fVar11 - *(float *)(iVar3 + 0x34);
            *(float *)(iVar3 + 0x88) = fVar12 - *(float *)(iVar3 + 0x38);
            uVar13 = tVector::Normalize((tVector *)(iVar3 + 0x80));
            iVar6 = *(int *)(param_2 + 0x50) + iVar6;
            iVar1 = *(int *)(param_2 + 0x50) + iVar7;
            fVar12 = *(float *)(iVar1 + 0x38);
            fVar11 = *(float *)(iVar1 + 0x34);
            fVar10 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar6 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar6 + 0x30);
            *(float *)(iVar6 + 0x84) = fVar11 - *(float *)(iVar6 + 0x34);
            *(undefined4 *)(iVar3 + 0x8c) = uVar13;
            *(float *)(iVar6 + 0x88) = fVar12 - fVar10;
            uVar13 = tVector::Normalize((tVector *)(iVar6 + 0x80));
            iVar1 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar6 + 0x8c) = uVar13;
            iVar6 = iVar7;
          } while (iVar8 < iVar1);
        }
        iVar6 = *(int *)(param_2 + 0x50) + iVar1 * 0xa8;
        iVar1 = *(int *)(param_2 + 0x4c) + iVar1 * 0xa8;
        *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar1 + 0x84) = 0;
        *(undefined4 *)(iVar1 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar6 = iVar6 + 1;
    iVar3 = iVar3 + 1;
    iVar1 = iVar5;
  } while( true );
}
