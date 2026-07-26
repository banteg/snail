/*
 * mangled: _ZN6cRPath9BuildHumpEffibPcS0_
 * demangled: cRPath::BuildHump(float, float, int, bool, char*, char*)
 * address: 00051bec
 * size: 1812
 */

/* cRPath::BuildHump(float, float, int, bool, char*, char*) */

void cRPath::BuildHump(float param_1,float param_2,int param_3,bool param_4,char *param_5,
                      char *param_6)

{
  int iVar1;
  int iVar2;
  tVector *ptVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  int iVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined8 uVar14;
  float fVar15;

  *(uint *)((int)param_1 + 0x48) = (uint)param_4;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x14;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar9 = (int)(param_2 * 4.0);
  iVar7 = iVar9 + 0xe;
  *(int *)((int)param_1 + 0x38) = iVar7;
  uVar10 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar10;
  fVar15 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
  uVar14 = CONCAT44(fVar15,param_3);
  fVar15 = (fVar15 / 6.2831855) * 0.6;
  uVar10 = RShellMemoryMalloc(iVar7 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar10;
  uVar10 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar10;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar2 = 0;
    iVar1 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(iVar1 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
      iVar4 = iVar1 + *(int *)((int)param_1 + 0x4c);
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
    } while (iVar2 < *(int *)((int)param_1 + 0x38));
  }
  iVar2 = 0;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  iVar1 = 0;
  do {
    fVar8 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) = fVar8 * 0.5 - 4.0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar1 + 1;
    iVar4 = iVar2 + *(int *)((int)param_1 + 0x4c);
    uVar10 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = uVar10;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    iVar1 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar1 + 0x38) = uVar10;
    iVar1 = iVar6;
  } while (iVar6 != 7);
  iVar2 = iVar9 * 0xa8 + 0x498;
  iVar1 = iVar9 + 7;
  do {
    fVar8 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90) = fVar8 * -0.5 + 4.0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar6 = iVar1 + 1;
    iVar4 = iVar2 + *(int *)((int)param_1 + 0x4c);
    uVar10 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = uVar10;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    iVar1 = *(int *)((int)param_1 + 0x50) + iVar2;
    iVar2 = iVar2 + 0xa8;
    *(undefined4 *)(iVar1 + 0x38) = uVar10;
    iVar1 = iVar6;
  } while (iVar6 != iVar7);
  if (0 < iVar9) {
    iVar7 = 0x498;
    iVar1 = 0;
    do {
      while( true ) {
        iVar2 = *(int *)((int)param_1 + 0x4c);
        fVar13 = 1.0;
        fVar8 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
        fVar11 = *(float *)(iVar2 + 0x90);
        fVar12 = (fVar8 * 6.2831855) / (float)((ulonglong)uVar14 >> 0x20);
        fVar8 = (float)Cos(fVar12 * 0.5);
        *(float *)(iVar7 + iVar2 + 0x90) = fVar11 * fVar8;
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
        *(float *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0x9c) = fVar13;
        tMatrix::Identity((tMatrix *)(iVar7 + *(int *)((int)param_1 + 0x4c)));
        iVar2 = iVar7 + *(int *)((int)param_1 + 0x4c);
        *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
        iVar2 = *(int *)((int)param_1 + 0x4c);
        fVar8 = (float)Cos(fVar12);
        *(float *)(iVar7 + iVar2 + 0x34) = (fVar13 - fVar8) * fVar15 * (float)uVar14;
        uVar10 = VectorSignedToFloat(iVar1 + 7,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar10;
        tMatrix::Identity((tMatrix *)(iVar7 + *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x50) + 0x30) =
             *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x4c) + 0x90);
        iVar2 = *(int *)((int)param_1 + 0x50);
        fVar8 = (float)Cos(fVar12);
        *(float *)(iVar7 + iVar2 + 0x34) = (fVar13 - fVar8) * fVar15 * (float)uVar14 + 0.49;
        *(undefined4 *)(iVar7 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar10;
        if (0 < iVar1) break;
        iVar1 = iVar1 + 1;
        tMatrix::RotIdentity((tMatrix *)(iVar7 + *(int *)((int)param_1 + 0x4c) + -0xa8));
        tMatrix::RotIdentity((tMatrix *)(iVar7 + *(int *)((int)param_1 + 0x50) + -0xa8));
        iVar7 = iVar7 + 0xa8;
        if (iVar1 == iVar9) goto LAB_0005219c;
      }
      iVar1 = iVar1 + 1;
      pfVar5 = (float *)(iVar7 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      *pfVar5 = fVar13;
      pfVar5[2] = 0.0;
      pfVar5[1] = 0.0;
      iVar2 = iVar7 + *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar4 = iVar7 + *(int *)((int)param_1 + 0x4c);
      fVar8 = *(float *)(iVar4 + 0x34);
      fVar11 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x24) = fVar8 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x28) = fVar11 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + *(int *)((int)param_1 + 0x4c) + -0x88));
      ptVar3 = (tVector *)(iVar7 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      pfVar5 = (float *)(iVar7 + *(int *)((int)param_1 + 0x50) + -0xa8);
      *pfVar5 = fVar13;
      pfVar5[2] = 0.0;
      pfVar5[1] = 0.0;
      iVar2 = iVar7 + *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar4 = iVar7 + *(int *)((int)param_1 + 0x50);
      fVar8 = *(float *)(iVar4 + 0x34);
      fVar11 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x24) = fVar8 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x28) = fVar11 - *(float *)(iVar2 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + *(int *)((int)param_1 + 0x50) + -0x88));
      ptVar3 = (tVector *)(iVar7 + *(int *)((int)param_1 + 0x50) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      iVar7 = iVar7 + 0xa8;
    } while (iVar1 != iVar9);
  }
LAB_0005219c:
  iVar7 = *(int *)((int)param_1 + 0x38);
  if (0 < iVar7 + -1) {
    iVar1 = 0;
    iVar9 = 0;
    do {
      iVar1 = iVar1 + 1;
      iVar7 = iVar9 + *(int *)((int)param_1 + 0x4c);
      iVar2 = iVar9 + *(int *)((int)param_1 + 0x4c) + 0xa8;
      fVar15 = *(float *)(iVar2 + 0x34);
      fVar8 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar15 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar8 - *(float *)(iVar7 + 0x38);
      iVar7 = iVar9 + *(int *)((int)param_1 + 0x4c);
      uVar10 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      *(undefined4 *)(iVar7 + 0x8c) = uVar10;
      iVar7 = iVar9 + *(int *)((int)param_1 + 0x50);
      iVar2 = iVar9 + *(int *)((int)param_1 + 0x50) + 0xa8;
      fVar15 = *(float *)(iVar2 + 0x34);
      fVar8 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar2 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar15 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar8 - *(float *)(iVar7 + 0x38);
      iVar7 = iVar9 + *(int *)((int)param_1 + 0x50);
      uVar10 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar9 = iVar9 + 0xa8;
      *(undefined4 *)(iVar7 + 0x8c) = uVar10;
      iVar7 = *(int *)((int)param_1 + 0x38);
    } while (iVar1 < iVar7 + -1);
  }
  iVar7 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar7 * 0xa8;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) =
       0x3f800000;
  iVar7 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) =
       0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
