/*
 * mangled: _ZN6cRPath10BuildStartEfibPcS0_
 * demangled: cRPath::BuildStart(float, int, bool, char*, char*)
 * address: 0005edd0
 * size: 2100
 */

/* cRPath::BuildStart(float, int, bool, char*, char*) */

void cRPath::BuildStart(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  int iVar1;
  int iVar2;
  tVector *ptVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  undefined4 uVar8;
  float fVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  ulonglong uVar13;

  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x2c) = 0x2c;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  iVar10 = (int)((float)param_2 * 3.1415927);
  fVar12 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
  uVar13 = (ulonglong)(uint)fVar12;
  iVar7 = iVar10 + 0x10;
  *(int *)((int)param_1 + 0x38) = iVar7;
  iVar6 = iVar10 + 5;
  fVar12 = fVar12 / 3.1415927;
  uVar8 = VectorSignedToFloat(iVar10 + 0xf,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)((int)param_1 + 0x40) = uVar8;
  uVar8 = RShellMemoryMalloc(iVar7 * 0xa8,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar8;
  uVar8 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  iVar4 = *(int *)((int)param_1 + 0x38);
  *(undefined4 *)((int)param_1 + 0x50) = uVar8;
  if (0 < iVar4) {
    iVar2 = 0;
    iVar1 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar1 + 0xa0) = 0;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar1;
      iVar1 = iVar1 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
      iVar4 = *(int *)((int)param_1 + 0x38);
    } while (iVar2 < iVar4);
  }
  *(int *)((int)param_1 + 0x38) = iVar4 + -1;
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  fVar9 = fVar12 + fVar12;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  fVar11 = fVar9 + 0.49;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x34) = fVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x8c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(float *)(*(int *)((int)param_1 + 0x50) + 0x34) = fVar11;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x8c) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x13c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x148) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0xdc) = fVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x134) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(float *)(*(int *)((int)param_1 + 0x50) + 0xdc) = fVar11;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xe0) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x134) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e4) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1f0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x184) = fVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1dc) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(float *)(*(int *)((int)param_1 + 0x50) + 0x184) = fVar11;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x188) = 0x40000000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x1dc) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x290) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x28c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x298) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x294) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x228) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x22c) = fVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x230) = 0x40400000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x284) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x1f8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x228) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x288);
  *(float *)(*(int *)((int)param_1 + 0x50) + 0x22c) = fVar11;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x230) = 0x40400000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x284) = 0x3f800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x338) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x334) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x340) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x33c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x2d4) = fVar9;
  *(undefined1 **)(*(int *)((int)param_1 + 0x4c) + 0x2d8) = &DAT_40800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x32c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x2a0));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x2d0) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x330);
  *(float *)(*(int *)((int)param_1 + 0x50) + 0x2d4) = fVar11;
  *(undefined1 **)(*(int *)((int)param_1 + 0x50) + 0x2d8) = &DAT_40800000;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x32c) = 0x3f800000;
  iVar4 = iVar10 * 0xa8 + 0x348;
  do {
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x4c)));
    iVar2 = iVar6 + 1;
    iVar1 = iVar4 + *(int *)((int)param_1 + 0x4c);
    uVar8 = VectorSignedToFloat(iVar6,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x34) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x38) = uVar8;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x8c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar4 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x34) = 0x3efae148;
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar4 + 0x38) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar4 + 0x38);
    iVar6 = *(int *)((int)param_1 + 0x50) + iVar4;
    iVar4 = iVar4 + 0xa8;
    *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
    iVar6 = iVar2;
  } while (iVar2 != iVar7);
  if (0 < iVar10) {
    iVar4 = 0;
    iVar6 = 0x348;
    do {
      while( true ) {
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x90) = 0;
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x98) = 0;
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x94) = 0;
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
        tMatrix::Identity((tMatrix *)(iVar6 + *(int *)((int)param_1 + 0x4c)));
        fVar9 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
        iVar7 = iVar6 + *(int *)((int)param_1 + 0x4c);
        *(undefined4 *)(iVar7 + 0x30) = *(undefined4 *)(iVar7 + 0x90);
        uVar8 = VectorSignedToFloat(iVar4 + 5,(byte)(in_fpscr >> 0x16) & 3);
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x38) = uVar8;
        iVar7 = *(int *)((int)param_1 + 0x4c);
        fVar9 = (float)Cos((fVar9 * 3.1415927) / (float)uVar13);
        *(float *)(iVar6 + iVar7 + 0x34) = fVar12 + fVar9 * fVar12;
        tMatrix::Identity((tMatrix *)(iVar6 + *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x50) + 0x30) =
             *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x90);
        *(undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar8;
        *(float *)(iVar6 + *(int *)((int)param_1 + 0x50) + 0x34) =
             *(float *)(iVar6 + *(int *)((int)param_1 + 0x4c) + 0x34) + 0.49;
        if (0 < iVar4) break;
        iVar4 = iVar4 + 1;
        tMatrix::RotIdentity((tMatrix *)(iVar6 + *(int *)((int)param_1 + 0x4c) + -0xa8));
        tMatrix::RotIdentity((tMatrix *)(iVar6 + *(int *)((int)param_1 + 0x50) + -0xa8));
        iVar6 = iVar6 + 0xa8;
        if (iVar4 == iVar10) goto LAB_0005f534;
      }
      iVar4 = iVar4 + 1;
      puVar5 = (undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      iVar7 = iVar6 + *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar1 = iVar6 + *(int *)((int)param_1 + 0x4c);
      fVar9 = *(float *)(iVar1 + 0x34);
      fVar11 = *(float *)(iVar1 + 0x38);
      *(float *)(iVar7 + 0x20) = *(float *)(iVar1 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x24) = fVar9 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x28) = fVar11 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + *(int *)((int)param_1 + 0x4c) + -0x88));
      ptVar3 = (tVector *)(iVar6 + *(int *)((int)param_1 + 0x4c) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      puVar5 = (undefined4 *)(iVar6 + *(int *)((int)param_1 + 0x50) + -0xa8);
      puVar5[2] = 0;
      puVar5[1] = 0;
      *puVar5 = 0x3f800000;
      iVar7 = iVar6 + *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar1 = iVar6 + *(int *)((int)param_1 + 0x50);
      fVar9 = *(float *)(iVar1 + 0x34);
      fVar11 = *(float *)(iVar1 + 0x38);
      *(float *)(iVar7 + 0x20) = *(float *)(iVar1 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x24) = fVar9 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x28) = fVar11 - *(float *)(iVar7 + 0x38);
      tVector::Normalize((tVector *)(iVar6 + *(int *)((int)param_1 + 0x50) + -0x88));
      ptVar3 = (tVector *)(iVar6 + *(int *)((int)param_1 + 0x50) + -0xa8);
      tVector::Cross(ptVar3 + 0x10,ptVar3 + 0x20,ptVar3);
      iVar6 = iVar6 + 0xa8;
    } while (iVar4 != iVar10);
  }
