/*
 * mangled: _ZN7tMatrixC1ERK7tVectorf
 * demangled: tMatrix::tMatrix(tVector const&, float)
 * address: 00028c74
 * size: 276
 */

/* tMatrix::tMatrix(tVector const&, float) */

tMatrix * __thiscall tMatrix::tMatrix(tMatrix *this,tVector *param_1,float param_2)

{
  float in_r2;
  float fVar1;
  tVector atStack_38 [12];
  float local_2c;
  undefined4 local_28;
  float local_24;

  *(undefined4 *)(this + 0xc) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(undefined4 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x34) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0x3f800000;
  tVector::Normalize(atStack_38,param_1);
  *(undefined4 *)(this + 0x20) = *(undefined4 *)param_1;
  local_24 = *(float *)param_1;
  *(undefined4 *)(this + 0x24) = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(this + 0x28) = *(undefined4 *)(param_1 + 8);
  if (local_24 == 0.0) {
    local_2c = *(float *)(param_1 + 8);
    if (local_2c == 0.0) {
      local_2c = 1.0;
      local_24 = 0.0;
      goto LAB_00028cfc;
    }
  }
  else {
    local_2c = *(float *)(param_1 + 8);
  }
  local_2c = -local_2c;
LAB_00028cfc:
  local_28 = 0;
  tVector::Normalize((tVector *)&local_2c);
  *(float *)this = local_2c;
  *(undefined4 *)(this + 4) = local_28;
  *(float *)(this + 8) = local_24;
  fVar1 = (float)tVector::Cross((tVector *)&local_2c,param_1,(tVector *)&local_2c);
  *(float *)(this + 0x10) = local_2c;
  *(undefined4 *)(this + 0x14) = local_28;
  *(float *)(this + 0x18) = local_24;
  if (in_r2 != 0.0) {
    RotLocalZ(this,fVar1);
  }
  return this;
}
