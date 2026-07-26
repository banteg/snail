/*
 * mangled: _ZN14cAccelerometer5InputEfff
 * demangled: cAccelerometer::Input(float, float, float)
 * address: 0005b8d8
 * size: 16
 */

/* cAccelerometer::Input(float, float, float) */

void __thiscall
cAccelerometer::Input(cAccelerometer *this,float param_1,float param_2,float param_3)

{
  undefined4 in_r1;
  undefined4 in_r2;
  undefined4 in_r3;

  *(undefined4 *)(this + 8) = in_r3;
  *(undefined4 *)this = in_r1;
  *(undefined4 *)(this + 4) = in_r2;
  tVector::Normalize((tVector *)this);
  return;
}
