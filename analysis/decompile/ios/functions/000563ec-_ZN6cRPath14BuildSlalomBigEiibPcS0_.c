/*
 * mangled: _ZN6cRPath14BuildSlalomBigEiibPcS0_
 * demangled: cRPath::BuildSlalomBig(int, int, bool, char*, char*)
 * address: 000563ec
 * size: 2660
 */

/* cRPath::BuildSlalomBig(int, int, bool, char*, char*) */

void cRPath::BuildSlalomBig(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  tMatrix *ptVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  ulonglong uVar11;

  *(undefined4 *)(param_1 + 0x2c) = 0x1b;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  iVar5 = param_2 + 8;
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(int *)(param_1 + 0x38) = iVar5;
  uVar7 = VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar4 = param_2 + 4;
  uVar11 = (ulonglong)(uint)param_2;
  *(undefined4 *)(param_1 + 0x40) = uVar7;
  uVar7 = RShellMemoryMalloc(iVar5 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar7;
  uVar7 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar7;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar3 = 0;
    iVar5 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0xa0) = 0;
      iVar6 = *(int *)(param_1 + 0x4c) + iVar5;
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar6 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x98) = 0;
  uVar7 = VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
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
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x13c) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x148) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xd8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdc) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xe0) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xd8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e4) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1f0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x180) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x184) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x188) = 0x40000000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x180) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x184) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x288) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x290) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x28c) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x298) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x294) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x1f8));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x228) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x22c) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x230) = 0x40400000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x1f8));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x228) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x22c) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x230) = 0x40400000;
  iVar5 = iVar4 * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c)));
  iVar3 = iVar5 + *(int *)(param_1 + 0x4c);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x38) = uVar7;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  iVar6 = iVar4 + 1;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x38) = uVar7;
  iVar5 = iVar6 * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c)));
  iVar3 = iVar5 + *(int *)(param_1 + 0x4c);
  uVar7 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x38) = uVar7;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  iVar6 = iVar4 + 2;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x38) = uVar7;
  iVar5 = iVar6 * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c)));
  iVar3 = iVar5 + *(int *)(param_1 + 0x4c);
  uVar7 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x38) = uVar7;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x38) = uVar7;
  iVar5 = (iVar4 + 3) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar5 + 0x90) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x4c)));
  iVar3 = iVar5 + *(int *)(param_1 + 0x4c);
  uVar7 = VectorSignedToFloat(iVar4 + 3,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x38) = uVar7;
  tMatrix::Identity((tMatrix *)(iVar5 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar5 + *(int *)(param_1 + 0x50) + 0x38) = uVar7;
  if (0 < (int)uVar11) {
    fVar10 = (float)VectorSignedToFloat((int)uVar11,(byte)(in_fpscr >> 0x16) & 3);
    iVar5 = 0;
    iVar4 = 0x2a0;
    do {
      while( true ) {
        iVar3 = *(int *)(param_1 + 0x4c);
        fVar8 = (float)VectorSignedToFloat(iVar5,(byte)(in_fpscr >> 0x16) & 3);
        fVar8 = fVar8 / fVar10;
        fVar2 = (float)Sin(fVar8 * 6.2831855);
        fVar8 = fVar8 - 0.5;
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar8 < 0.0) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          fVar8 = fVar8 + 1.0;
        }
        else {
          fVar8 = 1.0 - fVar8;
        }
        *(float *)(iVar3 + iVar4 + 0x90) = fVar2 * 4.4444447 * fVar8 * fVar8;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x98) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x94) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0xa0) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x4c)));
        iVar3 = iVar4 + *(int *)(param_1 + 0x4c);
        uVar7 = VectorSignedToFloat(iVar5 + 4,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x34) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x38) = uVar7;
        tMatrix::Identity((tMatrix *)(iVar4 + *(int *)(param_1 + 0x50)));
        *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar4 + 0x30) =
             *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar4 + 0x90);
        *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar4 + 0x34) = 0x3efae148;
        *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar4 + 0x38) = uVar7;
        if (0 < iVar5) break;
        iVar5 = iVar5 + 1;
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar4));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar4));
        iVar4 = iVar4 + 0xa8;
        if (iVar5 == (int)uVar11) goto LAB_00056ce4;
      }
      fVar9 = 0.2617994;
      iVar5 = iVar5 + 1;
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar4;
      *(undefined4 *)(iVar3 + 0x18) = 0;
      *(undefined4 *)(iVar3 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar3 + 0x10) = 0;
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar4;
      iVar6 = *(int *)(param_1 + 0x4c) + iVar4;
      fVar8 = *(float *)(iVar6 + 0x34);
      fVar2 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar3 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x24) = fVar8 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x28) = fVar2 - *(float *)(iVar3 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)(param_1 + 0x4c) + -0x88));
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8;
      iVar6 = iVar3 + iVar4;
      tVector::Cross((tVector *)(iVar3 + iVar4),(tVector *)(iVar6 + 0x10),(tVector *)(iVar6 + 0x20))
      ;
      ptVar1 = (tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar4);
      tMatrix::RotLocalZ(ptVar1,*(float *)(ptVar1 + 0x90) * fVar9);
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8 + iVar4;
      *(undefined4 *)(iVar3 + 0x18) = 0;
      *(undefined4 *)(iVar3 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar3 + 0x10) = 0;
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8 + iVar4;
      iVar6 = *(int *)(param_1 + 0x50) + iVar4;
      fVar8 = *(float *)(iVar6 + 0x34);
      fVar2 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar3 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x24) = fVar8 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x28) = fVar2 - *(float *)(iVar3 + 0x38);
      tVector::Normalize((tVector *)(iVar4 + *(int *)(param_1 + 0x50) + -0x88));
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8;
      iVar6 = iVar3 + iVar4;
      tVector::Cross((tVector *)(iVar3 + iVar4),(tVector *)(iVar6 + 0x10),(tVector *)(iVar6 + 0x20))
      ;
      iVar3 = iVar4 + *(int *)(param_1 + 0x4c);
      ptVar1 = (tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar4);
      iVar4 = iVar4 + 0xa8;
      tMatrix::RotLocalZ(ptVar1,*(float *)(iVar3 + -0x18) * fVar9);
    } while (iVar5 != (int)uVar11);
  }
LAB_00056ce4:
  iVar4 = *(int *)(param_1 + 0x38);
  if (0 < iVar4 + -1) {
    iVar3 = 0;
    iVar5 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar4 = *(int *)(param_1 + 0x4c) + iVar5;
      iVar6 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar5;
      fVar10 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar10 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar8 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar5 + *(int *)(param_1 + 0x4c);
      uVar7 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      *(undefined4 *)(iVar4 + 0x8c) = uVar7;
      iVar4 = *(int *)(param_1 + 0x50) + iVar5;
      iVar6 = *(int *)(param_1 + 0x50) + 0xa8 + iVar5;
      fVar10 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x84) = fVar10 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x88) = fVar8 - *(float *)(iVar4 + 0x38);
      iVar4 = iVar5 + *(int *)(param_1 + 0x50);
      uVar7 = tVector::Normalize((tVector *)(iVar4 + 0x80));
      iVar5 = iVar5 + 0xa8;
      *(undefined4 *)(iVar4 + 0x8c) = uVar7;
      iVar4 = *(int *)(param_1 + 0x38);
    } while (iVar3 < iVar4 + -1);
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
