/*
 * mangled: _ZN7tMatrixplERKS_
 * demangled: tMatrix::operator+(tMatrix const&)
 * address: 0002734c
 * size: 292
 */

/* tMatrix::TEMPNAMEPLACEHOLDERVALUE(tMatrix const&) */

tMatrix * __thiscall tMatrix::operator+(tMatrix *this,tMatrix *param_1)

{
  float *in_r2;

  tMatrix(this,*(float *)(param_1 + 0x1c) + in_r2[7],*(float *)(param_1 + 0x24),
          *(float *)(param_1 + 0x20) + in_r2[8],*(float *)(param_1 + 0x28),
          *(float *)(param_1 + 0x24) + in_r2[9],*(float *)(param_1 + 0x34),
          *(float *)(param_1 + 0x3c) + in_r2[0xf],*(float *)(param_1 + 0x38),
          *(float *)(param_1 + 0x34) + in_r2[0xd],*(float *)param_1,*(float *)param_1 + *in_r2,
          *(float *)(param_1 + 0x38) + in_r2[0xe],*(float *)(param_1 + 4),
          *(float *)(param_1 + 4) + in_r2[1],*(float *)(param_1 + 8),
          *(float *)(param_1 + 8) + in_r2[2]);
  return this;
}
