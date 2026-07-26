/*
 * mangled: _ZN8cRBorder2AIEv
 * demangled: cRBorder::AI()
 * address: 000600ac
 * size: 2328
 */

/* cRBorder::AI() */

void __thiscall cRBorder::AI(cRBorder *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int *piVar10;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;

  uVar4 = *(uint *)(this + 0x194);
  uVar6 = uVar4 & 0xfffdffff;
  iVar9 = DAT_00060478 + 0x600cc;
  *(uint *)(this + 0x198) = uVar4;
  *(uint *)(this + 0x194) = uVar6;
  fVar13 = DAT_00060470;
  fVar14 = DAT_00060464;
  if ((uVar4 & 0x100000) != 0) {
    fVar15 = *(float *)(this + 0x230) + DAT_0006045c * *(float *)(this + 0x240);
    fVar12 = *(float *)(this + 0x22c) + DAT_00060458 * *(float *)(this + 0x23c) + DAT_00060460;
    fVar11 = fVar15 + DAT_0006046c;
    *(float *)(this + 0x17c) =
         (*(float *)(this + 0x22c) + DAT_00060468 * *(float *)(this + 0x23c)) - DAT_00060460;
    *(float *)(this + 0x178) = fVar12 - fVar13;
    *(float *)(this + 0x184) = fVar11 - fVar14;
    *(float *)(this + 0x180) = fVar15 - fVar14;
  }
  *(float *)(this + 0x174) =
       *(float *)(this + 0x174) +
       (*(float *)(this + 0x170) - *(float *)(this + 0x174)) * DAT_00060468;
  fVar13 = DAT_000604a0;
  fVar14 = DAT_0006049c;
  if (uVar6 == 0) {
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar9 + DAT_00060488) + 0x358),(cRBod *)this);
    cRToolTip::ReSet((cRToolTip *)(this + 0x284));
    return;
  }
  if ((uVar4 & 0x200) != 0) {
    *(uint *)(this + 0x194) = uVar4 & 0xfffdfdff;
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(iVar9 + DAT_00060488) + 0x358),(cRBod *)this);
    cRToolTip::ReSet((cRToolTip *)(this + 0x284));
    *(undefined4 *)(this + 0x194) = 0;
    return;
  }
  if ((uVar4 & 0x400) == 0) {
    if ((uVar4 & 0x1000) != 0) {
      return;
    }
    if ((uVar4 & 0x8000) == 0) {
      if ((uVar4 & 2) != 0) {
        *(float *)(this + 0x200) = DAT_0006049c;
      }
      iVar3 = DAT_00060a28;
      iVar7 = DAT_00060488;
      if ((uVar4 & 0x80000) != 0) {
        piVar10 = *(int **)(iVar9 + DAT_00060a28);
        iVar2 = cRMouse::IsActive((cRMouse *)(*piVar10 + 0x228));
        iVar7 = iVar3;
        if ((iVar2 != 0) && (iVar3 = RShellInkey(), iVar3 == *(int *)(this + 0x188))) {
          cRToolTip::ReSet((cRToolTip *)(this + 0x284));
          if ((*(uint *)(this + 0x194) & 0x1000000) == 0) {
            cRBorderManager::DelayClick((cRBorderManager *)(*piVar10 + 0xd14),this,0x20);
          }
          else {
            *(uint *)(this + 0x194) = *(uint *)(this + 0x194) | 0x20;
          }
        }
      }
      iVar3 = cRMouse::IsActive((cRMouse *)(**(int **)(iVar9 + iVar7) + 0x228));
      if ((iVar3 != 0) || (uVar4 = *(uint *)(this + 0x194), (uVar4 & 8) != 0)) {
        iVar3 = MouseTest(this);
        if (iVar3 != 0) {
          uVar4 = *(uint *)(this + 0x194);
          uVar6 = uVar4 | 0x20000;
          *(uint *)(this + 0x194) = uVar6;
          if ((uVar4 & 4) != 0) {
            *(float *)(this + 0x200) = DAT_0006049c;
            *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x20c);
          }
          if (((uVar4 & 2) == 0) && ((uVar4 & 4) != 0)) {
            if ((uVar4 & 0x40000) == 0) {
              cRSound::Play(*(int *)(iVar9 + DAT_00060a2c));
              uVar6 = *(uint *)(this + 0x194);
            }
            uVar6 = uVar6 | 2;
            *(uint *)(this + 0x194) = uVar6;
          }
          if ((((uVar6 & 0x10) != 0) &&
              (iVar3 = **(int **)(iVar9 + iVar7), *(char *)(iVar3 + 0x43df8) == '\0')) &&
             ((*(uint *)(*(int *)(iVar3 + 0x224) + 0x30) & 0x4000) != 0)) {
            if ((uVar6 & 0x1000000) == 0) {
              cRBorderManager::DelayClick((cRBorderManager *)(iVar3 + 0xd14),this,0x20);
              uVar6 = *(uint *)(this + 0x194);
            }
            else {
              uVar6 = uVar6 | 0x20;
              *(uint *)(this + 0x194) = uVar6;
            }
            if ((uVar6 & 0x800000) == 0) {
              cRSound::Play(*(int *)(iVar9 + DAT_00060a2c));
            }
            if ((*(uint *)(this + 0x28c) & 0x20) == 0) {
              cRToolTip::ReSet((cRToolTip *)(this + 0x284));
            }
            uVar6 = *(uint *)(this + 0x194);
          }
          if (((uVar6 & 0x40) != 0) &&
             ((*(uint *)(*(int *)(**(int **)(iVar9 + iVar7) + 0x224) + 0x30) & 0x8000) != 0)) {
            if ((uVar6 & 0x1000000) == 0) {
              cRBorderManager::DelayClick
                        ((cRBorderManager *)(**(int **)(iVar9 + iVar7) + 0xd14),this,0x80);
            }
            else {
              *(uint *)(this + 0x194) = uVar6 | 0x80;
            }
            cRSound::Play(*(int *)(iVar9 + DAT_00060484));
            cRToolTip::ReSet((cRToolTip *)(this + 0x284));
            uVar6 = *(uint *)(this + 0x194);
          }
          goto LAB_0006019c;
        }
        uVar4 = *(uint *)(this + 0x194);
      }
      *(uint *)(this + 0x194) = uVar4 & 0xffdfffff;
      if (((uVar4 & 0x2000) == 0) && ((uVar4 & 4) != 0)) {
        UnHighlight(this);
      }
      uVar6 = *(uint *)(this + 0x194);
      *(float *)(this + 0x218) = DAT_000604a0;
      if ((uVar6 & 4) != 0) {
        uVar6 = uVar6 & 0xfffffffd;
        *(uint *)(this + 0x194) = uVar6;
      }
    }
    else {
      uVar6 = uVar4 & 0xfffdfffd;
      *(uint *)(this + 0x194) = uVar6;
      *(float *)(this + 0x218) = fVar13;
      iVar7 = DAT_00060488;
    }
  }
  else {
    fVar13 = *(float *)(this + 0x25c);
    *(float *)(this + 0x25c) = fVar13 + *(float *)(this + 0x260);
    iVar7 = DAT_00060488;
    if (fVar14 < fVar13 + *(float *)(this + 0x260)) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar9 + DAT_00060488) + 0x358),(cRBod *)this);
      cRToolTip::ReSet((cRToolTip *)(this + 0x284));
      *(undefined4 *)(this + 0x194) = 0;
      return;
    }
  }
