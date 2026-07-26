/*
 * mangled: _ZN16cRTwinkleManager4InitEP8cRBorder
 * demangled: cRTwinkleManager::Init(cRBorder*)
 * address: 0005cb74
 * size: 160
 */

/* cRTwinkleManager::Init(cRBorder*) */

void __thiscall cRTwinkleManager::Init(cRTwinkleManager *this,cRBorder *param_1)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  cRTwinkleManager *pcVar4;
  int iVar5;
  uint in_fpscr;
  int iVar6;
  float fVar7;

  iVar6 = (int)(*(float *)(param_1 + 0x23c) * *(float *)(param_1 + 0x240) * DAT_0005cc14);
  if (iVar6 < 1) {
    iVar6 = 1;
  }
  else if (4 < iVar6) {
    iVar6 = 5;
  }
  iVar5 = 0;
  *(int *)(this + 0xf4) = iVar6;
  fVar1 = DAT_0005cc18;
  *(undefined4 *)(this + 0xf0) = 1;
  uVar2 = DAT_0005cc1c;
  pcVar4 = this;
  do {
    *(undefined4 *)pcVar4 = 1;
    iVar5 = iVar5 + 1;
    uVar3 = gRMathRand2();
    iVar6 = *(int *)(this + 0xf4);
    *(undefined4 *)(pcVar4 + 0xc) = uVar2;
    *(cRBorder **)(pcVar4 + 0x2c) = param_1;
    fVar7 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(pcVar4 + 8) = fVar7 * fVar1;
    pcVar4 = pcVar4 + 0x30;
  } while (iVar5 < iVar6);
  return;
}
