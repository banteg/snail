/*
 * mangled: _ZN12cRLoadingBar2AIEv
 * demangled: cRLoadingBar::AI()
 * address: 00017724
 * size: 700
 */

/* cRLoadingBar::AI() */

void __thiscall cRLoadingBar::AI(cRLoadingBar *this)

{
  undefined *puVar1;
  float fVar2;

  switch(*(undefined4 *)(this + 0x1c)) {
  case 1:
    this[0x24] = (cRLoadingBar)0x1;
    *(float *)(this + 0x28) = 1.0 - *(float *)(this + 0x2c);
    fVar2 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
    *(float *)(this + 0x2c) = fVar2;
    if (1.0 < fVar2) {
      *(undefined4 *)(this + 0x2c) = 0;
      *(undefined4 *)(this + 0x28) = 0;
      *(undefined4 *)(this + 0x1c) = 2;
      cRSplashWindowManager::SetSplash
                ((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,
                 "Sprites/alpha72gamesloading.jpg");
    }
    break;
  case 2:
    this[0x24] = (cRLoadingBar)0x1;
    *(float *)(this + 0x28) = *(float *)(this + 0x2c);
    fVar2 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
    *(float *)(this + 0x2c) = fVar2;
    if (1.0 < fVar2) {
      *(undefined4 *)(this + 0x2c) = 0;
      *(undefined4 *)(this + 0x1c) = 3;
      *(undefined4 *)(this + 0x28) = 0x3f800000;
      this[0x24] = (cRLoadingBar)0x0;
    }
    break;
  case 3:
    *(undefined4 *)(this + 0x28) = 0x3f800000;
    *(undefined4 *)(this + 0x2c) = 0;
    this[0x24] = (cRLoadingBar)0x0;
    break;
  case 4:
    *(float *)(this + 0x28) = 1.0 - *(float *)(this + 0x2c);
    fVar2 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
    *(float *)(this + 0x2c) = fVar2;
    if (1.0 < fVar2) {
      this[0x24] = (cRLoadingBar)0x1;
      *(undefined4 *)(this + 0x2c) = 0;
      *(undefined4 *)(this + 0x1c) = 5;
      puVar1 = PTR__G0SplashManager_001b61d4;
      cRSplashWindowManager::SetSplash
                ((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,"Sprites/loading.jpg");
      cRSplashWindowManager::SetBar
                ((cRSplashWindowManager *)puVar1,"Sprites/loadingbaron.tga",0.0,210.0,512.0,64.0,
                 72.0,406.0);
    }
    break;
  case 5:
    this[0x24] = (cRLoadingBar)0x1;
    *(float *)(this + 0x28) = *(float *)(this + 0x2c);
    fVar2 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
    *(float *)(this + 0x2c) = fVar2;
    if (1.0 < fVar2) {
      *(undefined4 *)(this + 0x2c) = 0;
      this[0x24] = (cRLoadingBar)0x0;
      *(undefined4 *)(this + 0x28) = 0x3f800000;
      *(undefined4 *)(this + 0x1c) = 6;
    }
    break;
  case 6:
  case 8:
    this[0x24] = (cRLoadingBar)0x0;
    break;
  case 7:
    this[0x24] = (cRLoadingBar)0x1;
    *(float *)(this + 0x28) = 1.0 - *(float *)(this + 0x2c);
    fVar2 = *(float *)(this + 0x2c) + *(float *)(this + 0x30);
    *(float *)(this + 0x2c) = fVar2;
    if (1.0 < fVar2) {
      *(undefined4 *)(this + 0x1c) = 8;
      *(undefined4 *)(this + 0x2c) = 0;
      *(undefined4 *)(this + 0x28) = 0;
      puVar1 = PTR__G0SplashManager_001b61d4;
      cRSplashWindowManager::Render((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,0.0);
      MacSwapBuffers();
      wprintf("Loading Coubt Final %i\n",*(undefined4 *)(this + 4));
      *(undefined4 *)(PTR__gConfig_001b60d4 + 0xac) = *(undefined4 *)(this + 4);
      cRSplashWindowManager::SetSplash((cRSplashWindowManager *)puVar1,"");
      _glDepthMask(1);
      _glEnable(0xb71);
      _glMatrixMode(0x1701);
      _glDisableClientState(&DAT_00008074);
      _glDisableClientState(&DAT_00008078);
      this[0x24] = (cRLoadingBar)0x0;
      return;
    }
  }
  puVar1 = PTR__G0SplashManager_001b61d4;
  cRSplashWindowManager::Render
            ((cRSplashWindowManager *)PTR__G0SplashManager_001b61d4,*(float *)(this + 0x28));
  MacSwapBuffers();
  if (*(float *)(this + 0x28) == 0.0) {
    cRSplashWindowManager::Render((cRSplashWindowManager *)puVar1,*(float *)(this + 0x28));
    MacSwapBuffers();
  }
  return;
}
