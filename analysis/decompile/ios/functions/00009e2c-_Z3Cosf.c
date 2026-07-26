/*
 * mangled: _Z3Cosf
 * demangled: Cos(float)
 * address: 00009e2c
 * size: 56
 */

/* Cos(float) */

undefined4 Cos(float param_1)

{
  return (&_RMathCos)[(int)((param_1 / 6.2831855) * 32768.0) & 0x7fff];
}
