/*
 * mangled: _ZN8cRSprite2AIEv
 * demangled: cRSprite::AI()
 * address: 0003d234
 * size: 488
 */

/* cRSprite::AI() */

void __thiscall cRSprite::AI(cRSprite *this)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  float fVar4;
  float fVar5;

  uVar3 = *(uint *)(this + 4);
  if (((uVar3 & 0x800) == 0) || (gRSpriteManager == '\0')) {
    if ((uVar3 & 8) == 0) {
      fVar5 = *(float *)(this + 0x68) + *(float *)(this + 0x6c);
      *(float *)(this + 0x68) = fVar5;
      if ((1.0 < fVar5) || (fVar5 < 0.0)) {
        *(undefined4 *)(this + 0x68) = 0x3f800000;
        if ((uVar3 & 0x100) != 0) {
          return;
        }
        Kill(this);
        return;
      }
      fVar5 = *(float *)(this + 0x74);
      if (fVar5 != 0.0) {
        fVar4 = *(float *)(this + 0x70);
        *(float *)(this + 0x70) = fVar5 + fVar4;
        if (1.0 < fVar5 + fVar4) {
          *(undefined4 *)(this + 0x74) = 0;
          fVar5 = 0.0;
        }
      }
    }
    else {
      uVar3 = uVar3 & 0xfffffff7;
      *(uint *)(this + 4) = uVar3;
      fVar5 = *(float *)(this + 0x74);
    }
    *(uint *)(this + 4) = uVar3 & 0xfffffff7;
    uVar1 = *(undefined4 *)(this + 0x4c);
    *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + *(float *)(this + 0x58);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0x40) = uVar1;
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(this + 0x50);
    *(float *)(this + 0x48) = *(float *)(this + 0x48) + *(float *)(this + 0x54);
    *(float *)(this + 0x50) = *(float *)(this + 0x50) + *(float *)(this + 0x5c);
    *(float *)(this + 0x58) = *(float *)(this + 0x58) + *(float *)(this + 0x78);
    *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
    if (0.0 < fVar5) {
      uVar3 = uVar3 & 0xfffffff7 | 0x200;
      *(uint *)(this + 4) = uVar3;
    }
    else {
      uVar3 = uVar3 & 0xfffffdf7;
      *(uint *)(this + 4) = uVar3;
    }
    if ((uVar3 & 0x2000) != 0) {
      fVar5 = *(float *)(this + 0xa8) + *(float *)(this + 0xac);
      *(float *)(this + 0xa8) = fVar5;
      if (1.0 < fVar5) {
        iVar2 = *(int *)(this + 0xa4) + *(int *)(this + 0xa0);
        *(int *)(this + 0xa0) = iVar2;
        *(float *)(this + 0xa8) = fVar5 - 1.0;
        if ((*(uint *)(this + 4) & 0x4000) == 0) {
          if (iVar2 == *(int *)(this + 0x9c)) {
            *(undefined4 *)(this + 0xa0) = 0;
            iVar2 = 0;
          }
        }
        else {
          if (iVar2 == *(int *)(this + 0x9c)) {
            iVar2 = iVar2 + -1;
            *(int *)(this + 0xa0) = iVar2;
            *(undefined4 *)(this + 0xa4) = 0xffffffff;
          }
          if (iVar2 == -1) {
            iVar2 = 0;
            *(undefined4 *)(this + 0xa0) = 0;
            *(undefined4 *)(this + 0xa4) = 1;
          }
        }
        SetTextureRef(this,*(int *)(this + 0x98),iVar2);
        return;
      }
    }
  }
  return;
}
