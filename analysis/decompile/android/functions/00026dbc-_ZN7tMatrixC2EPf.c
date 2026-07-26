/*
 * mangled: _ZN7tMatrixC2EPf
 * demangled: tMatrix::tMatrix(float*)
 * address: 00026dbc
 * size: 60
 */

/* tMatrix::tMatrix(float*) */

tMatrix * __thiscall tMatrix::tMatrix(tMatrix *this,float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;

  fVar1 = param_1[1];
  fVar2 = param_1[2];
  fVar3 = param_1[3];
  *(float *)this = *param_1;
  *(float *)(this + 4) = fVar1;
  *(float *)(this + 8) = fVar2;
  *(float *)(this + 0xc) = fVar3;
  fVar1 = param_1[5];
  fVar2 = param_1[6];
  fVar3 = param_1[7];
  *(float *)(this + 0x10) = param_1[4];
  *(float *)(this + 0x14) = fVar1;
  *(float *)(this + 0x18) = fVar2;
  *(float *)(this + 0x1c) = fVar3;
  fVar1 = param_1[9];
  fVar2 = param_1[10];
  fVar3 = param_1[0xb];
  *(float *)(this + 0x20) = param_1[8];
  *(float *)(this + 0x24) = fVar1;
  *(float *)(this + 0x28) = fVar2;
  *(float *)(this + 0x2c) = fVar3;
  fVar1 = param_1[0xd];
  fVar2 = param_1[0xe];
  fVar3 = param_1[0xf];
  *(float *)(this + 0x30) = param_1[0xc];
  *(float *)(this + 0x34) = fVar1;
  *(float *)(this + 0x38) = fVar2;
  *(float *)(this + 0x3c) = fVar3;
  return this;
}
