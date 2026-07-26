/*
 * mangled: _ZN12tColourSmall5AlphaEf
 * demangled: tColourSmall::Alpha(float)
 * address: 0000a57c
 * size: 28
 */

/* tColourSmall::Alpha(float) */

void __thiscall tColourSmall::Alpha(tColourSmall *this,float param_1)

{
  this[3] = SUB41((int)(param_1 * 255.0),0);
  return;
}
