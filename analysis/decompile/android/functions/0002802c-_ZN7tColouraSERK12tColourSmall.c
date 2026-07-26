/*
 * mangled: _ZN7tColouraSERK12tColourSmall
 * demangled: tColour::operator=(tColourSmall const&)
 * address: 0002802c
 * size: 88
 */

/* tColour::TEMPNAMEPLACEHOLDERVALUE(tColourSmall const&) */

void __thiscall tColour::operator=(tColour *this,tColourSmall *param_1)

{
  float fVar1;
  uint in_fpscr;
  float fVar2;

  fVar1 = DAT_00028084;
  fVar2 = (float)VectorUnsignedToFloat((uint)(byte)param_1[2],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)this = fVar2 / DAT_00028084;
  fVar2 = (float)VectorUnsignedToFloat((uint)(byte)param_1[1],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 4) = fVar2 / fVar1;
  fVar2 = (float)VectorUnsignedToFloat((uint)(byte)*param_1,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 8) = fVar2 / fVar1;
  fVar2 = (float)VectorUnsignedToFloat((uint)(byte)param_1[3],(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(this + 0xc) = fVar2 / fVar1;
  return;
}
