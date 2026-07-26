/*
 * mangled: _ZN8cRBorder9MouseTestEv
 * demangled: cRBorder::MouseTest()
 * address: 0005c8fc
 * size: 620
 */

/* cRBorder::MouseTest() */

uint __thiscall cRBorder::MouseTest(cRBorder *this)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  int iVar14;

  iVar3 = **(int **)(DAT_0005cb68 + 0x5c90c + DAT_0005cb6c);
  if ((4 < *(int *)(iVar3 + 600)) && ((*(uint *)(this + 0x194) & 0x100000) == 0)) {
    return 0;
  }
  if (this[0x50] != (cRBorder)0x0) {
    fVar11 = *(float *)(this + 0x234);
    fVar8 = *(float *)(this + 0x248);
    if (fVar11 + fVar8 <= *(float *)(*(int *)(iVar3 + 0x224) + 0x60)) {
      return 0;
    }
    fVar6 = *(float *)(*(int *)(iVar3 + 0x224) + 100);
    fVar9 = *(float *)(this + 0x238);
    if (NAN(fVar6) || NAN(fVar9)) {
      return 0;
    }
    fVar5 = *(float *)(this + 0x24c);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar6 < fVar9 + fVar5) << 0x1f;
    if (!SUB41(uVar1 >> 0x1f,0)) {
      return 0;
    }
    fVar6 = *(float *)(iVar3 + 0x234);
    fVar7 = *(float *)(iVar3 + 0x238);
    iVar3 = cRSpriteManager::GetTga
                      (*(cRSpriteManager **)(DAT_0005cb68 + 0x5c90c + DAT_0005cb70),
                       *(int *)(this + 0x58));
    uVar4 = (uint)*(ushort *)(iVar3 + 0xc);
    uVar2 = (uint)*(ushort *)(iVar3 + 0xe);
    fVar12 = (float)VectorSignedToFloat(uVar4,(byte)(uVar1 >> 0x16) & 3);
    fVar13 = (float)VectorSignedToFloat(uVar2,(byte)(uVar1 >> 0x16) & 3);
    iVar10 = (int)(fVar12 * ((fVar6 - fVar11) / fVar8));
    iVar14 = (int)(fVar13 * ((fVar7 - fVar9) / fVar5));
    if (iVar10 < 0) {
      iVar10 = 0;
    }
    else if ((int)uVar4 <= iVar10) {
      iVar10 = uVar4 - 1;
    }
    if (iVar14 < 0) {
      iVar14 = 0;
    }
    else if (iVar14 < (int)uVar2) {
      iVar14 = uVar4 * iVar14;
    }
    else {
      iVar14 = uVar4 * (uVar2 - 1);
    }
    uVar1 = (uint)*(byte *)(iVar3 + (iVar14 + iVar10) * 3 + 0x12);
    if (1 < uVar1) {
      return 0;
    }
    return 1 - uVar1;
  }
  fVar11 = *(float *)(this + 0x22c);
  fVar6 = *(float *)(this + 0x210);
  fVar8 = *(float *)(iVar3 + 0x234);
  if (((fVar11 - fVar6 < fVar8) && (fVar8 < fVar6 + fVar11 + *(float *)(this + 0x23c))) ||
     ((*(uint *)(this + 0x194) & 0x2000000) != 0)) {
    fVar9 = *(float *)(iVar3 + 0x238);
    if ((fVar9 <= *(float *)(this + 0x230) - fVar6) ||
       (fVar6 + *(float *)(this + 0x230) + *(float *)(this + 0x240) <= fVar9)) goto LAB_0005ca38;
    iVar3 = *(int *)(iVar3 + 0x224);
    fVar5 = *(float *)(iVar3 + 0x60);
    if ((fVar8 == fVar5) && (fVar9 == *(float *)(iVar3 + 100))) {
      return 1;
    }
  }
  else {
LAB_0005ca38:
    iVar3 = *(int *)(iVar3 + 0x224);
    fVar5 = *(float *)(iVar3 + 0x60);
  }
  if ((fVar5 <= fVar11 - fVar6) || (fVar6 + fVar11 + *(float *)(this + 0x23c) <= fVar5)) {
    if ((*(uint *)(this + 0x194) & 0x2000000) != 0) {
      fVar8 = *(float *)(this + 0x230);
      fVar11 = *(float *)(iVar3 + 100);
      if (fVar8 - fVar6 < fVar11) goto LAB_0005ca7c;
    }
  }
  else {
    fVar8 = *(float *)(this + 0x230);
    fVar11 = *(float *)(iVar3 + 100);
    if (fVar8 - fVar6 < fVar11) {
LAB_0005ca7c:
      return (uint)(fVar11 < fVar6 + fVar8 + *(float *)(this + 0x240));
    }
  }
  return 0;
}
