/*
 * mangled: _ZN6cRPath10BuildScrewEiibPcS0_
 * demangled: cRPath::BuildScrew(int, int, bool, char*, char*)
 * address: 000586dc
 * size: 2752
 */

/* cRPath::BuildScrew(int, int, bool, char*, char*) */

void cRPath::BuildScrew(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint in_fpscr;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  uint uVar10;
  float fVar11;
  longlong lVar9;
  ulonglong uVar12;

  *(undefined4 *)(param_1 + 0x2c) = 0x19;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  iVar2 = param_2 + 8;
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(int *)(param_1 + 0x38) = iVar2;
  uVar5 = VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  uVar12 = (ulonglong)(uint)param_2;
  *(undefined4 *)(param_1 + 0x40) = uVar5;
  uVar5 = RShellMemoryMalloc(iVar2 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar5;
  uVar5 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar5;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar1 = 0;
    iVar2 = 0;
    do {
      iVar1 = iVar1 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar3 = *(int *)(param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar3 + 0x9c) = 0x3f800000;
    } while (iVar1 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90) = 0x3f000000;
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
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138) = 0x3f000000;
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
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0) = 0x3f000000;
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
  iVar2 = (param_2 + 3) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0xbf000000;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar1 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar5 = VectorSignedToFloat(param_2 + 3,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar5;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar5;
  iVar2 = (param_2 + 4) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0xbf000000;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar1 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar5 = VectorSignedToFloat(param_2 + 4,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar5;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar5;
  iVar2 = (param_2 + 5) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0xbf000000;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar1 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar5 = VectorSignedToFloat(param_2 + 5,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar5;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar5;
  iVar2 = (param_2 + 6) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0xbf000000;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar1 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar5 = VectorSignedToFloat(param_2 + 6,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar5;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar5;
  iVar2 = (param_2 + 7) * 0xa8;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0xbf000000;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
  iVar1 = iVar2 + *(int *)(param_1 + 0x4c);
  uVar5 = VectorSignedToFloat(param_2 + 7,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x38) = uVar5;
  tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x50) + 0x38) = uVar5;
  if (0 < (int)uVar12) {
    uVar10 = VectorSignedToFloat((int)uVar12,(byte)(in_fpscr >> 0x16) & 3);
    lVar9 = (ulonglong)uVar10 << 0x20;
    iVar1 = 0;
    iVar2 = 0x1f8;
    do {
      while( true ) {
        fVar7 = 0.5;
        iVar3 = *(int *)(param_1 + 0x4c);
        fVar6 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
        fVar11 = (float)((ulonglong)lVar9 >> 0x20);
        fVar8 = (fVar6 * 6.2831855) / fVar11;
        fVar6 = (float)Cos(fVar8 * 0.5);
        *(float *)(iVar2 + iVar3 + 0x90) = fVar6 * fVar7;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x98) = 0;
        *(float *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x94) = fVar8;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
        iVar3 = iVar2 + *(int *)(param_1 + 0x4c);
        *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x90);
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x34) = 0;
        uVar5 = VectorSignedToFloat(iVar1 + 3,(byte)(in_fpscr >> 0x16) & 3);
        lVar9 = CONCAT44(fVar11,uVar5);
        *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x38) = uVar5;
        tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
        iVar3 = *(int *)(param_1 + 0x50);
        fVar7 = *(float *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90);
        fVar6 = (float)Sin(fVar8);
        *(float *)(iVar2 + iVar3 + 0x30) = fVar7 + fVar6 * -0.49;
        iVar3 = *(int *)(param_1 + 0x50);
        fVar6 = (float)Cos(fVar8);
        *(float *)(iVar2 + iVar3 + 0x34) = fVar6 * 0.49;
        *(int *)(*(int *)(param_1 + 0x50) + iVar2 + 0x38) = (int)lVar9;
        if (0 < iVar1) break;
        iVar1 = iVar1 + 1;
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2));
        tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2));
        iVar2 = iVar2 + 0xa8;
        if (iVar1 == (int)uVar12) goto LAB_0005900c;
      }
      iVar1 = iVar1 + 1;
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      fVar6 = (float)Sin(fVar8);
      uVar5 = Cos(fVar8);
      *(undefined4 *)(iVar3 + 0x18) = 0;
      *(float *)(iVar3 + 0x10) = -fVar6;
      *(undefined4 *)(iVar3 + 0x14) = uVar5;
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      iVar4 = *(int *)(param_1 + 0x4c) + iVar2;
      fVar6 = *(float *)(iVar4 + 0x34);
      fVar7 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar3 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x24) = fVar6 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x28) = fVar7 - *(float *)(iVar3 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x4c) + -0x88));
      iVar3 = *(int *)(param_1 + 0x4c) + -0xa8;
      iVar4 = iVar3 + iVar2;
      tVector::Cross((tVector *)(iVar3 + iVar2),(tVector *)(iVar4 + 0x10),(tVector *)(iVar4 + 0x20))
      ;
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      fVar6 = (float)Sin(fVar8);
      uVar5 = Cos(fVar8);
      *(undefined4 *)(iVar3 + 0x18) = 0;
      *(float *)(iVar3 + 0x10) = -fVar6;
      *(undefined4 *)(iVar3 + 0x14) = uVar5;
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      iVar4 = *(int *)(param_1 + 0x50) + iVar2;
      fVar6 = *(float *)(iVar4 + 0x34);
      fVar7 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar3 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar3 + 0x30);
      *(float *)(iVar3 + 0x24) = fVar6 - *(float *)(iVar3 + 0x34);
      *(float *)(iVar3 + 0x28) = fVar7 - *(float *)(iVar3 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x50) + -0x88));
      iVar3 = *(int *)(param_1 + 0x50) + -0xa8;
      iVar4 = iVar3 + iVar2;
      tVector::Cross((tVector *)(iVar3 + iVar2),(tVector *)(iVar4 + 0x10),(tVector *)(iVar4 + 0x20))
      ;
      iVar2 = iVar2 + 0xa8;
    } while (iVar1 != (int)uVar12);
  }
