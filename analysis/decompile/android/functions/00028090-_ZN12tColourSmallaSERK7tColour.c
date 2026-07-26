/*
 * mangled: _ZN12tColourSmallaSERK7tColour
 * demangled: tColourSmall::operator=(tColour const&)
 * address: 00028090
 * size: 88
 */

/* tColourSmall::TEMPNAMEPLACEHOLDERVALUE(tColour const&) */

void __thiscall tColourSmall::operator=(tColourSmall *this,tColour *param_1)

{
  float fVar1;

  fVar1 = DAT_000280e8;
  this[2] = SUB41((int)(DAT_000280e8 * *(float *)param_1),0);
  this[1] = SUB41((int)(fVar1 * *(float *)(param_1 + 4)),0);
  *this = SUB41((int)(fVar1 * *(float *)(param_1 + 8)),0);
  this[3] = SUB41((int)(fVar1 * *(float *)(param_1 + 0xc)),0);
  return;
}
