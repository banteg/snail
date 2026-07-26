/*
 * mangled: _ZN8cRSprite2AIEv
 * demangled: cRSprite::AI()
 * address: 000114c4
 * size: 652
 */

/* cRSprite::AI() */

void __thiscall cRSprite::AI(cRSprite *this)

{
  cRSprite *pcVar1;
  int iVar2;
  cRSprite *pcVar3;
  int iVar4;
  uint uVar5;
  cRSprite *pcVar6;
  float fVar7;
  float fVar8;

  uVar5 = *(uint *)(this + 4);
  if (((uVar5 & 0x800) != 0) && (_gRSpriteManager != '\0')) {
    return;
  }
  if ((uVar5 & 8) == 0) {
    fVar7 = *(float *)(this + 0x68) + *(float *)(this + 0x6c);
    *(float *)(this + 0x68) = fVar7;
    if ((1.0 < fVar7) || (fVar7 < 0.0)) {
      *(undefined4 *)(this + 0x68) = 0x3f800000;
      if ((uVar5 & 0x100) != 0) {
        return;
      }
      if ((uVar5 & 1) == 0) {
        RShellError("Sprite kill error, already dead (%s)",*(int *)(this + 0x1c) + 0xc);
      }
      if (this == (cRSprite *)&_gSpriteDummy) {
        return;
      }
      iVar2 = *(int *)(this + 8);
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffffe;
      if (this != (cRSprite *)(&DAT_002ac5dc)[iVar2]) {
        iVar2 = *(int *)(this + 0x10);
        if (iVar2 != 0) {
          *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(this + 0xc);
        }
        if (*(int *)(this + 0xc) != 0) {
          *(int *)(*(int *)(this + 0xc) + 0x10) = iVar2;
        }
        *(cRSprite **)(this + 0xc) = DAT_002ac5e8;
        DAT_002ac5e8 = this;
        return;
      }
      iVar4 = *(int *)(this + 0xc);
      if (iVar4 != 0) {
        *(undefined4 *)(iVar4 + 0x10) = 0;
      }
      (&DAT_002ac5dc)[iVar2] = iVar4;
      *(cRSprite **)(this + 0xc) = DAT_002ac5e8;
      DAT_002ac5e8 = this;
      return;
    }
    fVar7 = *(float *)(this + 0x74);
    if (fVar7 != 0.0) {
      fVar8 = *(float *)(this + 0x70);
      *(float *)(this + 0x70) = fVar7 + fVar8;
      if (1.0 < fVar7 + fVar8) {
        fVar7 = 0.0;
        *(undefined4 *)(this + 0x74) = 0;
      }
    }
  }
  else {
    uVar5 = uVar5 & 0xfffffff7;
    *(uint *)(this + 4) = uVar5;
    fVar7 = *(float *)(this + 0x74);
  }
  pcVar1 = *(cRSprite **)(this + 0x50);
  pcVar3 = this + 0x3c;
  pcVar6 = (cRSprite *)(uVar5 & 0xfffffff7);
  *(cRSprite **)(this + 4) = pcVar6;
  *(undefined4 *)pcVar3 = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(this + 0x40) = *(undefined4 *)(this + 0x4c);
  *(cRSprite **)(this + 0x44) = pcVar1;
  *(float *)(this + 0x48) = *(float *)(this + 0x48) + *(float *)(this + 0x54);
  if (0.0 < fVar7) {
    pcVar1 = (cRSprite *)((uint)pcVar6 | 0x200);
    pcVar6 = pcVar1;
  }
  else {
    pcVar3 = (cRSprite *)(uVar5 & 0xfffffdf7);
  }
  if (fVar7 <= 0.0) {
    *(cRSprite **)(this + 4) = pcVar3;
  }
  else {
    *(cRSprite **)(this + 4) = pcVar6;
    pcVar3 = pcVar1;
  }
  *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + *(float *)(this + 0x58);
  *(float *)(this + 0x50) = *(float *)(this + 0x50) + *(float *)(this + 0x5c);
  *(float *)(this + 0x58) = *(float *)(this + 0x58) + *(float *)(this + 0x78);
  *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
  if (((uint)pcVar3 & 0x2000) == 0) {
    return;
  }
  fVar7 = *(float *)(this + 0xa8) + *(float *)(this + 0xac);
  *(float *)(this + 0xa8) = fVar7;
  if (fVar7 <= 1.0) {
    return;
  }
  iVar2 = *(int *)(this + 0xa0) + *(int *)(this + 0xa4);
  *(int *)(this + 0xa0) = iVar2;
  *(float *)(this + 0xa8) = fVar7 - 1.0;
  if (((uint)pcVar3 & 0x4000) == 0) {
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
  *(int *)(this + 0x1c) = *(int *)(&DAT_002ac600 + *(int *)(this + 0x98) * 0x20) + iVar2 * 0xa4;
  return;
}
