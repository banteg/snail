/*
 * mangled: _ZN8cRSprite4KillEv
 * demangled: cRSprite::Kill()
 * address: 0003d048
 * size: 248
 */

/* cRSprite::Kill() */

void __thiscall cRSprite::Kill(cRSprite *this)

{
  int iVar1;
  int iVar2;
  cRSprite *pcVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;

  iVar5 = DAT_0003d140 + 0x3d064;
  if ((*(uint *)(this + 4) & 1) == 0) {
    RShellError((char *)(iVar5 + DAT_0003d14c),*(int *)(this + 0x1c) + 0xc);
    if (this == *(cRSprite **)(iVar5 + DAT_0003d144)) {
      return;
    }
  }
  else if (this == *(cRSprite **)(iVar5 + DAT_0003d144)) {
    return;
  }
  iVar1 = DAT_0003d148;
  iVar2 = *(int *)(iVar5 + DAT_0003d148);
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffffe;
  pcVar3 = *(cRSprite **)(iVar2 + (*(int *)(this + 8) + 44000) * 4 + 4);
  if (pcVar3 == this) {
    iVar6 = *(int *)(this + 0xc);
    iVar2 = *(int *)(pcVar3 + 8);
    iVar5 = *(int *)(iVar5 + iVar1);
    if (iVar6 != 0) {
      *(undefined4 *)(iVar6 + 0x10) = 0;
    }
    uVar4 = *(undefined4 *)(iVar5 + 0x2af90);
    *(int *)(iVar5 + (iVar2 + 44000) * 4 + 4) = iVar6;
    *(undefined4 *)(pcVar3 + 0xc) = uVar4;
    *(cRSprite **)(iVar5 + 0x2af90) = pcVar3;
    return;
  }
  iVar2 = *(int *)(this + 0x10);
  iVar5 = *(int *)(iVar5 + iVar1);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(this + 0xc);
  }
  if (*(int *)(this + 0xc) != 0) {
    *(int *)(*(int *)(this + 0xc) + 0x10) = iVar2;
  }
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar5 + 0x2af90);
  *(cRSprite **)(iVar5 + 0x2af90) = this;
  return;
}
