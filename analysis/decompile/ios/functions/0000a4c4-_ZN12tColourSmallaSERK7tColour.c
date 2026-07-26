/*
 * mangled: _ZN12tColourSmallaSERK7tColour
 * demangled: tColourSmall::operator=(tColour const&)
 * address: 0000a4c4
 * size: 88
 */

/* tColourSmall::TEMPNAMEPLACEHOLDERVALUE(tColour const&) */

void __thiscall tColourSmall::operator=(tColourSmall *this,tColour *param_1)

{
  this[2] = SUB41((int)(*(float *)param_1 * 255.0),0);
  this[1] = SUB41((int)(*(float *)(param_1 + 4) * 255.0),0);
  *this = SUB41((int)(*(float *)(param_1 + 8) * 255.0),0);
  this[3] = SUB41((int)(*(float *)(param_1 + 0xc) * 255.0),0);
  return;
}
