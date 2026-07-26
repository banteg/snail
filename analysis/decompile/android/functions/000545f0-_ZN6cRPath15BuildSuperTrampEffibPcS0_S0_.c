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
  int iVar2;
  tMatrix *ptVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float extraout_s0;
  float extraout_s0_00;
  int iVar8;
  undefined4 uVar9;
  float fVar10;
  float fVar11;

  *(char **)(param_3 + 0x48) = param_6;
  *(undefined4 *)(param_3 + 0x2c) = 0x26;
  *(undefined4 *)(param_3 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_3 + 0x30) = 0;
  iVar5 = 0;
  *(undefined4 *)(param_3 + 0x34) = 0;
  iVar6 = 0;
  iVar8 = (int)((float)param_5 * 1.0461504);
  uVar9 = VectorSignedToFloat(iVar8 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(int *)(param_3 + 0x38) = iVar8 + 8;
  fVar11 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(param_3 + 0x40) = uVar9;
  fVar11 = fVar11 / 1.0461504;
  GetNodes((cRPath *)param_3);
  iVar2 = *(int *)(param_3 + 0x4c);
  *(undefined1 *)(param_3 + 0x84) = 0;
  *(int *)(param_3 + 0x38) = *(int *)(param_3 + 0x38) + -1;
  do {
    uVar9 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    ptVar3 = (tMatrix *)(iVar2 + iVar5);
    *(float *)(ptVar3 + 0x90) = (float)(uint)param_4 + 0.0;
    *(undefined4 *)(ptVar3 + 0x98) = 0;
    *(undefined4 *)(ptVar3 + 0x94) = 0;
    *(undefined4 *)(ptVar3 + 0xa0) = 0;
    *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
    iVar6 = iVar6 + 1;
    tMatrix::Identity(ptVar3);
    iVar2 = *(int *)(param_3 + 0x50);
    iVar4 = *(int *)(param_3 + 0x4c) + iVar5;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0;
    *(undefined4 *)(iVar4 + 0x38) = uVar9;
    tMatrix::Identity((tMatrix *)(iVar2 + iVar5));
    iVar2 = *(int *)(param_3 + 0x4c);
    iVar4 = *(int *)(param_3 + 0x50) + iVar5;
    *(undefined4 *)(iVar4 + 0x38) = uVar9;
    *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
    uVar9 = *(undefined4 *)(iVar2 + iVar5 + 0x90);
    *(undefined4 *)(iVar4 + 0x34) = 0x3efae148;
    iVar5 = iVar5 + 0xa8;
    *(undefined4 *)(iVar4 + 0x30) = uVar9;
  } while (iVar6 != 7);
  if (-1 < iVar8) {
    iVar5 = 0x498;
    iVar6 = 0;
    while( true ) {
      VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
      ptVar3 = (tMatrix *)(iVar2 + iVar5);
      *(float *)(ptVar3 + 0x90) = (float)(uint)param_4 + 0.0;
      *(undefined4 *)(ptVar3 + 0x98) = 0;
      *(undefined4 *)(ptVar3 + 0x94) = 0;
      *(undefined4 *)(ptVar3 + 0xa0) = 0;
      *(undefined4 *)(ptVar3 + 0x9c) = 0x3f800000;
      iVar6 = iVar6 + 1;
      fVar7 = (float)tMatrix::Identity(ptVar3);
      iVar2 = *(int *)(param_3 + 0x4c) + iVar5;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar2 + 0x90);
      fVar7 = (float)Sin(fVar7);
      iVar4 = *(int *)(param_3 + 0x4c);
      *(float *)(iVar2 + 0x38) = fVar7 * fVar11 + 7.0;
      fVar7 = (float)Cos(extraout_s0);
      iVar2 = *(int *)(param_3 + 0x50);
      *(float *)(iVar4 + iVar5 + 0x34) = fVar11 - fVar7 * fVar11;
      fVar7 = (float)tMatrix::Identity((tMatrix *)(iVar2 + iVar5));
      iVar2 = *(int *)(param_3 + 0x50) + iVar5;
      *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar5 + 0x90);
      fVar7 = (float)Sin(fVar7);
      iVar4 = *(int *)(param_3 + 0x50);
      *(float *)(iVar2 + 0x38) = fVar7 * (fVar11 - 0.49) + 7.0;
      fVar7 = (float)Cos(extraout_s0_00);
      iVar2 = *(int *)(param_3 + 0x4c) + iVar5;
      fVar10 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_3 + 0x4c) + iVar5) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x18) = 7.0 - fVar10;
      *(float *)(iVar4 + iVar5 + 0x34) = fVar11 - (fVar11 - 0.49) * fVar7;
      *(float *)(iVar2 + 0x14) = fVar11 - *(float *)(iVar2 + 0x34);
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_3 + 0x4c) + iVar5);
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      iVar2 = *(int *)(param_3 + 0x50) + iVar5;
      fVar7 = *(float *)(iVar2 + 0x34);
      fVar10 = *(float *)(iVar2 + 0x38);
      *(undefined4 *)(*(int *)(param_3 + 0x50) + iVar5) = 0x3f800000;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 4) = 0;
      *(undefined4 *)(iVar2 + 0x10) = 0;
      *(float *)(iVar2 + 0x14) = fVar11 - fVar7;
      *(float *)(iVar2 + 0x18) = 7.0 - fVar10;
      tVector::Normalize((tVector *)(iVar2 + 0x10));
      ptVar1 = (tVector *)(*(int *)(param_3 + 0x50) + iVar5);
      iVar5 = iVar5 + 0xa8;
      tVector::Cross(ptVar1 + 0x20,ptVar1,ptVar1 + 0x10);
      if (iVar8 < iVar6) break;
      iVar2 = *(int *)(param_3 + 0x4c);
    }
  }
  if (0 < *(int *)(param_3 + 0x38)) {
    iVar5 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar2 + 0xa8;
      iVar5 = iVar5 + 1;
      iVar8 = *(int *)(param_3 + 0x4c) + iVar2;
      iVar6 = *(int *)(param_3 + 0x4c) + iVar4;
      fVar7 = *(float *)(iVar6 + 0x38);
      fVar11 = *(float *)(iVar6 + 0x34);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar11 - *(float *)(iVar8 + 0x34);
      *(float *)(iVar8 + 0x88) = fVar7 - *(float *)(iVar8 + 0x38);
      uVar9 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar2 = *(int *)(param_3 + 0x50) + iVar2;
      iVar6 = *(int *)(param_3 + 0x50) + iVar4;
      fVar7 = *(float *)(iVar6 + 0x38);
      fVar11 = *(float *)(iVar6 + 0x34);
      fVar10 = *(float *)(iVar2 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar11 - *(float *)(iVar2 + 0x34);
      *(undefined4 *)(iVar8 + 0x8c) = uVar9;
      *(float *)(iVar2 + 0x88) = fVar7 - fVar10;
      uVar9 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar6 = *(int *)(param_3 + 0x38);
      *(undefined4 *)(iVar2 + 0x8c) = uVar9;
      iVar2 = iVar4;
    } while (iVar5 < iVar6);
  }
  CalcLengthZ((cRPath *)param_3);
  return;
}
