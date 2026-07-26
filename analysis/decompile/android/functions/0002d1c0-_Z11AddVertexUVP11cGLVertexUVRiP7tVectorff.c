/*
 * mangled: _Z11AddVertexUVP11cGLVertexUVRiP7tVectorff
 * demangled: AddVertexUV(cGLVertexUV*, int&, tVector*, float, float)
 * address: 0002d1c0
 * size: 212
 */

/* AddVertexUV(cGLVertexUV*, int&, tVector*, float, float) */

int AddVertexUV(cGLVertexUV *param_1,int *param_2,tVector *param_3,float param_4,float param_5)

{
  float in_r3;
  cGLVertexUV *pcVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float in_stack_00000000;

  iVar2 = *param_2;
  if (iVar2 < 1) {
    fVar4 = *(float *)(param_3 + 8);
    fVar6 = *(float *)param_3;
    fVar5 = *(float *)(param_3 + 4);
  }
  else {
    iVar3 = 0;
    fVar4 = *(float *)(param_3 + 8);
    fVar6 = *(float *)param_3;
    fVar5 = *(float *)(param_3 + 4);
    pcVar1 = param_1;
    do {
      if ((((*(float *)pcVar1 == fVar6) && (*(float *)(pcVar1 + 4) == fVar5)) &&
          (*(float *)(pcVar1 + 8) == fVar4)) &&
         ((*(float *)(pcVar1 + 0xc) == in_r3 && (*(float *)(pcVar1 + 0x10) == in_stack_00000000))))
      {
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      pcVar1 = pcVar1 + 0x14;
    } while (iVar3 < iVar2);
  }
  *(float *)(param_1 + iVar2 * 0x14) = fVar6;
  *param_2 = iVar2 + 1;
  *(float *)(param_1 + iVar2 * 0x14 + 0x10) = in_stack_00000000;
  *(float *)(param_1 + iVar2 * 0x14 + 4) = fVar5;
  *(float *)(param_1 + iVar2 * 0x14 + 8) = fVar4;
  *(float *)(param_1 + iVar2 * 0x14 + 0xc) = in_r3;
  return iVar2;
}
