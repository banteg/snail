/*
 * mangled: _ZN12cRSubSpeedUp2AIEv
 * demangled: cRSubSpeedUp::AI()
 * address: 00031224
 * size: 244
 */

/* cRSubSpeedUp::AI() */

void __thiscall cRSubSpeedUp::AI(cRSubSpeedUp *this)

{
  int iVar1;
  uint uVar2;
  int iVar3;

  if (*(char *)(*(int *)(this + 0x80) + 0x12) != '\0') {
    return;
  }
  if (*(int *)(this + 0x74) == 1) {
    if (*(float *)(&DAT_000027f4 + *(int *)(this + 0x78)) <= *(float *)(this + 100)) {
      return;
    }
    *(undefined4 *)(this + 0x74) = 0;
    iVar1 = *(int *)PTR__Game_001b60b8;
    uVar2 = *(uint *)(this + 4);
  }
  else {
    if (*(int *)(this + 0x74) != 2) {
      return;
    }
    *(undefined4 *)(this + 0x74) = 0;
    iVar1 = *(int *)PTR__Game_001b60b8;
    uVar2 = *(uint *)(this + 4);
  }
  if ((uVar2 & 0x200) != 0) {
    if ((uVar2 & 0x40) == 0) {
      iVar3 = *(int *)(this + 0xc);
      if (iVar3 != 0) {
        *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar1 + 0x35c) = iVar3;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar3;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar1 + 0x360);
      *(cRSubSpeedUp **)(iVar1 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    cRSprite::Kill(*(cRSprite **)(this + 0xa0));
    return;
  }
  RShellError("List remove");
  cRSprite::Kill(*(cRSprite **)(this + 0xa0));
  return;
}
