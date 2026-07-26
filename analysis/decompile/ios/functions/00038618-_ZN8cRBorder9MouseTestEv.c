/*
 * mangled: _ZN8cRBorder9MouseTestEv
 * demangled: cRBorder::MouseTest()
 * address: 00038618
 * size: 640
 */

/* cRBorder::MouseTest() */

uint __thiscall cRBorder::MouseTest(cRBorder *this)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  uint in_fpscr;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  float fVar12;

  iVar3 = *(int *)PTR__Game_001b60b8;
  if ((4 < *(int *)(iVar3 + 600)) && ((*(uint *)(this + 0x194) & 0x100000) == 0)) {
    return 0;
  }
  if (this[0x50] != (cRBorder)0x0) {
    if (*(float *)(this + 0x234) + *(float *)(this + 0x248) <=
        *(float *)(*(int *)(iVar3 + 0x224) + 0x60)) {
      return 0;
    }
    fVar7 = *(float *)(*(int *)(iVar3 + 0x224) + 100);
    fVar9 = *(float *)(this + 0x238);
    if (NAN(fVar7) || NAN(fVar9)) {
      return 0;
    }
    uVar2 = in_fpscr & 0xfffffff | (uint)(fVar7 < fVar9 + *(float *)(this + 0x24c)) << 0x1f;
    if (!SUB41(uVar2 >> 0x1f,0)) {
      return 0;
    }
    fVar12 = (*(float *)(iVar3 + 0x234) - *(float *)(this + 0x234)) / *(float *)(this + 0x248);
    fVar9 = (*(float *)(iVar3 + 0x238) - fVar9) / *(float *)(this + 0x24c);
    iVar1 = cRSpriteManager::GetTga
                      ((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,*(int *)(this + 0x58));
    uVar4 = (uint)*(ushort *)(iVar1 + 0xc);
    fVar7 = (float)VectorSignedToFloat(uVar4,(byte)(uVar2 >> 0x16) & 3);
    iVar3 = (int)(fVar7 * fVar12);
    fVar7 = (float)VectorSignedToFloat((uint)*(ushort *)(iVar1 + 0xe),(byte)(uVar2 >> 0x16) & 3);
    bVar6 = iVar3 < 0;
    if (bVar6) {
      iVar3 = 0;
    }
    iVar11 = (int)(fVar7 * fVar9);
    if ((!bVar6) && ((int)(uVar4 - 1) <= iVar3)) {
      iVar3 = uVar4 - 1;
    }
    if (iVar11 < 0) {
      iVar11 = 0;
    }
    else {
      iVar5 = *(ushort *)(iVar1 + 0xe) - 1;
      if (iVar5 <= iVar11) {
        iVar11 = iVar5;
      }
      iVar11 = uVar4 * iVar11;
    }
    uVar2 = (uint)*(byte *)((iVar11 + iVar3) * 3 + iVar1 + 0x12);
    if (1 < uVar2) {
      return 0;
    }
    return 1 - uVar2;
  }
  fVar7 = *(float *)(this + 0x22c);
  fVar12 = *(float *)(this + 0x210);
  fVar9 = *(float *)(iVar3 + 0x234);
  if ((fVar9 <= fVar7 - fVar12) || (fVar12 + fVar7 + *(float *)(this + 0x23c) <= fVar9)) {
    if ((*(uint *)(this + 0x194) & 0x2000000) != 0) {
      fVar10 = *(float *)(this + 0x230);
      fVar8 = *(float *)(iVar3 + 0x238);
      if (fVar10 - fVar12 < fVar8) goto LAB_00038854;
    }
  }
  else {
    fVar10 = *(float *)(this + 0x230);
    fVar8 = *(float *)(iVar3 + 0x238);
    if (fVar10 - fVar12 < fVar8) {
LAB_00038854:
      if (fVar8 < fVar12 + fVar10 + *(float *)(this + 0x240)) {
        iVar3 = *(int *)(iVar3 + 0x224);
        fVar10 = *(float *)(iVar3 + 0x60);
        if ((fVar9 == fVar10) && (fVar8 == *(float *)(iVar3 + 100))) {
          return 1;
        }
        goto LAB_000387b0;
      }
    }
  }
  iVar3 = *(int *)(iVar3 + 0x224);
  fVar10 = *(float *)(iVar3 + 0x60);
LAB_000387b0:
  if (((fVar7 - fVar12 < fVar10) && (fVar10 < fVar12 + fVar7 + *(float *)(this + 0x23c))) ||
     ((*(uint *)(this + 0x194) & 0x2000000) != 0)) {
    if (*(float *)(this + 0x230) - fVar12 < *(float *)(iVar3 + 100)) {
      return (uint)(*(float *)(iVar3 + 100) <
                   fVar12 + *(float *)(this + 0x230) + *(float *)(this + 0x240));
    }
  }
  return 0;
}
