/*
 * mangled: _Z9CrossProdffffffPf
 * demangled: CrossProd(float, float, float, float, float, float, float*)
 * address: 0008a814
 * size: 68
 */

/* CrossProd(float, float, float, float, float, float, float*) */

void CrossProd(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,
              float *param_7)

{
  float in_r1;
  float in_r2;
  float in_r3;
  float in_stack_00000000;
  float in_stack_00000004;
  float *in_stack_00000008;

  in_stack_00000008[2] = (float)param_7 * in_stack_00000000 - in_r3 * in_r1;
  in_stack_00000008[1] = in_r3 * in_r2 - (float)param_7 * in_stack_00000004;
  *in_stack_00000008 = in_r1 * in_stack_00000004 - in_stack_00000000 * in_r2;
  return;
}
