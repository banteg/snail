/*
 * mangled: _ZN17cRResourceManager6ReInitEv
 * demangled: cRResourceManager::ReInit()
 * address: 0008ed5c
 * size: 180
 */

/* cRResourceManager::ReInit() */

void __thiscall cRResourceManager::ReInit(cRResourceManager *this)

{
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;

  wprintf("Resource ReInit");
  cRSplashManager::Init((cRSplashManager *)G0SplashManager);
  cRSplashManager::RenderStart();
  Invalidate(this);
  cRSplashManager::SetBar((cRSplashManager *)G0SplashManager,"Sprites/loadingbaron.tga");
  cRSplashManager::SetBarPos
            ((cRSplashManager *)G0SplashManager,extraout_s0,extraout_s1,extraout_s2,extraout_s3,
             extraout_s4,extraout_s5);
  cRSplashManager::SetSplash((cRSplashManager *)G0SplashManager,"Sprites/loading.png");
  G0SplashManager._160_4_ = 0;
  *(undefined4 *)this = 1;
  this[0x29048] = (cRResourceManager)0x1;
  return;
}
