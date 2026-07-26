/*
 * mangled: _Z9RMathInitv
 * demangled: RMathInit()
 * address: 00029698
 * size: 172
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RMathInit() */

void RMathInit(void)

{
  undefined4 extraout_r0;
  undefined4 extraout_r0_00;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  int iVar1;
  int iVar2;
  uint in_fpscr;
  double in_d0;
  double dVar3;
  double dVar4;

  iVar1 = 0;
  iVar2 = 0;
  dVar3 = 0.0;
  dVar4 = 1.0;
  while( true ) {
    iVar2 = iVar2 + 1;
    *(float *)(RMathSin + iVar1) = (float)dVar3;
    *(float *)(RMathCos + iVar1) = (float)dVar4;
    iVar1 = iVar1 + 4;
    if (iVar2 == 0x8000) break;
    VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    dVar3 = cos(in_d0);
    dVar4 = (double)CONCAT44(extraout_r1,extraout_r0);
    in_d0 = sin(dVar3);
    dVar3 = (double)CONCAT44(extraout_r1_00,extraout_r0_00);
  }
  gRMathRand2Init();
  tColour::White();
  return;
}
