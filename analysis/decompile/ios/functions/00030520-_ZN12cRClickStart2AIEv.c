/*
 * mangled: _ZN12cRClickStart2AIEv
 * demangled: cRClickStart::AI()
 * address: 00030520
 * size: 784
 */

/* cRClickStart::AI() */

void __thiscall cRClickStart::AI(cRClickStart *this)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;

  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) != '\0') {
    return;
  }
  if (this[0x9c] == (cRClickStart)0x0) {
    cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
    iVar2 = *(int *)(this + 0x74);
  }
  else {
    cRBorder::HideInit(*(cRBorder **)(this + 0x78));
    iVar2 = *(int *)(this + 0x74);
  }
  puVar1 = PTR__Game_001b60b8;
  if (iVar2 == 3) {
    RandSeed(*(int *)(*(int *)(&DAT_00353540 + *(int *)PTR__Game_001b60b8) + 0x68));
    *(undefined4 *)(this + 0x74) = 4;
    *(undefined4 *)(this + 0x7c) = 0;
    *(undefined4 *)(this + 0x80) = 0x3c888889;
    cRBorderManager::Kill((cRBorder *)(*(int *)puVar1 + 0xd14));
  }
  else if (iVar2 != 4) {
    if (iVar2 != 2) {
      return;
    }
    *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x4e640) = 1;
    if (8 < *(int *)(&DAT_00353550 + *(int *)puVar1)) {
      *(undefined4 *)(&DAT_00353550 + *(int *)puVar1) = 8;
    }
    iVar2 = *(int *)puVar1;
    if (*(char *)(iVar2 + 0x72b8a) != '\0') {
      return;
    }
    if ((*(uint *)(*(int *)(iVar2 + 0x72b84) + 0x194) & 0x20000) != 0) {
      return;
    }
    if ((&DAT_00353544)[iVar2] == '\0') {
      if (this[0x9c] != (cRClickStart)0x0) {
        return;
      }
      if ((*(uint *)(*(int *)(iVar2 + 0x224) + 0x30) & 0x4000) == 0) {
        return;
      }
    }
    else if ((*(ushort *)
               (*(int *)(&DAT_00353550 + iVar2) * 6 + *(int *)(&DAT_00353548 + iVar2) + 0x74) & 0x20
             ) == 0) {
      return;
    }
    *(undefined1 *)(iVar2 + 0x23d) = 1;
    puVar1 = PTR__Game_001b60b8;
    *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x23f) = 1;
    *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = *(undefined4 *)(&DAT_00353550 + *(int *)puVar1)
    ;
    *(undefined4 *)(this + 0x74) = 3;
    iVar2 = *(int *)puVar1;
    if ((&DAT_00353544)[iVar2] == '\0') {
      iVar2 = *(int *)(&DAT_00353550 + iVar2) * 6 + *(int *)(&DAT_00353540 + iVar2);
      *(ushort *)(iVar2 + 0x74) = *(ushort *)(iVar2 + 0x74) | 0x20;
      iVar2 = *(int *)(&DAT_00353550 + *(int *)puVar1) * 6 +
              *(int *)(&DAT_00353540 + *(int *)puVar1);
      *(ushort *)(iVar2 + 0x74) = *(ushort *)(iVar2 + 0x74) & 0xfffe;
      *(undefined4 *)(*(int *)(&DAT_00353540 + *(int *)puVar1) + 0x24) =
           *(undefined4 *)(&DAT_00353550 + *(int *)puVar1);
    }
    RShellSetMouse(0,320.0,240.0);
    RShellSetMouse(1,320.0,240.0);
    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
    return;
  }
  puVar1 = PTR__Game_001b60b8;
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x7c) * 16.0;
  *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
  iVar2 = *(int *)puVar1;
  if ((*(uint *)(this + 4) & 0x200) != 0) {
    if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar3 = *(int *)(this + 0xc);
      if (iVar3 != 0) {
        *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar3;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar3;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar2 + 0x360);
      *(cRClickStart **)(iVar2 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    *(undefined4 *)(this + 0x74) = 0;
    return;
  }
  RShellError("List remove");
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
