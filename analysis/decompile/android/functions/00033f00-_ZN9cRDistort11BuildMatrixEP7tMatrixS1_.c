/*
 * mangled: _ZN9cRDistort11BuildMatrixEP7tMatrixS1_
 * demangled: cRDistort::BuildMatrix(tMatrix*, tMatrix*)
 * address: 00033f00
 * size: 396
 */

/* cRDistort::BuildMatrix(tMatrix*, tMatrix*) */

void cRDistort::BuildMatrix(tMatrix *param_1,tMatrix *param_2)

{
  float fVar1;
  float *in_r2;
  float fVar2;
  float fVar3;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;

  fVar1 = *(float *)(param_2 + 4);
  fVar2 = *(float *)(param_2 + 8);
  fVar3 = *(float *)(param_2 + 0xc);
  *in_r2 = *(float *)param_2;
  in_r2[1] = fVar1;
  in_r2[2] = fVar2;
  in_r2[3] = fVar3;
  fVar1 = *(float *)(param_2 + 0x14);
  fVar2 = *(float *)(param_2 + 0x18);
  fVar3 = *(float *)(param_2 + 0x1c);
  in_r2[4] = *(float *)(param_2 + 0x10);
  in_r2[5] = fVar1;
  in_r2[6] = fVar2;
  in_r2[7] = fVar3;
  fVar1 = *(float *)(param_2 + 0x24);
  fVar2 = *(float *)(param_2 + 0x28);
  fVar3 = *(float *)(param_2 + 0x2c);
  in_r2[8] = *(float *)(param_2 + 0x20);
  in_r2[9] = fVar1;
  in_r2[10] = fVar2;
  in_r2[0xb] = fVar3;
  fVar1 = *(float *)(param_2 + 0x34);
  fVar2 = *(float *)(param_2 + 0x38);
  fVar3 = *(float *)(param_2 + 0x3c);
  in_r2[0xc] = *(float *)(param_2 + 0x30);
  in_r2[0xd] = fVar1;
  in_r2[0xe] = fVar2;
  in_r2[0xf] = fVar3;
  if (*(float *)(param_1 + 4) != 0.0) {
    fVar1 = (float)Sin(in_s0);
    fVar1 = fVar1 + 1.0;
    fVar2 = (float)Sin(extraout_s0_00);
    in_r2[2] = in_r2[2] * fVar1;
    *in_r2 = *in_r2 * fVar1;
    fVar2 = 1.0 - fVar2;
    in_r2[1] = in_r2[1] * fVar1;
    in_r2[6] = in_r2[6] * fVar2;
    in_r2[4] = in_r2[4] * fVar2;
    in_r2[5] = in_r2[5] * fVar2;
    in_s0 = extraout_s0_01;
  }
  if (*(float *)(param_1 + 8) != 0.0) {
    fVar1 = (float)Sin(in_s0);
    fVar2 = fVar1 * 0.1 + 1.0;
    fVar1 = (float)Sin(extraout_s0);
    in_r2[6] = in_r2[6] * fVar2;
    *in_r2 = *in_r2 * fVar2;
    fVar1 = 1.0 - fVar1;
    in_r2[1] = in_r2[1] * fVar2;
    in_r2[10] = in_r2[10] * fVar1;
    in_r2[2] = in_r2[2] * fVar2;
    in_r2[4] = in_r2[4] * fVar2;
    in_r2[5] = in_r2[5] * fVar2;
    in_r2[8] = in_r2[8] * fVar1;
    in_r2[9] = in_r2[9] * fVar1;
  }
  return;
}