LAB_0005f534:
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar6 = 0;
    do {
      iVar4 = iVar4 + 1;
      iVar7 = *(int *)((int)param_1 + 0x4c) + iVar6;
      iVar10 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar6;
      fVar12 = *(float *)(iVar10 + 0x34);
      fVar9 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar12 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar9 - *(float *)(iVar7 + 0x38);
      iVar7 = iVar6 + *(int *)((int)param_1 + 0x4c);
      uVar8 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      *(undefined4 *)(iVar7 + 0x8c) = uVar8;
      iVar7 = *(int *)((int)param_1 + 0x50) + iVar6;
      iVar10 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar6;
      fVar12 = *(float *)(iVar10 + 0x34);
      fVar9 = *(float *)(iVar10 + 0x38);
      *(float *)(iVar7 + 0x80) = *(float *)(iVar10 + 0x30) - *(float *)(iVar7 + 0x30);
      *(float *)(iVar7 + 0x84) = fVar12 - *(float *)(iVar7 + 0x34);
      *(float *)(iVar7 + 0x88) = fVar9 - *(float *)(iVar7 + 0x38);
      iVar7 = iVar6 + *(int *)((int)param_1 + 0x50);
      uVar8 = tVector::Normalize((tVector *)(iVar7 + 0x80));
      iVar6 = iVar6 + 0xa8;
      *(undefined4 *)(iVar7 + 0x8c) = uVar8;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  CalcLengthZ((cRPath *)param_1);
  return;
}
