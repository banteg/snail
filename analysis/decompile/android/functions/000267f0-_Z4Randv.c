/*
 * mangled: _Z4Randv
 * demangled: Rand()
 * address: 000267f0
 * size: 96
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* Rand() */

ushort Rand(void)

{
  uint uVar1;

  uVar1 = gRMathRandIndex + 1 & 0xffff;
  uVar1 = uVar1 + (uVar1 / 0x1fff + (uVar1 - uVar1 / 0x1fff >> 1) >> 0xc) * -0x1fff;
  gRMathRandIndex = (short)uVar1;
  return *(ushort *)(gRMathRand2Table + (uVar1 & 0xffff) * 2) & 0x7fff;
}
