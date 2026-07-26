/*
 * mangled: _ZN12cRLoadingBar6UnInitEv
 * demangled: cRLoadingBar::UnInit()
 * address: 0008a230
 * size: 64
 */

/* cRLoadingBar::UnInit() */

void __thiscall cRLoadingBar::UnInit(cRLoadingBar *this)

{
  gConfig._172_4_ = *(undefined4 *)(this + 4);
  cRSplashManager::SetSplash((cRSplashManager *)G0SplashManager,"");
  cRSplashManager::RenderEnd();
  return;
}
