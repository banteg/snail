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
  float fVar2;
  float fVar3;
  float in_r1;
  float in_r2;
  float in_r3;
  float fVar4;
  float in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;

  fVar3 = (float)RShellGetScreenWidth();
  fVar2 = DAT_00089acc;
  fVar1 = DAT_00089ac8;
  *(float *)(this + 0x88) = (fVar3 * in_r1) / DAT_00089ac8;
  fVar3 = (float)RShellGetScreenHeight();
  *(float *)(this + 0x8c) = (fVar3 * in_r2) / fVar2;
  fVar3 = (float)RShellGetScreenWidth();
  *(float *)(this + 0x90) = (fVar3 * in_r3) / fVar1;
  fVar3 = (float)RShellGetScreenHeight();
  fVar1 = DAT_00089ad0;
  fVar4 = in_stack_00000008 * DAT_00089ad0;
  *(undefined4 *)(this + 0xa0) = DAT_00089ad4;
  *(float *)(this + 0x9c) = fVar4 / in_r3;
  *(float *)(this + 0x94) = -(fVar3 * in_stack_00000000) / fVar2;
  *(float *)(this + 0x98) = (in_stack_00000004 * fVar1) / in_r3;
  return;
}
