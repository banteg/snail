/*
 * mangled: _ZN7tColouraSERK12tColourSmall
 * demangled: tColour::operator=(tColourSmall const&)
 * address: 0002802c
 * size: 88
 */

/* tColour::TEMPNAMEPLACEHOLDERVALUE(tColourSmall const&) */

void __thiscall tColour::operator=(tColour *this,tColourSmall *param_1)

{
  uint in_fpscr;
  float fVar1;

  fVar1 = (float)VectorUnsignedToFloat((uint)(byte)param_1[2],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)this = fVar1 / 255.0;
  fVar1 = (float)VectorUnsignedToFloat((uint)(byte)param_1[1],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 4) = fVar1 / 255.0;
  fVar1 = (float)VectorUnsignedToFloat((uint)(byte)*param_1,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 8) = fVar1 / 255.0;
  fVar1 = (float)VectorUnsignedToFloat((uint)(byte)param_1[3],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 0xc) = fVar1 / 255.0;
  return;
}
