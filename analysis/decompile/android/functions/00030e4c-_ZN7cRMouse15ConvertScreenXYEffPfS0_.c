/*
 * mangled: _ZN7cRMouse15ConvertScreenXYEffPfS0_
 * demangled: cRMouse::ConvertScreenXY(float, float, float*, float*)
 * address: 00030e4c
 * size: 288
 */

/* cRMouse::ConvertScreenXY(float, float, float*, float*) */

void __thiscall
cRMouse::ConvertScreenXY(cRMouse *this,float param_1,float param_2,float *param_3,float *param_4)

{
  int iVar1;
  float *in_r3;
  float fVar2;
  float *in_stack_00000000;

  fVar2 = ((float)param_4 * 460.0) / 470.0 + 10.0;
  iVar1 = (int)(*(float *)(Game + 0x3c) - gAndroidOrientation) % 0x168;
  if (iVar1 == 0x5a) {
    *in_r3 = (fVar2 * 640.0) / -480.0 + 639.0;
    *in_stack_00000000 = ((float)param_3 * 480.0) / 640.0;
    return;
  }
  if (iVar1 < 0x5b) {
    if (iVar1 == 0) {
      *in_r3 = (float)param_3;
      *in_stack_00000000 = fVar2;
    }
    return;
  }
  if (iVar1 == 0xb4) {
    *in_r3 = 639.0 - (float)param_3;
    *in_stack_00000000 = 479.0 - fVar2;
    return;
  }
  if (iVar1 == 0x10e) {
    *in_r3 = (fVar2 * 640.0) / 480.0;
    *in_stack_00000000 = ((float)param_3 * 480.0) / -640.0 + 479.0;
    return;
  }
  return;
}
