/*
 * mangled: _Z14MacSwapBuffersv
 * demangled: MacSwapBuffers()
 * address: 00007844
 * size: 56
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacSwapBuffers() */

void MacSwapBuffers(void)

{
  ID IVar1;

  IVar1 = UIApplication::sharedApplication((ID)&_OBJC_CLASS___UIApplication,"sharedApplication");
  IVar1 = UIApplication::delegate(IVar1,"delegate");
  UIApplication::SwapBuffers(IVar1,"SwapBuffers");
  return;
}
