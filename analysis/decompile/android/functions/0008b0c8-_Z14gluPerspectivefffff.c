/*
 * mangled: _Z14gluPerspectivefffff
 * demangled: gluPerspective(float, float, float, float, float)
 * address: 0008b0c8
 * size: 132
 */

/* gluPerspective(float, float, float, float, float) */

void gluPerspective(float param_1,float param_2,float param_3,float param_4,float param_5)

{
  float extraout_r0;
  float in_r1;
  float in_r2;
  float fVar1;
  float in_stack_00000000;

  tanf(param_1);
  fVar1 = extraout_r0 * in_r2;
  glFrustumf(-fVar1 * in_r1,fVar1 * in_r1,-fVar1 + in_stack_00000000 * 0.05,
             in_stack_00000000 * 0.05 + fVar1);
  return;
}
