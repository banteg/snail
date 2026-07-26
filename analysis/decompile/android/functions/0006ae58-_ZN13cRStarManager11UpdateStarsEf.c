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
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float in_r1;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;

  fVar7 = DAT_0006afb4;
  fVar6 = DAT_0006afb0;
  fVar5 = DAT_0006afac;
  fVar4 = DAT_0006afa8;
  fVar3 = DAT_0006afa4;
  fVar2 = DAT_0006afa0;
  iVar13 = *(int *)(this + 0x34);
  if (0 < iVar13) {
    iVar12 = 0;
    iVar10 = *(int *)(this + 0x30);
    iVar11 = **(int **)(DAT_0006afb8 + 0x6ae74 + DAT_0006afbc);
    do {
      fVar18 = *(float *)(iVar10 + 0x24) + *(float *)(iVar10 + 0x20);
      *(float *)(iVar10 + 0x24) = fVar18;
      if (fVar18 <= fVar2) {
        iVar14 = *(int *)(iVar10 + 0x1c);
      }
      else {
        *(float *)(iVar10 + 0x24) = fVar3;
        iVar14 = *(int *)(iVar10 + 0x1c);
        *(float *)(iVar14 + 0x88) = fVar3;
        fVar18 = *(float *)(iVar11 + 0x448);
        fVar19 = *(float *)(iVar11 + 0x450) + fVar4 * *(float *)(iVar11 + 0x440);
        fVar17 = *(float *)(iVar11 + 0x458);
        fVar16 = *(float *)(iVar11 + 0x454) + fVar4 * *(float *)(iVar11 + 0x444);
        *(float *)(iVar14 + 0x48) = fVar19;
        fVar17 = fVar17 + fVar4 * fVar18;
        *(float *)(iVar14 + 0x4c) = fVar16;
        *(float *)(iVar14 + 0x50) = fVar17;
        uVar8 = *(undefined4 *)(iVar10 + 0x14);
        uVar9 = *(undefined4 *)(iVar10 + 0x18);
        *(undefined4 *)(iVar14 + 0x54) = *(undefined4 *)(iVar10 + 0x10);
        *(undefined4 *)(iVar14 + 0x58) = uVar8;
        *(undefined4 *)(iVar14 + 0x5c) = uVar9;
        fVar18 = *(float *)(iVar10 + 0x14);
        fVar15 = *(float *)(iVar10 + 0x10);
        *(float *)(iVar14 + 0x50) = fVar17 + fVar5 * *(float *)(iVar10 + 0x18);
        *(float *)(iVar14 + 0x4c) = fVar16 + fVar5 * fVar18;
        *(float *)(iVar14 + 0x48) = fVar19 + fVar5 * fVar15;
        fVar18 = fVar3 + fVar5 * *(float *)(iVar10 + 0x20);
        *(float *)(iVar10 + 0x24) = fVar18;
      }
      pfVar1 = (float *)(iVar10 + 0x28);
      iVar12 = iVar12 + 1;
      iVar10 = iVar10 + 0x2c;
      *(float *)(iVar14 + 0x38) = ((fVar6 * *pfVar1 * (fVar18 - fVar7)) / fVar2) * in_r1;
    } while (iVar12 != iVar13);
  }
  return;
}
