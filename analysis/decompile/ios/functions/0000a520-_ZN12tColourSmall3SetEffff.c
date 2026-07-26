/*
 * mangled: _ZN12tColourSmall3SetEffff
 * demangled: tColourSmall::Set(float, float, float, float)
 * address: 0000a520
 * size: 88
 */

/* tColourSmall::Set(float, float, float, float) */

void __thiscall
tColourSmall::Set(tColourSmall *this,float param_1,float param_2,float param_3,float param_4)

{
  undefined4 uVar1;

  uVar1 = VectorFloatToUnsigned(param_1 * 255.0,3);
  this[2] = SUB41(uVar1,0);
  uVar1 = VectorFloatToUnsigned(param_2 * 255.0,3);
  this[1] = SUB41(uVar1,0);
  uVar1 = VectorFloatToUnsigned(param_3 * 255.0,3);
  *this = SUB41(uVar1,0);
  uVar1 = VectorFloatToUnsigned(param_4 * 255.0,3);
  this[3] = SUB41(uVar1,0);
  return;
}
