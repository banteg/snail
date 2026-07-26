/*
 * mangled: _ZN6cRPath6BuildPEififfiPcS0_
 * demangled: cRPath::BuildP(int, float, int, float, float, int, char*, char*)
 * address: 00053c04
 * size: 1264
 */

/* cRPath::BuildP(int, float, int, float, float, int, char*, char*) */

void cRPath::BuildP(int param_1,float param_2,int param_3,float param_4,float param_5,int param_6,
                   char *param_7,char *param_8)

{
  tVector *ptVar1;
  tMatrix *ptVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  uint uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  float fVar16;
  float in_stack_00000004;
  int in_stack_00000008;

  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(char **)(param_1 + 0x48) = param_7;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(int *)(param_1 + 0x2c) = param_3 + 0x29;
  iVar7 = 0xa8;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(int *)(param_1 + 0x38) = in_stack_00000008 + 2;
  iVar8 = 0;
  fVar16 = (in_stack_00000004 - (float)param_8) * 0.5;
  iVar9 = (in_stack_00000008 + 1) * 0xa8;
  uVar14 = VectorSignedToFloat(in_stack_00000008 + 2,(byte)(in_fpscr >> 0x16) & 3);
  uVar10 = in_fpscr & 0xfffffff | (uint)(fVar16 < 0.0) << 0x1f;
  *(undefined4 *)(param_1 + 0x40) = uVar14;
  if (SUB41(uVar10 >> 0x1f,0)) {
    fVar16 = (in_stack_00000004 - (float)param_8) * -0.5;
  }
  GetNodes((cRPath *)param_1);
  ptVar2 = *(tMatrix **)(param_1 + 0x4c);
  *(char **)(ptVar2 + 0x90) = param_8;
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  *(undefined1 *)(param_1 + 0x84) = 0;
  uVar14 = VectorSignedToFloat(in_stack_00000008 + 1,(byte)(uVar10 >> 0x16) & 3);
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x4c);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar3 + 0x34) = 0;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  iVar3 = *(int *)(param_1 + 0x50);
  ptVar2 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar9);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar3 + 0x38) = 0;
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(ptVar2 + 0x98) = 0;
  *(undefined4 *)(ptVar2 + 0x94) = 0;
  *(undefined4 *)(ptVar2 + 0xa0) = 0;
  *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
  *(float *)(ptVar2 + 0x90) = in_stack_00000004;
  tMatrix::Identity(ptVar2);
  iVar3 = *(int *)(param_1 + 0x50);
  iVar4 = *(int *)(param_1 + 0x4c) + iVar9;
  *(undefined4 *)(iVar4 + 0x38) = uVar14;
  *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
  *(undefined4 *)(iVar4 + 0x34) = 0;
  fVar11 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar9));
  iVar4 = *(int *)(param_1 + 0x4c);
  iVar3 = *(int *)(param_1 + 0x50) + iVar9;
  *(undefined4 *)(iVar3 + 0x38) = uVar14;
  *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar4 + iVar9 + 0x90);
  if (0 < in_stack_00000008) {
    iVar3 = 1;
    VectorSignedToFloat(in_stack_00000008,(byte)(uVar10 >> 0x16) & 3);
    iVar9 = 0;
    while( true ) {
      VectorSignedToFloat(iVar9,(byte)(uVar10 >> 0x16) & 3);
      iVar6 = *(int *)(param_1 + 0x2c);
      if (iVar6 == 0x2a) {
        fVar11 = (float)Cos(fVar11);
        iVar6 = iVar4 + iVar7;
        iVar4 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar6 + 0x90) = ((-fVar16 * fVar11 + 2.0) - fVar16) + 0.5;
      }
      else if (iVar6 == 0x2b) {
        fVar11 = (float)Sin(fVar11);
        iVar6 = iVar4 + iVar7;
        iVar4 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar6 + 0x90) = fVar16 + fVar16 * fVar11 + 0.5;
      }
      else if (iVar6 == 0x29) {
        fVar11 = (float)Sin(fVar11);
        iVar6 = iVar4 + iVar7;
        iVar4 = *(int *)(param_1 + 0x4c);
        *(float *)(iVar6 + 0x90) = (fVar16 * fVar11 - fVar16) + 0.5;
      }
      uVar15 = VectorSignedToFloat(iVar3,(byte)(uVar10 >> 0x16) & 3);
      ptVar2 = (tMatrix *)(iVar4 + iVar7);
      *(undefined4 *)(ptVar2 + 0x98) = 0;
      *(undefined4 *)(ptVar2 + 0x94) = 0;
      *(undefined4 *)(ptVar2 + 0xa0) = 0;
      *(undefined4 *)(ptVar2 + 0x9c) = 0x3f800000;
      tMatrix::Identity(ptVar2);
      iVar4 = *(int *)(param_1 + 0x50);
      iVar6 = *(int *)(param_1 + 0x4c) + iVar7;
      *(undefined4 *)(iVar6 + 0x34) = 0;
      *(undefined4 *)(iVar6 + 0x30) = *(undefined4 *)(iVar6 + 0x90);
      *(undefined4 *)(iVar6 + 0x38) = uVar15;
      tMatrix::Identity((tMatrix *)(iVar4 + iVar7));
      iVar5 = *(int *)(param_1 + 0x4c);
      iVar6 = iVar5 + iVar7;
      fVar11 = *(float *)(iVar6 + 0x34);
      iVar4 = *(int *)(param_1 + 0x50) + iVar7;
      uVar14 = *(undefined4 *)(iVar6 + 0x90);
      *(undefined4 *)(iVar4 + 0x38) = uVar15;
      *(undefined4 *)(iVar4 + 0x30) = uVar14;
      *(float *)(iVar4 + 0x34) = fVar11 + 0.49;
      if (iVar9 < 1) {
        tMatrix::RotIdentity((tMatrix *)(iVar5 + iVar8));
        fVar11 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar8));
      }
      else {
        iVar5 = iVar5 + iVar8;
        fVar13 = *(float *)(iVar6 + 0x38);
        fVar11 = *(float *)(iVar6 + 0x34);
        fVar12 = *(float *)(iVar6 + 0x30);
        *(undefined4 *)(iVar5 + 0x18) = 0;
        *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x10) = 0;
        *(float *)(iVar5 + 0x24) = fVar11 - *(float *)(iVar5 + 0x34);
        *(float *)(iVar5 + 0x20) = fVar12 - *(float *)(iVar5 + 0x30);
        *(float *)(iVar5 + 0x28) = fVar13 - *(float *)(iVar5 + 0x38);
        tVector::Normalize((tVector *)(iVar5 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar8);
        tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
        iVar4 = *(int *)(param_1 + 0x50) + iVar7;
        iVar6 = *(int *)(param_1 + 0x50) + iVar8;
        fVar13 = *(float *)(iVar4 + 0x38);
        fVar11 = *(float *)(iVar4 + 0x34);
        fVar12 = *(float *)(iVar4 + 0x30);
        *(undefined4 *)(iVar6 + 0x18) = 0;
        *(undefined4 *)(iVar6 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar6 + 0x10) = 0;
        *(float *)(iVar6 + 0x20) = fVar12 - *(float *)(iVar6 + 0x30);
        *(float *)(iVar6 + 0x24) = fVar11 - *(float *)(iVar6 + 0x34);
        *(float *)(iVar6 + 0x28) = fVar13 - *(float *)(iVar6 + 0x38);
        tVector::Normalize((tVector *)(iVar6 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar8);
        fVar11 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
      }
      if (in_stack_00000008 <= iVar3) break;
      iVar3 = iVar3 + 1;
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 0xa8;
      iVar7 = iVar7 + 0xa8;
      iVar4 = *(int *)(param_1 + 0x4c);
    }
    iVar4 = *(int *)(param_1 + 0x4c);
  }
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar7 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar9 = 0;
    iVar8 = 0;
    while( true ) {
      iVar6 = iVar8 + 0xa8;
      iVar3 = iVar4 + iVar8;
      iVar4 = iVar4 + iVar6;
      fVar11 = *(float *)(iVar4 + 0x38);
      fVar16 = *(float *)(iVar4 + 0x34);
      iVar9 = iVar9 + 1;
      *(float *)(iVar3 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x84) = fVar16 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x88) = fVar11 - *(float *)(iVar3 + 0x38);
      uVar14 = tVector::Normalize((tVector *)(iVar3 + 0x80));
      iVar8 = *(int *)(param_1 + 0x50) + iVar8;
      iVar7 = *(int *)(param_1 + 0x50) + iVar6;
      fVar11 = *(float *)(iVar7 + 0x38);
      fVar16 = *(float *)(iVar7 + 0x34);
      fVar12 = *(float *)(iVar8 + 0x38);
      *(float *)(iVar8 + 0x80) = *(float *)(iVar7 + 0x30) - *(float *)(iVar8 + 0x30);
      *(float *)(iVar8 + 0x84) = fVar16 - *(float *)(iVar8 + 0x34);
      *(undefined4 *)(iVar3 + 0x8c) = uVar14;
      *(float *)(iVar8 + 0x88) = fVar11 - fVar12;
      uVar14 = tVector::Normalize((tVector *)(iVar8 + 0x80));
      iVar7 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar8 + 0x8c) = uVar14;
      if (iVar7 <= iVar9) break;
      iVar4 = *(int *)(param_1 + 0x4c);
      iVar8 = iVar6;
    }
    iVar4 = *(int *)(param_1 + 0x4c);
  }
  iVar8 = *(int *)(param_1 + 0x50) + iVar7 * 0xa8;
  iVar4 = iVar4 + iVar7 * 0xa8;
  *(undefined4 *)(iVar4 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar4 + 0x84) = 0;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar8 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x80) = 0;
  *(undefined4 *)(iVar8 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_1);
  return;
}
