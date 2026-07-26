/*
 * mangled: _ZN13cRStarManager11UpdateStarsEf
 * demangled: cRStarManager::UpdateStars(float)
 * address: 00066aa4
 * size: 420
 */

/* cRStarManager::UpdateStars(float) */

void __thiscall cRStarManager::UpdateStars(cRStarManager *this,float param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  if (*(int *)(this + 0x34) < 1) {
    return;
  }
  iVar5 = 0;
  iVar6 = 0;
  do {
    iVar4 = iVar6 + *(int *)(this + 0x30);
    *(float *)(iVar4 + 0x24) = *(float *)(iVar4 + 0x24) + *(float *)(iVar4 + 0x20);
    iVar4 = *(int *)(this + 0x30);
    if (35.0 < *(float *)(iVar6 + iVar4 + 0x24)) {
      *(undefined4 *)(iVar6 + iVar4 + 0x24) = 0;
      *(undefined4 *)(*(int *)(*(int *)(this + 0x30) + iVar6 + 0x1c) + 0x88) = 0;
      iVar4 = *(int *)(*(int *)(this + 0x30) + iVar6 + 0x1c);
      iVar2 = *(int *)PTR__Game_001b60b8;
      fVar9 = *(float *)(iVar2 + 0x444);
      fVar8 = *(float *)(iVar2 + 0x454);
      *(float *)(iVar4 + 0x48) = *(float *)(iVar2 + 0x450) + *(float *)(iVar2 + 0x440) * 50.0;
      fVar7 = *(float *)(iVar2 + 0x448);
      fVar10 = *(float *)(iVar2 + 0x458);
      *(float *)(iVar4 + 0x4c) = fVar8 + fVar9 * 50.0;
      *(float *)(iVar4 + 0x50) = fVar10 + fVar7 * 50.0;
      iVar4 = iVar6 + *(int *)(this + 0x30);
      iVar2 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(undefined4 *)(iVar4 + 0x14);
      uVar3 = *(undefined4 *)(iVar4 + 0x18);
      *(undefined4 *)(iVar2 + 0x54) = *(undefined4 *)(iVar4 + 0x10);
      *(undefined4 *)(iVar2 + 0x58) = uVar1;
      *(undefined4 *)(iVar2 + 0x5c) = uVar3;
      iVar2 = iVar6 + *(int *)(this + 0x30);
      iVar4 = *(int *)(iVar2 + 0x1c);
      fVar8 = *(float *)(iVar2 + 0x14);
      fVar7 = *(float *)(iVar2 + 0x18);
      *(float *)(iVar4 + 0x48) = *(float *)(iVar4 + 0x48) + *(float *)(iVar2 + 0x10) * 10.0;
      *(float *)(iVar4 + 0x4c) = *(float *)(iVar4 + 0x4c) + fVar8 * 10.0;
      *(float *)(iVar4 + 0x50) = *(float *)(iVar4 + 0x50) + fVar7 * 10.0;
      iVar4 = iVar6 + *(int *)(this + 0x30);
      *(float *)(iVar4 + 0x24) = *(float *)(iVar4 + 0x24) + *(float *)(iVar4 + 0x20) * 10.0;
      iVar4 = *(int *)(this + 0x30);
    }
    iVar4 = iVar6 + iVar4;
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 0x2c;
    *(float *)(*(int *)(iVar4 + 0x1c) + 0x38) =
         ((*(float *)(iVar4 + 0x28) * 0.5 * (*(float *)(iVar4 + 0x24) - 2.0)) / 35.0) * param_1;
  } while (iVar5 < *(int *)(this + 0x34));
  return;
}
