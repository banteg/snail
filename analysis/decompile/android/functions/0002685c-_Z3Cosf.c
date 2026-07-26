/*
 * mangled: _Z3Cosf
 * demangled: Cos(float)
 * address: 0002685c
 * size: 60
 */

/* Cos(float) */

undefined4 Cos(float param_1)

{
  float in_r0;

  return *(undefined4 *)(RMathCos + ((int)((in_r0 / 6.2831855) * 32768.0) & 0x7fffU) * 4);
}
