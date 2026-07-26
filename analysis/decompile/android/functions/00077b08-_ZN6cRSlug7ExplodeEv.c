/*
 * mangled: _ZN6cRSlug7ExplodeEv
 * demangled: cRSlug::Explode()
 * address: 00077b08
 * size: 732
 */

/* cRSlug::Explode() */

void __thiscall cRSlug::Explode(cRSlug *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint in_fpscr;
  float extraout_s0;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;

  iVar15 = DAT_00077e24 + 0x77b24;
  iVar12 = **(int **)(iVar15 + DAT_00077e28);
  if (((gDirectory[iVar12 + 0x2544] == '\0') && (*(int *)(iVar12 + 100) == 1)) &&
     (*(int *)(iVar12 + 0x71900) != 7)) {
    if (**(int **)(iVar15 + DAT_00077e30) != -1) {
      iVar12 = **(int **)(iVar15 + DAT_00077e30) * 0x168 + *(int *)(iVar15 + DAT_00077e34);
      *(int *)(iVar12 + 0x28) = *(int *)(iVar12 + 0x28) + 1;
    }
    *(int *)(*(int *)(iVar15 + DAT_00077e38) + 0xc) =
         *(int *)(*(int *)(iVar15 + DAT_00077e38) + 0xc) + 1;
  }
  iVar12 = DAT_00077e2c;
  fVar9 = DAT_00077e04;
  fVar8 = DAT_00077e00;
  fVar7 = DAT_00077dfc;
  fVar6 = DAT_00077df8;
  fVar5 = DAT_00077df4;
  fVar4 = DAT_00077df0;
  fVar3 = DAT_00077dec;
  fVar2 = DAT_00077de8;
  fVar1 = DAT_00077de4;
  iVar14 = 0;
  do {
    uVar10 = gRMathRand2();
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    fVar16 = fVar2 + fVar20 * fVar1 * fVar2;
    uVar10 = gRMathRand2();
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    fVar17 = fVar4 + fVar20 * fVar1 * fVar3;
    iVar11 = cRSpriteManager::New(*(int *)(iVar15 + iVar12),1,0x75,-1);
    *(float *)(iVar11 + 0x84) = fVar17 + fVar17;
    *(float *)(iVar11 + 0x68) = fVar5;
    *(uint *)(iVar11 + 4) = *(uint *)(iVar11 + 4) | 0x802;
    uVar10 = gRMathRand2();
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 + fVar20 * fVar1 * fVar6 == 0.0) << 0x1e;
    fVar20 = fVar5;
    if (!SUB41(in_fpscr >> 0x1e,0)) {
      uVar10 = gRMathRand2();
      fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
      fVar20 = fVar9 / ((fVar7 + fVar20 * fVar1 * fVar6) * fVar8);
    }
    fVar18 = *(float *)(*(int *)(this + 0x7c) + 0x54);
    *(float *)(iVar11 + 0x70) = fVar5;
    *(float *)(iVar11 + 0x74) = fVar5;
    iVar14 = iVar14 + 1;
    *(float *)(iVar11 + 0x6c) = fVar20 * fVar18;
    uVar10 = gRMathRand2();
    VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    tColour::Grey((tColour *)(iVar11 + 0x2c),extraout_s0);
    iVar13 = *(int *)(this + 0x7c);
    *(float *)(iVar11 + 100) = fVar17 * DAT_00077e0c;
    fVar20 = DAT_00077e10;
    *(float *)(iVar11 + 0x60) = fVar17 * fVar7;
    *(float *)(iVar11 + 0x78) =
         *(float *)(iVar13 + 0x54) * *(float *)(iVar13 + 0x54) * fVar20 * DAT_00077e14;
    uVar10 = gRMathRand2();
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    fVar20 = (fVar20 - DAT_00077e18) * DAT_00077e1c;
    uVar10 = gRMathRand2();
    fVar17 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    uVar10 = gRMathRand2();
    fVar19 = *(float *)(*(int *)(this + 0x7c) + 0x54);
    fVar18 = *(float *)(*(int *)(this + 0x7c) + 0xfed4);
    *(float *)(iVar11 + 0x54) = fVar20 * fVar16 * fVar19;
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(iVar11 + 0x58) = fVar17 * fVar1 * (fVar16 + fVar7) * fVar19;
    *(float *)(iVar11 + 0x5c) = (fVar18 + fVar20 * fVar1 * fVar16) * fVar19;
    uVar10 = gRMathRand2();
    fVar16 = *(float *)(this + 0x5c);
    fVar17 = *(float *)(this + 0x60);
    fVar20 = (float)VectorSignedToFloat(uVar10,(byte)(in_fpscr >> 0x16) & 3);
    fVar20 = fVar20 * fVar1 * DAT_00077e20;
    *(float *)(iVar11 + 0x50) = *(float *)(this + 100) + fVar20 * *(float *)(iVar11 + 0x5c);
    *(float *)(iVar11 + 0x48) = fVar16 + fVar20 * *(float *)(iVar11 + 0x54);
    *(float *)(iVar11 + 0x4c) = fVar17 + fVar20 * *(float *)(iVar11 + 0x58);
  } while (iVar14 != 0x14);
  return;
}
