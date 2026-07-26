/*
 * mangled: _ZN8cRGalaxy5BoxOnEi
 * demangled: cRGalaxy::BoxOn(int)
 * address: 00058d80
 * size: 1200
 */

/* cRGalaxy::BoxOn(int) */

void __thiscall cRGalaxy::BoxOn(cRGalaxy *this,int param_1)

{
  bool bVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  cRBorder *pcVar12;
  int iVar13;
  int iVar14;
  cRBorder *pcVar15;
  float fVar16;
  int local_6c;
  float local_60;
  float local_5c;
  float local_58;
  float local_54 [2];

  fVar16 = DAT_0005917c;
  *(int *)(this + 0x8e34) = param_1;
  *(undefined4 *)(this + 4) = 1;
  local_6c = 0;
  bVar2 = false;
  cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e44));
  fVar11 = DAT_000591c0;
  fVar9 = DAT_00059198;
  uVar8 = DAT_00059194;
  fVar7 = DAT_00059190;
  fVar6 = DAT_0005918c;
  fVar5 = DAT_00059188;
  fVar4 = DAT_00059184;
  fVar3 = DAT_00059180;
  bVar1 = false;
  sprintf((char *)(*(int *)(this + 0x8e44) + 0x2c4),(char *)(DAT_000591b0 + 0x58dec + DAT_000591b8),
          *(undefined4 *)
           (*(int *)(DAT_000591b0 + 0x58dec + DAT_000591b4) + *(int *)(this + 0x8e34) * 4),
          this + *(int *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x208) * 0xa0 + 0x87e4);
  fVar10 = DAT_000591a0;
  iVar13 = *(int *)(this + 0x8e34);
  iVar14 = *(int *)(this + 0x8e44);
  *(float *)(iVar14 + 0x6ec) = *(float *)(this + iVar13 * 0x2a0 + 0x210) + DAT_0005919c;
  *(float *)(iVar14 + 0x6f0) = *(float *)(this + iVar13 * 0x2a0 + 0x214) - fVar10;
  do {
    cRBorder::RePosition(*(cRBorder **)(this + 0x8e44));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e48));
    Rstrcpy((char *)(*(int *)(this + 0x8e48) + 0x2c4),
            (char *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x224));
    cRBorder::SetBelow(*(cRBorder **)(this + 0x8e48),*(cRBorder **)(this + 0x8e44));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e4c));
    Rstrcpy((char *)(*(int *)(this + 0x8e4c) + 0x2c4),
            (char *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x2a4));
    cRBorder::SetBelow(*(cRBorder **)(this + 0x8e4c),*(cRBorder **)(this + 0x8e48));
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e50));
    pcVar15 = *(cRBorder **)(this + 0x8e50);
    pcVar12 = *(cRBorder **)(this + 0x8e4c);
    *(float *)(pcVar15 + 600) =
         (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
         fVar16 * *(float *)(*(int *)(this + 0x8e44) + 0x23c)) - fVar11;
    cRBorder::SetBelow(pcVar15,pcVar12);
    iVar13 = *(int *)(this + 0x8e24) + (*(int *)(this + 0x8e34) + 0x16) * 0x38;
    if (((*(int *)(gGroup0 + iVar13 + 0x5cdfc) == 1) && (gGroup0[iVar13 + 0x5ce20] != '\0')) &&
       (*(int *)(this + 0xc) == 2)) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e54));
      pcVar15 = *(cRBorder **)(this + 0x8e54);
      pcVar12 = *(cRBorder **)(this + 0x8e4c);
      *(float *)(pcVar15 + 600) =
           (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
           fVar16 * *(float *)(*(int *)(this + 0x8e44) + 0x23c)) - fVar11;
      cRBorder::SetBelow(pcVar15,pcVar12);
      cRBorder::SetBelow(*(cRBorder **)(this + 0x8e50),*(cRBorder **)(this + 0x8e54));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
    }
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e40));
    local_54[0] = fVar3;
    local_58 = fVar4;
    local_5c = fVar3;
    local_60 = fVar4;
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e44));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e48));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e4c));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e50));
    local_58 = local_58 + fVar5;
    local_60 = local_60 + fVar5;
    local_54[0] = local_54[0] - fVar5;
    if ((fVar6 < local_58) && (!bVar1)) {
      *(float *)(*(int *)(this + 0x8e44) + 0x6ec) =
           (*(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210) - (local_58 - local_54[0])) -
           fVar7;
    }
    if (local_54[0] < fVar7) {
      bVar1 = true;
      *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6ec) = uVar8;
    }
    if ((fVar9 < local_60) && (!bVar2)) {
      *(float *)(*(int *)(this + 0x8e44) + 0x6f0) = fVar9 - (local_60 - local_5c);
    }
    if (local_5c < fVar7) {
      bVar2 = true;
      *(float *)(*(int *)(this + 0x8e44) + 0x6f0) = fVar7;
    }
  } while (((((DAT_000591a4 < local_58) || (local_54[0] < DAT_000591a8)) ||
            (local_5c < DAT_000591a8)) || (DAT_000591ac < local_60)) &&
          (local_6c = local_6c + 1, local_6c != 5));
  pcVar12 = *(cRBorder **)(this + 0x8e54);
  iVar13 = *(int *)(this + 0x8e50);
  iVar14 = *(int *)(this + 0x8e40);
  *(float *)(iVar14 + 0x40) = local_54[0];
  *(float *)(iVar14 + 0x44) = local_5c;
  fVar16 = DAT_000591bc;
  *(float *)(iVar14 + 0x48) = local_58 - local_54[0];
  fVar16 = (local_54[0] + fVar16 * (local_58 - local_54[0])) - DAT_000591c0;
  *(float *)(iVar14 + 0x4c) = local_60 - local_5c;
  *(float *)(iVar13 + 600) = fVar16;
  *(float *)(pcVar12 + 600) = fVar16;
  cRBorder::RePosition(pcVar12);
  cRBorder::RePosition(*(cRBorder **)(this + 0x8e50));
  return;
}
