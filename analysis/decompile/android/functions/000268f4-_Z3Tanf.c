/*
 * mangled: _Z3Tanf
 * demangled: Tan(float)
 * address: 000268f4
 * size: 80
 */

/* Tan(float) */

float Tan(float param_1)

{
  float fVar1;
  float fVar2;
  float extraout_s0;
  float extraout_s0_00;

  fVar1 = (float)Cos(param_1);
  if (fVar1 == 0.0) {
    fVar1 = 1e+06;
  }
  else {
    fVar1 = (float)Sin(extraout_s0);
    fVar2 = (float)Cos(extraout_s0_00);
    fVar1 = fVar1 / fVar2;
  }
  return fVar1;
}
