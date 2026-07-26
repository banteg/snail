/*
 * mangled: _Z8MacInit2v
 * demangled: MacInit2()
 * address: 00008128
 * size: 128
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacInit2() */

void MacInit2(void)

{
  ID IVar1;

  wprintf("MacInit2\n");
  G0TextureSetLoad(1);
  cRGame::InitLast(_Game);
  _G0RenderAvailable = 0;
  cRLoadingBar::Finish((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
  _OFState = 0;
  IVar1 = UIApplication::sharedApplication((ID)&_OBJC_CLASS___UIApplication,"sharedApplication");
  IVar1 = UIApplication::delegate(IVar1,"delegate");
  UIApplication::initializeOpenfeint(IVar1,"initializeOpenfeint");
  cRFade::StartOn((cRFade *)(_Game + 0x24));
  return;
}
