/*
 * mangled: _ZN6cRPath14BuildSlalomBigEiibPcS0_
 * demangled: cRPath::BuildSlalomBig(int, int, bool, char*, char*)
 * address: 0005581c
 * size: 1200
 */

/* cRPath::BuildSlalomBig(int, int, bool, char*, char*) */

void cRPath::BuildSlalomBig(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  tVector *ptVar2;
  int iVar3;
  int iVar4;
  tMatrix *ptVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;

  iVar7 = param_2 + 8;
  uVar14 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  fVar11 = DAT_00055bd8;
  *(undefined4 *)(param_1 + 0x2c) = 0x1b;
  *(float *)(param_1 + 0x44) = fVar11;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar8 = 0;
  *(int *)(param_1 + 0x38) = iVar7;
  iVar9 = 0;
  *(undefined4 *)(param_1 + 0x40) = uVar14;
  uVar1 = DAT_00055bdc;
  GetNodes((cRPath *)param_1);
  uVar14 = DAT_00055bc4;
  iVar4 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  do {
    uVar17 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(undefined4 *)(ptVar5 + 0x90) = uVar1;
    *(undefined4 *)(ptVar5 + 0x98) = uVar1;
    *(undefined4 *)(ptVar5 + 0x94) = uVar1;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
    *(float *)(ptVar5 + 0x9c) = fVar11;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar1;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(iVar6 + 0x38) = uVar17;
    tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar3 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar3 + 0x38) = uVar17;
    iVar6 = iVar4 + iVar8;
    *(undefined4 *)(iVar3 + 0x34) = uVar14;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
  } while (iVar9 != 4);
  iVar9 = param_2 + 4;
  iVar8 = iVar9 * 0xa8;
  do {
    uVar17 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    ptVar5 = (tMatrix *)(iVar4 + iVar8);
    *(undefined4 *)(ptVar5 + 0x90) = uVar1;
    *(undefined4 *)(ptVar5 + 0x98) = uVar1;
    *(undefined4 *)(ptVar5 + 0x94) = uVar1;
    *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
    *(float *)(ptVar5 + 0x9c) = fVar11;
    iVar9 = iVar9 + 1;
    tMatrix::Identity(ptVar5);
    iVar4 = *(int *)(param_1 + 0x50);
    iVar6 = *(int *)(param_1 + 0x4c) + iVar8;
    *(undefined4 *)(iVar6 + 0x34) = uVar1;
    *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    *(undefined4 *)(iVar6 + 0x38) = uVar17;
    fVar10 = (float)tMatrix::Identity((tMatrix *)(iVar4 + iVar8));
    iVar4 = *(int *)(param_1 + 0x4c);
    iVar3 = *(int *)(param_1 + 0x50) + iVar8;
    *(undefined4 *)(iVar3 + 0x38) = uVar17;
    iVar6 = iVar4 + iVar8;
    *(undefined4 *)(iVar3 + 0x34) = uVar14;
    iVar8 = iVar8 + 0xa8;
    *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
    fVar16 = DAT_00055bd0;
    fVar13 = DAT_00055bcc;
  } while (iVar9 != iVar7);
  if (0 < param_2) {
    fVar18 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = 0;
    iVar7 = 0x1f8;
    do {
      fVar15 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      iVar9 = iVar7 + 0xa8;
      fVar15 = fVar15 / fVar18 - fVar16;
      fVar10 = (float)Sin(fVar10);
      ptVar5 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar9);
      *(undefined4 *)(ptVar5 + 0x98) = uVar1;
      *(undefined4 *)(ptVar5 + 0x94) = uVar1;
      *(undefined4 *)(ptVar5 + 0xa0) = uVar1;
      *(float *)(ptVar5 + 0x9c) = fVar11;
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar15 < 0.0) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar15 = fVar15 + fVar11;
      }
      else {
        fVar15 = fVar11 - fVar15;
      }
      uVar17 = VectorSignedToFloat(iVar8 + 4,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar4 + iVar9 + 0x90) = fVar10 * fVar13 * fVar15 * fVar15;
      tMatrix::Identity(ptVar5);
      iVar4 = *(int *)(param_1 + 0x50);
      iVar6 = *(int *)(param_1 + 0x4c) + iVar9;
      *(undefined4 *)(iVar6 + 0x34) = uVar1;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      *(undefined4 *)(iVar6 + 0x38) = uVar17;
      tMatrix::Identity((tMatrix *)(iVar4 + iVar9));
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar4 = *(int *)(param_1 + 0x50) + iVar9;
      *(undefined4 *)(iVar4 + 0x38) = uVar17;
      iVar6 = iVar3 + iVar9;
      *(undefined4 *)(iVar4 + 0x34) = uVar14;
      *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      if (iVar8 == 0) {
        tMatrix::RotIdentity((tMatrix *)(iVar3 + iVar7));
        fVar10 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar7));
        if (param_2 < 2) goto LAB_00055ba4;
      }
      else {
        iVar3 = iVar3 + iVar7;
        fVar12 = *(float *)(iVar6 + 0x38);
        fVar10 = *(float *)(iVar6 + 0x34);
        fVar15 = *(float *)(iVar6 + 0x30);
        *(undefined4 *)(iVar3 + 0x18) = uVar1;
        *(float *)(iVar3 + 0x14) = fVar11;
        *(undefined4 *)(iVar3 + 0x10) = uVar1;
        *(float *)(iVar3 + 0x24) = fVar10 - *(float *)(iVar3 + 0x34);
        *(float *)(iVar3 + 0x20) = fVar15 - *(float *)(iVar3 + 0x30);
        *(float *)(iVar3 + 0x28) = fVar12 - *(float *)(iVar3 + 0x38);
        tVector::Normalize((tVector *)(iVar3 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar7);
        fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
        tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar7),fVar10);
        iVar4 = *(int *)(param_1 + 0x50) + iVar9;
        iVar6 = *(int *)(param_1 + 0x50) + iVar7;
        fVar12 = *(float *)(iVar4 + 0x38);
        fVar10 = *(float *)(iVar4 + 0x30);
        fVar15 = *(float *)(iVar4 + 0x34);
        *(undefined4 *)(iVar6 + 0x18) = uVar1;
        *(float *)(iVar6 + 0x14) = fVar11;
        *(undefined4 *)(iVar6 + 0x10) = uVar1;
        *(float *)(iVar6 + 0x24) = fVar15 - *(float *)(iVar6 + 0x34);
        *(float *)(iVar6 + 0x28) = fVar12 - *(float *)(iVar6 + 0x38);
        *(float *)(iVar6 + 0x20) = fVar10 - *(float *)(iVar6 + 0x30);
        tVector::Normalize((tVector *)(iVar6 + 0x20));
        ptVar2 = (tVector *)(*(int *)(param_1 + 0x50) + iVar7);
        fVar10 = (float)tVector::Cross(ptVar2,ptVar2 + 0x10,ptVar2 + 0x20);
        fVar10 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x50) + iVar7),fVar10);
        if (param_2 <= iVar8 + 1) goto LAB_00055ba4;
      }
      iVar8 = iVar8 + 1;
      iVar4 = *(int *)(param_1 + 0x4c);
      iVar7 = iVar9;
    } while( true );
  }
