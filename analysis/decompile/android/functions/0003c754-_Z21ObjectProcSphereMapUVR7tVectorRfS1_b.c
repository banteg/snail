/*
 * mangled: _Z21ObjectProcSphereMapUVR7tVectorRfS1_b
 * demangled: ObjectProcSphereMapUV(tVector&, float&, float&, bool)
 * address: 0003c754
 * size: 144
 */

/* ObjectProcSphereMapUV(tVector&, float&, float&, bool) */

void ObjectProcSphereMapUV(tVector *param_1,float *param_2,float *param_3,bool param_4)

{
  float fVar1;
  float in_s0;

  if (!param_4) {
    return;
  }
  *param_2 = (*param_2 - 0.5) + (*param_2 - 0.5);
  *param_3 = (*param_3 - 0.5) + (*param_3 - 0.5);
  fVar1 = (float)ACos(in_s0);
  fVar1 = (fVar1 + fVar1) / 3.1415927;
  *param_2 = fVar1 * *(float *)param_1 * 0.5 + 0.5;
  *param_3 = fVar1 * *(float *)(param_1 + 4) * 0.5 + 0.5;
  return;
}
