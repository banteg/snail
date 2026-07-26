/*
 * mangled: _ZN21cRSplashWindowManager4InitEv
 * demangled: cRSplashWindowManager::Init()
 * address: 00017484
 * size: 52
 */

/* cRSplashWindowManager::Init() */

void __thiscall cRSplashWindowManager::Init(cRSplashWindowManager *this)

{
  this[4] = (cRSplashWindowManager)0x0;
  this[5] = (cRSplashWindowManager)0x0;
  _glGenTextures(1,this + 0x24);
  _glGenTextures(1,this + 0x28);
  return;
}
