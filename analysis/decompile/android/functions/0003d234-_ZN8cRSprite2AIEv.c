/*
 * mangled: _ZN8cRSprite2AIEv
 * demangled: cRSprite::AI()
 * address: 0003d234
 * size: 488
 */

/* cRSprite::AI() */

void __thiscall cRSprite::AI(cRSprite *this)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  fVar1 = DAT_0003d41c;
  uVar4 = *(uint *)(this + 4);
  if (((uVar4 & 0x800) == 0) || (**(char **)(DAT_0003d424 + 0x3d250 + DAT_0003d428) == '\0')) {
    if ((uVar4 & 8) == 0) {
      fVar7 = *(float *)(this + 0x68) + *(float *)(this + 0x6c);
      *(float *)(this + 0x68) = fVar7;
      fVar6 = DAT_0003d420;
      if ((fVar1 < fVar7) || (fVar7 < 0.0)) {
        *(float *)(this + 0x68) = DAT_0003d41c;
        if ((uVar4 & 0x100) != 0) {
          return;
        }
        Kill(this);
        return;
      }
      fVar7 = *(float *)(this + 0x74);
      if (fVar7 != 0.0) {
        fVar5 = *(float *)(this + 0x70);
        *(float *)(this + 0x70) = fVar7 + fVar5;
        if (fVar1 < fVar7 + fVar5) {
          *(float *)(this + 0x74) = fVar6;
          fVar7 = fVar6;
        }
      }
    }
    else {
      uVar4 = uVar4 & 0xfffffff7;
      *(uint *)(this + 4) = uVar4;
      fVar7 = *(float *)(this + 0x74);
    }
    *(uint *)(this + 4) = uVar4 & 0xfffffff7;
    uVar2 = *(undefined4 *)(this + 0x4c);
    *(float *)(this + 0x4c) = *(float *)(this + 0x4c) + *(float *)(this + 0x58);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0x40) = uVar2;
    *(undefined4 *)(this + 0x44) = *(undefined4 *)(this + 0x50);
    *(float *)(this + 0x48) = *(float *)(this + 0x48) + *(float *)(this + 0x54);
    *(float *)(this + 0x50) = *(float *)(this + 0x50) + *(float *)(this + 0x5c);
    *(float *)(this + 0x58) = *(float *)(this + 0x58) + *(float *)(this + 0x78);
    *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
    if (0.0 < fVar7) {
      uVar4 = uVar4 & 0xfffffff7 | 0x200;
      *(uint *)(this + 4) = uVar4;
    }
    else {
      uVar4 = uVar4 & 0xfffffdf7;
      *(uint *)(this + 4) = uVar4;
    }
    fVar1 = DAT_0003d41c;
    if ((uVar4 & 0x2000) != 0) {
      fVar6 = *(float *)(this + 0xa8) + *(float *)(this + 0xac);
      *(float *)(this + 0xa8) = fVar6;
      if (fVar1 < fVar6) {
        iVar3 = *(int *)(this + 0xa4) + *(int *)(this + 0xa0);
        *(int *)(this + 0xa0) = iVar3;
        *(float *)(this + 0xa8) = fVar6 - fVar1;
        if ((*(uint *)(this + 4) & 0x4000) == 0) {
          if (iVar3 == *(int *)(this + 0x9c)) {
            *(undefined4 *)(this + 0xa0) = 0;
            iVar3 = 0;
          }
        }
        else {
          if (iVar3 == *(int *)(this + 0x9c)) {
            iVar3 = iVar3 + -1;
            *(int *)(this + 0xa0) = iVar3;
            *(undefined4 *)(this + 0xa4) = 0xffffffff;
          }
          if (iVar3 == -1) {
            iVar3 = 0;
            *(undefined4 *)(this + 0xa0) = 0;
            *(undefined4 *)(this + 0xa4) = 1;
          }
        }
        SetTextureRef(this,*(int *)(this + 0x98),iVar3);
        return;
      }
    }
  }
  return;
}
