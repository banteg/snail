/*
 * mangled: _ZN17cRResourceManager6ReInitEv
 * demangled: cRResourceManager::ReInit()
 * address: 0008ed5c
 * size: 180
 */

/* cRResourceManager::ReInit() */

void __thiscall cRResourceManager::ReInit(cRResourceManager *this)

{
  int iVar1;
  cRSplashManager *this_00;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float extraout_s4;
  float extraout_s5;

  iVar1 = DAT_0008ee1c + 0x8ed74;
  wprintf((char *)(iVar1 + DAT_0008ee20));
  this_00 = *(cRSplashManager **)(iVar1 + DAT_0008ee24);
  cRSplashManager::Init(this_00);
  cRSplashManager::RenderStart();
  Invalidate(this);
  cRSplashManager::SetBar(this_00,(char *)(iVar1 + DAT_0008ee28));
  cRSplashManager::SetBarPos
            (this_00,extraout_s0,extraout_s1,extraout_s2,extraout_s3,extraout_s4,extraout_s5);
  cRSplashManager::SetSplash(this_00,(char *)(iVar1 + DAT_0008ee2c));
  *(undefined4 *)(this_00 + 0xa0) = 0;
  *(undefined4 *)this = 1;
  this[0x29048] = (cRResourceManager)0x1;
  return;
}
