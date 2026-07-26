/*
 * mangled: _ZN12cRSubGarbage2AIEv
 * demangled: cRSubGarbage::AI()
 * address: 000773f0
 * size: 836
 */

/* cRSubGarbage::AI() */

void cRSubGarbage::AI(void)

{
  cRSubGoldy cVar1;
  bool bVar2;
  char *pcVar3;
  cRSubGarbage *in_r0;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  cRSubGoldy *pcVar7;
  int iVar8;
  uint in_fpscr;
  uint uVar9;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  pcVar3 = DAT_00077734;
  iVar6 = *(int *)(in_r0 + 0x80);
  if (*(char *)(iVar6 + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x78)) {
  case 0:
    return;
  case 1:
    iVar8 = *(int *)(in_r0 + 0xa8);
    pcVar7 = *(cRSubGoldy **)(in_r0 + 0xb4);
    uVar4 = *(undefined4 *)(in_r0 + 0x60);
    uVar5 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar8 + 0x4c) = uVar4;
    *(undefined4 *)(iVar8 + 0x50) = uVar5;
    if (*(float *)(in_r0 + 100) < *(float *)(pcVar7 + 0x27fc)) goto LAB_000776b8;
    if (0.0 < *(float *)(pcVar7 + 0x364)) {
      *(undefined4 *)(in_r0 + 0x78) = 2;
      if (0.0 < *(float *)(in_r0 + 0x5c)) {
        *(undefined4 *)(in_r0 + 0x7c) = 1;
      }
      else {
        *(undefined4 *)(in_r0 + 0x7c) = 2;
      }
      in_s0 = (float)cRSubGoldy::ScoreAdd(pcVar7,0,0);
      iVar6 = *(int *)(in_r0 + 0x80);
    }
    cREnemyManager::Register
              ((cREnemyManager *)(gGroup0 + iVar6 + 0xc0700),(tVector *)(in_r0 + 0x5c),in_s0,
               *(int *)(in_r0 + 0x90),(cRBodPos *)0x0);
    iVar8 = *(int *)(in_r0 + 0xa8);
    pcVar7 = *(cRSubGoldy **)(in_r0 + 0xb4);
    goto LAB_000775d4;
  case 2:
    *(undefined4 *)(in_r0 + 0x78) = 3;
    fVar13 = (float)SRAND(in_s0,pcVar3);
    fVar15 = (float)RAND(extraout_s0,(char *)0x3e4ccccd);
    fVar10 = (float)RAND(extraout_s0_00,(char *)0x3e99999a);
    iVar6 = *(int *)(in_r0 + 0x80);
    fVar11 = *(float *)(iVar6 + 0x54);
    fVar13 = fVar13 * fVar11;
    *(float *)(in_r0 + 0x88) = (fVar15 + (float)pcVar3) * fVar11;
    *(float *)(in_r0 + 0x84) = fVar13;
    *(float *)(in_r0 + 0x8c) = fVar10 * fVar11;
    if (*(int *)(in_r0 + 0x7c) == 1) {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
LAB_00077700:
        fVar13 = -fVar13;
        uVar9 = uVar9 & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
        if (SUB41(uVar9 >> 0x1f,0)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
      }
      else {
        bVar2 = false;
      }
      *(float *)(in_r0 + 0x84) = fVar13;
    }
    else if (*(int *)(in_r0 + 0x7c) == 2) {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (!SUB41(uVar9 >> 0x1f,0)) goto LAB_00077700;
      bVar2 = true;
      *(float *)(in_r0 + 0x84) = fVar13;
    }
    else {
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
    }
    fVar15 = DAT_00077740;
    uVar4 = DAT_0007773c;
    fVar10 = DAT_00077738;
    if (!bVar2) {
      uVar9 = uVar9 & 0xfffffff | (uint)(fVar13 == 0.0) << 0x1e;
      fVar10 = (float)VectorSignedToFloat((uint)!SUB41(uVar9 >> 0x1e,0),(byte)(uVar9 >> 0x16) & 3);
      fVar10 = fVar10 * DAT_00077754;
    }
    fVar13 = fVar13 + fVar10 * *(float *)(iVar6 + 0x54);
    *(undefined4 *)(in_r0 + 0x98) = DAT_0007773c;
    *(float *)(in_r0 + 0x84) = fVar13;
    fVar11 = *(float *)(iVar6 + 0x54);
    *(undefined4 *)(in_r0 + 0xa0) = uVar4;
    fVar10 = DAT_00077744;
    *(float *)(in_r0 + 0x9c) = fVar11 * fVar15;
    *(float *)(in_r0 + 0xa4) = *(float *)(iVar6 + 0x54) * fVar10;
    break;
  case 3:
    fVar13 = *(float *)(in_r0 + 0x84);
    break;
  default:
    goto switchD_00077424_default;
  }
  fVar10 = *(float *)(in_r0 + 0x60);
  fVar11 = *(float *)(in_r0 + 100);
  fVar14 = *(float *)(in_r0 + 0x88);
  fVar12 = *(float *)(in_r0 + 0x8c);
  iVar8 = *(int *)(in_r0 + 0xa8);
  *(float *)(in_r0 + 0x5c) = *(float *)(in_r0 + 0x5c) + fVar13;
  *(float *)(in_r0 + 0x60) = fVar10 + fVar14;
  fVar13 = DAT_00077748;
  *(float *)(in_r0 + 100) = fVar11 + fVar12;
  fVar15 = DAT_0007774c;
  uVar4 = *(undefined4 *)(in_r0 + 0x60);
  uVar5 = *(undefined4 *)(in_r0 + 100);
  *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
  *(undefined4 *)(iVar8 + 0x4c) = uVar4;
  *(undefined4 *)(iVar8 + 0x50) = uVar5;
  *(float *)(in_r0 + 0x88) =
       *(float *)(in_r0 + 0x88) + *(float *)(iVar6 + 0x54) * *(float *)(iVar6 + 0x54) * fVar15;
  fVar15 = DAT_00077750;
  if ((fVar10 + fVar14 < fVar13) ||
     (pcVar7 = *(cRSubGoldy **)(in_r0 + 0xb4), fVar11 + fVar12 < *(float *)(pcVar7 + 0x27fc))) {
LAB_000776b8:
    Kill(in_r0);
    return;
  }
  fVar13 = *(float *)(in_r0 + 0xa0);
  *(float *)(in_r0 + 0xa0) = fVar13 + *(float *)(in_r0 + 0xa4);
  if (fVar15 < fVar13 + *(float *)(in_r0 + 0xa4)) {
    *(undefined4 *)(in_r0 + 0xa0) = DAT_0007773c;
    Smoke(in_r0,(tVector *)(in_r0 + 0x5c),(tVector *)(in_r0 + 0x84),pcVar7);
switchD_00077424_default:
    iVar8 = *(int *)(in_r0 + 0xa8);
    pcVar7 = *(cRSubGoldy **)(in_r0 + 0xb4);
  }
LAB_000775d4:
  fVar13 = *(float *)(pcVar7 + 0x360);
  fVar15 = *(float *)(in_r0 + 0x94);
  cVar1 = pcVar7[0x374];
  *(float *)(iVar8 + 0x7c) = fVar13 + fVar15;
  if (cVar1 != (cRSubGoldy)0x0) {
    *(float *)(iVar8 + 0x7c) =
         fVar13 + fVar15 + *(float *)(pcVar7 + 0x390) + *(float *)(pcVar7 + 0x38c);
  }
  return;
}
