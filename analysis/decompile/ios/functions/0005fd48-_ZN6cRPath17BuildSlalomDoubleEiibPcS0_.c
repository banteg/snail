/*
 * mangled: _ZN6cRPath17BuildSlalomDoubleEiibPcS0_
 * demangled: cRPath::BuildSlalomDouble(int, int, bool, char*, char*)
 * address: 0005fd48
 * size: 2728
 */

/* cRPath::BuildSlalomDouble(int, int, bool, char*, char*) */

void cRPath::BuildSlalomDouble(int param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  tMatrix *this;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  int local_34;

  *(undefined4 *)(param_1 + 0x2c) = 0x28;
  *(undefined4 *)(param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x38) = 0x46;
  *(uint *)(param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)(param_1 + 0x40) = 0x428c0000;
  *(undefined1 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x2df0,"Path Tile Nodes");
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)(param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)(param_1 + 0x50) = uVar1;
  if (0 < *(int *)(param_1 + 0x38)) {
    iVar4 = 0;
    iVar2 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x90) = 0;
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
  *(undefined4 *)(&DAT_00002be0 + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002be8 + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002be4 + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002bf0 + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002bec + *(int *)(param_1 + 0x4c)) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(&DAT_00002b50 + *(int *)(param_1 + 0x4c)));
  *(undefined4 *)(&DAT_00002b80 + *(int *)(param_1 + 0x4c)) =
       *(undefined4 *)(&DAT_00002be0 + *(int *)(param_1 + 0x4c));
  *(undefined4 *)(&DAT_00002b84 + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002b88 + *(int *)(param_1 + 0x4c)) = 0x42840000;
  tMatrix::Identity((tMatrix *)(&DAT_00002b50 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(&DAT_00002b80 + *(int *)(param_1 + 0x50)) =
       *(undefined4 *)(&DAT_00002be0 + *(int *)(param_1 + 0x4c));
  *(undefined4 *)(&DAT_00002b84 + *(int *)(param_1 + 0x50)) = 0x3efae148;
  *(undefined4 *)(&DAT_00002b88 + *(int *)(param_1 + 0x50)) = 0x42840000;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c88) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c90) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c8c) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c98) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c94) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(&DAT_00002bf8 + *(int *)(param_1 + 0x4c)));
  *(undefined4 *)(&DAT_00002c28 + *(int *)(param_1 + 0x4c)) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c88);
  *(undefined4 *)(&DAT_00002c2c + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&DAT_00002c30 + *(int *)(param_1 + 0x4c)) = 0x42860000;
  tMatrix::Identity((tMatrix *)(&DAT_00002bf8 + *(int *)(param_1 + 0x50)));
  *(undefined4 *)(&DAT_00002c28 + *(int *)(param_1 + 0x50)) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2c88);
  *(undefined4 *)(&DAT_00002c2c + *(int *)(param_1 + 0x50)) = 0x3efae148;
  *(undefined4 *)(&DAT_00002c30 + *(int *)(param_1 + 0x50)) = 0x42860000;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d30) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d38) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d34) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d40) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d3c) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x2ca0));
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2cd0) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d30);
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2cd4) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2cd8) = 0x42880000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x2ca0));
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x2cd0) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2d30);
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x2cd4) = 0x3efae148;
  *(undefined4 *)(*(int *)(param_1 + 0x50) + 0x2cd8) = 0x42880000;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2dd8) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2de0) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2ddc) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2de8) = 0;
  *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2de4) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x4c) + 0x2d48));
  *(undefined4 *)((int)&DAT_00002d78 + *(int *)(param_1 + 0x4c)) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2dd8);
  *(undefined4 *)((int)&DAT_00002d7c + *(int *)(param_1 + 0x4c)) = 0;
  *(undefined4 *)(&__GLOBAL__I_MACAppPath + *(int *)(param_1 + 0x4c)) = 0x428a0000;
  tMatrix::Identity((tMatrix *)(*(int *)(param_1 + 0x50) + 0x2d48));
  *(undefined4 *)((int)&DAT_00002d78 + *(int *)(param_1 + 0x50)) =
       *(undefined4 *)(*(int *)(param_1 + 0x4c) + 0x2dd8);
  *(undefined4 *)((int)&DAT_00002d7c + *(int *)(param_1 + 0x50)) = 0x3efae148;
  *(undefined4 *)(&__GLOBAL__I_MACAppPath + *(int *)(param_1 + 0x50)) = 0x428a0000;
  iVar2 = 0x2a0;
  local_34 = 1;
  do {
    iVar4 = *(int *)(param_1 + 0x4c);
    fVar9 = 1.0;
    fVar7 = (float)VectorSignedToFloat(local_34 + -1,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = fVar7 / 62.0;
    fVar8 = fVar7 * 12.566371;
    fVar3 = (float)Sin(fVar8);
    fVar7 = fVar7 - 0.5;
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 < 0.0) << 0x1f;
    if (SUB41(in_fpscr >> 0x1f,0)) {
      fVar7 = fVar7 + 1.0;
    }
    else {
      fVar7 = 1.0 - fVar7;
    }
    *(float *)(iVar4 + iVar2 + 0x90) = fVar3 * 4.4444447 * fVar7 * fVar7;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x94) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0xa0) = 0;
    *(float *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x9c) = fVar9;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x4c)));
    iVar4 = iVar2 + *(int *)(param_1 + 0x4c);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    iVar4 = *(int *)(param_1 + 0x4c);
    fVar7 = (float)Cos(fVar8 * 0.5);
    *(float *)(iVar2 + iVar4 + 0x34) = fVar9 - fVar7;
    uVar1 = VectorSignedToFloat(local_34 + 3,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x38) = uVar1;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)(param_1 + 0x50)));
    *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x90);
    *(float *)(*(int *)(param_1 + 0x50) + iVar2 + 0x34) =
         *(float *)(*(int *)(param_1 + 0x4c) + iVar2 + 0x34) + 0.49;
    *(undefined4 *)(*(int *)(param_1 + 0x50) + iVar2 + 0x38) = uVar1;
    if (local_34 + -1 == 0) {
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2));
      tMatrix::RotIdentity((tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2));
    }
    else {
      fVar8 = 0.2617994;
      iVar4 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      *(float *)(iVar4 + 0x14) = fVar9;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar4 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2;
      iVar5 = *(int *)(param_1 + 0x4c) + iVar2;
      fVar7 = *(float *)(iVar5 + 0x34);
      fVar3 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x24) = fVar7 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x28) = fVar3 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x4c) + -0x88));
      iVar4 = *(int *)(param_1 + 0x4c) + -0xa8;
      iVar5 = iVar4 + iVar2;
      tVector::Cross((tVector *)(iVar4 + iVar2),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      this = (tMatrix *)(*(int *)(param_1 + 0x4c) + -0xa8 + iVar2);
      tMatrix::RotLocalZ(this,*(float *)(this + 0x90) * fVar8);
      iVar4 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      *(float *)(iVar4 + 0x14) = fVar9;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar4 = *(int *)(param_1 + 0x50) + -0xa8 + iVar2;
      iVar5 = *(int *)(param_1 + 0x50) + iVar2;
      fVar7 = *(float *)(iVar5 + 0x34);
      fVar3 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x24) = fVar7 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x28) = fVar3 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)(param_1 + 0x50) + -0x88));
      iVar4 = *(int *)(param_1 + 0x50) + -0xa8;
      iVar5 = iVar4 + iVar2;
      tVector::Cross((tVector *)(iVar4 + iVar2),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      tMatrix::RotLocalZ((tMatrix *)(*(int *)(param_1 + 0x50) + -0xa8 + iVar2),
                         *(float *)(iVar2 + *(int *)(param_1 + 0x4c) + -0x18) * fVar8);
      if (0x3d < local_34) {
        iVar2 = *(int *)(param_1 + 0x38);
        if (0 < iVar2 + -1) {
          iVar5 = 0;
          iVar4 = 0;
          do {
            iVar5 = iVar5 + 1;
            iVar2 = *(int *)(param_1 + 0x4c) + iVar4;
            iVar6 = *(int *)(param_1 + 0x4c) + 0xa8 + iVar4;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar3 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar7 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar3 - *(float *)(iVar2 + 0x38);
            iVar2 = iVar4 + *(int *)(param_1 + 0x4c);
            uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            *(undefined4 *)(iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)(param_1 + 0x50) + iVar4;
            iVar6 = *(int *)(param_1 + 0x50) + 0xa8 + iVar4;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar3 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar7 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar3 - *(float *)(iVar2 + 0x38);
            iVar2 = iVar4 + *(int *)(param_1 + 0x50);
            uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            iVar4 = iVar4 + 0xa8;
            *(undefined4 *)(iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)(param_1 + 0x38);
          } while (iVar5 < iVar2 + -1);
        }
        iVar2 = *(int *)(param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x4c) + -0x1c) =
             0x3f800000;
        iVar2 = *(int *)(param_1 + 0x50) + -0xa8 + *(int *)(param_1 + 0x38) * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)(*(int *)(param_1 + 0x38) * 0xa8 + *(int *)(param_1 + 0x50) + -0x1c) =
             0x3f800000;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar2 = iVar2 + 0xa8;
    local_34 = local_34 + 1;
  } while( true );
}
