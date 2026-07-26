/*
 * mangled: _ZN7tVectordVE7tMatrix
 * demangled: tVector::operator/=(tMatrix)
 * address: 00026b88
 * size: 116
 */

/* tVector::TEMPNAMEPLACEHOLDERVALUE(tMatrix) */

void __thiscall
tVector::operator/=(tVector *this,float param_2,float param_3,float param_4,undefined4 param_5,
                   float param_6,float param_7,float param_8,undefined4 param_9,float param_10,
                   float param_11,float param_12)

{
  float fVar1;
  float fVar2;
  float fVar3;

  fVar3 = *(float *)(this + 4);
  fVar1 = *(float *)this;
  fVar2 = *(float *)(this + 8);
  *(float *)(this + 4) = fVar3 * param_7 + fVar1 * param_6 + fVar2 * param_8;
  *(float *)(this + 8) = fVar3 * param_11 + fVar1 * param_10 + fVar2 * param_12;
  *(float *)this = fVar3 * param_3 + fVar1 * param_2 + fVar2 * param_4;
  return;
}
