/*
 * mangled: _ZN6cRPath10BuildSweepEfibPcS0_
 * demangled: cRPath::BuildSweep(float, int, bool, char*, char*)
 * address: 0005536c
 * size: 1160
 */

/* cRPath::BuildSweep(float, int, bool, char*, char*) */

void cRPath::BuildSweep(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  tMatrix *ptVar11;
  uint in_fpscr;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  undefined4 uVar18;

  uVar1 = DAT_000556f4;
  uVar4 = DAT_000556d4;
  *(undefined4 *)(param_2 + 0x2c) = 0x20;
  *(undefined4 *)(param_2 + 0x44) = uVar1;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = uVar4;
  *(undefined4 *)(param_2 + 0x38) = 0x1e;
  iVar8 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar15 = DAT_000556d8;
  GetNodes((cRPath *)param_2);
  iVar10 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  uVar4 = DAT_000556f8;
  fVar16 = DAT_000556e0;
  fVar12 = DAT_000556dc;
  iVar2 = 0;
  do {
    fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar1;
    iVar9 = iVar2 + 1;
    uVar17 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = fVar14 * fVar15 - fVar12;
    tMatrix::Identity(ptVar11);
    iVar2 = *(int *)(param_2 + 0x50);
    iVar10 = *(int *)(param_2 + 0x4c) + iVar8;
    *(undefined4 *)(iVar10 + 0x38) = uVar17;
    *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(iVar10 + 0x90);
    *(undefined4 *)(iVar10 + 0x34) = uVar4;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar8));
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar5 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    iVar2 = iVar10 + iVar8;
    *(float *)(iVar5 + 0x34) = fVar16;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    fVar13 = DAT_000556e4;
    fVar14 = DAT_000556dc;
    iVar2 = iVar9;
  } while (iVar9 != 3);
  iVar8 = 0x11b8;
  iVar2 = 0x1b;
  do {
    fVar15 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar1;
    uVar17 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar11 + 0x90) = fVar14 + fVar15 * fVar13;
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x38) = uVar17;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = uVar4;
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar10 + iVar8));
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar9 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar9 + 0x38) = uVar17;
    iVar5 = iVar10 + iVar8;
    iVar8 = iVar8 + 0xa8;
    uVar17 = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar9 + 0x34) = fVar16;
    *(undefined4 *)(iVar9 + 0x30) = uVar17;
    fVar15 = DAT_000556f0;
    iVar2 = iVar2 + 1;
  } while (iVar8 != 0x13b0);
  iVar5 = 1;
  iVar8 = 0;
  iVar2 = 0x150;
  do {
    VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    iVar7 = iVar2 + 0xa8;
    fVar12 = (float)Cos(fVar12);
    fVar14 = *(float *)(*(int *)(param_2 + 0x4c) + 0x90);
    ptVar11 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7);
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(undefined4 *)(ptVar11 + 0x9c) = uVar1;
    *(float *)(iVar10 + iVar7 + 0x90) = fVar12 * fVar14;
    fVar12 = (float)tMatrix::Identity(ptVar11);
    iVar9 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    fVar12 = (float)Sin(fVar12);
    uVar18 = VectorSignedToFloat(iVar8 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar10 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar7 + 0x38) = uVar18;
    *(float *)(iVar9 + 0x34) = fVar12 * fVar15;
    tMatrix::Identity((tMatrix *)(iVar10 + iVar7));
    iVar6 = *(int *)(param_2 + 0x4c);
    iVar9 = iVar6 + iVar7;
    fVar12 = *(float *)(iVar9 + 0x34);
    iVar10 = *(int *)(param_2 + 0x50) + iVar7;
    uVar17 = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar10 + 0x38) = uVar18;
    *(undefined4 *)(iVar10 + 0x30) = uVar17;
    *(float *)(iVar10 + 0x34) = fVar12 + fVar16;
    if (iVar8 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar6 + iVar2));
      fVar12 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar2));
    }
    else {
      iVar6 = iVar6 + iVar2;
      fVar13 = *(float *)(iVar9 + 0x38);
      fVar12 = *(float *)(iVar9 + 0x34);
      fVar14 = *(float *)(iVar9 + 0x30);
      *(undefined4 *)(iVar6 + 0x18) = uVar4;
      *(undefined4 *)(iVar6 + 0x14) = uVar1;
      *(undefined4 *)(iVar6 + 0x10) = uVar4;
      *(float *)(iVar6 + 0x24) = fVar12 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x20) = fVar14 - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x28) = fVar13 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar2);
      tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      iVar10 = *(int *)(param_2 + 0x50) + iVar7;
      iVar9 = *(int *)(param_2 + 0x50) + iVar2;
      fVar13 = *(float *)(iVar10 + 0x38);
      fVar12 = *(float *)(iVar10 + 0x34);
      fVar14 = *(float *)(iVar10 + 0x30);
      *(undefined4 *)(iVar9 + 0x18) = uVar4;
      *(undefined4 *)(iVar9 + 0x14) = uVar1;
      *(undefined4 *)(iVar9 + 0x10) = uVar4;
      *(float *)(iVar9 + 0x20) = fVar14 - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x24) = fVar12 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x28) = fVar13 - *(float *)(iVar9 + 0x38);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x50) + iVar2);
      fVar12 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      if (0x17 < iVar5) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar2 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar10 = 0;
          iVar8 = 0;
          do {
            iVar9 = iVar8 + 0xa8;
            iVar10 = iVar10 + 1;
            iVar5 = *(int *)(param_2 + 0x4c) + iVar8;
            iVar2 = *(int *)(param_2 + 0x4c) + iVar9;
            fVar12 = *(float *)(iVar2 + 0x38);
            fVar15 = *(float *)(iVar2 + 0x34);
            *(float *)(iVar5 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar15 - *(float *)(iVar5 + 0x34);
            *(float *)(iVar5 + 0x88) = fVar12 - *(float *)(iVar5 + 0x38);
            uVar4 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar8 = *(int *)(param_2 + 0x50) + iVar8;
            iVar2 = *(int *)(param_2 + 0x50) + iVar9;
            fVar12 = *(float *)(iVar2 + 0x38);
            fVar15 = *(float *)(iVar2 + 0x34);
            fVar16 = *(float *)(iVar8 + 0x38);
            *(float *)(iVar8 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar8 + 0x30);
            *(float *)(iVar8 + 0x84) = fVar15 - *(float *)(iVar8 + 0x34);
            *(undefined4 *)(iVar5 + 0x8c) = uVar4;
            *(float *)(iVar8 + 0x88) = fVar12 - fVar16;
            uVar4 = tVector::Normalize((tVector *)(iVar8 + 0x80));
            iVar2 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar8 + 0x8c) = uVar4;
            iVar8 = iVar9;
          } while (iVar10 < iVar2);
        }
        uVar1 = DAT_000556f8;
        uVar4 = DAT_000556f4;
        iVar8 = *(int *)(param_2 + 0x50) + iVar2 * 0xa8;
        iVar2 = *(int *)(param_2 + 0x4c) + iVar2 * 0xa8;
        *(undefined4 *)(iVar2 + 0x8c) = DAT_000556f4;
        *(undefined4 *)(iVar2 + 0x88) = uVar4;
        *(undefined4 *)(iVar2 + 0x84) = uVar1;
        *(undefined4 *)(iVar2 + 0x80) = uVar1;
        *(undefined4 *)(iVar8 + 0x8c) = uVar4;
        *(undefined4 *)(iVar8 + 0x80) = uVar1;
        *(undefined4 *)(iVar8 + 0x88) = uVar4;
        *(undefined4 *)(iVar8 + 0x84) = uVar1;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar10 = *(int *)(param_2 + 0x4c);
    iVar8 = iVar8 + 1;
    iVar5 = iVar5 + 1;
    iVar2 = iVar7;
  } while( true );
}
