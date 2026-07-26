/*
 * mangled: _ZN13cRStarManager2AIEv
 * demangled: cRStarManager::AI()
 * address: 000670f4
 * size: 364
 */

/* cRStarManager::AI() */

void __thiscall cRStarManager::AI(cRStarManager *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  switch(*(undefined4 *)(this + 0x2c)) {
  case 0:
    if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 4) != 0) {
      *(undefined4 *)(this + 0x2c) = 2;
      Init(this);
      *(undefined4 *)(this + 0x2c) = 2;
      *(undefined4 *)(this + 0x38) = 0;
      *(undefined4 *)(this + 0x3c) = 0x3caaaaab;
      UpdateStars(this,0.0);
      return;
    }
    return;
  case 1:
    UpdateStars(this,1.0);
    if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 4) == 0) {
      *(undefined4 *)(this + 0x38) = 0x3f800000;
      *(undefined4 *)(this + 0x3c) = 0x3caaaaab;
      *(undefined4 *)(this + 0x2c) = 3;
      return;
    }
    return;
  case 2:
    UpdateStars(this,*(float *)(this + 0x38));
    if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 4) != 0) {
      fVar4 = *(float *)(this + 0x38);
      *(float *)(this + 0x38) = fVar4 + *(float *)(this + 0x3c);
      if (1.0 < fVar4 + *(float *)(this + 0x3c)) {
        *(undefined4 *)(this + 0x2c) = 1;
      }
      return;
    }
    *(undefined4 *)(this + 0x2c) = 3;
    return;
  case 3:
    break;
  default:
    return;
  }
  UpdateStars(this,*(float *)(this + 0x38));
  if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 4) != 0) {
    *(undefined4 *)(this + 0x2c) = 2;
    return;
  }
  fVar4 = *(float *)(this + 0x38);
  *(float *)(this + 0x38) = fVar4 - *(float *)(this + 0x3c);
  if (fVar4 - *(float *)(this + 0x3c) < 0.0) {
    if (0 < *(int *)(this + 0x34)) {
      iVar2 = 0;
      iVar3 = 0;
      do {
        iVar2 = iVar2 + 1;
        *(undefined4 *)(*(int *)(this + 0x30) + iVar3) = 0;
        iVar1 = *(int *)(this + 0x30) + iVar3;
        iVar3 = iVar3 + 0x2c;
        cRSprite::Kill(*(cRSprite **)(iVar1 + 0x1c));
      } while (iVar2 < *(int *)(this + 0x34));
    }
    *(undefined4 *)(this + 0x2c) = 0;
    return;
  }
  return;
}
