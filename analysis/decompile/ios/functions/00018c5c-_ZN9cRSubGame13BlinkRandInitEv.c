/*
 * mangled: _ZN9cRSubGame13BlinkRandInitEv
 * demangled: cRSubGame::BlinkRandInit()
 * address: 00018c5c
 * size: 184
 */

/* cRSubGame::BlinkRandInit() */

void __thiscall cRSubGame::BlinkRandInit(cRSubGame *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;

  iVar3 = 0;
  *(undefined4 *)(this + 0xf3e4) = 0;
  do {
    while( true ) {
      uVar2 = gRMathRand2();
      fVar5 = 1.0;
      fVar6 = 3.0517578e-05;
      fVar4 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar4 * 3.0517578e-05 + 1.0 == 0.0) << 0x1e;
      if (!SUB41(in_fpscr >> 0x1e,0)) break;
      iVar1 = iVar3 + 0xf3e8;
      iVar3 = iVar3 + 4;
      *(undefined4 *)(this + iVar1) = 0;
      if (iVar3 == 0x60) {
        return;
      }
    }
    uVar2 = gRMathRand2();
    iVar1 = iVar3 + 0xf3e8;
    iVar3 = iVar3 + 4;
    fVar4 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + iVar1) = fVar5 / ((fVar5 + fVar4 * fVar6) * 60.0);
  } while (iVar3 != 0x60);
  return;
}
