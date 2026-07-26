/*
 * mangled: _ZN9cRSubGolb4KillEv
 * demangled: cRSubGolb::Kill()
 * address: 000402a0
 * size: 448
 */

/* cRSubGolb::Kill() */

void __thiscall cRSubGolb::Kill(cRSubGolb *this)

{
  int iVar1;
  int iVar2;

  iVar1 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + 4) & 0x200) == 0) {
    RShellError("List remove");
  }
  else {
    if ((*(uint *)(this + 4) & 0x40) != 0) {
      RShellError("List remove NEXTBOD");
      *(undefined4 *)(this + 0x224) = 0;
      iVar1 = *(int *)(this + 0x1a0);
      goto joined_r0x0004034c;
    }
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
    *(cRSubGolb **)(iVar1 + 0x360) = this;
    *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
  }
  *(undefined4 *)(this + 0x224) = 0;
  iVar1 = *(int *)(this + 0x1a0);
joined_r0x0004034c:
  if (iVar1 == 1) {
    iVar1 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x78) & 0x200) == 0) {
      RShellError("List remove");
      return;
    }
    if ((*(uint *)(this + 0x78) & 0x40) == 0) {
      iVar2 = *(int *)(this + 0x80);
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(this + 0x7c);
      }
      if (*(int *)(this + 0x7c) == 0) {
        *(int *)(iVar1 + 0x35c) = iVar2;
      }
      else {
        *(int *)(*(int *)(this + 0x7c) + 0xc) = iVar2;
      }
      *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar1 + 0x360);
      *(cRSubGolb **)(iVar1 + 0x360) = this + 0x74;
      *(uint *)(this + 0x78) = *(uint *)(this + 0x78) & 0xfffffdff;
      return;
    }
    RShellError("List remove NEXTBOD");
    return;
  }
  if (iVar1 == 2) {
    iVar1 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x104) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 0x104) & 0x40) == 0) {
      iVar2 = *(int *)(this + 0x10c);
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(this + 0x108);
      }
      if (*(int *)(this + 0x108) == 0) {
        *(int *)(iVar1 + 0x35c) = iVar2;
      }
      else {
        *(int *)(*(int *)(this + 0x108) + 0xc) = iVar2;
      }
      *(undefined4 *)(this + 0x10c) = *(undefined4 *)(iVar1 + 0x360);
      *(cRSubGolb **)(iVar1 + 0x360) = this + 0x100;
      *(uint *)(this + 0x104) = *(uint *)(this + 0x104) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    iVar1 = *(int *)(this + 0x174);
    if (iVar1 != 0) {
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xffffefff;
    }
    return;
  }
  if (iVar1 != 0) {
    return;
  }
  cRSprite::Kill(*(cRSprite **)(this + 0x228));
  return;
}
