/*
 * mangled: _ZN7tMatrix5ScaleEf
 * demangled: tMatrix::Scale(float)
 * address: 0000a3f8
 * size: 116
 */

/* tMatrix::Scale(float) */

void __thiscall tMatrix::Scale(tMatrix *this,float param_1)

{
  *(float *)this = *(float *)this * param_1;
  *(float *)(this + 4) = *(float *)(this + 4) * param_1;
  *(float *)(this + 8) = *(float *)(this + 8) * param_1;
  *(float *)(this + 0x10) = *(float *)(this + 0x10) * param_1;
  *(float *)(this + 0x14) = *(float *)(this + 0x14) * param_1;
  *(float *)(this + 0x18) = *(float *)(this + 0x18) * param_1;
  *(float *)(this + 0x20) = *(float *)(this + 0x20) * param_1;
  *(float *)(this + 0x24) = *(float *)(this + 0x24) * param_1;
  *(float *)(this + 0x28) = *(float *)(this + 0x28) * param_1;
  return;
}
