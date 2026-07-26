/*
 * mangled: _Z11gRMathRand2v
 * demangled: gRMathRand2()
 * address: 0002678c
 * size: 88
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* gRMathRand2() */

undefined2 gRMathRand2(void)

{
  uint uVar1;

  uVar1 = gRMathRand2Index + 1 & 0xffff;
  uVar1 = uVar1 + (uVar1 / 0x1fff + (uVar1 - uVar1 / 0x1fff >> 1) >> 0xc) * -0x1fff;
  gRMathRand2Index = (short)uVar1;
  return *(undefined2 *)(gRMathRand2Table + (uVar1 & 0xffff) * 2);
}
