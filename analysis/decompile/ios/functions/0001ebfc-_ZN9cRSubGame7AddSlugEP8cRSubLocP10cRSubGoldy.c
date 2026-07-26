/*
 * mangled: _ZN9cRSubGame7AddSlugEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)
 * address: 0001ebfc
 * size: 1160
 */

/* cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddSlug(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  byte bVar1;
  cRSubGame *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  cRSubGame *pcVar8;
  bool bVar9;
  uint in_fpscr;
  uint uVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  iVar5 = 0;
  if (*(int *)(this + 0x2da4) != 0) {
    if (*(int *)(this + 0x2e84) == 0) {
      iVar5 = 1;
    }
    else if (*(int *)(this + 0x2f64) == 0) {
      iVar5 = 2;
    }
    else if (*(int *)(this + 0x3044) == 0) {
      iVar5 = 3;
    }
    else if (*(int *)(this + 0x3124) == 0) {
      iVar5 = 4;
    }
    else if (*(int *)(this + 0x3204) == 0) {
      iVar5 = 5;
    }
    else if (*(int *)(this + 0x32e4) == 0) {
      iVar5 = 6;
    }
    else if (*(int *)(this + 0x33c4) == 0) {
      iVar5 = 7;
    }
    else if (*(int *)(this + 0x34a4) == 0) {
      iVar5 = 8;
    }
    else if (*(int *)(this + 0x3584) == 0) {
      iVar5 = 9;
    }
    else if (*(int *)(this + 0x3664) == 0) {
      iVar5 = 10;
    }
    else if (*(int *)(this + 0x3744) == 0) {
      iVar5 = 0xb;
    }
    else if (*(int *)(this + 0x3824) == 0) {
      iVar5 = 0xc;
    }
    else if (*(int *)(this + 0x3904) == 0) {
      iVar5 = 0xd;
    }
    else if (*(int *)(this + 0x39e4) == 0) {
      iVar5 = 0xe;
    }
    else {
      if (*(int *)(this + 0x3ac4) != 0) {
        return;
      }
      iVar5 = 0xf;
    }
  }
  iVar3 = iVar5 * 0xe0;
  *(undefined4 *)(this + iVar3 + 0x2da4) = 1;
  fVar14 = 0.0;
  *(cRSubGoldy **)(this + iVar3 + 0x2de4) = param_2;
  tMatrix::Identity((tMatrix *)(this + (int)(&DAT_00002d5c + iVar5 * 0x38)));
  fVar13 = *(float *)(param_1 + 0x10);
  fVar12 = *(float *)(param_1 + 0x14);
  *(float *)(this + iVar3 + 0x2d94) = *(float *)(param_1 + 0x18) + fVar14;
  *(float *)(this + iVar3 + 0x2d90) = fVar12 + 1.7;
  *(float *)(this + iVar3 + 0x2d8c) = fVar13 + fVar14;
  CalcRealPos(this,(tVector *)(this + (int)(&DAT_00002d8c + iVar5 * 0x38)),
              (float *)(this + iVar3 + 0x2dbc));
  fVar14 = *(float *)(this + 0x4c) * fVar14;
  *(float *)(this + iVar3 + 0x2db8) = *(float *)(this + 0x4c) * -0.2;
  *(float *)(this + iVar3 + 0x2db4) = fVar14;
  *(float *)(this + iVar3 + 0x2db0) = fVar14;
  iVar6 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + iVar3 + 0x2d34) & 0x200) == 0) {
    pcVar8 = this + 0xf448;
    *(cRSubGame **)(this + iVar3 + 0x2d3c) = pcVar8;
    bVar9 = *(cRSubGame **)(iVar6 + 0x35c) != pcVar8;
    if (bVar9) {
      pcVar8 = this + 0xf000;
    }
    pcVar2 = this + iVar3 + 0x2d30;
    if (bVar9) {
      *(undefined4 *)(this + iVar3 + 0x2d38) = *(undefined4 *)(pcVar8 + 0x450);
      *(cRSubGame **)(pcVar8 + 0x450) = pcVar2;
      *(cRSubGame **)(*(int *)(this + iVar3 + 0x2d38) + 0xc) = pcVar2;
    }
    else {
      *(cRSubGame **)(this + 0xf450) = pcVar2;
      *(cRSubGame **)(iVar6 + 0x35c) = pcVar2;
      *(undefined4 *)(this + iVar3 + 0x2d38) = 0;
    }
    *(uint *)(this + iVar5 * 0xe0 + 0x2d34) = *(uint *)(this + iVar5 * 0xe0 + 0x2d34) | 0x200;
  }
  else {
    RShellError("List ADDbefore");
  }
  iVar3 = cRSpriteManager::New((int)PTR__gRSpriteManager_001b61e4,*(int *)(param_2 + 0x370),0x6a,-1)
  ;
  *(int *)(this + iVar5 * 0xe0 + 0x2dd0) = iVar3;
  *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x800;
  tColour::White((tColour *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 0x2c));
  *(undefined4 *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 0x78) = 0;
  *(undefined4 *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 0x68) = 0;
  *(undefined4 *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 0x6c) = 0;
  *(undefined4 *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 0x60) = 0x40000000;
  *(undefined4 *)(*(int *)(this + iVar5 * 0xe0 + 0x2dd0) + 100) = 0x40000000;
  uVar4 = *(undefined4 *)(this + iVar5 * 0xe0 + 0x2d90);
  uVar7 = *(undefined4 *)(this + iVar5 * 0xe0 + 0x2d94);
  iVar3 = *(int *)(this + iVar5 * 0xe0 + 0x2dd0);
  *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(this + iVar5 * 0xe0 + 0x2d8c);
  *(undefined4 *)(iVar3 + 0x4c) = uVar4;
  *(undefined4 *)(iVar3 + 0x50) = uVar7;
  *(undefined4 *)(this + iVar5 * 0xe0 + 0x2df4) = 0;
  *(cRSubLoc **)(this + iVar5 * 0xe0 + 0x2dd4) = param_1;
  this[iVar5 * 0xe0 + 0x2dd8] = (cRSubGame)0x0;
  this[iVar5 * 0xe0 + 0x2df0] = (cRSubGame)0x0;
  fVar12 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x72bc4);
  *(undefined4 *)(this + iVar5 * 0xe0 + 0x2dec) = 7;
  this[iVar5 * 0xe0 + 0x2dfc] = (cRSubGame)0x0;
  *(uint *)(this + iVar5 * 0xe0 + 0x2d34) = *(uint *)(this + iVar5 * 0xe0 + 0x2d34) & 0xffffefff;
  this[iVar5 * 0xe0 + 0x2dfd] = (cRSubGame)0x0;
  *(undefined4 *)(this + iVar5 * 0xe0 + 0x2e00) = 0;
  *(float *)(this + iVar5 * 0xe0 + 0x2df8) = fVar12 * 0.16666667;
  *(undefined4 *)(this + iVar5 * 0xe0 + 0x2e04) = 0x3d088889;
  fVar14 = *(float *)(param_1 + 0x18);
  pcVar8 = this + 0x303aac;
  fVar12 = *(float *)pcVar8;
  uVar11 = in_fpscr & 0xfffffff | (uint)(fVar14 < fVar12) << 0x1f | (uint)(fVar14 == fVar12) << 0x1e
  ;
  uVar10 = uVar11 | (uint)(NAN(fVar14) || NAN(fVar12)) << 0x1c;
  bVar1 = (byte)(uVar11 >> 0x18);
  if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar10 >> 0x1c) & 1)) {
    *(undefined4 *)(this + iVar5 * 0xe0 + 0x2de8) = 1;
    *(float *)pcVar8 = *(float *)pcVar8 + *(float *)(this + 0x303ab0);
  }
  fVar12 = 1.0;
  *(undefined4 *)(this + iVar5 * 0xe0 + 0x2e08) = 0;
  uVar4 = gRMathRand2();
  fVar13 = 3.0517578e-05;
  fVar14 = (float)VectorSignedToFloat(uVar4,(byte)(uVar10 >> 0x16) & 3);
  uVar11 = uVar10 & 0xfffffff | (uint)(fVar12 + fVar14 * 3.0517578e-05 == 0.0) << 0x1e;
  if (SUB41(uVar11 >> 0x1e,0)) {
    fVar12 = 0.0;
  }
  else {
    uVar4 = gRMathRand2();
    fVar14 = (float)VectorSignedToFloat(uVar4,(byte)(uVar11 >> 0x16) & 3);
    fVar12 = fVar12 / ((fVar12 + fVar14 * fVar13) * 60.0);
  }
  *(float *)(this + iVar5 * 0xe0 + 0x2e0c) = fVar12;
  return;
}
