/*
 * mangled: _ZN6cRPath9BuildWormEPc
 * demangled: cRPath::BuildWorm(char*)
 * address: 000571b0
 * size: 2680
 */

/* cRPath::BuildWorm(char*) */

void cRPath::BuildWorm(char *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  tVector *ptVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;

  param_1[0x2c] = '\x1c';
  param_1[0x2d] = '\0';
  param_1[0x2e] = '\0';
  param_1[0x2f] = '\0';
  param_1[0x48] = '\x10';
  param_1[0x49] = '\0';
  param_1[0x4a] = '\0';
  param_1[0x4b] = '\0';
  *(undefined1 **)(param_1 + 0x44) = &DAT_40800000;
  param_1[0x38] = '\x18';
  param_1[0x39] = '\0';
  param_1[0x3a] = '\0';
  param_1[0x3b] = '\0';
  param_1[0x30] = '\0';
  param_1[0x34] = '\0';
  param_1[0x35] = '\0';
  param_1[0x36] = '\0';
  param_1[0x37] = '\0';
  param_1[0x40] = '\0';
  param_1[0x41] = '\0';
  param_1[0x42] = -0x40;
  param_1[0x43] = 'B';
  uVar1 = RShellMemoryMalloc(0xfc0,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar1;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)(param_1 + 0x38));
  }
  fVar7 = 0.0;
  param_1[0x84] = '\0';
  fVar8 = 3.0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90) = 0;
  iVar3 = 1;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x4c));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x34) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x38) = *(float *)(param_1 + 0x44) * fVar7;
  tMatrix::Identity(*(tMatrix **)(param_1 + 0x50));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x34) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x50) + 0x38) = *(float *)(param_1 + 0x44) * fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x138) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x140) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x13c) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x148) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xd8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xe0) = *(undefined4 *)(param_1 + 0x44);
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xd8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xe0) = *(undefined4 *)(param_1 + 0x44);
  *(float *)(*(int *)(param_1 + 0x4c) + 0x1e0) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x1e8) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x1e4) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x1f0) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x180) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x184) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x188) =
       *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x44);
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x180) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x184) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x50) + 0x188) =
       *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x44);
  *(float *)(*(int *)(param_1 + 0x4c) + 0x288) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x290) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x28c) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x298) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x294) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x1f8));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x228) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x22c) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0x230) = *(float *)(param_1 + 0x44) * fVar8;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x1f8));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x228) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x288);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x22c) = 0x3efae148;
  fVar9 = 20.0;
  *(float *)(*(int *)(param_1 + 0x50) + 0x230) = *(float *)(param_1 + 0x44) * fVar8;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xdb0) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xdb8) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xdb4) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xdc0) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdbc) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xd20));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xd50) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdb0);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xd54) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xd58) = *(float *)(param_1 + 0x44) * fVar9;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xd20));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xd50) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdb0);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xd54) = 0x3efae148;
  fVar8 = 21.0;
  *(float *)(*(int *)(param_1 + 0x50) + 0xd58) = *(float *)(param_1 + 0x44) * fVar9;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xe58) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xe60) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xe5c) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xe68) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xe64) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xdc8));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdf8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xe58);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xdfc) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xe00) = *(float *)(param_1 + 0x44) * fVar8;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xdc8));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xdf8) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xe58);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xdfc) = 0x3efae148;
  fVar9 = 22.0;
  *(float *)(*(int *)(param_1 + 0x50) + 0xe00) = *(float *)(param_1 + 0x44) * fVar8;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xf00) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xf08) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xf04) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xf10) = fVar7;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xf0c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xe70));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xea0) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xf00);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xea4) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xea8) = *(float *)(param_1 + 0x44) * fVar9;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xe70));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xea0) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xf00);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xea4) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x50) + 0xea8) = *(float *)(param_1 + 0x44) * fVar9;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xfa8) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xfb0) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xfac) = fVar7;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xfb8) = fVar7;
  fVar7 = 23.0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xfb4) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0xf18));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xf48) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xfa8);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xf4c) = 0x3efae148;
  *(float *)(*(int *)(param_1 + 0x4c) + 0xf50) = *(float *)(param_1 + 0x44) * fVar7;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0xf18));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xf48) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0xfa8);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0xf4c) = 0x3efae148;
  iVar2 = 0x2a0;
  *(float *)(*(int *)(param_1 + 0x50) + 0xf50) = *(float *)(param_1 + 0x44) * fVar7;
  do {
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
    *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x30) =
         *(undefined4 *)(iVar2 + *(int *)(param_1 + 0x4c) + 0x90);
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x34) = 0x3efae148;
    fVar7 = (float)VectorSignedToFloat(iVar3 + 3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x38) = fVar7 * *(float *)(param_1 + 0x44);
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
    *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x34) = 0x3efae148;
    *(float *)(*(int *)(param_1 + 0x50) + iVar2 + 0x38) = fVar7 * *(float *)(param_1 + 0x44);
    if (iVar3 == 1) {
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2));
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2));
    }
    else {
      iVar5 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar5 + 0x10) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      iVar6 = *(int *)(param_1 + 0x4c) + iVar2;
      fVar7 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar7 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar8 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x4c) + -0x88));
      iVar5 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      tVector::Cross((tVector *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2),(tVector *)(iVar5 + 0x10)
                     ,(tVector *)(iVar5 + 0x20));
      ptVar4 = (tVector *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2);
      tVector::Cross(ptVar4 + 0x10,ptVar4 + 0x20,ptVar4);
      iVar5 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      *(undefined4 *)(iVar5 + 0x18) = 0;
      *(undefined4 *)(iVar5 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar5 + 0x10) = 0;
      iVar5 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      iVar6 = *(int *)(param_1 + 0x50) + iVar2;
      fVar7 = *(float *)(iVar6 + 0x34);
      fVar8 = *(float *)(iVar6 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar6 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar7 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar8 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x50) + -0x88));
      iVar5 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      tVector::Cross((tVector *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2),(tVector *)(iVar5 + 0x10)
                     ,(tVector *)(iVar5 + 0x20));
      ptVar4 = (tVector *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2);
      tVector::Cross(ptVar4 + 0x10,ptVar4 + 0x20,ptVar4);
      if (0xf < iVar3) {
        iVar2 = *(int *)(param_1 + 0x38);
        if (0 < iVar2 + -1) {
          iVar5 = 0;
          iVar3 = 0;
          do {
            iVar5 = iVar5 + 1;
            iVar2 = *(int *)(param_1 + 0x4c) + iVar3;
            iVar6 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar3;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar8 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar7 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar8 - *(float *)(iVar2 + 0x38);
            iVar2 = *(int *)(param_1 + 0x4c);
            uVar1 = tVector::Normalize((tVector *)(iVar3 + iVar2 + 0x80));
            *(undefined4 *)(iVar3 + iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)(param_1 + 0x50) + iVar3;
            iVar6 = *(int *)(param_1 + 0x50) + 0xa8 + iVar3;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar8 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar7 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar8 - *(float *)(iVar2 + 0x38);
            iVar2 = iVar3 + *(int *)(param_1 + 0x50);
            uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            iVar3 = iVar3 + 0xa8;
            *(undefined4 *)(iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)(param_1 + 0x38);
          } while (iVar5 < iVar2 + -1);
        }
        iVar2 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) =
             *(undefined4 *)(param_1 + 0x44);
        iVar2 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) =
             *(undefined4 *)(param_1 + 0x44);
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar2 = iVar2 + 0xa8;
    iVar3 = iVar3 + 1;
  } while( true );
}
