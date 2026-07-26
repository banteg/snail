/*
 * mangled: _ZN8cRGalaxy5BoxOnEi
 * demangled: cRGalaxy::BoxOn(int)
 * address: 00068c08
 * size: 1584
 */

/* cRGalaxy::BoxOn(int) */

void __thiscall cRGalaxy::BoxOn(cRGalaxy *this,int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;

  *(undefined4 *)(this + 4) = 1;
  *(int *)(this + 0x8e34) = param_1;
  cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e44));
  bVar2 = false;
  bVar1 = false;
  iVar6 = 0;
  _sprintf((char *)(*(int *)(this + 0x8e44) + 0x2c4),"%s: %s",
           (&_gRomanNumbers)[*(int *)(this + 0x8e34)],
           this + *(int *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x208) * 0xa0 + 0x87e4);
  *(float *)(*(int *)(this + 0x8e44) + 0x6ec) =
       *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210) + 60.0;
  *(float *)(*(int *)(this + 0x8e44) + 0x6f0) =
       *(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x214) - 130.0;
  do {
    cRBorder::RePosition(*(cRBorder **)(this + 0x8e44));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e48));
    fVar12 = 0.5;
    fVar11 = 320.0;
    Rstrcpy((char *)(*(int *)(this + 0x8e48) + 0x2c4),
            (char *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x224));
    cRBorder::SetBelow(*(cRBorder **)(this + 0x8e48),*(cRBorder **)(this + 0x8e44));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e4c));
    Rstrcpy((char *)(*(int *)(this + 0x8e4c) + 0x2c4),
            (char *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x2a4));
    cRBorder::SetBelow(*(cRBorder **)(this + 0x8e4c),*(cRBorder **)(this + 0x8e48));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e50));
    *(float *)(*(int *)(this + 0x8e50) + 600) =
         (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
         *(float *)(*(int *)(this + 0x8e44) + 0x23c) * fVar12) - fVar11;
    cRBorder::SetBelow(*(cRBorder **)(this + 0x8e50),*(cRBorder **)(this + 0x8e4c));
    iVar5 = (*(int *)(this + 0x8e34) + 0x16) * 0x38 + *(int *)(this + 0x8e24);
    if (((*(int *)(&DAT_002a01b0 + iVar5) == 1) && ((&DAT_002a01d4)[iVar5] != '\0')) &&
       (*(int *)(this + 0xc) == 2)) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e54));
      *(float *)(*(int *)(this + 0x8e54) + 600) =
           (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
           *(float *)(*(int *)(this + 0x8e44) + 0x23c) * fVar12) - fVar11;
      cRBorder::SetBelow(*(cRBorder **)(this + 0x8e54),*(cRBorder **)(this + 0x8e4c));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x8e50),*(cRBorder **)(this + 0x8e54));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
    }
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e40));
    iVar5 = *(int *)(this + 0x8e44);
    if (*(int *)(iVar5 + 0x254) == 2) {
      fVar11 = *(float *)(iVar5 + 0x23c);
      if (fVar11 <= -2000.0) {
        fVar7 = 1000.0;
        fVar12 = -1000.0;
      }
      else {
        fVar12 = -1000.0;
        fVar7 = (fVar11 - -2000.0) * -0.5 + 1000.0;
        fVar7 = fVar7 + (fVar11 - (-1000.0 - fVar7)) * 0.5;
      }
    }
    else {
      fVar12 = *(float *)(iVar5 + 0x22c);
      fVar7 = fVar12;
      if (1000.0 <= fVar12) {
        fVar7 = 1000.0;
      }
      fVar12 = fVar12 + *(float *)(iVar5 + 0x23c);
      if (fVar12 <= -1000.0) {
        fVar12 = -1000.0;
      }
    }
    fVar8 = *(float *)(iVar5 + 0x230);
    iVar3 = *(int *)(this + 0x8e48);
    fVar11 = fVar8;
    if (1000.0 <= fVar8) {
      fVar11 = 1000.0;
    }
    fVar8 = fVar8 + *(float *)(iVar5 + 0x240);
    if (fVar8 <= -1000.0) {
      fVar8 = -1000.0;
    }
    if (*(int *)(iVar3 + 0x254) == 2) {
      fVar9 = *(float *)(iVar3 + 0x23c);
      if (fVar12 - fVar7 < fVar9) {
        fVar7 = fVar7 + (fVar9 - (fVar12 - fVar7)) * -0.5;
        fVar7 = fVar7 + (fVar9 - (fVar12 - fVar7)) * 0.5;
      }
    }
    else {
      fVar9 = *(float *)(iVar3 + 0x22c);
      if (fVar9 < fVar7) {
        fVar7 = fVar9;
      }
      fVar9 = fVar9 + *(float *)(iVar3 + 0x23c);
      if (fVar12 < fVar9) {
        fVar12 = fVar9;
      }
    }
    fVar10 = *(float *)(iVar3 + 0x230);
    iVar4 = *(int *)(this + 0x8e4c);
    fVar9 = fVar10 + *(float *)(iVar3 + 0x240);
    if (fVar10 < fVar11) {
      fVar11 = fVar10;
    }
    if (fVar9 <= fVar8) {
      fVar9 = fVar8;
    }
    if (*(int *)(iVar4 + 0x254) == 2) {
      fVar8 = *(float *)(iVar4 + 0x23c);
      if (fVar12 - fVar7 < fVar8) {
        fVar7 = fVar7 + (fVar8 - (fVar12 - fVar7)) * -0.5;
        fVar7 = fVar7 + (fVar8 - (fVar12 - fVar7)) * 0.5;
      }
    }
    else {
      fVar8 = *(float *)(iVar4 + 0x22c);
      if (fVar8 < fVar7) {
        fVar7 = fVar8;
      }
      fVar8 = fVar8 + *(float *)(iVar4 + 0x23c);
      if (fVar12 < fVar8) {
        fVar12 = fVar8;
      }
    }
    fVar10 = *(float *)(iVar4 + 0x230);
    iVar3 = *(int *)(this + 0x8e50);
    fVar8 = fVar10 + *(float *)(iVar4 + 0x240);
    if (fVar10 < fVar11) {
      fVar11 = fVar10;
    }
    if (fVar8 <= fVar9) {
      fVar8 = fVar9;
    }
    if (*(int *)(iVar3 + 0x254) == 2) {
      fVar9 = *(float *)(iVar3 + 0x23c);
      if (fVar12 - fVar7 < fVar9) {
        fVar7 = fVar7 + (fVar9 - (fVar12 - fVar7)) * -0.5;
        fVar7 = fVar7 + (fVar9 - (fVar12 - fVar7)) * 0.5;
      }
    }
    else {
      fVar9 = *(float *)(iVar3 + 0x22c);
      if (fVar9 < fVar7) {
        fVar7 = fVar9;
      }
      fVar9 = fVar9 + *(float *)(iVar3 + 0x23c);
      if (fVar12 < fVar9) {
        fVar12 = fVar9;
      }
    }
    fVar9 = *(float *)(iVar3 + 0x230);
    if (fVar9 < fVar11) {
      fVar11 = fVar9;
    }
    fVar9 = fVar9 + *(float *)(iVar3 + 0x240);
    fVar7 = fVar7 - 8.0;
    if (fVar9 <= fVar8) {
      fVar9 = fVar8;
    }
    fVar12 = fVar12 + 8.0;
    fVar9 = fVar9 + 8.0;
    if ((620.0 < fVar12) && (!bVar1)) {
      *(float *)(iVar5 + 0x6ec) =
           (*(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210) - (fVar12 - fVar7)) - 40.0;
    }
    if (fVar7 < 40.0) {
      bVar1 = true;
      *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6ec) = 0x42480000;
    }
    if ((390.0 < fVar9) && (!bVar2)) {
      *(float *)(*(int *)(this + 0x8e44) + 0x6f0) = 390.0 - (fVar9 - fVar11);
    }
    if (fVar11 < 40.0) {
      bVar2 = true;
      *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6f0) = 0x42200000;
    }
  } while (((((621.0 < fVar12) || (fVar7 < 39.0)) || (fVar11 < 39.0)) || (391.0 < fVar9)) &&
          (iVar6 = iVar6 + 1, iVar6 != 5));
  *(float *)(*(int *)(this + 0x8e40) + 0x48) = fVar12 - fVar7;
  *(float *)(*(int *)(this + 0x8e40) + 0x4c) = fVar9 - fVar11;
  *(float *)(*(int *)(this + 0x8e40) + 0x40) = fVar7;
  *(float *)(*(int *)(this + 0x8e40) + 0x44) = fVar11;
  *(float *)(*(int *)(this + 0x8e50) + 600) =
       (*(float *)(*(int *)(this + 0x8e40) + 0x40) +
       *(float *)(*(int *)(this + 0x8e40) + 0x48) * 0.5) - 320.0;
  *(float *)(*(int *)(this + 0x8e54) + 600) =
       (*(float *)(*(int *)(this + 0x8e40) + 0x40) +
       *(float *)(*(int *)(this + 0x8e40) + 0x48) * 0.5) - 320.0;
  cRBorder::RePosition(*(cRBorder **)(this + 0x8e54));
  cRBorder::RePosition(*(cRBorder **)(this + 0x8e50));
  return;
}
