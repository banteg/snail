/*
 * mangled: _ZN7tVectormLE7tMatrix
 * demangled: tVector::operator*=(tMatrix)
 * address: 00026afc
 * size: 140
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

  fVar3 = *(float *)(this + 4);
  fVar1 = *(float *)this;
  fVar2 = *(float *)(this + 8);
  *(float *)this = fVar3 * param_6 + fVar1 * param_2 + fVar2 * param_10 + param_14;
  *(float *)(this + 4) = fVar3 * param_7 + fVar1 * param_3 + fVar2 * param_11 + param_15;
  *(float *)(this + 8) = fVar3 * param_8 + fVar1 * param_4 + fVar2 * param_12 + param_16;
  return;
}
