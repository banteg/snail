/*
 * mangled: _ZN16cRTwinkleManager4InitEP8cRBorder
 * demangled: cRTwinkleManager::Init(cRBorder*)
 * address: 0005cb74
 * size: 160
 */

/* cRTwinkleManager::Init(cRBorder*) */

void __thiscall cRTwinkleManager::Init(cRTwinkleManager *this,cRBorder *param_1)

{
  undefined4 uVar1;
  cRTwinkleManager *pcVar2;
  int iVar3;
  uint in_fpscr;
  int iVar4;
  float fVar5;

  iVar4 = (int)(*(float *)(param_1 + 0x23c) * *(float *)(param_1 + 0x240) * 0.0009765625);
  if (iVar4 < 1) {
    iVar4 = 1;
  }
  else if (4 < iVar4) {
    iVar4 = 5;
  }
  iVar3 = 0;
  *(int *)(this + 0xf4) = iVar4;
  *(undefined4 *)(this + 0xf0) = 1;
  pcVar2 = this;
  do {
    *(undefined4 *)pcVar2 = 1;
    iVar3 = iVar3 + 1;
    uVar1 = gRMathRand2();
    iVar4 = *(int *)(this + 0xf4);
    *(undefined4 *)(pcVar2 + 0xc) = 0x3c888889;
    *(cRBorder **)(pcVar2 + 0x2c) = param_1;
    fVar5 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(pcVar2 + 8) = fVar5 * 3.0517578e-05;
    pcVar2 = pcVar2 + 0x30;
  } while (iVar3 < iVar4);
  return;
}
