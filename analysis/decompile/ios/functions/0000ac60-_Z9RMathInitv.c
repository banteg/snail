/*
 * mangled: _Z9RMathInitv
 * demangled: RMathInit()
 * address: 0000ac60
 * size: 228
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RMathInit() */

void RMathInit(void)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint in_fpscr;
  float fVar5;

  iVar3 = 0;
  do {
    iVar4 = iVar3 + 1;
    fVar5 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar5 = (fVar5 * 3.0517578e-05 + fVar5 * 3.0517578e-05) * 3.1415927;
    uVar1 = _cosf(fVar5);
    (&_RMathCos)[iVar3] = uVar1;
    uVar1 = _sinf(fVar5);
    (&_RMathSin)[iVar3] = uVar1;
    iVar3 = iVar4;
  } while (iVar4 != 0x8000);
  wprintf("RAND_MAX=%i\n",0x7fffffff);
  uVar2 = _rand();
  iVar3 = 4;
  _gRMathRand2Table = uVar2 & 0x7fff;
  do {
    uVar2 = _rand();
    *(uint *)((int)&_gRMathRand2Table + iVar3) = uVar2 & 0x7fff;
    iVar3 = iVar3 + 4;
  } while (iVar3 != 0x7ffc);
  _gRMathRand2Index = 0;
  _tColWhite = 0x3f800000;
  DAT_0023a614 = 0x3f800000;
  DAT_0023a618 = 0x3f800000;
  DAT_0023a61c = 0x3f800000;
  return;
}
