/*
 * mangled: _ZN7tColour3SetEfff
 * demangled: tColour::Set(float, float, float)
 * address: 0000a4b4
 * size: 16
 */

/* tColour::Set(float, float, float) */

void __thiscall tColour::Set(tColour *this,float param_1,float param_2,float param_3)

{
  *(float *)this = param_1;
  *(float *)(this + 4) = param_2;
  *(float *)(this + 8) = param_3;
  return;
}