LAB_00055ba8:
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar7 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar9 = 0;
    iVar8 = 0;
    while( true ) {
      iVar6 = iVar8 + 0xa8;
      iVar7 = iVar4 + iVar8;
      iVar4 = iVar4 + iVar6;
      fVar13 = *(float *)(iVar4 + 0x38);
      fVar11 = *(float *)(iVar4 + 0x34);
      iVar9 = iVar9 + 1;
      *(float *)(iVar7 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar11 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar13 - *(float *)(iVar7 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar8 = *(int *)(param_1 + 0x50) + iVar8;
      iVar4 = *(int *)(param_1 + 0x50) + iVar6;
      fVar13 = *(float *)(iVar4 + 0x38);
      fVar11 = *(float *)(iVar4 + 0x34);
      fVar16 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar11 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar7 + 0x8c) = uVar14;
      *(float *)(iVar8 + 0x88) = fVar13 - fVar16;
      uVar14 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar7 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar14;
      if (iVar7 <= iVar9) break;
      iVar4 = *(int *)(param_1 + 0x4c);
      iVar8 = iVar6;
    }
    iVar4 = *(int *)(param_1 + 0x4c);
  }
  uVar14 = DAT_00055bdc;
  fVar11 = DAT_00055bd8;
  iVar8 = *(int *)(param_1 + 0x50) + iVar7 * 0xa8;
  iVar4 = iVar4 + iVar7 * 0xa8;
  *(float *)(iVar4 + 0x8c) = DAT_00055bd8;
  *(float *)(iVar4 + 0x88) = fVar11;
  *(undefined4 *)(iVar4 + 0x84) = uVar14;
  *(undefined4 *)(iVar4 + 0x80) = uVar14;
  *(float *)(iVar8 + 0x8c) = fVar11;
  *(undefined4 *)(iVar8 + 0x80) = uVar14;
  *(float *)(iVar8 + 0x88) = fVar11;
  *(undefined4 *)(iVar8 + 0x84) = uVar14;
  CalcLengthZ((cRPath *)param_1);
  return;
LAB_00055ba4:
  iVar4 = *(int *)(param_1 + 0x4c);
  goto LAB_00055ba8;
}
