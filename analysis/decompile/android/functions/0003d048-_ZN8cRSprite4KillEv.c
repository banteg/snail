/*
 * mangled: _ZN8cRSprite4KillEv
 * demangled: cRSprite::Kill()
 * address: 0003d048
 * size: 248
 */

/* cRSprite::Kill() */

void __thiscall cRSprite::Kill(cRSprite *this)

{
  cRSprite *pcVar1;
  int iVar2;
  int iVar3;

  if ((*(uint *)(this + 4) & 1) == 0) {
    RShellError("Sprite kill error, already dead (%s)",*(int *)(this + 0x1c) + 0xc);
    if (this == (cRSprite *)gSpriteDummy) {
      return;
    }
  }
  else if (this == (cRSprite *)gSpriteDummy) {
    return;
  }
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffffe;
  pcVar1 = *(cRSprite **)(&DAT_00132054 + (*(int *)(this + 8) + 44000) * 4);
  if (pcVar1 == this) {
    iVar3 = *(int *)(this + 0xc);
    iVar2 = *(int *)(pcVar1 + 8);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x10) = 0;
    }
    *(int *)(&DAT_00132054 + (iVar2 + 44000) * 4) = iVar3;
    *(cRSprite **)(pcVar1 + 0xc) = pcRam0015cfe0;
    pcRam0015cfe0 = pcVar1;
    return;
  }
  iVar2 = *(int *)(this + 0x10);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(this + 0xc);
  }
  if (*(int *)(this + 0xc) != 0) {
    *(int *)(*(int *)(this + 0xc) + 0x10) = iVar2;
  }
  *(cRSprite **)(this + 0xc) = pcRam0015cfe0;
  pcRam0015cfe0 = this;
  return;
}
