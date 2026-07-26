/*
 * mangled: _Z3Sinf
 * demangled: Sin(float)
 * address: 00009e74
 * size: 56
 */

/* Sin(float) */

undefined4 Sin(float param_1)

{
  return (&_RMathSin)[(int)((param_1 / 6.2831855) * 32768.0) & 0x7fff];
}
