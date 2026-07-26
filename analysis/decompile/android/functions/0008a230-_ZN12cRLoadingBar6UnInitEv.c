/*
 * mangled: _ZN12cRLoadingBar6UnInitEv
 * demangled: cRLoadingBar::UnInit()
 * address: 0008a230
 * size: 64
 */

/* cRLoadingBar::UnInit() */

void __thiscall cRLoadingBar::UnInit(cRLoadingBar *this)

{
  int iVar1;
  cRSplashManager *this_00;

  iVar1 = DAT_0008a270 + 0x8a240;
  this_00 = *(cRSplashManager **)(iVar1 + DAT_0008a278);
  *(undefined4 *)(*(int *)(iVar1 + DAT_0008a274) + 0xac) = *(undefined4 *)(this + 4);
  cRSplashManager::SetSplash(this_00,(char *)(iVar1 + DAT_0008a27c));
  cRSplashManager::RenderEnd();
  return;
}
