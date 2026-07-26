/*
 * mangled: _Z3Expf
 * demangled: Exp(float)
 * address: 00028f90
 * size: 36
 */

/* Exp(float) */

float Exp(float param_1)

{
  undefined4 extraout_r0;
  undefined4 extraout_r1;
  undefined4 in_s1;

  exp((double)CONCAT44(in_s1,param_1));
  return (float)(double)CONCAT44(extraout_r1,extraout_r0);
}
