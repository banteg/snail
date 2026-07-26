/*
 * mangled: _ZN9cRSubRing2AIEv
 * demangled: cRSubRing::AI()
 * address: 0006e8a0
 * size: 864
 */

/* cRSubRing::AI() */

void cRSubRing::AI(void)

{
  cRBod *in_r0;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  cRBod *pcVar5;
  cRBod *pcVar6;
  float in_s0;
  float fVar7;
  float fVar8;

  iVar3 = *(int *)(in_r0 + 0x184);
  if (*(char *)(iVar3 + 0x19) != '\0') {
    return;
  }
  if (*(int *)(in_r0 + 0x19c) == 2) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(in_r0 + 0x19c) + 1;
  }
  *(int *)(in_r0 + 0x19c) = iVar1;
  switch(*(undefined4 *)(in_r0 + 0x74)) {
  case 1:
    if (in_r0[400] != (cRBod)0x0) {
      fVar7 = *(float *)(in_r0 + 0x194) + *(float *)(in_r0 + 0x198);
      *(float *)(in_r0 + 0x194) = fVar7;
      if (6.2831855 < fVar7) {
        *(float *)(in_r0 + 0x194) = fVar7 - 6.2831855;
      }
      else if (fVar7 < 0.0) {
        *(float *)(in_r0 + 0x194) = fVar7 + 6.2831855;
      }
      fVar7 = (float)Sin(in_s0);
      *(float *)(in_r0 + 0x5c) = fVar7 * 6.0 * 0.5;
    }
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      cRSubRingStar::AI();
    } while (iVar3 != 8);
    if (*(float *)(*(int *)(in_r0 + 0x78) + 0x27fc) <= *(float *)(in_r0 + 100)) {
      if (*(int *)(*(int *)(in_r0 + 0x78) + 0x3fc) < *(int *)(in_r0 + 0x80)) {
        *(undefined4 *)(in_r0 + 0x74) = 4;
      }
      return;
    }
    iVar3 = 0;
    *(undefined4 *)(in_r0 + 0x74) = 0;
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),in_r0);
    do {
      iVar3 = iVar3 + 1;
      cRSprite::Kill(*(cRSprite **)(in_r0 + 0x84));
      in_r0 = in_r0 + 0x20;
    } while (iVar3 != 8);
    return;
  case 2:
    *(undefined4 *)(in_r0 + 0x188) = 0;
    fVar7 = *(float *)(iVar3 + 0x54);
    *(undefined4 *)(in_r0 + 0x74) = 3;
    *(float *)(in_r0 + 0x18c) = fVar7 * 0.06944445;
    goto LAB_0006e9b0;
  case 3:
LAB_0006e9b0:
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      cRSubRingStar::AI();
    } while (iVar3 != 8);
    fVar7 = *(float *)(in_r0 + 0x188);
    *(float *)(in_r0 + 0x188) = fVar7 + *(float *)(in_r0 + 0x18c);
    if (fVar7 + *(float *)(in_r0 + 0x18c) <= 1.0) {
      iVar3 = *(int *)(in_r0 + 0x78);
      fVar8 = *(float *)(iVar3 + 0x27e8);
      fVar7 = *(float *)(iVar3 + 0x27e4);
      *(float *)(in_r0 + 0x5c) =
           *(float *)(in_r0 + 0x5c) +
           ((*(float *)(iVar3 + 0x27e0) + 0.0) - *(float *)(in_r0 + 0x5c)) * 0.94;
      *(float *)(in_r0 + 0x60) =
           *(float *)(in_r0 + 0x60) + ((fVar7 + 0.0) - *(float *)(in_r0 + 0x60)) * 0.94;
      *(float *)(in_r0 + 100) =
           *(float *)(in_r0 + 100) + ((fVar8 + 0.2) - *(float *)(in_r0 + 100)) * 0.94;
      pcVar5 = in_r0;
      do {
        *(float *)(pcVar5 + 0xa0) = *(float *)(pcVar5 + 0xa0) * 0.94;
        uVar2 = *(undefined4 *)(in_r0 + 0x60);
        uVar4 = *(undefined4 *)(in_r0 + 100);
        pcVar6 = pcVar5 + 0x20;
        *(undefined4 *)(pcVar5 + 0x8c) = *(undefined4 *)(in_r0 + 0x5c);
        *(undefined4 *)(pcVar5 + 0x90) = uVar2;
        *(undefined4 *)(pcVar5 + 0x94) = uVar4;
        pcVar5 = pcVar6;
      } while (pcVar6 != in_r0 + 0x100);
      return;
    }
    iVar3 = 0;
    *(undefined4 *)(in_r0 + 0x74) = 0;
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),in_r0);
    do {
      iVar3 = iVar3 + 1;
      cRSprite::Kill(*(cRSprite **)(in_r0 + 0x84));
      in_r0 = in_r0 + 0x20;
    } while (iVar3 != 8);
    return;
  case 4:
    *(undefined4 *)(in_r0 + 0x188) = 0;
    fVar7 = *(float *)(iVar3 + 0x54);
    *(undefined4 *)(in_r0 + 0x74) = 5;
    *(float *)(in_r0 + 0x18c) = fVar7 * 0.06944445;
    break;
  case 5:
    break;
  default:
    goto switchD_0006e8e0_default;
  }
  iVar3 = 0;
  do {
    iVar3 = iVar3 + 1;
    cRSubRingStar::AI();
  } while (iVar3 != 8);
  fVar7 = *(float *)(in_r0 + 0x188);
  *(float *)(in_r0 + 0x188) = fVar7 + *(float *)(in_r0 + 0x18c);
  if (1.0 < fVar7 + *(float *)(in_r0 + 0x18c)) {
    iVar3 = 0;
    *(undefined4 *)(in_r0 + 0x74) = 0;
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),in_r0);
    do {
      iVar3 = iVar3 + 1;
      cRSprite::Kill(*(cRSprite **)(in_r0 + 0x84));
      in_r0 = in_r0 + 0x20;
    } while (iVar3 != 8);
    return;
  }
  pcVar5 = in_r0;
  do {
    *(float *)(pcVar5 + 0xa0) = *(float *)(pcVar5 + 0xa0) * 1.1;
    uVar2 = *(undefined4 *)(in_r0 + 0x60);
    uVar4 = *(undefined4 *)(in_r0 + 100);
    pcVar6 = pcVar5 + 0x20;
    *(undefined4 *)(pcVar5 + 0x8c) = *(undefined4 *)(in_r0 + 0x5c);
    *(undefined4 *)(pcVar5 + 0x90) = uVar2;
    *(undefined4 *)(pcVar5 + 0x94) = uVar4;
    pcVar5 = pcVar6;
  } while (pcVar6 != in_r0 + 0x100);
switchD_0006e8e0_default:
  return;
}
