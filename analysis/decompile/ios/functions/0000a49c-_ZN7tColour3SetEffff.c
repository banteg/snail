/*
 * mangled: _ZN7tColour3SetEffff
 * demangled: tColour::Set(float, float, float, float)
 * address: 0000a49c
 * size: 24
 */

/* tColour::Set(float, float, float, float) */

void __thiscall tColour::Set(tColour *this,float param_1,float param_2,float param_3,float param_4)

{
  *(float *)(this + 4) = param_2;
  *(float *)(this + 8) = param_3;
  *(float *)this = param_1;
  *(float *)(this + 0xc) = param_4;
  return;
}
