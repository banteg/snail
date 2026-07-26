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
  float fVar3;
  float *in_stack_00000000;

  fVar2 = ((float)param_4 * DAT_00030f6c) / DAT_00030f70 + DAT_00030f74;
  iVar1 = (int)(*(float *)(**(int **)(DAT_00030f90 + 0x30e6c + DAT_00030f94) + 0x3c) -
               **(float **)(DAT_00030f90 + 0x30e6c + DAT_00030f98)) % 0x168;
  if (iVar1 == 0x5a) {
    fVar3 = ((float)param_3 * DAT_00030f78) / DAT_00030f7c;
    *in_r3 = (fVar2 * DAT_00030f7c) / DAT_00030f88 + DAT_00030f8c;
    *in_stack_00000000 = fVar3;
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
    fVar2 = DAT_00030f84 - fVar2;
    *in_r3 = DAT_00030f8c - (float)param_3;
    *in_stack_00000000 = fVar2;
    return;
  }
  if (iVar1 == 0x10e) {
    fVar3 = ((float)param_3 * DAT_00030f78) / DAT_00030f80 + DAT_00030f84;
    *in_r3 = (fVar2 * DAT_00030f7c) / DAT_00030f78;
    *in_stack_00000000 = fVar3;
    return;
  }
  return;
}
