/*
 * mangled: _Z3Powff
 * demangled: Pow(float, float)
 * address: 00028f60
 * size: 48
 */

/* Pow(float, float) */

float Pow(float param_1,float param_2)

{
  undefined4 extraout_r0;
  undefined4 extraout_r1;
  double in_d1;

  pow((double)CONCAT44(param_2,param_1),in_d1);
  return (float)(double)CONCAT44(extraout_r1,extraout_r0);
}