LAB_0005900c:
  iVar2 = *(int *)(param_1 + 0x38);
  if (0 < iVar2 + -1) {
    iVar3 = 0;
    iVar1 = 0;
    do {
      iVar3 = iVar3 + 1;
      iVar2 = *(int *)(param_1 + 0x4c) + iVar1;
      iVar4 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar1;
      fVar6 = *(float *)(iVar4 + 0x34);
      fVar7 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar6 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar7 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar1 + *(int *)(param_1 + 0x4c);
      uVar5 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      *(undefined4 *)(iVar2 + 0x8c) = uVar5;
      iVar2 = *(int *)(param_1 + 0x50) + iVar1;
      iVar4 = *(int *)(param_1 + 0x50) + 0xa8 + iVar1;
      fVar6 = *(float *)(iVar4 + 0x34);
      fVar7 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar2 + 0x80) = *(float *)(iVar4 + 0x30) - *(float *)(iVar2 + 0x30);
      *(float *)(iVar2 + 0x84) = fVar6 - *(float *)(iVar2 + 0x34);
      *(float *)(iVar2 + 0x88) = fVar7 - *(float *)(iVar2 + 0x38);
      iVar2 = iVar1 + *(int *)(param_1 + 0x50);
      uVar5 = tVector::Normalize((tVector *)(iVar2 + 0x80));
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar2 + 0x8c) = uVar5;
      iVar2 = *(int *)(param_1 + 0x38);
    } while (iVar3 < iVar2 + -1);
  }
  iVar2 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) = 0x3f800000;
  iVar2 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
  *(undefined4 *)(iVar2 + 0x84) = 0;
  *(undefined4 *)(iVar2 + 0x80) = 0;
  *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
  *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) = 0x3f800000;
  CalcLengthZ((cRPath *)param_1);
  return;
}
