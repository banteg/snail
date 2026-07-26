/*
 * mangled: _Z8G0Renderv
 * demangled: G0Render()
 * address: 0006e1a8
 * size: 116
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0Render() */

void G0Render(void)

{
  int iVar1;

  iVar1 = cRSplashWindowManager::Render((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,1.0);
  if (iVar1 != 0) {
    _glClear(0x100);
    return;
  }
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x328) != 0) {
    cRGame::Render(*(cRGame **)PTR__Game_001b60b8);
    return;
  }
  _glClear(0x100);
  cRGame::Render(*(cRGame **)PTR__Game_001b60b8);
  return;
}
