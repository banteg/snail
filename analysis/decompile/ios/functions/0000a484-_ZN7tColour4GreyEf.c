/*
 * mangled: _ZN7tColour4GreyEf
 * demangled: tColour::Grey(float)
 * address: 0000a484
 * size: 24
 */

/* tColour::Grey(float) */

void __thiscall tColour::Grey(tColour *this,float param_1)

{
  *(float *)this = param_1;
  *(float *)(this + 4) = param_1;
  *(float *)(this + 8) = param_1;
  *(undefined4 *)(this + 0xc) = 0x3f800000;
  return;
}
