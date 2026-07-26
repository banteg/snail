/*
 * mangled: _ZN17cRResourceManager12RenderSplashEv
 * demangled: cRResourceManager::RenderSplash()
 * address: 0008eb10
 * size: 52
 */

/* cRResourceManager::RenderSplash() */

void __thiscall cRResourceManager::RenderSplash(cRResourceManager *this)

{
  undefined4 uVar1;
  float fVar2;

  uVar1 = CalcPercent(this);
  *(undefined4 *)(*(int *)(DAT_0008eb44 + 0x8eb28 + DAT_0008eb48) + 0xa0) = uVar1;
  fVar2 = (float)cRSplashManager::RenderStart();
  cRSplashManager::Render(fVar2);
  return;
}
