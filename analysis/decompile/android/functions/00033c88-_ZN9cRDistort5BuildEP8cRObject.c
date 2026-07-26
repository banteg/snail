/*
 * mangled: _ZN9cRDistort5BuildEP8cRObject
 * demangled: cRDistort::Build(cRObject*)
 * address: 00033c88
 * size: 604
 */

/* cRDistort::Build(cRObject*) */

void cRDistort::Build(cRObject *param_1)

{
  bool bVar1;
  float fVar2;
  float *pfVar3;
  int in_r1;
  int iVar4;
  int iVar5;
  float *unaff_r5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;

  fVar11 = *(float *)param_1;
  pfVar8 = *(float **)(in_r1 + 0xa4);
  if (fVar11 == 0.0) {
    bVar1 = false;
    pfVar6 = pfVar8;
  }
  else {
    if (*(int *)(in_r1 + 0xa0) < 1) {
      pfVar6 = *(float **)(in_r1 + 0xa8);
    }
    else {
      unaff_r5 = (float *)0x0;
      pfVar6 = *(float **)(in_r1 + 0xa8);
      iVar7 = 0;
      pfVar3 = pfVar8;
      while( true ) {
        fVar12 = (float)((undefined4 *)((int)pfVar8 + (int)unaff_r5))[1];
        *(undefined4 *)((int)pfVar6 + (int)unaff_r5) = *(undefined4 *)((int)pfVar8 + (int)unaff_r5);
        iVar7 = iVar7 + 1;
        fVar2 = (float)Sin(in_s0);
        iVar4 = *(int *)(in_r1 + 0xa0);
        fVar9 = pfVar3[2];
        pfVar3 = pfVar3 + 3;
        *(float *)((int)pfVar6 + (int)unaff_r5 + 4) = fVar12 + fVar11 * (fVar2 + 1.0);
        pfVar6 = *(float **)(in_r1 + 0xa8);
        iVar5 = (int)pfVar6 + (int)unaff_r5;
        unaff_r5 = unaff_r5 + 3;
        *(float *)(iVar5 + 8) = fVar9;
        in_s0 = extraout_s0;
        if (iVar4 <= iVar7) break;
        fVar11 = *(float *)param_1;
      }
    }
    bVar1 = true;
  }
  if (*(float *)(param_1 + 4) != 0.0) {
    fVar11 = (float)Sin(in_s0);
    fVar2 = (float)Sin(extraout_s0_01);
    iVar7 = *(int *)(in_r1 + 0xa0);
    if (iVar7 < 1) {
      unaff_r5 = *(float **)(in_r1 + 0xa8);
    }
    if (0 < iVar7) {
      unaff_r5 = *(float **)(in_r1 + 0xa8);
      iVar4 = 0;
      pfVar8 = unaff_r5;
      do {
        fVar9 = pfVar6[1];
        iVar4 = iVar4 + 1;
        pfVar8[2] = pfVar6[2];
        fVar12 = *pfVar6;
        pfVar6 = pfVar6 + 3;
        pfVar8[1] = (1.0 - fVar2) * fVar9 + 0.0;
        *pfVar8 = fVar12 * (fVar11 + 1.0);
        pfVar8 = pfVar8 + 3;
      } while (iVar4 != iVar7);
    }
    bVar1 = true;
    pfVar6 = unaff_r5;
    in_s0 = extraout_s0_02;
  }
  if (*(float *)(param_1 + 8) == 0.0) {
    if (!bVar1) {
      return;
    }
  }
  else {
    fVar11 = (float)Sin(in_s0);
    fVar2 = fVar11 * 0.1 + 1.0;
    fVar11 = (float)Sin(extraout_s0_00);
    iVar7 = *(int *)(in_r1 + 0xa0);
    if (0 < iVar7) {
      pfVar3 = *(float **)(in_r1 + 0xa8);
      iVar4 = 0;
      pfVar8 = pfVar3;
      do {
        fVar12 = *pfVar6;
        fVar9 = pfVar6[1];
        fVar10 = pfVar6[2];
        iVar4 = iVar4 + 1;
        pfVar6 = pfVar6 + 3;
        *pfVar8 = fVar12 * fVar2;
        pfVar8[1] = fVar9 * fVar2;
        pfVar8[2] = fVar10 * (1.0 - fVar11);
        pfVar8 = pfVar8 + 3;
      } while (iVar4 != iVar7);
      *(float **)(in_r1 + 0xa4) = pfVar3;
      return;
    }
  }
  *(undefined4 *)(in_r1 + 0xa4) = *(undefined4 *)(in_r1 + 0xa8);
  return;
}
