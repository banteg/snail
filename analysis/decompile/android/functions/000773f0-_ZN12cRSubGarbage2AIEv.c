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
  cRSubGarbage *in_r0;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  cRSubGoldy *pcVar6;
  int iVar7;
  uint in_fpscr;
  uint uVar8;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  iVar5 = *(int *)(in_r0 + 0x80);
  if (*(char *)(iVar5 + 0x19) != '\0') {
    return;
  }
  switch(*(undefined4 *)(in_r0 + 0x78)) {
  case 0:
    return;
  case 1:
    iVar7 = *(int *)(in_r0 + 0xa8);
    pcVar6 = *(cRSubGoldy **)(in_r0 + 0xb4);
    uVar3 = *(undefined4 *)(in_r0 + 0x60);
    uVar4 = *(undefined4 *)(in_r0 + 100);
    *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(iVar7 + 0x4c) = uVar3;
    *(undefined4 *)(iVar7 + 0x50) = uVar4;
    if (*(float *)(in_r0 + 100) < *(float *)(pcVar6 + 0x27fc)) goto LAB_000776b8;
    if (0.0 < *(float *)(pcVar6 + 0x364)) {
      *(undefined4 *)(in_r0 + 0x78) = 2;
      if (0.0 < *(float *)(in_r0 + 0x5c)) {
        *(undefined4 *)(in_r0 + 0x7c) = 1;
      }
      else {
        *(undefined4 *)(in_r0 + 0x7c) = 2;
      }
      in_s0 = (float)cRSubGoldy::ScoreAdd(pcVar6,0,0);
      iVar5 = *(int *)(in_r0 + 0x80);
    }
    cREnemyManager::Register
              ((cREnemyManager *)(gGroup0 + iVar5 + 0xc0700),(tVector *)(in_r0 + 0x5c),in_s0,
               *(int *)(in_r0 + 0x90),(cRBodPos *)0x0);
    iVar7 = *(int *)(in_r0 + 0xa8);
    pcVar6 = *(cRSubGoldy **)(in_r0 + 0xb4);
    goto LAB_000775d4;
  case 2:
    *(undefined4 *)(in_r0 + 0x78) = 3;
    fVar11 = (float)SRAND(in_s0,(char *)0x3dcccccd);
    fVar13 = (float)RAND(extraout_s0,(char *)0x3e4ccccd);
    fVar9 = (float)RAND(extraout_s0_00,(char *)0x3e99999a);
    iVar5 = *(int *)(in_r0 + 0x80);
    fVar10 = *(float *)(iVar5 + 0x54);
    fVar11 = fVar11 * fVar10;
    *(float *)(in_r0 + 0x88) = (fVar13 + 0.1) * fVar10;
    *(float *)(in_r0 + 0x84) = fVar11;
    *(float *)(in_r0 + 0x8c) = fVar9 * fVar10;
    if (*(int *)(in_r0 + 0x7c) == 1) {
      uVar8 = in_fpscr & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
      if (SUB41(uVar8 >> 0x1f,0)) {
LAB_00077700:
        fVar11 = -fVar11;
        uVar8 = uVar8 & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
        if (SUB41(uVar8 >> 0x1f,0)) {
          bVar2 = true;
        }
        else {
          bVar2 = false;
        }
      }
      else {
        bVar2 = false;
      }
      *(float *)(in_r0 + 0x84) = fVar11;
    }
    else if (*(int *)(in_r0 + 0x7c) == 2) {
      uVar8 = in_fpscr & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
      if (!SUB41(uVar8 >> 0x1f,0)) goto LAB_00077700;
      bVar2 = true;
      *(float *)(in_r0 + 0x84) = fVar11;
    }
    else {
      uVar8 = in_fpscr & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
      if (SUB41(uVar8 >> 0x1f,0)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
    }
    if (bVar2) {
      fVar13 = -0.2;
    }
    else {
      uVar8 = uVar8 & 0xfffffff | (uint)(fVar11 == 0.0) << 0x1e;
      fVar13 = (float)VectorSignedToFloat((uint)!SUB41(uVar8 >> 0x1e,0),(byte)(uVar8 >> 0x16) & 3);
      fVar13 = fVar13 * 0.2;
    }
    fVar11 = fVar11 + fVar13 * *(float *)(iVar5 + 0x54);
    *(undefined4 *)(in_r0 + 0x98) = 0;
    *(float *)(in_r0 + 0x84) = fVar11;
    fVar13 = *(float *)(iVar5 + 0x54);
    *(undefined4 *)(in_r0 + 0xa0) = 0;
    *(float *)(in_r0 + 0x9c) = fVar13 * 0.008333334;
    *(float *)(in_r0 + 0xa4) = *(float *)(iVar5 + 0x54) * 0.2777778;
    break;
  case 3:
    fVar11 = *(float *)(in_r0 + 0x84);
    break;
  default:
    goto switchD_00077424_default;
  }
  fVar13 = *(float *)(in_r0 + 0x60);
  fVar9 = *(float *)(in_r0 + 100);
  fVar12 = *(float *)(in_r0 + 0x88);
  fVar10 = *(float *)(in_r0 + 0x8c);
  iVar7 = *(int *)(in_r0 + 0xa8);
  *(float *)(in_r0 + 0x5c) = *(float *)(in_r0 + 0x5c) + fVar11;
  *(float *)(in_r0 + 0x60) = fVar13 + fVar12;
  *(float *)(in_r0 + 100) = fVar9 + fVar10;
  uVar3 = *(undefined4 *)(in_r0 + 0x60);
  uVar4 = *(undefined4 *)(in_r0 + 100);
  *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(in_r0 + 0x5c);
  *(undefined4 *)(iVar7 + 0x4c) = uVar3;
  *(undefined4 *)(iVar7 + 0x50) = uVar4;
  *(float *)(in_r0 + 0x88) =
       *(float *)(in_r0 + 0x88) + *(float *)(iVar5 + 0x54) * *(float *)(iVar5 + 0x54) * -0.01;
  if ((fVar13 + fVar12 < -10.0) ||
     (pcVar6 = *(cRSubGoldy **)(in_r0 + 0xb4), fVar9 + fVar10 < *(float *)(pcVar6 + 0x27fc))) {
LAB_000776b8:
    Kill(in_r0);
    return;
  }
  fVar11 = *(float *)(in_r0 + 0xa0);
  *(float *)(in_r0 + 0xa0) = fVar11 + *(float *)(in_r0 + 0xa4);
  if (1.0 < fVar11 + *(float *)(in_r0 + 0xa4)) {
    *(undefined4 *)(in_r0 + 0xa0) = 0;
    Smoke(in_r0,(tVector *)(in_r0 + 0x5c),(tVector *)(in_r0 + 0x84),pcVar6);
switchD_00077424_default:
    iVar7 = *(int *)(in_r0 + 0xa8);
    pcVar6 = *(cRSubGoldy **)(in_r0 + 0xb4);
  }
LAB_000775d4:
  fVar11 = *(float *)(pcVar6 + 0x360);
  fVar13 = *(float *)(in_r0 + 0x94);
  cVar1 = pcVar6[0x374];
  *(float *)(iVar7 + 0x7c) = fVar11 + fVar13;
  if (cVar1 != (cRSubGoldy)0x0) {
    *(float *)(iVar7 + 0x7c) =
         fVar11 + fVar13 + *(float *)(pcVar6 + 0x390) + *(float *)(pcVar6 + 0x38c);
  }
  return;
}