LAB_0006019c:
  if ((uVar6 & 0x8000) != 0) {
    *(uint *)(this + 0x194) = uVar6 & 0xffdfffff;
    DeactivateHighlight(this);
    uVar6 = *(uint *)(this + 0x194);
  }
  fVar14 = DAT_00060458;
  if ((uVar6 & 0x40000) == 0) {
    fVar11 = *(float *)(this + 0x218);
    fVar13 = *(float *)(this + 0x21c) + (fVar11 - *(float *)(this + 0x21c)) * DAT_00060458;
    *(float *)(this + 0x21c) = fVar13;
    *(float *)(this + 0x204) =
         *(float *)(this + 0x204) + (*(float *)(this + 0x200) - *(float *)(this + 0x204)) * fVar14;
    fVar13 = fVar11 - fVar13;
    *(float *)(this + 0x214) =
         *(float *)(this + 0x214) + (*(float *)(this + 0x210) - *(float *)(this + 0x214)) * fVar14;
    if (fVar13 < 0.0) {
      bVar1 = DAT_00060494 < fVar13;
    }
    else if (fVar14 <= fVar13) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      *(float *)(this + 0x21c) = fVar11;
      uVar6 = *(uint *)(this + 0x194);
    }
    else {
      uVar6 = *(uint *)(this + 0x194);
    }
  }
  else {
    *(undefined4 *)(this + 0x204) = *(undefined4 *)(this + 0x200);
    *(uint *)(this + 0x194) = uVar6 & 0xfffbffff;
    *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x210);
    *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x218);
  }
  if ((uVar6 & 0x2000) != 0) {
    piVar10 = *(int **)(iVar9 + iVar7);
    iVar3 = cRMouse::IsActive((cRMouse *)(*piVar10 + 0x228));
    if ((iVar3 != 0) && (InputText(this), (*(uint *)(this + 0x194) & 0x2000) == 0)) {
      cRBorderManager::ActivateBorders((cRBorderManager *)(*piVar10 + 0xd14));
    }
  }
  cRTwinkleManager::AI((cRTwinkleManager *)(this + 0x74));
  cRToolTip::AI((cRToolTip *)(this + 0x284));
  uVar6 = *(uint *)(this + 0x194);
  RePosition(this);
  uVar4 = *(uint *)(this + 0x194);
  if ((uVar4 & 0x1000) == 0) {
    tColour::Set((tColour *)(this + 0x1a0),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    tColour::Set((tColour *)(this + 0x1d0),extraout_s0_00,extraout_s1_00,extraout_s2_00,
                 extraout_s3_00);
    fVar14 = DAT_00060498;
    uVar4 = *(uint *)(this + 0x194);
    if ((uVar4 & 0x8000) != 0) {
      fVar13 = *(float *)(this + 0x1d4) * DAT_00060498;
      *(float *)(this + 0x1d0) = *(float *)(this + 0x1d0) * DAT_00060498;
      *(float *)(this + 0x1d4) = fVar13;
      *(float *)(this + 0x1ac) = *(float *)(this + 0x1ac) * fVar14;
      *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) * fVar14;
      *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) * fVar14;
      *(float *)(this + 0x1a0) = *(float *)(this + 0x1a0) * fVar14;
      *(float *)(this + 0x1a4) = *(float *)(this + 0x1a4) * fVar14;
      *(float *)(this + 0x1a8) = *(float *)(this + 0x1a8) * fVar14;
    }
    if ((uVar4 & 0x800) == 0) {
      if ((uVar4 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 (*(uint *)(*(int *)(iVar9 + DAT_00060480) + 0x1c) & 0x1ff) >> 8,
                 *(undefined4 *)(this + 0x254),*(undefined4 *)(this + 600),0x1000000,
                 *(undefined4 *)(this + 0x1d0),*(undefined4 *)(this + 0x1d4),
                 *(undefined4 *)(this + 0x1d8),*(undefined4 *)(this + 0x1dc),0,(uVar6 & 0x1ff) >> 8)
        ;
        fVar11 = *(float *)(this + 0x22c) + DAT_00060a10 * *(float *)(this + 0x23c);
        fVar14 = DAT_00060a14 * *(float *)(this + 0x23c);
        *(float *)(this + 0x22c) = fVar11;
        *(float *)(this + 0x23c) = fVar14;
        fVar13 = DAT_00060a1c;
        if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
          fVar14 = fVar14 * DAT_00060a18;
          *(undefined4 *)(this + 0x23c) = DAT_00060a20;
          fVar12 = *(float *)(this + 0x240) + DAT_00060a24;
          *(float *)(this + 0x22c) = (fVar11 + fVar14) - fVar13;
          *(float *)(this + 0x240) = fVar12;
        }
        if (*(float *)(this + 0x244) != 0.0) {
          *(float *)(this + 0x23c) = *(float *)(this + 0x244);
        }
      }
      else {
        *(undefined4 *)(this + 0x22c) = *(undefined4 *)(this + 0x40);
        *(undefined4 *)(this + 0x230) = *(undefined4 *)(this + 0x44);
        *(undefined4 *)(this + 0x23c) = *(undefined4 *)(this + 0x48);
        *(undefined4 *)(this + 0x240) = *(undefined4 *)(this + 0x4c);
      }
    }
    Draw(this);
    uVar4 = *(uint *)(this + 0x194);
  }
  if (*(int *)(this + 0x270) != 0) {
    *(int *)(this + 0x270) = *(int *)(this + 0x270) + -1;
  }
  iVar7 = **(int **)(iVar9 + iVar7);
  *(undefined4 *)(this + 0x274) = *(undefined4 *)(iVar7 + 0x234);
  *(undefined4 *)(this + 0x278) = *(undefined4 *)(iVar7 + 0x238);
  fVar14 = DAT_00060490;
  if ((uVar4 & 0x100000) == 0) {
    return;
  }
  iVar7 = *(int *)(this + 0x714);
  if ((*(uint *)(iVar7 + 0x194) & 0x20) == 0) {
    fVar13 = *(float *)(this + 0x170);
    iVar3 = *(int *)(this + 0x710);
    uVar4 = *(uint *)(iVar3 + 0x194);
    if ((uVar4 & 0x20) != 0) goto LAB_00060250;
LAB_00060320:
    if (fVar13 != 0.0) {
      uVar4 = uVar4 & 0xffff7fff;
      *(uint *)(iVar3 + 0x194) = uVar4;
      goto LAB_00060284;
    }
  }
  else {
    fVar13 = DAT_0006048c + *(float *)(this + 0x170);
    iVar3 = *(int *)(this + 0x710);
    *(uint *)(iVar7 + 0x194) = *(uint *)(iVar7 + 0x194) & 0xffffffdf;
    uVar4 = *(uint *)(iVar3 + 0x194);
    *(float *)(this + 0x170) = fVar13;
    fVar11 = DAT_0006049c;
    if (fVar14 <= fVar13) {
      *(float *)(this + 0x170) = DAT_0006049c;
      fVar13 = fVar11;
    }
    if ((uVar4 & 0x20) == 0) goto LAB_00060320;
LAB_00060250:
    fVar14 = DAT_00060458;
    fVar13 = fVar13 - DAT_0006048c;
    uVar4 = uVar4 & 0xffffffdf;
    *(uint *)(iVar3 + 0x194) = uVar4;
    *(float *)(this + 0x170) = fVar13;
    fVar11 = DAT_000604a0;
    if (fVar14 < fVar13) goto LAB_00060320;
    *(float *)(this + 0x170) = DAT_000604a0;
    fVar13 = fVar11;
  }
  uVar4 = uVar4 | 0x8000;
  *(uint *)(iVar3 + 0x194) = uVar4;
