/*
 * mangled: _Z8RandSeedi
 * demangled: RandSeed(int)
 * address: 00029588
 * size: 64
 */

/* RandSeed(int) */

void RandSeed(int param_1)

{
  gRMathRandIndex = (short)param_1 + (short)(param_1 / 0x1fff) * -0x1fff;
  srand48(param_1);
  return;
}
