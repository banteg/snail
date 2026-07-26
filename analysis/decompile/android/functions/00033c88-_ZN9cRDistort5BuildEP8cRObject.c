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
  float fVar3;
  float *pfVar4;
  int in_r1;
  int iVar5;
  int iVar6;
  float *unaff_r5;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  fVar2 = DAT_00033ef4;
  fVar12 = *(float *)param_1;
  pfVar9 = *(float **)(in_r1 + 0xa4);
  if (fVar12 == 0.0) {
    bVar1 = false;
    pfVar7 = pfVar9;
  }
  else {
    if (*(int *)(in_r1 + 0xa0) < 1) {
      pfVar7 = *(float **)(in_r1 + 0xa8);
    }
    else {
      unaff_r5 = (float *)0x0;
      pfVar7 = *(float **)(in_r1 + 0xa8);
      iVar8 = 0;
      pfVar4 = pfVar9;
      while( true ) {
        fVar13 = (float)((undefined4 *)((int)pfVar9 + (int)unaff_r5))[1];
        *(undefined4 *)((int)pfVar7 + (int)unaff_r5) = *(undefined4 *)((int)pfVar9 + (int)unaff_r5);
        iVar8 = iVar8 + 1;
        fVar3 = (float)Sin(in_s0);
        iVar5 = *(int *)(in_r1 + 0xa0);
        fVar10 = pfVar4[2];
        pfVar4 = pfVar4 + 3;
        *(float *)((int)pfVar7 + (int)unaff_r5 + 4) = fVar13 + fVar12 * (fVar3 + fVar2);
        pfVar7 = *(float **)(in_r1 + 0xa8);
        iVar6 = (int)pfVar7 + (int)unaff_r5;
        unaff_r5 = unaff_r5 + 3;
        *(float *)(iVar6 + 8) = fVar10;
        in_s0 = extraout_s0;
        if (iVar5 <= iVar8) break;
        fVar12 = *(float *)param_1;
      }
    }
    bVar1 = true;
  }
  fVar2 = DAT_00033ef4;
  if (*(float *)(param_1 + 4) != 0.0) {
    fVar3 = (float)Sin(in_s0);
    fVar10 = (float)Sin(extraout_s0_01);
    fVar12 = DAT_00033efc;
    iVar8 = *(int *)(in_r1 + 0xa0);
    if (iVar8 < 1) {
      unaff_r5 = *(float **)(in_r1 + 0xa8);
    }
    if (0 < iVar8) {
      unaff_r5 = *(float **)(in_r1 + 0xa8);
      iVar5 = 0;
      pfVar9 = unaff_r5;
      do {
        fVar13 = pfVar7[1];
        iVar5 = iVar5 + 1;
        pfVar9[2] = pfVar7[2];
        fVar11 = *pfVar7;
        pfVar7 = pfVar7 + 3;
        pfVar9[1] = fVar12 + (fVar2 - fVar10) * fVar13;
        *pfVar9 = fVar11 * (fVar3 + fVar2);
        pfVar9 = pfVar9 + 3;
      } while (iVar5 != iVar8);
    }
    bVar1 = true;
    pfVar7 = unaff_r5;
    in_s0 = extraout_s0_02;
  }
  fVar12 = DAT_00033ef8;
  fVar2 = DAT_00033ef4;
  if (*(float *)(param_1 + 8) == 0.0) {
    if (!bVar1) {
      return;
    }
  }
  else {
    fVar3 = (float)Sin(in_s0);
    fVar3 = fVar2 + fVar3 * fVar12;
    fVar12 = (float)Sin(extraout_s0_00);
    iVar8 = *(int *)(in_r1 + 0xa0);
    if (0 < iVar8) {
      pfVar4 = *(float **)(in_r1 + 0xa8);
      iVar5 = 0;
      pfVar9 = pfVar4;
      do {
        fVar13 = *pfVar7;
        fVar10 = pfVar7[1];
        fVar11 = pfVar7[2];
        iVar5 = iVar5 + 1;
        pfVar7 = pfVar7 + 3;
        *pfVar9 = fVar13 * fVar3;
        pfVar9[1] = fVar10 * fVar3;
        pfVar9[2] = fVar11 * (fVar2 - fVar12);
        pfVar9 = pfVar9 + 3;
      } while (iVar5 != iVar8);
      *(float **)(in_r1 + 0xa4) = pfVar4;
      return;
    }
  }
  *(undefined4 *)(in_r1 + 0xa4) = *(undefined4 *)(in_r1 + 0xa8);
  return;
}
