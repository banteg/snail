/*
 * mangled: _ZN6cRPath8BuildDipEfibPcS0_
 * demangled: cRPath::BuildDip(float, int, bool, char*, char*)
 * address: 000591b8
 * size: 1588
 */

/* cRPath::BuildDip(float, int, bool, char*, char*) */

void cRPath::BuildDip(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

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
  ulonglong uVar14;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x18;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar8 = (int)((float)param_2 * 5.0);
  iVar4 = iVar8 + 2;
  *(int *)((int)param_1 + 0x38) = iVar4;
  uVar9 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar9;
  fVar13 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
  uVar14 = (ulonglong)(uint)fVar13;
  fVar13 = (fVar13 / 6.2831855) * 0.6 * 0.5;
  uVar9 = RShellMemoryMalloc(iVar4 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar9;
  uVar9 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar9;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar2 = 0;
    iVar4 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0xa0) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar4;
      iVar4 = iVar4 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar2 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  iVar4 = (iVar8 + 1) * 0xa8;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
  iVar2 = iVar4 + *(int *)((int)param_1 + 0x4c);
  uVar9 = VectorSignedToFloat(iVar8 + 1,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar9;
  tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar4 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar9;
  if (0 < iVar8) {
    fVar1 = 0.0;
    iVar2 = 0;
    iVar4 = 0xa8;
    do {
      while( true ) {
        fVar11 = 1.0;
        *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90) = 0;
        iVar2 = iVar2 + 1;
        *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x98) = 0;
        fVar12 = (fVar1 * 6.2831855) / (float)uVar14;
        *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x94) = 0;
        *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0xa0) = 0;
        *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
        iVar5 = iVar4 + *(int *)((int)param_1 + 0x4c);
        *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
        iVar5 = *(int *)((int)param_1 + 0x4c);
        fVar1 = (float)Cos(fVar12);
        *(float *)(iVar4 + iVar5 + 0x34) = -((fVar11 - fVar1) * fVar13);
        fVar1 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x38) = fVar1;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x30) =
             *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90);
        iVar5 = *(int *)((int)param_1 + 0x50);
        fVar12 = (float)Cos(fVar12);
        *(float *)(iVar4 + iVar5 + 0x34) = 0.49 - (fVar11 - fVar12) * fVar13;
        *(float *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x38) = fVar1;
        if (iVar2 != 1) break;
        tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0xa8));
        tMatrix::RotIdentity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0xa8));
        iVar4 = iVar4 + 0xa8;
        if (iVar8 == 1) goto LAB_00059680;
      }
      pfVar6 = (float *)(*(int *)((int)param_1 + 0x4c) + -0xa8 + iVar4);
      *pfVar6 = fVar11;
      pfVar6[2] = 0.0;
      pfVar6[1] = 0.0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar4;
      iVar7 = *(int *)((int)param_1 + 0x4c) + iVar4;
      fVar12 = *(float *)(iVar7 + 0x34);
      fVar10 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar7 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar12 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x4c) + -0x88));
      ptVar3 = (tVector *)(*(int *)((int)param_1 + 0x4c) + -0xa8 + iVar4);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      pfVar6 = (float *)(*(int *)((int)param_1 + 0x50) + -0xa8 + iVar4);
      *pfVar6 = fVar11;
      pfVar6[2] = 0.0;
      pfVar6[1] = 0.0;
      iVar5 = *(int *)((int)param_1 + 0x50) + -0xa8 + iVar4;
      iVar7 = *(int *)((int)param_1 + 0x50) + iVar4;
      fVar12 = *(float *)(iVar7 + 0x34);
      fVar11 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar7 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar12 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar11 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)((int)param_1 + 0x50) + -0x88));
      ptVar3 = (tVector *)(*(int *)((int)param_1 + 0x50) + -0xa8 + iVar4);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      iVar4 = iVar4 + 0xa8;
    } while (iVar2 != iVar8);
  }
LAB_00059680:
  iVar4 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar4 + -1) {
    iVar2 = 0;
    iVar8 = 0;
    do {
      iVar2 = iVar2 + 1;
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x4c);
      iVar5 = iVar8 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar13 = *(float *)(iVar5 + 0x34);
      fVar1 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar13 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar1 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x4c);
      uVar9 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      *(undefined4 *)(iVar4 + 0x8c) = uVar9;
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x50);
      iVar5 = iVar8 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar13 = *(float *)(iVar5 + 0x34);
      fVar1 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar13 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar1 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar8 + *(int *)((int)param_1 + 0x50);
      uVar9 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar8 = iVar8 + 0xa8;
      *(undefined4 *)(iVar4 + 0x8c) = uVar9;
      iVar4 = *(int *)((int)param_1 + 0x38);
    } while (iVar2 < iVar4 + -1);
  }
  iVar4 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar4 * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar4 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
