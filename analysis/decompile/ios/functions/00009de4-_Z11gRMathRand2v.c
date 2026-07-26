/*
 * mangled: _Z11gRMathRand2v
 * demangled: gRMathRand2()
 * address: 00009de4
 * size: 60
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* gRMathRand2() */

undefined4 gRMathRand2(void)

{
  _gRMathRand2Index = (_gRMathRand2Index + 1) % 0x1fff;
  return (&_gRMathRand2Table)[_gRMathRand2Index];
}
