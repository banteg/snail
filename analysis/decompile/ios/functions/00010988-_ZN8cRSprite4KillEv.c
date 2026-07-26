/*
 * mangled: _ZN8cRSprite4KillEv
 * demangled: cRSprite::Kill()
 * address: 00010988
 * size: 200
 */

/* cRSprite::Kill() */

void __thiscall cRSprite::Kill(cRSprite *this)

{
  int iVar1;
  int iVar2;

  if ((*(uint *)(this + 4) & 1) == 0) {
    RShellError("Sprite kill error, already dead (%s)",*(int *)(this + 0x1c) + 0xc);
    if (this == (cRSprite *)&_gSpriteDummy) {
      return;
    }
  }
  else if (this == (cRSprite *)&_gSpriteDummy) {
    return;
  }
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffffe;
  iVar1 = *(int *)(this + 8);
  if ((cRSprite *)(&DAT_002ac5dc)[iVar1] == this) {
    iVar2 = *(int *)(this + 0xc);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x10) = 0;
    }
    (&DAT_002ac5dc)[iVar1] = iVar2;
    *(cRSprite **)(this + 0xc) = DAT_002ac5e8;
    DAT_002ac5e8 = this;
    return;
  }
  iVar1 = *(int *)(this + 0x10);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(this + 0xc);
  }
  if (*(int *)(this + 0xc) != 0) {
    *(int *)(*(int *)(this + 0xc) + 0x10) = iVar1;
  }
  *(cRSprite **)(this + 0xc) = DAT_002ac5e8;
  DAT_002ac5e8 = this;
  return;
}
