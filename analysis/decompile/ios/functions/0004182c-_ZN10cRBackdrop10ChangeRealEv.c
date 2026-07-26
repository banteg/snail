/*
 * mangled: _ZN10cRBackdrop10ChangeRealEv
 * demangled: cRBackdrop::ChangeReal()
 * address: 0004182c
 * size: 340
 */

/* cRBackdrop::ChangeReal() */

void __thiscall cRBackdrop::ChangeReal(cRBackdrop *this)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;

  puVar1 = PTR__Game_001b60b8;
  iVar2 = *(int *)(this + 0x54);
  if (iVar2 == *(int *)(this + 0x50)) goto LAB_000418c0;
  iVar3 = *(int *)PTR__Game_001b60b8;
  if (*(float *)(iVar3 + 0x3c) == 0.0) {
    if ((&DAT_003594e4)[iVar2 * 0x1ac + iVar3] == '\0') goto LAB_00041880;
LAB_00041954:
    iVar2 = cRSpriteManager::GetTextureRef((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,7);
    G0TextureReLoad(iVar2,(char *)(*(int *)(this + 0x54) * 0x1ac + *(int *)puVar1 + 0x3594e5));
  }
  else {
    if ((*(float *)(iVar3 + 0x3c) == 180.0) && ((&DAT_003594e4)[iVar2 * 0x1ac + iVar3] != '\0'))
    goto LAB_00041954;
LAB_00041880:
    iVar2 = cRSpriteManager::GetTextureRef((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,7);
    G0TextureReLoad(iVar2,(char *)(*(int *)(this + 0x54) * 0x1ac + 0x359464 +
                                  *(int *)PTR__Game_001b60b8));
  }
  *(undefined4 *)(this + 0x50) = *(undefined4 *)(this + 0x54);
LAB_000418c0:
  SetDistort(this,*(float *)(this + 0x5c));
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0x1358) = 1;
  this[0x69] = this[0x68];
  this[0x4c] = this[0x4d];
  this[0x34] = *(cRBackdrop *)
                (*(int *)(this + 0x54) * 0x1ac + *(int *)PTR__Game_001b60b8 + 0x359584);
  return;
}
