/*
 * mangled: _ZN9cRSubGame13BlinkRandInitEv
 * demangled: cRSubGame::BlinkRandInit()
 * address: 00071f4c
 * size: 164
 */

/* cRSubGame::BlinkRandInit() */

void __thiscall cRSubGame::BlinkRandInit(cRSubGame *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;

  fVar2 = DAT_00071ff4;
  fVar1 = DAT_00071ff0;
  *(undefined4 *)(this + 0xfa60) = 0;
  fVar3 = DAT_00071ff8;
  iVar5 = 0;
  do {
    while( true ) {
      uVar4 = gRMathRand2();
      fVar7 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar2 + fVar7 * fVar1 == DAT_00071ffc) << 0x1e;
      if (!SUB41(in_fpscr >> 0x1e,0)) break;
      iVar6 = iVar5 + 4;
      *(float *)(this + iVar5 + 0xfa64) = DAT_00071ffc;
      iVar5 = iVar6;
      if (iVar6 == 0x60) {
        return;
      }
    }
    uVar4 = gRMathRand2();
    iVar6 = iVar5 + 4;
    fVar7 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + iVar5 + 0xfa64) = fVar2 / ((fVar2 + fVar7 * fVar1) * fVar3);
    iVar5 = iVar6;
  } while (iVar6 != 0x60);
  return;
}
