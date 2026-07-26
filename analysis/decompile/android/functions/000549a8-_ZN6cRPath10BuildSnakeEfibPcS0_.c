/*
 * mangled: _ZN6cRPath10BuildSnakeEfibPcS0_
 * demangled: cRPath::BuildSnake(float, int, bool, char*, char*)
 * address: 000549a8
 * size: 1200
 */

/* cRPath::BuildSnake(float, int, bool, char*, char*) */

void cRPath::BuildSnake(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  int iVar2;
  tVector *ptVar3;
  float fVar4;
  undefined4 uVar5;
  tMatrix *ptVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined4 uVar20;
  float fVar21;

  fVar15 = DAT_00054d54;
  uVar5 = DAT_00054d38;
  iVar10 = 0;
  iVar11 = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0x24;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(float *)(param_2 + 0x44) = fVar15;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x40) = uVar5;
  *(undefined4 *)(param_2 + 0x38) = 0x1b;
  uVar5 = DAT_00054d58;
  GetNodes((cRPath *)param_2);
  fVar14 = DAT_00054d3c;
  *(undefined1 *)(param_2 + 0x84) = 0;
  do {
    uVar20 = VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    iVar11 = iVar11 + 1;
    ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar10);
    *(undefined4 *)(ptVar6 + 0x90) = uVar5;
    *(undefined4 *)(ptVar6 + 0x98) = uVar5;
    *(undefined4 *)(ptVar6 + 0x94) = uVar5;
    *(undefined4 *)(ptVar6 + 0xa0) = uVar5;
    *(float *)(ptVar6 + 0x9c) = fVar15;
    tMatrix::Identity(ptVar6);
    iVar2 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar10;
    *(undefined4 *)(iVar7 + 0x38) = uVar20;
    *(undefined4 *)(iVar7 + 0x30) = uVar5;
    *(undefined4 *)(iVar7 + 0x34) = uVar5;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar10));
    iVar2 = *(int *)(param_2 + 0x50) + iVar10;
    iVar10 = iVar10 + 0xa8;
    *(undefined4 *)(iVar2 + 0x38) = uVar20;
    *(undefined4 *)(iVar2 + 0x30) = uVar5;
    *(float *)(iVar2 + 0x34) = fVar14;
    fVar21 = DAT_00054d44;
    fVar4 = DAT_00054d40;
  } while (iVar11 != 6);
  iVar2 = *(int *)(param_2 + 0x4c);
  iVar11 = 0xfc0;
  iVar10 = 0x18;
  do {
    fVar17 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar6 = (tMatrix *)(iVar2 + iVar11);
    *(undefined4 *)(ptVar6 + 0x98) = uVar5;
    *(undefined4 *)(ptVar6 + 0x94) = uVar5;
    *(undefined4 *)(ptVar6 + 0xa0) = uVar5;
    *(float *)(ptVar6 + 0x9c) = fVar15;
    uVar20 = VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar6 + 0x90) = fVar21 + fVar17 * fVar4;
    tMatrix::Identity(ptVar6);
    iVar2 = *(int *)(param_2 + 0x50);
    iVar7 = *(int *)(param_2 + 0x4c) + iVar11;
    *(undefined4 *)(iVar7 + 0x38) = uVar20;
    *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
    *(undefined4 *)(iVar7 + 0x34) = uVar5;
    fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar11));
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar8 = *(int *)(param_2 + 0x50) + iVar11;
    *(undefined4 *)(iVar8 + 0x38) = uVar20;
    iVar7 = iVar2 + iVar11;
    iVar11 = iVar11 + 0xa8;
    uVar20 = *(undefined4 *)(iVar7 + 0x90);
    *(float *)(iVar8 + 0x34) = fVar14;
    *(undefined4 *)(iVar8 + 0x30) = uVar20;
    fVar1 = DAT_00054d50;
    fVar17 = DAT_00054d40;
    iVar10 = iVar10 + 1;
  } while (iVar11 != 0x11b8);
  iVar7 = 1;
  iVar11 = 0;
  iVar10 = 0x348;
  do {
    VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    fVar21 = *(float *)(iVar2 + 0x1050);
    iVar8 = iVar10 + 0xa8;
    fVar4 = (float)Cos(fVar13);
    ptVar6 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar8);
    *(undefined4 *)(ptVar6 + 0x98) = uVar5;
    *(undefined4 *)(ptVar6 + 0x94) = uVar5;
    *(undefined4 *)(ptVar6 + 0xa0) = uVar5;
    *(float *)(ptVar6 + 0x9c) = fVar15;
    *(float *)(iVar2 + iVar8 + 0x90) = fVar21 * (fVar1 + fVar4 * fVar17);
    fVar4 = (float)tMatrix::Identity(ptVar6);
    iVar12 = *(int *)(param_2 + 0x4c) + iVar8;
    *(undefined4 *)(iVar12 + 0x30) = *(undefined4 *)(iVar12 + 0x90);
    fVar4 = (float)Cos(fVar4);
    uVar20 = VectorSignedToFloat(iVar11 + 6,(byte)(in_fpscr >> 0x16) & 3);
    iVar2 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar8 + 0x38) = uVar20;
    *(float *)(iVar12 + 0x34) = -(fVar15 - fVar4);
    fVar4 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar8));
    iVar2 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar8 + 0x90);
    fVar4 = (float)Cos(fVar4);
    *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar8 + 0x38) = uVar20;
    *(float *)(iVar2 + 0x34) = fVar14 - (fVar15 - fVar4);
    if (iVar11 == 0) {
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar10));
      fVar13 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar10));
    }
    else {
      iVar12 = *(int *)(param_2 + 0x4c);
      iVar9 = iVar12 + iVar10;
      iVar2 = iVar12 + iVar8;
      fVar18 = *(float *)(iVar9 + 0x30);
      fVar13 = *(float *)(iVar2 + 0x38);
      fVar4 = *(float *)(iVar2 + 0x34);
      fVar16 = *(float *)(iVar9 + 0x34);
      fVar21 = *(float *)(iVar2 + 0x30);
      *(undefined4 *)(iVar9 + 8) = uVar5;
      *(undefined4 *)(iVar9 + 4) = uVar5;
      *(float *)(iVar12 + iVar10) = fVar15;
      *(float *)(iVar9 + 0x24) = fVar4 - fVar16;
      *(float *)(iVar9 + 0x20) = fVar21 - fVar18;
      *(float *)(iVar9 + 0x28) = fVar13 - *(float *)(iVar9 + 0x38);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar10);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      iVar12 = *(int *)(param_2 + 0x50);
      iVar9 = iVar12 + iVar10;
      iVar2 = iVar12 + iVar8;
      fVar18 = *(float *)(iVar9 + 0x30);
      fVar13 = *(float *)(iVar2 + 0x38);
      fVar4 = *(float *)(iVar2 + 0x34);
      fVar21 = *(float *)(iVar2 + 0x30);
      fVar16 = *(float *)(iVar9 + 0x34);
      fVar19 = *(float *)(iVar9 + 0x38);
      *(undefined4 *)(iVar9 + 8) = uVar5;
      *(float *)(iVar12 + iVar10) = fVar15;
      *(undefined4 *)(iVar9 + 4) = uVar5;
      *(float *)(iVar9 + 0x20) = fVar21 - fVar18;
      *(float *)(iVar9 + 0x24) = fVar4 - fVar16;
      *(float *)(iVar9 + 0x28) = fVar13 - fVar19;
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_2 + 0x50) + iVar10);
      fVar13 = (float)tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      if (0x11 < iVar7) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar10 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar2 = 0;
          iVar11 = 0;
          do {
            iVar8 = iVar11 + 0xa8;
            iVar2 = iVar2 + 1;
            iVar7 = *(int *)(param_2 + 0x4c) + iVar11;
            iVar10 = *(int *)(param_2 + 0x4c) + iVar8;
            fVar15 = *(float *)(iVar10 + 0x38);
            fVar14 = *(float *)(iVar10 + 0x34);
            *(float *)(iVar7 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
            *(float *)(iVar7 + 0x84) = fVar14 - *(float *)(iVar7 + 0x34);
            *(float *)(iVar7 + 0x88) = fVar15 - *(float *)(iVar7 + 0x38);
            uVar5 = tVector::Normalize((tVector *)(iVar7 + 0x80));
            iVar11 = *(int *)(param_2 + 0x50) + iVar11;
            iVar10 = *(int *)(param_2 + 0x50) + iVar8;
            fVar15 = *(float *)(iVar10 + 0x38);
            fVar14 = *(float *)(iVar10 + 0x34);
            fVar4 = *(float *)(iVar11 + 0x38);
            *(float *)(iVar11 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar11 + 0x30);
            *(float *)(iVar11 + 0x84) = fVar14 - *(float *)(iVar11 + 0x34);
            *(undefined4 *)(iVar7 + 0x8c) = uVar5;
            *(float *)(iVar11 + 0x88) = fVar15 - fVar4;
            uVar5 = tVector::Normalize((tVector *)(iVar11 + 0x80));
            iVar10 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar11 + 0x8c) = uVar5;
            iVar11 = iVar8;
          } while (iVar2 < iVar10);
        }
        uVar5 = DAT_00054d58;
        fVar14 = DAT_00054d54;
        iVar11 = *(int *)(param_2 + 0x50) + iVar10 * 0xa8;
        iVar10 = *(int *)(param_2 + 0x4c) + iVar10 * 0xa8;
        *(float *)(iVar10 + 0x8c) = DAT_00054d54;
        *(float *)(iVar10 + 0x88) = fVar14;
        *(undefined4 *)(iVar10 + 0x84) = uVar5;
        *(undefined4 *)(iVar10 + 0x80) = uVar5;
        *(float *)(iVar11 + 0x8c) = fVar14;
        *(undefined4 *)(iVar11 + 0x80) = uVar5;
        *(float *)(iVar11 + 0x88) = fVar14;
        *(undefined4 *)(iVar11 + 0x84) = uVar5;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar2 = *(int *)(param_2 + 0x4c);
    iVar11 = iVar11 + 1;
    iVar7 = iVar7 + 1;
    iVar10 = iVar8;
  } while( true );
}
