/*
 * mangled: _ZN13cRSubRingStar2AIEv
 * demangled: cRSubRingStar::AI()
 * address: 0001d8f8
 * size: 384
 */

/* cRSubRingStar::AI() */

void __thiscall cRSubRingStar::AI(cRSubRingStar *this)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  iVar4 = *(int *)this;
  iVar5 = *(int *)(this + 4);
  fVar9 = *(float *)(this + 0x1c);
  fVar10 = 0.0;
  if (*(int *)(iVar5 + 0x7c) == 3) {
    fVar6 = *(float *)(this + 0x14);
  }
  else {
    fVar6 = *(float *)(this + 0x14) + *(float *)(this + 0x18);
    *(float *)(this + 0x14) = fVar6;
  }
  if (6.2831855 < fVar6) {
    fVar6 = fVar6 - 6.2831855;
    *(float *)(this + 0x14) = fVar6;
  }
  fVar6 = (float)Sin(fVar6);
  fVar8 = *(float *)(this + 0x1c);
  fVar1 = (float)Cos(*(float *)(this + 0x14));
  fVar7 = *(float *)(iVar5 + 0x60);
  *(float *)(iVar4 + 0x48) = *(float *)(iVar5 + 0x5c) + fVar9 * fVar6;
  fVar9 = *(float *)(iVar5 + 100);
  *(float *)(iVar4 + 0x4c) = fVar7 + fVar8 * fVar1;
  *(float *)(iVar4 + 0x50) = fVar9 + fVar10;
  iVar4 = *(int *)(this + 4);
  if ((*(int *)(iVar4 + 0x19c) == 0) && ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0)) {
    iVar4 = cRSpriteManager::New
                      ((int)PTR__gRSpriteManager_001b61e4,*(int *)(*(int *)(iVar4 + 0x78) + 0x370),
                       *(int *)(iVar4 + 0x1a0),-1);
    fVar6 = 1.0471976;
    *(float *)(iVar4 + 0x68) = fVar10;
    *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x800;
    *(undefined4 *)(iVar4 + 0x6c) = 0x3de38e39;
    *(undefined4 *)(iVar4 + 0x60) = 0x3ecccccd;
    *(undefined4 *)(iVar4 + 100) = 0x3e4ccccd;
    fVar7 = *(float *)(this + 0x1c);
    fVar9 = (float)Sin(*(float *)(this + 0x14) + 1.0471976);
    fVar1 = *(float *)(this + 0x1c);
    fVar6 = (float)Cos(*(float *)(this + 0x14) + fVar6);
    *(float *)(iVar4 + 0x5c) = fVar10;
    *(float *)(iVar4 + 0x58) = fVar1 * fVar6 * 0.3;
    *(float *)(iVar4 + 0x54) = fVar7 * fVar9 * 0.3;
    iVar5 = *(int *)this;
    *(float *)(iVar4 + 0x78) = fVar10;
    uVar2 = *(undefined4 *)(iVar5 + 0x4c);
    uVar3 = *(undefined4 *)(iVar5 + 0x50);
    *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(iVar5 + 0x48);
    *(undefined4 *)(iVar4 + 0x4c) = uVar2;
    *(undefined4 *)(iVar4 + 0x50) = uVar3;
  }
  return;
}
