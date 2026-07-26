/*
 * mangled: _ZN6cRPath11HalfPipePosEfffR7tMatrixRf
 * demangled: cRPath::HalfPipePos(float, float, float, tMatrix&, float&)
 * address: 0004ded8
 * size: 172
 */

/* cRPath::HalfPipePos(float, float, float, tMatrix&, float&) */

void __thiscall
cRPath::HalfPipePos(cRPath *this,float param_1,float param_2,float param_3,tMatrix *param_4,
                   float *param_5)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)Sqrt(param_1 * param_1 - 16.0);
  fVar1 = (float)ATan(4.0,fVar1);
  fVar2 = param_1 - param_3;
  *param_5 = fVar1 * param_2 * 0.25;
  tMatrix::RotIdentity(param_4);
  tMatrix::RotLocalZ(param_4,*param_5);
  fVar1 = (float)Sin(*param_5);
  *(float *)(param_4 + 0x30) = fVar2 * fVar1;
  fVar1 = (float)Cos(*param_5);
  *(float *)(param_4 + 0x34) = param_1 - fVar2 * fVar1;
  *param_5 = -*param_5;
  return;
}
