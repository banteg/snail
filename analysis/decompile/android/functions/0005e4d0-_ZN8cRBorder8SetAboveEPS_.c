/*
 * mangled: _ZN8cRBorder8SetAboveEPS_
 * demangled: cRBorder::SetAbove(cRBorder*)
 * address: 0005e4d0
 * size: 56
 */

/* cRBorder::SetAbove(cRBorder*) */

void __thiscall cRBorder::SetAbove(cRBorder *this,cRBorder *param_1)

{
  float fVar1;
  float fVar2;

  fVar2 = *(float *)(param_1 + 0x240);
  fVar1 = *(float *)(param_1 + 0x6f0);
  *(undefined4 *)(this + 0x6ec) = *(undefined4 *)(param_1 + 0x6ec);
  *(float *)(this + 0x6f0) = (fVar1 - fVar2) - *(float *)(this + 0x264);
  RePosition(this);
  return;
}
