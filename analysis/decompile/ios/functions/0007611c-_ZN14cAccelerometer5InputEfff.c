/*
 * mangled: _ZN14cAccelerometer5InputEfff
 * demangled: cAccelerometer::Input(float, float, float)
 * address: 0007611c
 * size: 28
 */

/* cAccelerometer::Input(float, float, float) */

void __thiscall
cAccelerometer::Input(cAccelerometer *this,float param_1,float param_2,float param_3)

{
  *(float *)this = param_1;
  *(float *)(this + 4) = param_2;
  *(float *)(this + 8) = param_3;
  tVector::Normalize((tVector *)this);
  return;
}
