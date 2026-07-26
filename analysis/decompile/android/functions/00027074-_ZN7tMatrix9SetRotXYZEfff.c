/*
 * mangled: _ZN7tMatrix9SetRotXYZEfff
 * demangled: tMatrix::SetRotXYZ(float, float, float)
 * address: 00027074
 * size: 200
 */

/* tMatrix::SetRotXYZ(float, float, float) */

void tMatrix::SetRotXYZ(float param_1,float param_2,float param_3)

{
  float *in_r0;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;

  fVar1 = (float)Cos(param_1);
  fVar2 = (float)Sin(extraout_s0);
  fVar3 = (float)Cos(extraout_s0_00);
  fVar4 = (float)Sin(extraout_s0_01);
  fVar5 = (float)Cos(extraout_s0_02);
  fVar6 = (float)Sin(extraout_s0_03);
  in_r0[10] = fVar5;
  *in_r0 = fVar1 * fVar3 - fVar2 * fVar4 * fVar5;
  in_r0[1] = fVar4 * -fVar1 - fVar2 * fVar3 * fVar5;
  in_r0[4] = fVar1 * fVar4 * fVar5 + fVar2 * fVar3;
  in_r0[5] = fVar1 * fVar3 * fVar5 - fVar2 * fVar4;
  in_r0[9] = fVar3 * fVar6;
  in_r0[6] = fVar6 * -fVar1;
  in_r0[8] = fVar4 * fVar6;
  in_r0[2] = fVar2 * fVar6;
  return;
}
