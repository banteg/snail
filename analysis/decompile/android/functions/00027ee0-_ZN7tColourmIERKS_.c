/*
 * mangled: _ZN7tColourmIERKS_
 * demangled: tColour::operator-=(tColour const&)
 * address: 00027ee0
 * size: 68
 */

/* tColour::TEMPNAMEPLACEHOLDERVALUE(tColour const&) */

void __thiscall tColour::operator-=(tColour *this,tColour *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;

  fVar3 = *(float *)(param_1 + 0xc);
  fVar1 = *(float *)(param_1 + 4);
  fVar2 = *(float *)(param_1 + 8);
  *(float *)this = *(float *)this - *(float *)param_1;
  *(float *)(this + 4) = *(float *)(this + 4) - fVar1;
  *(float *)(this + 8) = *(float *)(this + 8) - fVar2;
  *(float *)(this + 0xc) = *(float *)(this + 0xc) - fVar3;
  return;
}
