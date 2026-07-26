/*
 * mangled: _ZN13cRStarManager11UpdateStarsEf
 * demangled: cRStarManager::UpdateStars(float)
 * address: 0006ae58
 * size: 328
 */

/* cRStarManager::UpdateStars(float) */

void __thiscall cRStarManager::UpdateStars(cRStarManager *this,float param_1)

{
  float *pfVar1;
  int iVar2;
  float in_r1;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  iVar2 = Game;
  iVar7 = *(int *)(this + 0x34);
  if (0 < iVar7) {
    iVar6 = 0;
    iVar5 = *(int *)(this + 0x30);
    do {
      fVar12 = *(float *)(iVar5 + 0x24) + *(float *)(iVar5 + 0x20);
      *(float *)(iVar5 + 0x24) = fVar12;
      if (fVar12 <= 35.0) {
        iVar8 = *(int *)(iVar5 + 0x1c);
      }
      else {
        *(undefined4 *)(iVar5 + 0x24) = 0;
        iVar8 = *(int *)(iVar5 + 0x1c);
        *(undefined4 *)(iVar8 + 0x88) = 0;
        fVar12 = *(float *)(iVar2 + 0x448);
        fVar13 = *(float *)(iVar2 + 0x450) + *(float *)(iVar2 + 0x440) * 50.0;
        fVar11 = *(float *)(iVar2 + 0x458);
        fVar10 = *(float *)(iVar2 + 0x454) + *(float *)(iVar2 + 0x444) * 50.0;
        *(float *)(iVar8 + 0x48) = fVar13;
        fVar11 = fVar11 + fVar12 * 50.0;
        *(float *)(iVar8 + 0x4c) = fVar10;
        *(float *)(iVar8 + 0x50) = fVar11;
        uVar3 = *(undefined4 *)(iVar5 + 0x14);
        uVar4 = *(undefined4 *)(iVar5 + 0x18);
        *(undefined4 *)(iVar8 + 0x54) = *(undefined4 *)(iVar5 + 0x10);
        *(undefined4 *)(iVar8 + 0x58) = uVar3;
        *(undefined4 *)(iVar8 + 0x5c) = uVar4;
        fVar12 = *(float *)(iVar5 + 0x14);
        fVar9 = *(float *)(iVar5 + 0x10);
        *(float *)(iVar8 + 0x50) = fVar11 + *(float *)(iVar5 + 0x18) * 10.0;
        *(float *)(iVar8 + 0x4c) = fVar10 + fVar12 * 10.0;
        *(float *)(iVar8 + 0x48) = fVar13 + fVar9 * 10.0;
        fVar12 = *(float *)(iVar5 + 0x20) * 10.0 + 0.0;
        *(float *)(iVar5 + 0x24) = fVar12;
      }
      pfVar1 = (float *)(iVar5 + 0x28);
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x2c;
      *(float *)(iVar8 + 0x38) = ((*pfVar1 * 0.5 * (fVar12 - 2.0)) / 35.0) * in_r1;
    } while (iVar6 != iVar7);
  }
  return;
}
