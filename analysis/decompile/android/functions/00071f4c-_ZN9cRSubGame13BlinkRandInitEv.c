/*
 * mangled: _ZN9cRSubGame13BlinkRandInitEv
 * demangled: cRSubGame::BlinkRandInit()
 * address: 00071f4c
 * size: 164
 */

/* cRSubGame::BlinkRandInit() */

void __thiscall cRSubGame::BlinkRandInit(cRSubGame *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;

  *(undefined4 *)(this + 0xfa60) = 0;
  iVar2 = 0;
  do {
    while( true ) {
      uVar1 = gRMathRand2();
      fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar4 * 3.0517578e-05 + 1.0 == 0.0) << 0x1e;
      if (!SUB41(in_fpscr >> 0x1e,0)) break;
      iVar3 = iVar2 + 4;
      *(undefined4 *)(this + iVar2 + 0xfa64) = 0;
      iVar2 = iVar3;
      if (iVar3 == 0x60) {
        return;
      }
    }
    uVar1 = gRMathRand2();
    iVar3 = iVar2 + 4;
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + iVar2 + 0xfa64) = 1.0 / ((fVar4 * 3.0517578e-05 + 1.0) * 60.0);
    iVar2 = iVar3;
  } while (iVar3 != 0x60);
  return;
}
