/*
 * mangled: _ZN6cRPath11BuildSlalomEiibPcS0_
 * demangled: cRPath::BuildSlalom(int, int, bool, char*, char*)
 * address: 00056350
 * size: 1200
 */

/* cRPath::BuildSlalom(int, int, bool, char*, char*) */

void cRPath::BuildSlalom(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tVector *ptVar1;
  int iVar2;
  int iVar3;
  tMatrix *ptVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;

  iVar6 = param_2 + 8;
  uVar11 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)(param_1 + 0x2c) = 0x1a;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar7 = 0;
  *(int *)(param_1 + 0x38) = iVar6;
  iVar8 = 0;
  *(undefined4 *)(param_1 + 0x40) = uVar11;
  GetNodes((cRPath *)param_1);
  iVar3 = *(int *)(param_1 + 0x4c);
  *(undefined1 *)(param_1 + 0x84) = 0;
  do {
    uVar11 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar8 = iVar8 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar11;
    tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_1 + 0x4c);
    iVar2 = *(int *)(param_1 + 0x50) + iVar7;
    *(undefined4 *)(iVar2 + 0x38) = uVar11;
    iVar5 = iVar3 + iVar7;
    *(undefined4 *)(iVar2 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  } while (iVar8 != 4);
  iVar8 = param_2 + 4;
  iVar7 = iVar8 * 0xa8;
  do {
    uVar11 = VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
    ptVar4 = (tMatrix *)(iVar3 + iVar7);
    *(undefined4 *)(ptVar4 + 0x90) = 0;
    *(undefined4 *)(ptVar4 + 0x98) = 0;
    *(undefined4 *)(ptVar4 + 0x94) = 0;
    *(undefined4 *)(ptVar4 + 0xa0) = 0;
    *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
    iVar8 = iVar8 + 1;
    tMatrix::Identity(ptVar4);
    iVar3 = *(int *)(param_1 + 0x50);
    iVar5 = *(int *)(param_1 + 0x4c) + iVar7;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
    *(undefined4 *)(iVar5 + 0x38) = uVar11;
    fVar9 = (float)tMatrix::Identity((tMatrix *)(iVar3 + iVar7));
    iVar3 = *(int *)(param_1 + 0x4c);
    iVar2 = *(int *)(param_1 + 0x50) + iVar7;
    *(undefined4 *)(iVar2 + 0x38) = uVar11;
    iVar5 = iVar3 + iVar7;
    *(undefined4 *)(iVar2 + 0x34) = 0x3efae148;
    iVar7 = iVar7 + 0xa8;
    *(undefined4 *)(iVar2 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
  } while (iVar8 != iVar6);
  if (0 < param_2) {
    fVar13 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
    iVar7 = 0;
    iVar6 = 0x1f8;
    do {
      fVar12 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      iVar8 = iVar6 + 0xa8;
      fVar12 = fVar12 / fVar13 - 0.5;
      fVar9 = (float)Sin(fVar9);
      ptVar4 = (tMatrix *)(*(int *)(param_1 + 0x4c) + iVar8);
      *(undefined4 *)(ptVar4 + 0x98) = 0;
      *(undefined4 *)(ptVar4 + 0x94) = 0;
      *(undefined4 *)(ptVar4 + 0xa0) = 0;
      *(undefined4 *)(ptVar4 + 0x9c) = 0x3f800000;
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar12 < 0.0) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar12 = fVar12 + 1.0;
      }
      else {
        fVar12 = 1.0 - fVar12;
      }
      uVar11 = VectorSignedToFloat(iVar7 + 4,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(iVar3 + iVar8 + 0x90) = fVar9 * 5.0 * fVar12 * fVar12;
      tMatrix::Identity(ptVar4);
      iVar3 = *(int *)(param_1 + 0x50);
      iVar5 = *(int *)(param_1 + 0x4c) + iVar8;
      *(undefined4 *)(iVar5 + 0x34) = 0;
      *(undefined4 *)(iVar5 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
      *(undefined4 *)(iVar5 + 0x38) = uVar11;
      tMatrix::Identity((tMatrix *)(iVar3 + iVar8));
      iVar2 = *(int *)(param_1 + 0x4c);
      iVar3 = *(int *)(param_1 + 0x50) + iVar8;
      *(undefined4 *)(iVar3 + 0x38) = uVar11;
      iVar5 = iVar2 + iVar8;
      *(undefined4 *)(iVar3 + 0x34) = 0x3efae148;
      *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar5 + 0x90);
      if (iVar7 == 0) {
        tMatrix::RotIdentity((tMatrix *)(iVar2 + iVar6));
        fVar9 = (float)tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + iVar6));
        if (param_2 < 2) goto LAB_000566d8;
      }
      else {
        iVar2 = iVar2 + iVar6;
        fVar10 = *(float *)(iVar5 + 0x38);
        fVar9 = *(float *)(iVar5 + 0x34);
        fVar12 = *(float *)(iVar5 + 0x30);
        *(undefined4 *)(iVar2 + 0x18) = 0;
        *(undefined4 *)(iVar2 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar2 + 0x10) = 0;
        *(float *)(iVar2 + 0x24) = fVar9 - *(float *)(iVar2 + 0x34);
        *(float *)(iVar2 + 0x20) = fVar12 - *(float *)(iVar2 + 0x30);
        *(float *)(iVar2 + 0x28) = fVar10 - *(float *)(iVar2 + 0x38);
        tVector::Normalize((tVector *)(iVar2 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x4c) + iVar6);
        fVar9 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
        tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x4c) + iVar6),fVar9);
        iVar3 = *(int *)(param_1 + 0x50) + iVar8;
        iVar5 = *(int *)(param_1 + 0x50) + iVar6;
        fVar10 = *(float *)(iVar3 + 0x38);
        fVar9 = *(float *)(iVar3 + 0x30);
        fVar12 = *(float *)(iVar3 + 0x34);
        *(undefined4 *)(iVar5 + 0x18) = 0;
        *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
        *(undefined4 *)(iVar5 + 0x10) = 0;
        *(float *)(iVar5 + 0x24) = fVar12 - *(float *)(iVar5 + 0x34);
        *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
        *(float *)(iVar5 + 0x20) = fVar9 - *(float *)(iVar5 + 0x30);
        tVector::Normalize((tVector *)(iVar5 + 0x20));
        ptVar1 = (tVector *)(*(int *)(param_1 + 0x50) + iVar6);
        fVar9 = (float)tVector::Cross(ptVar1,ptVar1 + 0x10,ptVar1 + 0x20);
        fVar9 = (float)tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x50) + iVar6),fVar9);
        if (param_2 <= iVar7 + 1) goto LAB_000566d8;
      }
      iVar7 = iVar7 + 1;
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar6 = iVar8;
    } while( true );
  }
