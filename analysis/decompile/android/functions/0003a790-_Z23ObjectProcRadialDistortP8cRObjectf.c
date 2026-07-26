/*
 * mangled: _Z23ObjectProcRadialDistortP8cRObjectf
 * demangled: ObjectProcRadialDistort(cRObject*, float)
 * address: 0003a790
 * size: 200
 */

/* ObjectProcRadialDistort(cRObject*, float) */

float ObjectProcRadialDistort(cRObject *param_1,float param_2)

{
  float fVar1;
  float fVar2;
  char *in_r1;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float fVar10;
  float fVar11;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  if (0 < *(int *)(param_1 + 0xa0)) {
    iVar6 = 0;
    iVar7 = 0;
    do {
      iVar7 = iVar7 + 1;
      puVar5 = (undefined4 *)(*(int *)(param_1 + 0xa4) + iVar6);
      local_34 = *puVar5;
      uStack_30 = puVar5[1];
      uStack_2c = puVar5[2];
      fVar9 = (float)tVector::Normalize((tVector *)&local_34);
      iVar8 = *(int *)(param_1 + 0xa4);
      fVar9 = (float)SRAND(fVar9,in_r1);
      fVar1 = (float)SRAND(extraout_s0,in_r1);
      fVar2 = (float)SRAND(extraout_s0_00,in_r1);
      pfVar3 = (float *)(iVar8 + iVar6);
      fVar10 = pfVar3[1];
      fVar11 = pfVar3[2];
      iVar4 = *(int *)(param_1 + 0xa0);
      *(float *)(iVar8 + iVar6) = *pfVar3 + fVar9;
      iVar6 = iVar6 + 0xc;
      pfVar3[1] = fVar10 + fVar1;
      pfVar3[2] = fVar11 + fVar2;
      param_2 = extraout_s0_01;
    } while (iVar7 < iVar4);
  }
  return param_2;
}
