/*
 * mangled: _ZN6cRPath11BuildDetourEfibPcS0_
 * demangled: cRPath::BuildDetour(float, int, bool, char*, char*)
 * address: 00054e7c
 * size: 1228
 */

/* cRPath::BuildDetour(float, int, bool, char*, char*) */

void cRPath::BuildDetour(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  tVector *ptVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  tMatrix *ptVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  undefined4 uVar15;

  *(undefined4 *)(param_2 + 0x44) = DAT_0005525c;
  *(undefined4 *)(param_2 + 0x2c) = 0x23;
  uVar3 = DAT_00055240;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = uVar3;
  *(undefined4 *)(param_2 + 0x38) = 0x2e;
  iVar7 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  fVar10 = DAT_00055244;
  GetNodes((cRPath *)param_2);
  iVar5 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  uVar3 = DAT_00055260;
  fVar13 = DAT_0005524c;
  fVar12 = DAT_00055248;
  iVar1 = 0;
  do {
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar6 = (tMatrix *)(iVar5 + iVar7);
    *(undefined4 *)(ptVar6 + 0x98) = uVar3;
    *(undefined4 *)(ptVar6 + 0x94) = uVar3;
    iVar9 = iVar1 + 1;
    uVar14 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = fVar11 * fVar10 - fVar12;
    tMatrix::Identity(ptVar6);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar5 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x38) = uVar14;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = uVar3;
    fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar7));
    iVar5 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar7;
    *(undefined4 *)(iVar4 + 0x38) = uVar14;
    iVar1 = iVar5 + iVar7;
    *(float *)(iVar4 + 0x34) = fVar13;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    uVar14 = DAT_0005525c;
    iVar1 = iVar9;
  } while (iVar9 != 3);
  iVar7 = 1;
  iVar1 = 0x1f8;
  iVar5 = 0;
  do {
    VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (float)Sin(fVar11);
    fVar10 = (float)Cos(fVar10);
    iVar4 = *(int *)(param_2 + 0x4c);
    fVar10 = (float)Cos(fVar10);
    fVar12 = *(float *)(*(int *)(param_2 + 0x4c) + 0x90);
    ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar1);
    *(undefined4 *)(ptVar6 + 0x98) = uVar3;
    *(undefined4 *)(ptVar6 + 0x94) = uVar3;
    *(float *)(iVar4 + iVar1 + 0x90) = fVar10 * fVar12;
    tMatrix::Identity(ptVar6);
    uVar15 = VectorSignedToFloat(iVar5 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar4 = *(int *)(param_2 + 0x50);
    iVar9 = *(int *)(param_2 + 0x4c) + iVar1;
    *(undefined4 *)(iVar9 + 0x34) = uVar3;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar9 + 0x38) = uVar15;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar1));
    iVar9 = *(int *)(param_2 + 0x4c);
    iVar4 = *(int *)(param_2 + 0x50) + iVar1;
    *(undefined4 *)(iVar4 + 0x38) = uVar15;
    ptVar6 = (tMatrix *)(iVar9 + iVar1);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(ptVar6 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = *(undefined4 *)(ptVar6 + 0x34);
    if (iVar5 == 0) {
      tMatrix::RotIdentity(ptVar6);
      fVar11 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar1));
    }
    else {
      iVar8 = iVar1 + -0xa8;
      fVar11 = *(float *)(ptVar6 + 0x38);
      iVar9 = iVar9 + iVar8;
      fVar10 = *(float *)(ptVar6 + 0x34);
      fVar12 = *(float *)(ptVar6 + 0x30);
      *(undefined4 *)(iVar9 + 0x18) = uVar3;
      *(undefined4 *)(iVar9 + 0x14) = uVar14;
      *(undefined4 *)(iVar9 + 0x10) = uVar3;
      *(float *)(iVar9 + 0x24) = fVar10 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x20) = fVar12 - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x28) = fVar11 - *(float *)(iVar9 + 0x38);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar8);
      fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar8),fVar10);
      iVar4 = *(int *)(param_2 + 0x50) + iVar1;
      iVar9 = *(int *)(param_2 + 0x50) + iVar8;
      fVar11 = *(float *)(iVar4 + 0x38);
      fVar10 = *(float *)(iVar4 + 0x34);
      fVar12 = *(float *)(iVar4 + 0x30);
      *(undefined4 *)(iVar9 + 0x18) = uVar3;
      *(undefined4 *)(iVar9 + 0x14) = uVar14;
      *(undefined4 *)(iVar9 + 0x10) = uVar3;
      *(float *)(iVar9 + 0x24) = fVar10 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x20) = fVar12 - *(float *)(iVar9 + 0x30);
      *(float *)(iVar9 + 0x28) = fVar11 - *(float *)(iVar9 + 0x38);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar8);
      fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      fVar11 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x50) + iVar8),fVar10);
      iVar8 = *(int *)(param_2 + 0x50) + iVar8;
      *(float *)(iVar8 + 0x34) = *(float *)(iVar8 + 0x34) + fVar13 * *(float *)(iVar8 + 0x14);
      *(float *)(iVar8 + 0x38) = *(float *)(iVar8 + 0x38) + fVar13 * *(float *)(iVar8 + 0x18);
      *(float *)(iVar8 + 0x30) = *(float *)(iVar8 + 0x30) + fVar13 * *(float *)(iVar8 + 0x10);
      fVar10 = DAT_0005524c;
      if (0x28 < iVar7) {
        iVar1 = *(int *)(param_2 + 0x4c);
        iVar7 = 0x2b;
        iVar5 = 0x1c38;
        do {
          uVar14 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
          ptVar6 = (tMatrix *)(iVar1 + iVar5);
          *(undefined4 *)(ptVar6 + 0x90) = *(undefined4 *)(iVar1 + 0x90);
          *(undefined4 *)(ptVar6 + 0x98) = uVar3;
          *(undefined4 *)(ptVar6 + 0x94) = uVar3;
          tMatrix::Identity(ptVar6);
          iVar1 = *(int *)(param_2 + 0x50);
          iVar7 = iVar7 + 1;
          iVar4 = *(int *)(param_2 + 0x4c) + iVar5;
          *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
          *(undefined4 *)(iVar4 + 0x34) = uVar3;
          *(undefined4 *)(iVar4 + 0x38) = uVar14;
          tMatrix::Identity((tMatrix *)(iVar1 + iVar5));
          iVar9 = *(int *)(param_2 + 0x50);
          iVar1 = *(int *)(param_2 + 0x4c);
          iVar8 = iVar9 + iVar5;
          *(undefined4 *)(iVar8 + 0x38) = uVar14;
          iVar4 = iVar1 + iVar5;
          iVar5 = iVar5 + 0xa8;
          uVar14 = *(undefined4 *)(iVar4 + 0x90);
          *(float *)(iVar8 + 0x34) = fVar10;
          *(undefined4 *)(iVar8 + 0x30) = uVar14;
        } while (iVar5 != 0x1e30);
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar5 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar4 = 0;
          iVar7 = 0;
          while( true ) {
            iVar9 = iVar7 + 0xa8;
            iVar5 = iVar1 + iVar7;
            iVar1 = iVar1 + iVar9;
            fVar12 = *(float *)(iVar1 + 0x38);
            fVar10 = *(float *)(iVar1 + 0x34);
            iVar4 = iVar4 + 1;
            *(float *)(iVar5 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar10 - *(float *)(iVar5 + 0x34);
            *(float *)(iVar5 + 0x88) = fVar12 - *(float *)(iVar5 + 0x38);
            uVar3 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar7 = *(int *)(param_2 + 0x50) + iVar7;
            iVar1 = *(int *)(param_2 + 0x50) + iVar9;
            fVar12 = *(float *)(iVar1 + 0x38);
            fVar10 = *(float *)(iVar1 + 0x34);
            fVar13 = *(float *)(iVar7 + 0x38);
            *(float *)(iVar7 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar7 + 0x30);
            *(float *)(iVar7 + 0x84) = fVar10 - *(float *)(iVar7 + 0x34);
            *(undefined4 *)(iVar5 + 0x8c) = uVar3;
            *(float *)(iVar7 + 0x88) = fVar12 - fVar13;
            uVar3 = tVector::Normalize((tVector *)(iVar7 + 0x80));
            iVar5 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar7 + 0x8c) = uVar3;
            if (iVar5 <= iVar4) break;
            iVar1 = *(int *)(param_2 + 0x4c);
            iVar7 = iVar9;
          }
          iVar1 = *(int *)(param_2 + 0x4c);
          iVar9 = *(int *)(param_2 + 0x50);
        }
        uVar14 = DAT_00055260;
        uVar3 = DAT_0005525c;
        iVar9 = iVar9 + iVar5 * 0xa8;
        iVar1 = iVar1 + iVar5 * 0xa8;
        *(undefined4 *)(iVar1 + 0x8c) = DAT_0005525c;
        *(undefined4 *)(iVar1 + 0x88) = uVar3;
        *(undefined4 *)(iVar1 + 0x84) = uVar14;
        *(undefined4 *)(iVar1 + 0x80) = uVar14;
        *(undefined4 *)(iVar9 + 0x8c) = uVar3;
        *(undefined4 *)(iVar9 + 0x80) = uVar14;
        *(undefined4 *)(iVar9 + 0x88) = uVar3;
        *(undefined4 *)(iVar9 + 0x84) = uVar14;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar5 = iVar5 + 1;
    iVar1 = iVar1 + 0xa8;
    iVar7 = iVar7 + 1;
  } while( true );
}