LAB_000566dc:
  if (*(int *)(param_1 + 0x38) < 2) {
    iVar6 = *(int *)(param_1 + 0x38) + -1;
  }
  else {
    iVar8 = 0;
    iVar7 = 0;
    while( true ) {
      iVar5 = iVar7 + 0xa8;
      iVar6 = iVar3 + iVar7;
      iVar3 = iVar3 + iVar5;
      fVar13 = *(float *)(iVar3 + 0x38);
      fVar9 = *(float *)(iVar3 + 0x34);
      iVar8 = iVar8 + 1;
      *(float *)(iVar6 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar6 + 0x30);
      *(float *)(iVar6 + 0x84) = fVar9 - *(float *)(iVar6 + 0x34);
      *(float *)(iVar6 + 0x88) = fVar13 - *(float *)(iVar6 + 0x38);
      uVar11 = tVector::Normalize((tVector *)(iVar6 + 0x80));
      iVar7 = *(int *)(param_1 + 0x50) + iVar7;
      iVar3 = *(int *)(param_1 + 0x50) + iVar5;
      fVar13 = *(float *)(iVar3 + 0x38);
      fVar9 = *(float *)(iVar3 + 0x34);
      fVar12 = *(float *)(iVar7 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar3 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar9 - *(float *)(iVar7 + 0x34);
      *(undefined4 *)(iVar6 + 0x8c) = uVar11;
      *(float *)(iVar7 + 0x88) = fVar13 - fVar12;
      uVar11 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar6 = *(int *)(param_1 + 0x38) + -1;
      *(undefined4 *)(iVar7 + 0x8c) = uVar11;
      if (iVar6 <= iVar8) break;
      iVar3 = *(int *)(param_1 + 0x4c);
      iVar7 = iVar5;
    }
    iVar3 = *(int *)(param_1 + 0x4c);
  }
  iVar7 = *(int *)(param_1 + 0x50) + iVar6 * 0xa8;
  iVar3 = iVar3 + iVar6 * 0xa8;
  *(undefined4 *)(iVar3 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar3 + 0x84) = 0;
  *(undefined4 *)(iVar3 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x8c) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x80) = 0;
  *(undefined4 *)(iVar7 + 0x88) = 0x3f800000;
  *(undefined4 *)(iVar7 + 0x84) = 0;
  CalcLengthZ((cRPath *)param_1);
  return;
LAB_000566d8:
  iVar3 = *(int *)(param_1 + 0x4c);
  goto LAB_000566dc;
}
