/*
 * mangled: _ZN8cRBorder7SetSameEPS_
 * demangled: cRBorder::SetSame(cRBorder*)
 * address: 0005e540
 * size: 56
 */

/* cRBorder::SetSame(cRBorder*) */

void __thiscall cRBorder::SetSame(cRBorder *this,cRBorder *param_1)

{
  float fVar1;
  float fVar2;

  fVar2 = *(float *)(param_1 + 0x240);
  fVar1 = *(float *)(param_1 + 0x6f0);
  *(undefined4 *)(this + 0x6ec) = *(undefined4 *)(param_1 + 0x6ec);
  *(float *)(this + 0x6f0) = fVar1 + fVar2 + *(float *)(this + 0x264);
  RePosition(this);
  return;
}
