/*
 * mangled: _ZN15cRSplashManager9SetBarPosEffffff
 * demangled: cRSplashManager::SetBarPos(float, float, float, float, float, float)
 * address: 00089a20
 * size: 168
 */

/* cRSplashManager::SetBarPos(float, float, float, float, float, float) */

void __thiscall
cRSplashManager::SetBarPos
          (cRSplashManager *this,float param_1,float param_2,float param_3,float param_4,
          float param_5,float param_6)

{
  float fVar1;
  float in_r1;
  float in_r2;
  float in_r3;
  float in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;

  fVar1 = (float)RShellGetScreenWidth();
  *(float *)(this + 0x88) = (fVar1 * in_r1) / 480.0;
  fVar1 = (float)RShellGetScreenHeight();
  *(float *)(this + 0x8c) = (fVar1 * in_r2) / 320.0;
  fVar1 = (float)RShellGetScreenWidth();
  *(float *)(this + 0x90) = (fVar1 * in_r3) / 480.0;
  fVar1 = (float)RShellGetScreenHeight();
  *(undefined4 *)(this + 0xa0) = 0;
  *(float *)(this + 0x9c) = (in_stack_00000008 * 100.0) / in_r3;
  *(float *)(this + 0x94) = -(fVar1 * in_stack_00000000) / 320.0;
  *(float *)(this + 0x98) = (in_stack_00000004 * 100.0) / in_r3;
  return;
}
