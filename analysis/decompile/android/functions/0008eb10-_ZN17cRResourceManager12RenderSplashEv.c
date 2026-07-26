/*
 * mangled: _ZN17cRResourceManager12RenderSplashEv
 * demangled: cRResourceManager::RenderSplash()
 * address: 0008eb10
 * size: 52
 */

/* cRResourceManager::RenderSplash() */

void __thiscall cRResourceManager::RenderSplash(cRResourceManager *this)

{
  float fVar1;

  G0SplashManager._160_4_ = CalcPercent(this);
  fVar1 = (float)cRSplashManager::RenderStart();
  cRSplashManager::Render(fVar1);
  return;
}