LAB_00060284:
  bVar1 = fVar13 == DAT_0006049c;
  iVar3 = *(int *)(this + 0x718);
  fVar14 = DAT_00060458 + DAT_00060474 * fVar13;
  if (bVar1) {
    uVar4 = *(uint *)(iVar7 + 0x194);
  }
  if (!bVar1) {
    uVar4 = *(uint *)(iVar7 + 0x194);
  }
  *(undefined4 *)(iVar3 + 0x204) = *(undefined4 *)(this + 0x204);
  if (bVar1) {
    uVar4 = uVar4 | 0x8000;
  }
  uVar16 = *(undefined4 *)(this + 0x200);
  if (bVar1) {
    *(uint *)(iVar7 + 0x194) = uVar4;
  }
  else {
    *(uint *)(iVar7 + 0x194) = uVar4 & 0xffff7fff;
  }
  *(undefined4 *)(iVar3 + 0x200) = uVar16;
  uVar16 = *(undefined4 *)(this + 0x1d4);
  uVar5 = *(undefined4 *)(this + 0x1d8);
  uVar8 = *(undefined4 *)(this + 0x1dc);
  *(undefined4 *)(iVar3 + 0x1d0) = *(undefined4 *)(this + 0x1d0);
  *(undefined4 *)(iVar3 + 0x1d4) = uVar16;
  *(undefined4 *)(iVar3 + 0x1d8) = uVar5;
  *(undefined4 *)(iVar3 + 0x1dc) = uVar8;
  sprintf((char *)(iVar3 + 0x2c4),(char *)(iVar9 + DAT_0006047c),(int)fVar14);
  return;
}
