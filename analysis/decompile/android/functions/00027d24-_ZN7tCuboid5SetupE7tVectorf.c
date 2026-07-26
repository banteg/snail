/*
 * mangled: _ZN7tCuboid5SetupE7tVectorf
 * demangled: tCuboid::Setup(tVector, float)
 * address: 00027d24
 * size: 128
 */

/* tCuboid::Setup(tVector, float) */

void tCuboid::Setup(float *param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  float fVar2;

  fVar1 = DAT_00027da8;
  fVar2 = param_5 * DAT_00027da4;
  param_1[6] = param_2;
  param_1[7] = param_3;
  param_1[8] = param_4;
  param_1[9] = param_5 * fVar1;
  param_1[3] = fVar2 + param_1[6];
  param_1[5] = fVar2 + param_1[8];
  param_1[4] = fVar2 + param_1[7];
  param_1[2] = param_1[8] - fVar2;
  param_1[1] = param_1[7] - fVar2;
  *param_1 = param_1[6] - fVar2;
  return;
}
