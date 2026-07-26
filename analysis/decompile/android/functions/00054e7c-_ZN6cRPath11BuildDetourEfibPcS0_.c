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
  int iVar3;
  int iVar4;
  tMatrix *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;

  *(undefined4 *)(param_2 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_2 + 0x2c) = 0x23;
  *(char **)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x40) = 0x42380000;
  *(undefined4 *)(param_2 + 0x38) = 0x2e;
  iVar6 = 0;
  *(undefined1 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  GetNodes((cRPath *)param_2);
  iVar4 = *(int *)(param_2 + 0x4c);
  *(undefined1 *)(param_2 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(param_2 + 0x48),(byte)(in_fpscr >> 0x16) & 3
                                       );
    ptVar5 = (tMatrix *)(iVar4 + iVar6);
    *(undefined4 *)(ptVar5 + 0x98) = 0;
    *(undefined4 *)(ptVar5 + 0x94) = 0;
    iVar8 = iVar1 + 1;
    uVar12 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(ptVar5 + 0x90) = fVar10 * 0.5 - 4.0;
    tMatrix::Identity(ptVar5);
    iVar1 = *(int *)(param_2 + 0x50);
    iVar4 = *(int *)(param_2 + 0x4c) + iVar6;
    *(undefined4 *)(iVar4 + 0x38) = uVar12;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar1 + iVar6));
    iVar4 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar6;
    *(undefined4 *)(iVar3 + 0x38) = uVar12;
    iVar1 = iVar4 + iVar6;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    iVar1 = iVar8;
  } while (iVar8 != 3);
  iVar6 = 1;
  iVar1 = 0x1f8;
  iVar4 = 0;
  do {
    VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (float)Sin(fVar10);
    fVar10 = (float)Cos(fVar10);
    iVar3 = *(int *)(param_2 + 0x4c);
    fVar10 = (float)Cos(fVar10);
    fVar11 = *(float *)(*(int *)(param_2 + 0x4c) + 0x90);
    ptVar5 = (tMatrix *)(*(int *)(param_2 + 0x4c) + iVar1);
    *(undefined4 *)(ptVar5 + 0x98) = 0;
    *(undefined4 *)(ptVar5 + 0x94) = 0;
    *(float *)(iVar3 + iVar1 + 0x90) = fVar10 * fVar11;
    tMatrix::Identity(ptVar5);
    uVar12 = VectorSignedToFloat(iVar4 + 3,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = *(int *)(param_2 + 0x50);
    iVar8 = *(int *)(param_2 + 0x4c) + iVar1;
    *(undefined4 *)(iVar8 + 0x34) = 0;
    *(undefined4 *)(iVar8 + 0x30) = *(undefined4 *)(iVar8 + 0x90);
    *(undefined4 *)(iVar8 + 0x38) = uVar12;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar1));
    iVar8 = *(int *)(param_2 + 0x4c);
    iVar3 = *(int *)(param_2 + 0x50) + iVar1;
    *(undefined4 *)(iVar3 + 0x38) = uVar12;
    ptVar5 = (tMatrix *)(iVar8 + iVar1);
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(ptVar5 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = *(undefined4 *)(ptVar5 + 0x34);
    if (iVar4 == 0) {
      tMatrix::RotIdentity(ptVar5);
      fVar10 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_2 + 0x50) + iVar1));
    }
    else {
      iVar7 = iVar1 + -0xa8;
      fVar9 = *(float *)(ptVar5 + 0x38);
      iVar8 = iVar8 + iVar7;
      fVar10 = *(float *)(ptVar5 + 0x34);
      fVar11 = *(float *)(ptVar5 + 0x30);
      *(undefined4 *)(iVar8 + 0x18) = 0;
      *(undefined4 *)(iVar8 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar8 + 0x10) = 0;
      *(float *)(iVar8 + 0x24) = fVar10 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x20) = fVar11 - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x28) = fVar9 - *(float *)(iVar8 + 0x38);
      tVector::Normalize((tVector *)(iVar8 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x4c) + iVar7);
      fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x4c) + iVar7),fVar10);
      iVar3 = *(int *)(param_2 + 0x50) + iVar1;
      iVar8 = *(int *)(param_2 + 0x50) + iVar7;
      fVar9 = *(float *)(iVar3 + 0x38);
      fVar10 = *(float *)(iVar3 + 0x34);
      fVar11 = *(float *)(iVar3 + 0x30);
      *(undefined4 *)(iVar8 + 0x18) = 0;
      *(undefined4 *)(iVar8 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar8 + 0x10) = 0;
      *(float *)(iVar8 + 0x24) = fVar10 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x20) = fVar11 - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x28) = fVar9 - *(float *)(iVar8 + 0x38);
      tVector::Normalize((tVector *)(iVar8 + 0x20));
      ptVar2 = (tVector *)(*(int *)(param_2 + 0x50) + iVar7);
      fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
      fVar10 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_2 + 0x50) + iVar7),fVar10);
      iVar7 = *(int *)(param_2 + 0x50) + iVar7;
      *(float *)(iVar7 + 0x34) = *(float *)(iVar7 + 0x34) + *(float *)(iVar7 + 0x14) * 0.49;
      *(float *)(iVar7 + 0x38) = *(float *)(iVar7 + 0x38) + *(float *)(iVar7 + 0x18) * 0.49;
      *(float *)(iVar7 + 0x30) = *(float *)(iVar7 + 0x30) + *(float *)(iVar7 + 0x10) * 0.49;
      if (0x28 < iVar6) {
        iVar1 = *(int *)(param_2 + 0x4c);
        iVar6 = 0x2b;
        iVar4 = 0x1c38;
        do {
          uVar12 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
          ptVar5 = (tMatrix *)(iVar1 + iVar4);
          *(undefined4 *)(ptVar5 + 0x90) = *(undefined4 *)(iVar1 + 0x90);
          *(undefined4 *)(ptVar5 + 0x98) = 0;
          *(undefined4 *)(ptVar5 + 0x94) = 0;
          tMatrix::Identity(ptVar5);
          iVar1 = *(int *)(param_2 + 0x50);
          iVar6 = iVar6 + 1;
          iVar3 = *(int *)(param_2 + 0x4c) + iVar4;
          *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
          *(undefined4 *)(iVar3 + 0x34) = 0;
          *(undefined4 *)(iVar3 + 0x38) = uVar12;
          tMatrix::Identity((tMatrix *)(iVar1 + iVar4));
          iVar8 = *(int *)(param_2 + 0x50);
          iVar1 = *(int *)(param_2 + 0x4c);
          iVar7 = iVar8 + iVar4;
          *(undefined4 *)(iVar7 + 0x38) = uVar12;
          iVar3 = iVar1 + iVar4;
          iVar4 = iVar4 + 0xa8;
          uVar12 = *(undefined4 *)(iVar3 + 0x90);
          *(undefined4 *)(iVar7 + 0x34) = 0x3efae148;
          *(undefined4 *)(iVar7 + 0x30) = uVar12;
        } while (iVar4 != 0x1e30);
        if (*(int *)(param_2 + 0x38) < 2) {
          iVar4 = *(int *)(param_2 + 0x38) + -1;
        }
        else {
          iVar3 = 0;
          iVar6 = 0;
          while( true ) {
            iVar8 = iVar6 + 0xa8;
            iVar4 = iVar1 + iVar6;
            iVar1 = iVar1 + iVar8;
            fVar11 = *(float *)(iVar1 + 0x38);
            fVar10 = *(float *)(iVar1 + 0x34);
            iVar3 = iVar3 + 1;
            *(float *)(iVar4 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar4 + 0x30);
            *(float *)(iVar4 + 0x84) = fVar10 - *(float *)(iVar4 + 0x34);
            *(float *)(iVar4 + 0x88) = fVar11 - *(float *)(iVar4 + 0x38);
            uVar12 = tVector::Normalize((tVector *)(iVar4 + 0x80));
            iVar6 = *(int *)(param_2 + 0x50) + iVar6;
            iVar1 = *(int *)(param_2 + 0x50) + iVar8;
            fVar11 = *(float *)(iVar1 + 0x38);
            fVar10 = *(float *)(iVar1 + 0x34);
            fVar9 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar6 + 0x80) = *(float *)(iVar1 + 0x30) - *(float *)(iVar6 + 0x30);
            *(float *)(iVar6 + 0x84) = fVar10 - *(float *)(iVar6 + 0x34);
            *(undefined4 *)(iVar4 + 0x8c) = uVar12;
            *(float *)(iVar6 + 0x88) = fVar11 - fVar9;
            uVar12 = tVector::Normalize((tVector *)(iVar6 + 0x80));
            iVar4 = *(int *)(param_2 + 0x38) + -1;
            *(undefined4 *)(iVar6 + 0x8c) = uVar12;
            if (iVar4 <= iVar3) break;
            iVar1 = *(int *)(param_2 + 0x4c);
            iVar6 = iVar8;
          }
          iVar1 = *(int *)(param_2 + 0x4c);
          iVar8 = *(int *)(param_2 + 0x50);
        }
        iVar8 = iVar8 + iVar4 * 0xa8;
        iVar1 = iVar1 + iVar4 * 0xa8;
        *(undefined4 *)(iVar1 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar1 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar1 + 0x84) = 0;
        *(undefined4 *)(iVar1 + 0x80) = 0;
        *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x80) = 0;
        *(undefined4 *)(iVar8 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar8 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_2);
        return;
      }
    }
    iVar4 = iVar4 + 1;
    iVar1 = iVar1 + 0xa8;
    iVar6 = iVar6 + 1;
  } while( true );
}
