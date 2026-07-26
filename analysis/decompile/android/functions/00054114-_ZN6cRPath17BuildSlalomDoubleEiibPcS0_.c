/*
 * mangled: _ZN6cRPath17BuildSlalomDoubleEiibPcS0_
 * demangled: cRPath::BuildSlalomDouble(int, int, bool, char*, char*)
 * address: 00054114
 * size: 1208
 */

/* cRPath::BuildSlalomDouble(int, int, bool, char*, char*) */

void cRPath::BuildSlalomDouble(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  float fVar1;
  float fVar2;
  tVector *ptVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  tMatrix *ptVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 uVar19;
  undefined4 uVar20;

  fVar16 = DAT_000544c8;
  uVar4 = DAT_000544ac;
  *(undefined4 *)(param_1 + 0x2c) = 0x28;
  *(float *)(param_1 + 0x44) = fVar16;
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)(param_1 + 0x40) = uVar4;
  *(undefined4 *)(param_1 + 0x38) = 0x46;
  iVar8 = 0;
  *(undefined1 *)(param_1 + 0x30) = 0;
  iVar9 = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  uVar4 = DAT_000544cc;
  GetNodes((cRPath *)param_1);
  iVar10 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  fVar14 = DAT_000544b0;
  do {
    uVar19 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(undefined4 *)(ptVar11 + 0x90) = uVar4;
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(float *)(ptVar11 + 0x9c) = fVar16;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x34) = uVar4;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar19;
    tMatrix::Identity((tMatrix *)(iVar10 + iVar8));
    iVar10 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar19;
    iVar5 = iVar10 + iVar8;
    *(float *)(iVar6 + 0x34) = fVar14;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  } while (iVar9 != 4);
  iVar9 = 0x42;
  iVar8 = 0x2b50;
  do {
    uVar19 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar11 = (tMatrix *)(iVar10 + iVar8);
    *(undefined4 *)(ptVar11 + 0x90) = uVar4;
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(float *)(ptVar11 + 0x9c) = fVar16;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar11);
    iVar10 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar5 + 0x34) = uVar4;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar19;
    fVar13 = (float)tMatrix::Identity((tMatrix *)(iVar10 + iVar8));
    iVar10 = *(int *)(param_1 + 0x4c);
    iVar6 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar6 + 0x38) = uVar19;
    iVar5 = iVar10 + iVar8;
    iVar8 = iVar8 + 0xa8;
    uVar19 = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar6 + 0x34) = fVar14;
    *(undefined4 *)(iVar6 + 0x30) = uVar19;
    fVar2 = DAT_000544c0;
    fVar1 = DAT_000544bc;
    fVar18 = DAT_000544b4;
  } while (iVar8 != 0x2df0);
  iVar5 = 1;
  iVar9 = 0;
  iVar8 = 0x1f8;
  do {
    fVar17 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = iVar8 + 0xa8;
    fVar17 = fVar17 / fVar18 - fVar2;
    fVar13 = (float)Sin(fVar13);
    ptVar11 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar6);
    *(undefined4 *)(ptVar11 + 0x98) = uVar4;
    *(undefined4 *)(ptVar11 + 0x94) = uVar4;
    *(undefined4 *)(ptVar11 + 0xa0) = uVar4;
    *(float *)(ptVar11 + 0x9c) = fVar16;
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar17 < 0.0) << 0x1f;
    if (SUB41(in_fpscr >> 0x1f,0)) {
      fVar17 = fVar17 + fVar16;
    }
    else {
      fVar17 = fVar16 - fVar17;
    }
    *(float *)(iVar10 + iVar6 + 0x90) = fVar13 * fVar1 * fVar17 * fVar17;
    uVar20 = VectorSignedToFloat(iVar9 + 4,(byte)(in_fpscr >> 0x16) & 3);
    fVar13 = (float)tMatrix::Identity(ptVar11);
    iVar12 = *(int *)(param_1 + 0x4c) + iVar6;
    *(undefined4 *)(iVar12 + 0x30) = *(undefined4 *)(iVar12 + 0x90);
    fVar13 = (float)Cos(fVar13);
    iVar10 = *(int *)(param_1 + 0x50);
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar6 + 0x38) = uVar20;
    *(float *)(iVar12 + 0x34) = fVar16 - fVar13;
    tMatrix::Identity((tMatrix *)(iVar10 + iVar6));
    iVar7 = *(int *)(param_1 + 0x4c);
    iVar12 = iVar7 + iVar6;
    fVar13 = *(float *)(iVar12 + 0x34);
    iVar10 = *(int *)(param_1 + 0x50) + iVar6;
    uVar19 = *(undefined4 *)(iVar12 + 0x90);
    *(undefined4 *)(iVar10 + 0x38) = uVar20;
    *(undefined4 *)(iVar10 + 0x30) = uVar19;
    *(float *)(iVar10 + 0x34) = fVar13 + fVar14;
    if (iVar9 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar7 + iVar8));
      fVar13 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar8));
    }
    else {
      iVar7 = iVar7 + iVar8;
      fVar15 = *(float *)(iVar12 + 0x38);
      fVar13 = *(float *)(iVar12 + 0x34);
      fVar17 = *(float *)(iVar12 + 0x30);
      *(undefined4 *)(iVar7 + 0x18) = uVar4;
      *(float *)(iVar7 + 0x14) = fVar16;
      *(undefined4 *)(iVar7 + 0x10) = uVar4;
      *(float *)(iVar7 + 0x24) = fVar13 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x20) = fVar17 - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x28) = fVar15 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar7 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar8);
      fVar13 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar8),fVar13);
      iVar10 = *(int *)(param_1 + 0x50) + iVar6;
      iVar12 = *(int *)(param_1 + 0x50) + iVar8;
      fVar15 = *(float *)(iVar10 + 0x38);
      fVar13 = *(float *)(iVar10 + 0x30);
      fVar17 = *(float *)(iVar10 + 0x34);
      *(undefined4 *)(iVar12 + 0x18) = uVar4;
      *(float *)(iVar12 + 0x14) = fVar16;
      *(undefined4 *)(iVar12 + 0x10) = uVar4;
      *(float *)(iVar12 + 0x24) = fVar17 - *(float *)(iVar12 + 0x34);
      *(float *)(iVar12 + 0x28) = fVar15 - *(float *)(iVar12 + 0x38);
      *(float *)(iVar12 + 0x20) = fVar13 - *(float *)(iVar12 + 0x30);
      tVector::Normalize((tVector *)(iVar12 + 0x20));
      ptVar3 = (tVector *)(*(int *)(param_1 + 0x50) + iVar8);
      fVar13 = (float)tVector::Cross(ptVar3,ptVar3 + 0x10,ptVar3 + 0x20);
      fVar13 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x50) + iVar8),fVar13);
      if (0x3d < iVar5) {
        if (*(int *)(param_1 + 0x38) < 2) {
          iVar8 = *(int *)(param_1 + 0x38) + -1;
        }
        else {
          iVar10 = 0;
          iVar9 = 0;
          do {
            iVar6 = iVar9 + 0xa8;
            iVar10 = iVar10 + 1;
            iVar5 = *(int *)(param_1 + 0x4c) + iVar9;
            iVar8 = *(int *)(param_1 + 0x4c) + iVar6;
            fVar16 = *(float *)(iVar8 + 0x38);
            fVar14 = *(float *)(iVar8 + 0x34);
            *(float *)(iVar5 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar5 + 0x30);
            *(float *)(iVar5 + 0x84) = fVar14 - *(float *)(iVar5 + 0x34);
            *(float *)(iVar5 + 0x88) = fVar16 - *(float *)(iVar5 + 0x38);
            uVar4 = tVector::Normalize((tVector *)(iVar5 + 0x80));
            iVar9 = *(int *)(param_1 + 0x50) + iVar9;
            iVar8 = *(int *)(param_1 + 0x50) + iVar6;
            fVar16 = *(float *)(iVar8 + 0x38);
            fVar14 = *(float *)(iVar8 + 0x34);
            fVar18 = *(float *)(iVar9 + 0x38);
            *(float *)(iVar9 + 0x80) = *(float *)(iVar8 + 0x30) - *(float *)(iVar9 + 0x30);
            *(float *)(iVar9 + 0x84) = fVar14 - *(float *)(iVar9 + 0x34);
            *(undefined4 *)(iVar5 + 0x8c) = uVar4;
            *(float *)(iVar9 + 0x88) = fVar16 - fVar18;
            uVar4 = tVector::Normalize((tVector *)(iVar9 + 0x80));
            iVar8 = *(int *)(param_1 + 0x38) + -1;
            *(undefined4 *)(iVar9 + 0x8c) = uVar4;
            iVar9 = iVar6;
          } while (iVar10 < iVar8);
        }
        uVar4 = DAT_000544cc;
        fVar14 = DAT_000544c8;
        iVar9 = *(int *)(param_1 + 0x50) + iVar8 * 0xa8;
        iVar8 = *(int *)(param_1 + 0x4c) + iVar8 * 0xa8;
        *(float *)(iVar8 + 0x8c) = DAT_000544c8;
        *(float *)(iVar8 + 0x88) = fVar14;
        *(undefined4 *)(iVar8 + 0x84) = uVar4;
        *(undefined4 *)(iVar8 + 0x80) = uVar4;
        *(float *)(iVar9 + 0x8c) = fVar14;
        *(undefined4 *)(iVar9 + 0x80) = uVar4;
        *(float *)(iVar9 + 0x88) = fVar14;
        *(undefined4 *)(iVar9 + 0x84) = uVar4;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar10 = *(int *)(param_1 + 0x4c);
    iVar9 = iVar9 + 1;
    iVar5 = iVar5 + 1;
    iVar8 = iVar6;
  } while( true );
}
