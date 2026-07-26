/*
 * mangled: _ZN6cRPath9BuildHillEiffbPcS0_
 * demangled: cRPath::BuildHill(int, float, float, bool, char*, char*)
 * address: 00053ad0
 * size: 1700
 */

/* cRPath::BuildHill(int, float, float, bool, char*, char*) */

void cRPath::BuildHill(int param_1,float param_2,float param_3,bool param_4,char *param_5,
                      char *param_6)

{
  float fVar1;
  int iVar2;
  tVector *ptVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  uint in_fpscr;
  int iVar8;
  undefined4 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  iVar8 = (int)(float)(uint)param_4;
  *(undefined4 *)(param_1 + 0x2c) = 0x14;
  *(float *)(param_1 + 0x48) = param_2;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar4 = iVar8 + 2;
  *(int *)(param_1 + 0x38) = iVar4;
  iVar7 = iVar8 + 1;
  uVar9 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_1 + 0x40) = uVar9;
  uVar9 = RShellMemoryMalloc(iVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar9;
  uVar9 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar9;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar2 = 0;
    iVar4 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar4;
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar2 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  if (((uint)param_5 & 0xff) == 0) {
    fVar1 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3)
    ;
    *(float *)(*(int *)(param_1 + 0x4c) + 0x90) = fVar1 * 0.5 - 4.0;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90) = 0;
  }
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x4c));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x38) = 0;
  if (((uint)param_5 & 0xff) == 0) {
    fVar1 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x48),(byte)(in_fpscr >> 0x16) & 3)
    ;
    *(float *)(*(int *)(param_1 + 0x4c) + iVar7 * 0xa8 + 0x90) = fVar1 * 0.5 - 4.0;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar7 * 0xa8 + 0x90) = 0;
  }
  iVar2 = iVar7 * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x94) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar4 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar9 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x34) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x38) = uVar9;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x38) = uVar9;
  if (0 < iVar8) {
    fVar1 = 0.0;
    iVar7 = 0;
    iVar4 = 0xa8;
    fVar13 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    do {
      while( true ) {
        fVar10 = 1.0;
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x90) =
             *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
        fVar11 = 0.5;
        iVar7 = iVar7 + 1;
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
        fVar12 = (fVar1 * 6.2831855) / fVar13;
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x4c)));
        iVar2 = iVar4 + *(int *)(param_1 + 0x4c);
        *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
        iVar2 = *(int *)(param_1 + 0x4c);
        fVar1 = (float)Cos(fVar12);
        *(float *)(iVar4 + iVar2 + 0x34) = (fVar10 - fVar1) * fVar11 * param_3;
        fVar1 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x38) = fVar1;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x50)));
        *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x50) + 0x30) =
             *(undefined4 *)(iVar4 + *(int *)(param_1 + 0x4c) + 0x90);
        iVar2 = *(int *)(param_1 + 0x50);
        fVar12 = (float)Cos(fVar12);
        *(float *)(iVar4 + iVar2 + 0x34) = (fVar10 - fVar12) * fVar11 * param_3 + 0.49;
        *(float *)(iVar4 + *(int *)(param_1 + 0x50) + 0x38) = fVar1;
        if (iVar7 != 1) break;
        tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x4c) + -0xa8));
        tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x50) + -0xa8));
        iVar4 = iVar4 + 0xa8;
        if (iVar8 == 1) goto LAB_00053f88;
      }
      pfVar6 = (float *)(iVar4 + *(int *)(param_1 + 0x4c) + -0xa8);
      *pfVar6 = fVar10;
      pfVar6[2] = 0.0;
      pfVar6[1] = 0.0;
      iVar2 = iVar4 + *(int *)(param_1 + 0x4c) + -0xa8;
      iVar5 = iVar4 + *(int *)(param_1 + 0x4c);
      fVar12 = *(float *)(iVar5 + 0x34);
      fVar11 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar2 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x24) = fVar12 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x28) = fVar11 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)(param_1 + 0x4c) + -0x88));
      ptVar3 = (tVector *)(iVar4 + *(int *)(param_1 + 0x4c) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      pfVar6 = (float *)(iVar4 + *(int *)(param_1 + 0x50) + -0xa8);
      *pfVar6 = fVar10;
      pfVar6[2] = 0.0;
      pfVar6[1] = 0.0;
      iVar2 = iVar4 + *(int *)(param_1 + 0x50) + -0xa8;
      iVar5 = iVar4 + *(int *)(param_1 + 0x50);
      fVar12 = *(float *)(iVar5 + 0x34);
      fVar10 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar2 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x24) = fVar12 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x28) = fVar10 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)(param_1 + 0x50) + -0x88));
      ptVar3 = (tVector *)(iVar4 + *(int *)(param_1 + 0x50) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      iVar4 = iVar4 + 0xa8;
    } while (iVar7 != iVar8);
  }
LAB_00053f88:
  iVar4 = *(int *)(param_1 + 0x38);
  if (0 < iVar4 + -1) {
    iVar8 = 0;
    iVar7 = 0;
    do {
      iVar8 = iVar8 + 1;
      iVar4 = *(int *)(param_1 + 0x4c) + iVar7;
      iVar2 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar7;
      fVar1 = *(float *)(iVar2 + 0x34);
      fVar13 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar1 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar13 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar7 + *(int *)(param_1 + 0x4c);
      uVar9 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      *(undefined4 *)(iVar4 + 0x8c) = uVar9;
      iVar4 = *(int *)(param_1 + 0x50) + iVar7;
      iVar2 = *(int *)(param_1 + 0x50) + 0xa8 + iVar7;
      fVar1 = *(float *)(iVar2 + 0x34);
      fVar13 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar1 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar13 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar7 + *(int *)(param_1 + 0x50);
      uVar9 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar7 = iVar7 + 0xa8;
      *(undefined4 *)(iVar4 + 0x8c) = uVar9;
      iVar4 = *(int *)(param_1 + 0x38);
    } while (iVar8 < iVar4 + -1);
  }
  iVar4 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar4 * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) = 0x3f800000;
  iVar4 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
