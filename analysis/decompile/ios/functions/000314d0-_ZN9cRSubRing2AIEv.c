/*
 * mangled: _ZN9cRSubRing2AIEv
 * demangled: cRSubRing::AI()
 * address: 000314d0
 * size: 1292
 */

/* cRSubRing::AI() */

void __thiscall cRSubRing::AI(cRSubRing *this)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  cRSubRing *pcVar4;
  float fVar5;
  float fVar6;

  iVar1 = *(int *)(this + 0x184);
  if (*(char *)(iVar1 + 0x12) != '\0') {
    return;
  }
  if (*(int *)(this + 0x19c) == 2) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(this + 0x19c) + 1;
  }
  *(int *)(this + 0x19c) = iVar2;
  switch(*(undefined4 *)(this + 0x74)) {
  case 1:
    if (this[400] != (cRSubRing)0x0) {
      fVar5 = *(float *)(this + 0x194) + *(float *)(this + 0x198);
      *(float *)(this + 0x194) = fVar5;
      if (6.2831855 < fVar5) {
        fVar5 = fVar5 - 6.2831855;
        *(float *)(this + 0x194) = fVar5;
      }
      else if (fVar5 < 0.0) {
        fVar5 = fVar5 + 6.2831855;
        *(float *)(this + 0x194) = fVar5;
      }
      fVar5 = (float)Sin(fVar5);
      *(float *)(this + 0x5c) = fVar5 * 6.0 * 0.5;
    }
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x84));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xa4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xc4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xe4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x104));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x124));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x144));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x164));
    if (*(float *)(&DAT_000027f4 + *(int *)(this + 0x78)) <= *(float *)(this + 100)) {
      if (*(int *)(*(int *)(this + 0x78) + 0x3f4) < *(int *)(this + 0x80)) {
        *(undefined4 *)(this + 0x74) = 4;
      }
      return;
    }
    *(undefined4 *)(this + 0x74) = 0;
    break;
  case 2:
    *(undefined4 *)(this + 0x74) = 3;
    *(undefined4 *)(this + 0x188) = 0;
    *(float *)(this + 0x18c) = *(float *)(iVar1 + 0x4c) * 0.06944445;
  case 3:
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x84));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xa4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xc4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xe4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x104));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x124));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x144));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x164));
    fVar5 = *(float *)(this + 0x188);
    *(float *)(this + 0x188) = fVar5 + *(float *)(this + 0x18c);
    if (fVar5 + *(float *)(this + 0x18c) <= 1.0) {
      iVar1 = *(int *)(this + 0x78);
      fVar5 = *(float *)(&DAT_000027e0 + iVar1);
      pcVar4 = this + 0x5c;
      fVar6 = *(float *)(&DAT_000027d8 + iVar1);
      *(float *)(this + 0x60) =
           *(float *)(this + 0x60) +
           ((*(float *)(&DAT_000027dc + iVar1) + 0.0) - *(float *)(this + 0x60)) * 0.94;
      *(float *)(this + 100) =
           *(float *)(this + 100) + ((fVar5 + 0.2) - *(float *)(this + 100)) * 0.94;
      *(float *)(this + 0x5c) =
           *(float *)(this + 0x5c) + ((fVar6 + 0.0) - *(float *)(this + 0x5c)) * 0.94;
      *(float *)(this + 0xa0) = *(float *)(this + 0xa0) * 0.94;
      *(undefined4 *)(this + 0x8c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x90) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x94) = *(undefined4 *)(this + 100);
      *(float *)(this + 0xc0) = *(float *)(this + 0xc0) * 0.94;
      *(undefined4 *)(this + 0xac) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0xe0) = *(float *)(this + 0xe0) * 0.94;
      *(undefined4 *)(this + 0xcc) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x100) = *(float *)(this + 0x100) * 0.94;
      *(undefined4 *)(this + 0xec) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xf0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xf4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x120) = *(float *)(this + 0x120) * 0.94;
      *(undefined4 *)(this + 0x10c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x110) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x114) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x140) = *(float *)(this + 0x140) * 0.94;
      *(undefined4 *)(this + 300) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x130) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x134) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x160) = *(float *)(this + 0x160) * 0.94;
      *(undefined4 *)(this + 0x14c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x150) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x154) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x180) = *(float *)(this + 0x180) * 0.94;
      *(undefined4 *)(this + 0x16c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x170) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x174) = *(undefined4 *)(this + 100);
      return;
    }
    *(undefined4 *)(this + 0x74) = 0;
    break;
  case 4:
    *(undefined4 *)(this + 0x74) = 5;
    *(undefined4 *)(this + 0x188) = 0;
    *(float *)(this + 0x18c) = *(float *)(iVar1 + 0x4c) * 0.06944445;
  case 5:
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x84));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xa4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xc4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0xe4));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x104));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x124));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x144));
    cRSubRingStar::AI((cRSubRingStar *)(this + 0x164));
    fVar5 = *(float *)(this + 0x188);
    *(float *)(this + 0x188) = fVar5 + *(float *)(this + 0x18c);
    if (fVar5 + *(float *)(this + 0x18c) <= 1.0) {
      pcVar4 = this + 0x5c;
      *(float *)(this + 0xa0) = *(float *)(this + 0xa0) * 1.1;
      *(undefined4 *)(this + 0x8c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x90) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x94) = *(undefined4 *)(this + 100);
      *(float *)(this + 0xc0) = *(float *)(this + 0xc0) * 1.1;
      *(undefined4 *)(this + 0xac) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xb0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0xe0) = *(float *)(this + 0xe0) * 1.1;
      *(undefined4 *)(this + 0xcc) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x100) = *(float *)(this + 0x100) * 1.1;
      *(undefined4 *)(this + 0xec) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0xf0) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xf4) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x120) = *(float *)(this + 0x120) * 1.1;
      *(undefined4 *)(this + 0x10c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x110) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x114) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x140) = *(float *)(this + 0x140) * 1.1;
      *(undefined4 *)(this + 300) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x130) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x134) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x160) = *(float *)(this + 0x160) * 1.1;
      *(undefined4 *)(this + 0x14c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x150) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x154) = *(undefined4 *)(this + 100);
      *(float *)(this + 0x180) = *(float *)(this + 0x180) * 1.1;
      *(undefined4 *)(this + 0x16c) = *(undefined4 *)pcVar4;
      *(undefined4 *)(this + 0x170) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0x174) = *(undefined4 *)(this + 100);
