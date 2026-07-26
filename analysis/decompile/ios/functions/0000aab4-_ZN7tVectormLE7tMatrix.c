/*
 * mangled: _ZN7tVectormLE7tMatrix
 * demangled: tVector::operator*=(tMatrix)
 * address: 0000aab4
 * size: 136
 */

/* tVector::TEMPNAMEPLACEHOLDERVALUE(tMatrix) */

void __thiscall
tVector::operator*=(tVector *this,float param_2,float param_3,float param_4,undefined4 param_5,
                   float param_6,float param_7,float param_8,undefined4 param_9,float param_10,
                   float param_11,float param_12,undefined4 param_13,float param_14,float param_15,
                   float param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;

  fVar2 = *(float *)(this + 4);
  fVar3 = *(float *)this;
  fVar1 = *(float *)(this + 8);
  *(float *)this = fVar2 * param_6 + fVar3 * param_2 + fVar1 * param_10 + param_14;
  *(float *)(this + 4) = param_7 * fVar2 + param_3 * fVar3 + param_11 * fVar1 + param_15;
  *(float *)(this + 8) = param_8 * fVar2 + param_4 * fVar3 + param_12 * fVar1 + param_16;
  return;
}
