/*
 * mangled: _ZN6cRHelp2AIEv
 * demangled: cRHelp::AI()
 * address: 0006acec
 * size: 184
 */

/* cRHelp::AI() */

void __thiscall cRHelp::AI(cRHelp *this)

{
  undefined *puVar1;

  puVar1 = PTR__Game_001b60b8;
  if (((*(uint *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x30) & 0x4000) == 0) ||
     (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) != 0)) {
    if (this[4] == (cRHelp)0x0) {
      return;
    }
  }
  else if (this[4] == (cRHelp)0x0) {
    cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
    cRFade::Start((cRFade *)(*(int *)puVar1 + 0x24),(_func_void *)0x0);
    this[4] = (cRHelp)0x1;
  }
  puVar1 = PTR__Game_001b60b8;
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) != 4) {
    return;
  }
  cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(*(int *)puVar1 + 0x15c) = 2;
  *(undefined1 *)(*(int *)puVar1 + 0x2c0) = 1;
  return;
}
