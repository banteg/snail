/*
 * mangled: _ZN8cRBorder5ScaleEf
 * demangled: cRBorder::Scale(float)
 * address: 000385d4
 * size: 56
 */

/* cRBorder::Scale(float) */

void __thiscall cRBorder::Scale(cRBorder *this,float param_1)

{
  *(float *)(this + 0x23c) = *(float *)(this + 0x23c) * param_1;
  *(float *)(this + 0x240) = *(float *)(this + 0x240) * param_1;
  *(float *)(this + 0x248) = *(float *)(this + 0x248) * param_1;
  *(float *)(this + 0x24c) = *(float *)(this + 0x24c) * param_1;
  return;
}
