/*
 * mangled: _Z3Sinf
 * demangled: Sin(float)
 * address: 000268a8
 * size: 60
 */

/* Sin(float) */

undefined4 Sin(float param_1)

{
  float in_r0;

  return *(undefined4 *)(RMathSin + ((int)((in_r0 / 6.2831855) * 32768.0) & 0x7fffU) * 4);
}
