/*
 * mangled: _Z13PointTriangle7tVectorS_S_S_
 * demangled: PointTriangle(tVector, tVector, tVector, tVector)
 * address: 0004c13c
 * size: 312
 */

/* PointTriangle(tVector, tVector, tVector, tVector) */

bool PointTriangle(float param_1,undefined4 param_2,float param_3,float param_4,undefined4 param_5,
                  float param_6,float param_7,undefined4 param_8,float param_9,float param_10,
                  undefined4 param_11,float param_12)

{
  float fVar1;

  param_7 = param_7 - param_4;
  param_9 = param_9 - param_6;
  fVar1 = (((param_1 * param_9 - param_3 * param_7) - param_4 * param_9) + param_6 * param_7) /
          (param_9 * (param_10 - param_4) - param_7 * (param_12 - param_6));
  if ((0.0 <= fVar1) && (fVar1 <= 1.0)) {
    if (param_9 == 0.0) {
      param_7 = ((param_1 - param_4) - fVar1 * (param_10 - param_4)) / param_7;
    }
    else {
      param_7 = ((param_3 - param_6) - fVar1 * (param_12 - param_6)) / param_9;
    }
    if (0.0 <= param_7) {
      return param_7 <= 1.0 - fVar1;
    }
  }
  return false;
}
