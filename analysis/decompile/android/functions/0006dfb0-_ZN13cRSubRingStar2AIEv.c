/*
 * mangled: _ZN13cRSubRingStar2AIEv
 * demangled: cRSubRingStar::AI()
 * address: 0006dfb0
 * size: 188
 */

/* cRSubRingStar::AI() */

void cRSubRingStar::AI(void)

{
  cRSubRingStar *in_r0;
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float in_s0;
  float extraout_s0;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  iVar4 = *(int *)(in_r0 + 4);
  fVar9 = *(float *)(in_r0 + 0x1c);
  iVar5 = *(int *)in_r0;
  if (*(int *)(iVar4 + 0x7c) == 3) {
    fVar7 = *(float *)(in_r0 + 0x14);
  }
  else {
    fVar7 = *(float *)(in_r0 + 0x14) + *(float *)(in_r0 + 0x18);
    *(float *)(in_r0 + 0x14) = fVar7;
  }
  if (6.2831855 < fVar7) {
    *(float *)(in_r0 + 0x14) = fVar7 - 6.2831855;
  }
  fVar7 = (float)Sin(in_s0);
  fVar10 = *(float *)(in_r0 + 0x1c);
  fVar1 = (float)Cos(extraout_s0);
  fVar6 = *(float *)(iVar4 + 100);
  fVar8 = *(float *)(iVar4 + 0x60);
  iVar3 = *(int *)(in_r0 + 4);
  iVar2 = *(int *)(iVar3 + 0x19c);
  *(float *)(iVar5 + 0x48) = fVar9 * fVar7 + *(float *)(iVar4 + 0x5c);
  *(float *)(iVar5 + 0x50) = fVar6 + 0.0;
  *(float *)(iVar5 + 0x4c) = fVar8 + fVar10 * fVar1;
  if (iVar2 != 0) {
    return;
  }
  Shower(in_r0,*(cRSubGoldy **)(iVar3 + 0x78));
  return;
}
