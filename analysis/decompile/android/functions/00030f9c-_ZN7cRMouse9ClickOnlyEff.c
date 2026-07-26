/*
 * mangled: _ZN7cRMouse9ClickOnlyEff
 * demangled: cRMouse::ClickOnly(float, float)
 * address: 00030f9c
 * size: 68
 */

/* cRMouse::ClickOnly(float, float) */

void cRMouse::ClickOnly(float param_1,float param_2)

{
  cRMouse *in_r0;
  float *in_r1;
  float *in_r2;
  undefined4 local_10;
  undefined4 local_c;

  *(undefined4 *)(in_r0 + 0x30) = 0;
  ConvertScreenXY(in_r0,param_1,param_2,in_r1,in_r2);
  *(undefined4 *)(in_r0 + 0x28) = local_c;
  in_r0[0x24] = (cRMouse)0x1;
  *(undefined4 *)(in_r0 + 0x2c) = local_10;
  return;
}
