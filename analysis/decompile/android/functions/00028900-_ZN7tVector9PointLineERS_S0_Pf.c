/*
 * mangled: _ZN7tVector9PointLineERS_S0_Pf
 * demangled: tVector::PointLine(tVector&, tVector&, float*)
 * address: 00028900
 * size: 280
 */

/* tVector::PointLine(tVector&, tVector&, float*) */

undefined4 __thiscall
tVector::PointLine(tVector *this,tVector *param_1,tVector *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  float fVar5;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;

  local_20 = *(float *)(param_2 + 4) - *(float *)(param_1 + 4);
  fVar5 = local_20 * local_20;
  local_24 = *(float *)param_2 - *(float *)param_1;
  fVar1 = local_24 * local_24;
  local_30 = *(float *)this - *(float *)param_1;
  local_28 = *(float *)(this + 8) - *(float *)(param_1 + 8);
  local_1c = *(float *)(param_2 + 8) - *(float *)(param_1 + 8);
  local_2c = *(float *)(this + 4) - *(float *)(param_1 + 4);
  fVar2 = local_1c * local_1c;
  fVar3 = (float)Dot((tVector *)&local_24,(tVector *)&local_30);
  fVar3 = fVar3 / (fVar5 + fVar1 + fVar2);
  *param_3 = fVar3;
  if ((0.0 <= fVar3) && (fVar3 <= 1.0)) {
    local_3c = *(float *)this - (*(float *)param_1 + fVar3 * local_24);
    local_38 = *(float *)(this + 4) - (*(float *)(param_1 + 4) + fVar3 * local_20);
    local_34 = *(float *)(this + 8) - (*(float *)(param_1 + 8) + fVar3 * local_1c);
    uVar4 = Magnitude((tVector *)&local_3c);
    return uVar4;
  }
  return 0xbf800000;
}
