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
  cRBorder *pcVar3;
  int iVar4;
  int iVar5;
  cRBorder *pcVar6;
  float fVar7;
  int local_6c;
  float local_60;
  float local_5c;
  float local_58;
  float local_54 [2];

  *(int *)(this + 0x8e34) = param_1;
  *(undefined4 *)(this + 4) = 1;
  local_6c = 0;
  bVar2 = false;
  cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e44));
  bVar1 = false;
  sprintf((char *)(*(int *)(this + 0x8e44) + 0x2c4),"%s: %s",
          (&gRomanNumbers)[*(int *)(this + 0x8e34)],
          this + *(int *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x208) * 0xa0 + 0x87e4);
  iVar4 = *(int *)(this + 0x8e34);
  iVar5 = *(int *)(this + 0x8e44);
  *(float *)(iVar5 + 0x6ec) = *(float *)(this + iVar4 * 0x2a0 + 0x210) + 60.0;
  *(float *)(iVar5 + 0x6f0) = *(float *)(this + iVar4 * 0x2a0 + 0x214) - 130.0;
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
    pcVar6 = *(cRBorder **)(this + 0x8e50);
    pcVar3 = *(cRBorder **)(this + 0x8e4c);
    *(float *)(pcVar6 + 600) =
         (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
         *(float *)(*(int *)(this + 0x8e44) + 0x23c) * 0.5) - 320.0;
    cRBorder::SetBelow(pcVar6,pcVar3);
    iVar4 = *(int *)(this + 0x8e24) + (*(int *)(this + 0x8e34) + 0x16) * 0x38;
    if (((*(int *)(gGroup0 + iVar4 + 0x5cdfc) == 1) && (gGroup0[iVar4 + 0x5ce20] != '\0')) &&
       (*(int *)(this + 0xc) == 2)) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e54));
      pcVar6 = *(cRBorder **)(this + 0x8e54);
      pcVar3 = *(cRBorder **)(this + 0x8e4c);
      *(float *)(pcVar6 + 600) =
           (*(float *)(*(int *)(this + 0x8e44) + 0x22c) +
           *(float *)(*(int *)(this + 0x8e44) + 0x23c) * 0.5) - 320.0;
      cRBorder::SetBelow(pcVar6,pcVar3);
      cRBorder::SetBelow(*(cRBorder **)(this + 0x8e50),*(cRBorder **)(this + 0x8e54));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x8e54));
    }
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x8e40));
    local_54[0] = 1000.0;
    local_58 = -1000.0;
    local_5c = 1000.0;
    local_60 = -1000.0;
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e44));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e48));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e4c));
    BorderBound(this,local_54,&local_58,&local_5c,&local_60,*(cRBorder **)(this + 0x8e50));
    local_58 = local_58 + 8.0;
    local_60 = local_60 + 8.0;
    local_54[0] = local_54[0] - 8.0;
    if ((620.0 < local_58) && (!bVar1)) {
      *(float *)(*(int *)(this + 0x8e44) + 0x6ec) =
           (*(float *)(this + *(int *)(this + 0x8e34) * 0x2a0 + 0x210) - (local_58 - local_54[0])) -
           40.0;
    }
    if (local_54[0] < 40.0) {
      bVar1 = true;
      *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6ec) = 0x42480000;
    }
    if ((390.0 < local_60) && (!bVar2)) {
      *(float *)(*(int *)(this + 0x8e44) + 0x6f0) = 390.0 - (local_60 - local_5c);
    }
    if (local_5c < 40.0) {
      bVar2 = true;
      *(undefined4 *)(*(int *)(this + 0x8e44) + 0x6f0) = 0x42200000;
    }
  } while (((((621.0 < local_58) || (local_54[0] < 39.0)) || (local_5c < 39.0)) ||
           (391.0 < local_60)) && (local_6c = local_6c + 1, local_6c != 5));
  pcVar3 = *(cRBorder **)(this + 0x8e54);
  iVar4 = *(int *)(this + 0x8e50);
  iVar5 = *(int *)(this + 0x8e40);
  *(float *)(iVar5 + 0x40) = local_54[0];
  *(float *)(iVar5 + 0x44) = local_5c;
  *(float *)(iVar5 + 0x48) = local_58 - local_54[0];
  fVar7 = (local_54[0] + (local_58 - local_54[0]) * 0.5) - 320.0;
  *(float *)(iVar5 + 0x4c) = local_60 - local_5c;
  *(float *)(iVar4 + 600) = fVar7;
  *(float *)(pcVar3 + 600) = fVar7;
  cRBorder::RePosition(pcVar3);
  cRBorder::RePosition(*(cRBorder **)(this + 0x8e50));
  return;
}