switchD_0003150c_default:
      return;
    }
    *(undefined4 *)(this + 0x74) = 0;
    iVar1 = *(int *)PTR__Game_001b60b8;
    uVar3 = *(uint *)(this + 4);
    goto joined_r0x000317b4;
  default:
    goto switchD_0003150c_default;
  }
  iVar1 = *(int *)PTR__Game_001b60b8;
  uVar3 = *(uint *)(this + 4);
joined_r0x000317b4:
  if ((uVar3 & 0x200) == 0) {
    RShellError("List remove");
  }
  else if ((uVar3 & 0x40) == 0) {
    iVar2 = *(int *)(this + 0xc);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(this + 8);
    }
    if (*(int *)(this + 8) == 0) {
      *(int *)(iVar1 + 0x35c) = iVar2;
    }
    else {
      *(int *)(*(int *)(this + 8) + 0xc) = iVar2;
    }
    *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar1 + 0x360);
    *(cRSubRing **)(iVar1 + 0x360) = this;
    *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
  }
  else {
    RShellError("List remove NEXTBOD");
  }
  cRSprite::Kill(*(cRSprite **)(this + 0x84));
  cRSprite::Kill(*(cRSprite **)(this + 0xa4));
  cRSprite::Kill(*(cRSprite **)(this + 0xc4));
  cRSprite::Kill(*(cRSprite **)(this + 0xe4));
  cRSprite::Kill(*(cRSprite **)(this + 0x104));
  cRSprite::Kill(*(cRSprite **)(this + 0x124));
  cRSprite::Kill(*(cRSprite **)(this + 0x144));
  cRSprite::Kill(*(cRSprite **)(this + 0x164));
  return;
}
