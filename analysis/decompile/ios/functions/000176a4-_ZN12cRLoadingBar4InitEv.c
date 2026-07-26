/*
 * mangled: _ZN12cRLoadingBar4InitEv
 * demangled: cRLoadingBar::Init()
 * address: 000176a4
 * size: 116
 */

/* cRLoadingBar::Init() */

void __thiscall cRLoadingBar::Init(cRLoadingBar *this)

{
  undefined *this_00;

  this_00 = PTR__G0SplashManager_001b61d4;
  cRSplashWindowManager::SetSplash
            ((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,"Sprites/sandlotloading.jpg");
  cRSplashWindowManager::RenderStart();
  cRSplashWindowManager::Render((cRSplashWindowManager *)this_00,1.0);
  MacSwapBuffers();
  MacFinish();
  *(undefined4 *)(this + 0x1c) = 1;
  this[0x24] = (cRLoadingBar)0x1;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x28) = 0x3f800000;
  *(undefined4 *)(this + 0x30) = 0x3d888889;
  *(undefined4 *)(this + 0x20) = 0;
  return;
}
