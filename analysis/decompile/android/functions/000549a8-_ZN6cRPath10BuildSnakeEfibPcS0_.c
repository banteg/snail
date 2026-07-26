/*
 * mangled: _ZN6cRPath10BuildSnakeEfibPcS0_
 * demangled: cRPath::BuildSnake(float, int, bool, char*, char*)
 * address: 000549a8
 * size: 1200
 */

/* cRPath::BuildSnake(float, int, bool, char*, char*) */

void cRPath::BuildSnake(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  tVector *ptVar2;
  tMatrix *ptVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 uVar15;
  float fVar16;

  iVar7 = 0;
  iVar8 = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0x24;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x40) = 0x41d80000;
  *(undefined4 *)(param_2 + 0x38) = 0x1b;
  GetNodes((cRPath *)param_2);
  *(undefined1 *)(param_2 + 0x84) = 0;
  do {
    uVar15 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = iVar8 + 1;
    ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7);
    *(undefined4 *)(ptVar3 + 0x90) = 0;
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    tMatrix::Identity(ptVar3);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar7;
    *(undefined4 *)(iVar4 + 0x38) = uVar15;
    *(undefined4 *)(iVar4 + 0x30) = 0;
    *(undefined4 *)(iVar4 + 0x34) = 0;
    tMatrix::Identity((tMatrix *)(iVar1 + iVar7));
    iVar1 = *(int *)(param_2 + 0x50) + iVar7;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar1 + 0x38) = uVar15;
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(undefined4 *)(iVar1 + 0x34) = 0x3efae148;
  } while (iVar8 != 6);
  iVar1 = *(int *)(param_2 + 0x4c);
  iVar8 = 0xfc0;
  iVar7 = 0x18;
  do {
    fVar12 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar3 = (tMatrix *)(iVar1 + iVar8);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    uVar15 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar3 + 0x90) = fVar12 * -0.5 + 4.0;
    tMatrix::Identity(ptVar3);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar8;
    *(undefined4 *)(iVar4 + 0x38) = uVar15;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar8));
    iVar1 = *(int *)(param_2 + 0x4c);
    iVar5 = *(int *)(param_2 + 0x50) + iVar8;
    *(undefined4 *)(iVar5 + 0x38) = uVar15;
    iVar4 = iVar1 + iVar8;
    iVar8 = iVar8 + 0xa8;
    uVar15 = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar5 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar5 + 0x30) = uVar15;
    iVar7 = iVar7 + 1;
  } while (iVar8 != 0x11b8);
  iVar4 = 1;
  iVar8 = 0;
  iVar7 = 0x348;
  do {
    VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    fVar16 = *(float *)(iVar1 + 0x1050);
    iVar5 = iVar7 + 0xa8;
    fVar12 = (float)Cos(fVar12);
    ptVar3 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar5);
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    *(float *)(iVar1 + iVar5 + 0x90) = fVar16 * (fVar12 * -0.5 + 0.5);
    fVar12 = (float)tMatrix::Identity(ptVar3);
    iVar9 = *(int *)(param_2 + 0x4c) + iVar5;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    fVar12 = (float)Cos(fVar12);
    uVar15 = VectorSignedToFloat(iVar8 + 6,(byte)(in_fpscr >> 0x16) & 3);
    iVar1 = *(int *)(param_2 + 0x50);
    *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar5 + 0x38) = uVar15;
    *(float *)(iVar9 + 0x34) = -(1.0 - fVar12);
    fVar12 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar5));
    iVar1 = *(int *)(param_2 + 0x50) + iVar5;
    *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(*(int *)(param_2 + 0x4c) + iVar5 + 0x90);
    fVar12 = (float)Cos(fVar12);
    *(undefined4 *)(*(int *)(param_2 + 0x50) + iVar5 + 0x38) = uVar15;
    *(float *)(iVar1 + 0x34) = 0.49 - (1.0 - fVar12);
    if (iVar8 == 0) {
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7));
      fVar12 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar7));
    }
    else {
      iVar9 = *(int *)(param_2 + 0x4c);
      iVar6 = iVar9 + iVar7;
      iVar1 = iVar9 + iVar5;
      fVar13 = *(float *)(iVar6 + 0x30);
      fVar10 = *(float *)(iVar1 + 0x38);
      fVar12 = *(float *)(iVar1 + 0x34);
      fVar11 = *(float *)(iVar6 + 0x34);
      fVar16 = *(float *)(iVar1 + 0x30);
      *(undefined4 *)(iVar6 + 8) = 0;
      *(undefined4 *)(iVar6 + 4) = 0;
      *(undefined4 *)(iVar9 + iVar7) = 0x3f800000;
      *(float *)(iVar6 + 0x24) = fVar12 - fVar11;
      *(float *)(iVar6 + 0x20) = fVar16 - fVar13;
      *(float *)(iVar6 + 0x28) = fVar10 - *(float *)(iVar6 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
      tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      iVar9 = *(int *)(param_2 + 0x50);
      iVar6 = iVar9 + iVar7;
      iVar1 = iVar9 + iVar5;
      fVar13 = *(float *)(iVar6 + 0x30);
      fVar10 = *(float *)(iVar1 + 0x38);
      fVar12 = *(float *)(iVar1 + 0x34);
      fVar16 = *(float *)(iVar1 + 0x30);
      fVar11 = *(float *)(iVar6 + 0x34);
      fVar14 = *(float *)(iVar6 + 0x38);
      *(undefined4 *)(iVar6 + 8) = 0;
      *(undefined4 *)(iVar9 + iVar7) = 0x3f800000;
      *(undefined4 *)(iVar6 + 4) = 0;
      *(float *)(iVar6 + 0x20) = fVar16 - fVar13;
      *(float *)(iVar6 + 0x24) = fVar12 - fVar11;
      *(float *)(iVar6 + 0x28) = fVar10 - fVar14;
      tVector::Normalize((tVector *)(iVar6 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar7);
      fVar12 = (float)tVector::Cross(ptVar2 + 0x10,ptVar2 + 0x20,ptVar2);
      if (0x11 < iVar4) {
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar7 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar1 = 0;
          iVar8 = 0;
          do {
            iVar5 = iVar8 + 0xa8;
            iVar1 = iVar1 + 1;
            iVar4 = *(int *)(param_2 + 0x4c) + iVar8;
            iVar7 = *(int *)(param_2 + 0x4c) + iVar5;
            fVar16 = *(float *)(iVar7 + 0x38);
            fVar12 = *(float *)(iVar7 + 0x34);
            *(float *)(iVar4 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar4 + 0x30);
            *(float *)(iVar4 + 0x84) = fVar12 - *(float *)(iVar4 + 0x34);
            *(float *)(iVar4 + 0x88) = fVar16 - *(float *)(iVar4 + 0x38);
            uVar15 = tVector::Normalize((tVector *)(iVar4 + 0x80));
            iVar8 = *(int *)(param_2 + 0x50) + iVar8;
            iVar7 = *(int *)(param_2 + 0x50) + iVar5;
            fVar16 = *(float *)(iVar7 + 0x38);
            fVar12 = *(float *)(iVar7 + 0x34);
            fVar10 = *(float *)(iVar8 + 0x38);
            *(float *)(iVar8 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar8 + 0x30);
            *(float *)(iVar8 + 0x84) = fVar12 - *(float *)(iVar8 + 0x34);
            *(undefined4 *)(iVar4 + 0x8c) = uVar15;
            *(float *)(iVar8 + 0x88) = fVar16 - fVar10;
            uVar15 = tVector::Normalize((tVector *)(iVar8 + 0x80));
            iVar7 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar8 + 0x8c) = uVar15;
            iVar8 = iVar5;
          } while (iVar1 < iVar7);
        }
        iVar8 = *(int *)(param_2 + 0x50) + iVar7 * 0xa8;
        iVar7 = *(int *)(param_2 + 0x4c) + iVar7 * 0xa8;
        *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar7 + 0x84) = 0;
        *(undefined4 *)(iVar7 + 0x80) = 0;
        *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x80) = 0;
        *(undefined4 *)(iVar8 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar1 = *(int *)(param_2 + 0x4c);
    iVar8 = iVar8 + 1;
    iVar4 = iVar4 + 1;
    iVar7 = iVar5;
  } while( true );
}
