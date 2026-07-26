/*
 * mangled: _ZN6cRPath17BuildSlalomDoubleEiibPcS0_
 * demangled: cRPath::BuildSlalomDouble(int, int, bool, char*, char*)
 * address: 00054114
 * size: 1208
 */

/* cRPath::BuildSlalomDouble(int, int, bool, char*, char*) */

void cRPath::BuildSlalomDouble(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  tMatrix *ptVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined4 uVar13;
  undefined4 uVar14;

  *(undefined4 *)(param_1 + 0x2c) = 0x28;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)(param_1 + 0x40) = 0x428c0000;
  *(undefined4 *)(param_1 + 0x38) = 0x46;
  iVar5 = 0;
  *(undefined1 *)(param_1 + 0x30) = 0;
  iVar6 = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  GetNodes((cRPath *)param_1);
  iVar7 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  do {
    uVar13 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    ptVar8 = (tMatrix *)(iVar7 + iVar5);
    *(undefined4 *)(ptVar8 + 0x90) = 0;
    *(undefined4 *)(ptVar8 + 0x98) = 0;
    *(undefined4 *)(ptVar8 + 0x94) = 0;
    *(undefined4 *)(ptVar8 + 0xa0) = 0;
    *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
    iVar6 = iVar6 + 1;
    tMatrix::Identity(ptVar8);
    iVar7 = *(int *)(param_1 + 0x50);
    iVar2 = *(int *)(param_1 + 0x4c) + iVar5;
    *(undefined4 *)(iVar2 + 0x34) = 0;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    *(undefined4 *)(iVar2 + 0x38) = uVar13;
    tMatrix::Identity((tMatrix *)(iVar7 + iVar5));
    iVar7 = *(int *)(param_1 + 0x4c);
    iVar3 = *(int *)(param_1 + 0x50) + iVar5;
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    iVar2 = iVar7 + iVar5;
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
  } while (iVar6 != 4);
  iVar6 = 0x42;
  iVar5 = 0x2b50;
  do {
    uVar13 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    ptVar8 = (tMatrix *)(iVar7 + iVar5);
    *(undefined4 *)(ptVar8 + 0x90) = 0;
    *(undefined4 *)(ptVar8 + 0x98) = 0;
    *(undefined4 *)(ptVar8 + 0x94) = 0;
    *(undefined4 *)(ptVar8 + 0xa0) = 0;
    *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
    iVar6 = iVar6 + 1;
    tMatrix::Identity(ptVar8);
    iVar7 = *(int *)(param_1 + 0x50);
    iVar2 = *(int *)(param_1 + 0x4c) + iVar5;
    *(undefined4 *)(iVar2 + 0x34) = 0;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
    *(undefined4 *)(iVar2 + 0x38) = uVar13;
    fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar7 + iVar5));
    iVar7 = *(int *)(param_1 + 0x4c);
    iVar3 = *(int *)(param_1 + 0x50) + iVar5;
    *(undefined4 *)(iVar3 + 0x38) = uVar13;
    iVar2 = iVar7 + iVar5;
    iVar5 = iVar5 + 0xa8;
    uVar13 = *(undefined4 *)(iVar2 + 0x90);
    *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
    *(undefined4 *)(iVar3 + 0x30) = uVar13;
  } while (iVar5 != 0x2df0);
  iVar2 = 1;
  iVar6 = 0;
  iVar5 = 0x1f8;
  do {
    fVar12 = (float)VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = iVar5 + 0xa8;
    fVar12 = fVar12 / 62.0 - 0.5;
    fVar10 = (float)Sin(fVar10);
    ptVar8 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar3);
    *(undefined4 *)(ptVar8 + 0x98) = 0;
    *(undefined4 *)(ptVar8 + 0x94) = 0;
    *(undefined4 *)(ptVar8 + 0xa0) = 0;
    *(undefined4 *)(ptVar8 + 0x9c) = 0x3f800000;
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f;
    if (SUB41(in_fpscr >> 0x1f,0)) {
      fVar12 = fVar12 + 1.0;
    }
    else {
      fVar12 = 1.0 - fVar12;
    }
    *(float *)(iVar7 + iVar3 + 0x90) = fVar10 * 4.4444447 * fVar12 * fVar12;
    uVar14 = VectorSignedToFloat(iVar6 + 4,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (float)tMatrix::Identity(ptVar8);
    iVar9 = *(int *)(param_1 + 0x4c) + iVar3;
    *(undefined4 *)(iVar9 + 0x30) = *(undefined4 *)(iVar9 + 0x90);
    fVar10 = (float)Cos(fVar10);
    iVar7 = *(int *)(param_1 + 0x50);
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar3 + 0x38) = uVar14;
    *(float *)(iVar9 + 0x34) = 1.0 - fVar10;
    tMatrix::Identity((tMatrix *)(iVar7 + iVar3));
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar9 = iVar4 + iVar3;
    fVar10 = *(float *)(iVar9 + 0x34);
    iVar7 = *(int *)(param_1 + 0x50) + iVar3;
    uVar13 = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(iVar7 + 0x38) = uVar14;
    *(undefined4 *)(iVar7 + 0x30) = uVar13;
    *(float *)(iVar7 + 0x34) = fVar10 + 0.49;
    if (iVar6 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar4 + iVar5));
      fVar10 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar5));
    }
    else {
      iVar4 = iVar4 + iVar5;
      fVar11 = *(float *)(iVar9 + 0x38);
      fVar10 = *(float *)(iVar9 + 0x34);
      fVar12 = *(float *)(iVar9 + 0x30);
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      *(float *)(iVar4 + 0x24) = fVar10 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x20) = fVar12 - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x28) = fVar11 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar5);
      fVar10 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar5),fVar10);
      iVar7 = *(int *)(param_1 + 0x50) + iVar3;
      iVar9 = *(int *)(param_1 + 0x50) + iVar5;
      fVar11 = *(float *)(iVar7 + 0x38);
      fVar10 = *(float *)(iVar7 + 0x30);
      fVar12 = *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar9 + 0x18) = 0;
      *(undefined4 *)(iVar9 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar9 + 0x10) = 0;
      *(float *)(iVar9 + 0x24) = fVar12 - *(float *)(iVar9 + 0x34);
      *(float *)(iVar9 + 0x28) = fVar11 - *(float *)(iVar9 + 0x38);
      *(float *)(iVar9 + 0x20) = fVar10 - *(float *)(iVar9 + 0x30);
      tVector::Normalize((tVector *)(iVar9 + 0x20));
      ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar5);
      fVar10 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      fVar10 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x50) + iVar5),fVar10);
      if (0x3d < iVar2) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar5 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar7 = 0;
          iVar6 = 0;
          do {
            iVar3 = iVar6 + 0xa8;
            iVar7 = iVar7 + 1;
            iVar2 = *(int *)(param_1 + 0x4c) + iVar6;
            iVar5 = *(int *)(param_1 + 0x4c) + iVar3;
            fVar12 = *(float *)(iVar5 + 0x38);
            fVar10 = *(float *)(iVar5 + 0x34);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar10 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar12 - *(float *)(iVar2 + 0x38);
            uVar13 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            iVar6 = *(int *)(param_1 + 0x50) + iVar6;
            iVar5 = *(int *)(param_1 + 0x50) + iVar3;
            fVar12 = *(float *)(iVar5 + 0x38);
            fVar10 = *(float *)(iVar5 + 0x34);
            fVar11 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar6 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar6 + 0x30);
            *(float *)(iVar6 + 0x84) = fVar10 - *(float *)(iVar6 + 0x34);
            *(undefined4 *)(iVar2 + 0x8c) = uVar13;
            *(float *)(iVar6 + 0x88) = fVar12 - fVar11;
            uVar13 = tVector::Normalize((tVector *)(iVar6 + 0x80));
            iVar5 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar6 + 0x8c) = uVar13;
            iVar6 = iVar3;
          } while (iVar7 < iVar5);
        }
        iVar6 = *(int *)(param_1 + 0x50) + iVar5 * 0xa8;
        iVar5 = *(int *)(param_1 + 0x4c) + iVar5 * 0xa8;
        *(undefined4 *)(iVar5 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x84) = 0;
        *(undefined4 *)(iVar5 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
        *(undefined4 *)(iVar6 + 0x80) = 0;
        *(undefined4 *)(iVar6 + 0x88) = 0x3f800000;
        *(undefined4 *)(iVar6 + 0x84) = 0;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar7 = *(int *)(param_1 + 0x4c);
    iVar6 = iVar6 + 1;
    iVar2 = iVar2 + 1;
    iVar5 = iVar3;
  } while( true );
}
