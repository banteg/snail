/*
 * mangled: _ZN6cRPath15BuildSuperTrampEffibPcS0_S0_
 * demangled: cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*)
 * address: 000545f0
 * size: 932
 */

/* cRPath::BuildSuperTramp(float, float, int, bool, char*, char*, char*) */

void cRPath::BuildSuperTramp
               (float param_1,float param_2,int param_3,bool param_4,char *param_5,char *param_6,
               char *param_7)

{
  tVector *ptVar1;
  undefined4 uVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  float extraout_s0;
  float extraout_s0_00;
  float fVar9;
  float fVar10;
  float fVar11;
  int iVar12;
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;

  fVar9 = DAT_00054994;
  fVar11 = (float)param_5 * DAT_00054994;
  *(char **)(param_3 + 0x48) = param_6;
  uVar2 = DAT_0005499c;
  fVar10 = DAT_00054998;
  *(undefined4 *)(param_3 + 0x2c) = 0x26;
  *(undefined4 *)(param_3 + 0x44) = uVar2;
  *(undefined1 *)(param_3 + 0x30) = 0;
  iVar6 = 0;
  *(undefined4 *)(param_3 + 0x34) = 0;
  fVar15 = DAT_000549a0;
  iVar7 = 0;
  iVar12 = (int)fVar11;
  uVar13 = VectorSignedToFloat(iVar12 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_3 + 0x38) = iVar12 + 8;
  fVar11 = (float)VectorSignedToFloat(iVar12,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_3 + 0x40) = uVar13;
  fVar11 = fVar11 / fVar9;
  GetNodes((cRPath *)param_3);
  iVar3 = *(int *)(param_3 + 0x4c);
  *(undefined1 *)(param_3 + 0x84) = 0;
  *(int *)(param_3 + 0x38) = *(int *)(param_3 + 0x38) + -1;
  do {
    uVar13 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar6);
    *(float *)(ptVar4 + 0x90) = (float)(uint)param_4 + fVar10;
    *(float *)(ptVar4 + 0x98) = fVar10;
    *(float *)(ptVar4 + 0x94) = fVar10;
    *(float *)(ptVar4 + 0xa0) = fVar10;
    *(undefined4 *)(ptVar4 + 0x9c) = uVar2;
    iVar7 = iVar7 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_3 + 0x50);
    iVar5 = *(int *)(param_3 + 0x4c) + iVar6;
    *(undefined4 *)(iVar5 + 0x8c) = uVar2;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(float *)(iVar5 + 0x34) = fVar10;
    *(undefined4 *)(iVar5 + 0x38) = uVar13;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar6));
    iVar3 = *(int *)(param_3 + 0x4c);
    iVar5 = *(int *)(param_3 + 0x50) + iVar6;
    *(undefined4 *)(iVar5 + 0x38) = uVar13;
    *(undefined4 *)(iVar5 + 0x8c) = uVar2;
    uVar13 = *(undefined4 *)(iVar3 + iVar6 + 0x90);
    *(float *)(iVar5 + 0x34) = fVar15;
    iVar6 = iVar6 + 0xa8;
    *(undefined4 *)(iVar5 + 0x30) = uVar13;
    fVar9 = DAT_000549a4;
  } while (iVar7 != 7);
  if (-1 < iVar12) {
    iVar6 = 0x498;
    iVar7 = 0;
    while( true ) {
      VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      ptVar4 = (tMatrix *)(iVar3 + iVar6);
      *(float *)(ptVar4 + 0x90) = (float)(uint)param_4 + fVar10;
      *(float *)(ptVar4 + 0x98) = fVar10;
      *(float *)(ptVar4 + 0x94) = fVar10;
      *(float *)(ptVar4 + 0xa0) = fVar10;
      *(undefined4 *)(ptVar4 + 0x9c) = uVar2;
      iVar7 = iVar7 + 1;
      fVar8 = (float)tMatrix::Identity(ptVar4);
      iVar3 = *(int *)(param_3 + 0x4c) + iVar6;
      *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
      fVar16 = fVar11 - fVar15;
      fVar8 = (float)Sin(fVar8);
      iVar5 = *(int *)(param_3 + 0x4c);
      *(float *)(iVar3 + 0x38) = fVar9 + fVar8 * fVar11;
      fVar8 = (float)Cos(extraout_s0);
      iVar3 = *(int *)(param_3 + 0x50);
      *(float *)(iVar5 + iVar6 + 0x34) = fVar11 - fVar8 * fVar11;
      fVar8 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar6));
      iVar3 = *(int *)(param_3 + 0x50) + iVar6;
      *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar6 + 0x90);
      fVar8 = (float)Sin(fVar8);
      iVar5 = *(int *)(param_3 + 0x50);
      *(float *)(iVar3 + 0x38) = fVar9 + fVar8 * fVar16;
      fVar8 = (float)Cos(extraout_s0_00);
      iVar3 = *(int *)(param_3 + 0x4c) + iVar6;
      fVar14 = *(float *)(iVar3 + 0x38);
      *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar6) = uVar2;
      *(float *)(iVar3 + 8) = fVar10;
      *(float *)(iVar3 + 4) = fVar10;
      *(float *)(iVar3 + 0x10) = fVar10;
      *(float *)(iVar3 + 0x18) = fVar9 - fVar14;
      *(float *)(iVar5 + iVar6 + 0x34) = fVar11 - fVar16 * fVar8;
      *(float *)(iVar3 + 0x14) = fVar11 - *(float *)(iVar3 + 0x34);
      tVector::Normalize((tVector *)(iVar3 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_3 + 0x4c) + iVar6);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      iVar3 = *(int *)(param_3 + 0x50) + iVar6;
      fVar8 = *(float *)(iVar3 + 0x34);
      fVar14 = *(float *)(iVar3 + 0x38);
      *(undefined4 *)(*(int *)(param_3 + 0x50) + iVar6) = uVar2;
      *(float *)(iVar3 + 8) = fVar10;
      *(float *)(iVar3 + 4) = fVar10;
      *(float *)(iVar3 + 0x10) = fVar10;
      *(float *)(iVar3 + 0x14) = fVar11 - fVar8;
      *(float *)(iVar3 + 0x18) = fVar9 - fVar14;
      tVector::Normalize((tVector *)(iVar3 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_3 + 0x50) + iVar6);
      iVar6 = iVar6 + 0xa8;
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      if (iVar12 < iVar7) break;
      iVar3 = *(int *)(param_3 + 0x4c);
    }
  }
  if (0 < *(int *)(param_3 + 0x38)) {
    iVar6 = 0;
    iVar3 = 0;
    do {
      iVar5 = iVar3 + 0xa8;
      iVar6 = iVar6 + 1;
      iVar12 = *(int *)(param_3 + 0x4c) + iVar3;
      iVar7 = *(int *)(param_3 + 0x4c) + iVar5;
      fVar10 = *(float *)(iVar7 + 0x38);
      fVar9 = *(float *)(iVar7 + 0x34);
      *(float *)(iVar12 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar12 + 0x30);
      *(float *)(iVar12 + 0x84) = fVar9 - *(float *)(iVar12 + 0x34);
      *(float *)(iVar12 + 0x88) = fVar10 - *(float *)(iVar12 + 0x38);
      uVar2 = tVector::Normalize((tVector *)(iVar12 + 0x80));
      iVar3 = *(int *)(param_3 + 0x50) + iVar3;
      iVar7 = *(int *)(param_3 + 0x50) + iVar5;
      fVar10 = *(float *)(iVar7 + 0x38);
      fVar9 = *(float *)(iVar7 + 0x34);
      fVar15 = *(float *)(iVar3 + 0x38);
      *(float *)(iVar3 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar9 - *(float *)(iVar3 + 0x34);
      *(undefined4 *)(iVar12 + 0x8c) = uVar2;
      *(float *)(iVar3 + 0x88) = fVar10 - fVar15;
      uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar7 = *(int *)(param_3 + 0x38);
      *(undefined4 *)(iVar3 + 0x8c) = uVar2;
      iVar3 = iVar5;
    } while (iVar6 < iVar7);
  }
  CalcLengthZ((cRPath *)param_3);
  return;
}
