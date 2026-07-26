/*
 * mangled: _ZN12tColourSmall3SetEffff
 * demangled: tColourSmall::Set(float, float, float, float)
 * address: 0002811c
 * size: 88
 */

/* tColourSmall::Set(float, float, float, float) */

void __thiscall
tColourSmall::Set(tColourSmall *this,float param_1,float param_2,float param_3,float param_4)

{
  float in_r1;
  float in_r2;
  float in_r3;
  float fVar1;
  float fVar2;
  float fVar3;
  float in_stack_00000000;

  fVar2 = in_stack_00000000 * DAT_00028174;
  fVar1 = in_r2 * DAT_00028174;
  fVar3 = in_r3 * DAT_00028174;
  this[2] = (tColourSmall)((0.0 < in_r1 * DAT_00028174) * (char)(int)(in_r1 * DAT_00028174));
  this[1] = (tColourSmall)((0.0 < fVar1) * (char)(int)fVar1);
  *this = (tColourSmall)((0.0 < fVar3) * (char)(int)fVar3);
  this[3] = (tColourSmall)((0.0 < fVar2) * (char)(int)fVar2);
  return;
}
