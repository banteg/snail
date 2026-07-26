/*
 * mangled: _ZN12cRLoadingBar4InitEv
 * demangled: cRLoadingBar::Init()
 * address: 0008a660
 * size: 168
 */

/* cRLoadingBar::Init() */

void __thiscall cRLoadingBar::Init(cRLoadingBar *this)

{
  *(undefined4 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xcc) = 0;
  this[0x24] = (cRLoadingBar)0x0;
  *(undefined1 **)(this + 0xb8) = &gLoadingScript;
  this[0xbd] = (cRLoadingBar)0x0;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  this[0xd1] = (cRLoadingBar)0x0;
  this[0xd3] = (cRLoadingBar)0x0;
  this[0x36] = (cRLoadingBar)0x0;
  this[0x77] = (cRLoadingBar)0x0;
  this[0x35] = (cRLoadingBar)0x0;
  cRSplashManager::Init((cRSplashManager *)G0SplashManager);
  this[0xbc] = (cRLoadingBar)0x0;
  do {
    ScriptAI(this);
  } while (this[0xbc] == (cRLoadingBar)0x0);
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 0x28) = 0x3f800000;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  this[0x34] = (cRLoadingBar)0x1;
  *(undefined4 *)(this + 0x30) = 0x3d888889;
  return;
}
