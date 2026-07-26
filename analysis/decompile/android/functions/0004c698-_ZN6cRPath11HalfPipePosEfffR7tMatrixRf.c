/*
 * mangled: _ZN6cRPath11HalfPipePosEfffR7tMatrixRf
 * demangled: cRPath::HalfPipePos(float, float, float, tMatrix&, float&)
 * address: 0004c698
 * size: 164
 */

/* cRPath::HalfPipePos(float, float, float, tMatrix&, float&) */

void cRPath::HalfPipePos(float param_1,float param_2,float param_3,tMatrix *param_4,float *param_5)

{
  float fVar1;
  float in_r2;
  float in_r3;
  float extraout_s0;
  undefined8 uVar2;
  tMatrix *in_stack_00000000;
  float *in_stack_00000004;

  uVar2 = Sqrt(param_1);
  fVar1 = (float)ATan((float)uVar2,(float)((ulonglong)uVar2 >> 0x20));
  *in_stack_00000004 = fVar1 * in_r2 * 0.25;
  fVar1 = (float)tMatrix::RotIdentity(in_stack_00000000);
  fVar1 = (float)tMatrix::RotLocalZ(in_stack_00000000,fVar1);
  fVar1 = (float)Sin(fVar1);
  *(float *)(in_stack_00000000 + 0x30) = ((float)param_5 - in_r3) * fVar1;
  fVar1 = (float)Cos(extraout_s0);
  *(float *)(in_stack_00000000 + 0x34) = (float)param_5 - ((float)param_5 - in_r3) * fVar1;
  *in_stack_00000004 = -*in_stack_00000004;
  return;
}
