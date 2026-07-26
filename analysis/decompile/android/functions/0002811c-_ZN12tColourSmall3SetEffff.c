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
  float in_stack_00000000;

  this[2] = (tColourSmall)((0.0 < in_r1 * 255.0) * (char)(int)(in_r1 * 255.0));
  this[1] = (tColourSmall)((0.0 < in_r2 * 255.0) * (char)(int)(in_r2 * 255.0));
  *this = (tColourSmall)((0.0 < in_r3 * 255.0) * (char)(int)(in_r3 * 255.0));
  this[3] = (tColourSmall)
            ((0.0 < in_stack_00000000 * 255.0) * (char)(int)(in_stack_00000000 * 255.0));
  return;
}
