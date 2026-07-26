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
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float fVar8;
  undefined4 uVar9;
  float fVar10;

  uVar3 = *(uint *)(this + 0x194);
  uVar5 = uVar3 & 0xfffdffff;
  *(uint *)(this + 0x198) = uVar3;
  *(uint *)(this + 0x194) = uVar5;
  if ((uVar3 & 0x100000) != 0) {
    fVar8 = *(float *)(this + 0x230) + *(float *)(this + 0x240) * 0.5;
    *(float *)(this + 0x17c) = (*(float *)(this + 0x22c) + *(float *)(this + 0x23c) * 0.8) - 4.0;
    *(float *)(this + 0x178) =
         (*(float *)(this + 0x22c) + *(float *)(this + 0x23c) * 0.1 + 4.0) - 12.0;
    *(float *)(this + 0x184) = (fVar8 + 32.0) - 6.0;
    *(float *)(this + 0x180) = fVar8 - 6.0;
  }
  *(float *)(this + 0x174) =
       *(float *)(this + 0x174) + (*(float *)(this + 0x170) - *(float *)(this + 0x174)) * 0.8;
  if (uVar5 == 0) {
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
    cRToolTip::ReSet((cRToolTip *)(this + 0x284));
    return;
  }
  if ((uVar3 & 0x200) != 0) {
    *(uint *)(this + 0x194) = uVar3 & 0xfffdfdff;
    cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
    cRToolTip::ReSet((cRToolTip *)(this + 0x284));
    *(undefined4 *)(this + 0x194) = 0;
    return;
  }
  if ((uVar3 & 0x400) == 0) {
    if ((uVar3 & 0x1000) != 0) {
      return;
    }
    if ((uVar3 & 0x8000) == 0) {
      if ((uVar3 & 2) != 0) {
        *(undefined4 *)(this + 0x200) = 0x3f800000;
      }
      if ((((uVar3 & 0x80000) != 0) &&
          (iVar6 = cRMouse::IsActive((cRMouse *)(Game + 0x228)), iVar6 != 0)) &&
         (iVar6 = RShellInkey(), iVar6 == *(int *)(this + 0x188))) {
        cRToolTip::ReSet((cRToolTip *)(this + 0x284));
        if ((*(uint *)(this + 0x194) & 0x1000000) == 0) {
          cRBorderManager::DelayClick((cRBorderManager *)(Game + 0xd14),this,0x20);
        }
        else {
          *(uint *)(this + 0x194) = *(uint *)(this + 0x194) | 0x20;
        }
      }
      iVar6 = cRMouse::IsActive((cRMouse *)(Game + 0x228));
      if ((iVar6 != 0) || (uVar3 = *(uint *)(this + 0x194), (uVar3 & 8) != 0)) {
        iVar6 = MouseTest(this);
        if (iVar6 != 0) {
          uVar3 = *(uint *)(this + 0x194);
          uVar5 = uVar3 | 0x20000;
          *(uint *)(this + 0x194) = uVar5;
          if ((uVar3 & 4) != 0) {
            *(undefined4 *)(this + 0x200) = 0x3f800000;
            *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x20c);
          }
          if (((uVar3 & 2) == 0) && ((uVar3 & 4) != 0)) {
            if ((uVar3 & 0x40000) == 0) {
              cRSound::Play((int)&gRSound);
              uVar5 = *(uint *)(this + 0x194);
            }
            uVar5 = uVar5 | 2;
            *(uint *)(this + 0x194) = uVar5;
          }
          if ((((uVar5 & 0x10) != 0) && (*(char *)(Game + 0x43df8) == '\0')) &&
             ((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) != 0)) {
            if ((uVar5 & 0x1000000) == 0) {
              cRBorderManager::DelayClick((cRBorderManager *)(Game + 0xd14),this,0x20);
              uVar5 = *(uint *)(this + 0x194);
            }
            else {
              uVar5 = uVar5 | 0x20;
              *(uint *)(this + 0x194) = uVar5;
            }
            if ((uVar5 & 0x800000) == 0) {
              cRSound::Play((int)&gRSound);
            }
            if ((*(uint *)(this + 0x28c) & 0x20) == 0) {
              cRToolTip::ReSet((cRToolTip *)(this + 0x284));
            }
            uVar5 = *(uint *)(this + 0x194);
          }
          if (((uVar5 & 0x40) != 0) && ((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x8000) != 0)) {
            if ((uVar5 & 0x1000000) == 0) {
              cRBorderManager::DelayClick((cRBorderManager *)(Game + 0xd14),this,0x80);
            }
            else {
              *(uint *)(this + 0x194) = uVar5 | 0x80;
            }
            cRSound::Play((int)&gRSound);
            cRToolTip::ReSet((cRToolTip *)(this + 0x284));
            uVar5 = *(uint *)(this + 0x194);
          }
          goto LAB_0006019c;
        }
        uVar3 = *(uint *)(this + 0x194);
      }
      *(uint *)(this + 0x194) = uVar3 & 0xffdfffff;
      if (((uVar3 & 0x2000) == 0) && ((uVar3 & 4) != 0)) {
        UnHighlight(this);
      }
      uVar5 = *(uint *)(this + 0x194);
      *(undefined4 *)(this + 0x218) = 0;
      if ((uVar5 & 4) != 0) {
        uVar5 = uVar5 & 0xfffffffd;
        *(uint *)(this + 0x194) = uVar5;
      }
    }
    else {
      uVar5 = uVar3 & 0xfffdfffd;
      *(uint *)(this + 0x194) = uVar5;
      *(undefined4 *)(this + 0x218) = 0;
    }
  }
  else {
    fVar8 = *(float *)(this + 0x25c);
    *(float *)(this + 0x25c) = fVar8 + *(float *)(this + 0x260);
    if (1.0 < fVar8 + *(float *)(this + 0x260)) {
      cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
      cRToolTip::ReSet((cRToolTip *)(this + 0x284));
      *(undefined4 *)(this + 0x194) = 0;
      return;
    }
  }
LAB_0006019c:
  if ((uVar5 & 0x8000) != 0) {
    *(uint *)(this + 0x194) = uVar5 & 0xffdfffff;
    DeactivateHighlight(this);
    uVar5 = *(uint *)(this + 0x194);
  }
  if ((uVar5 & 0x40000) == 0) {
    fVar10 = *(float *)(this + 0x218);
    fVar8 = *(float *)(this + 0x21c) + (fVar10 - *(float *)(this + 0x21c)) * 0.1;
    *(float *)(this + 0x21c) = fVar8;
    *(float *)(this + 0x204) =
         *(float *)(this + 0x204) + (*(float *)(this + 0x200) - *(float *)(this + 0x204)) * 0.1;
    fVar8 = fVar10 - fVar8;
    *(float *)(this + 0x214) =
         *(float *)(this + 0x214) + (*(float *)(this + 0x210) - *(float *)(this + 0x214)) * 0.1;
    if (fVar8 < 0.0) {
      bVar1 = -0.1 < fVar8;
    }
    else if (0.1 <= fVar8) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      *(float *)(this + 0x21c) = fVar10;
      uVar5 = *(uint *)(this + 0x194);
    }
    else {
      uVar5 = *(uint *)(this + 0x194);
    }
  }
  else {
    *(undefined4 *)(this + 0x204) = *(undefined4 *)(this + 0x200);
    *(uint *)(this + 0x194) = uVar5 & 0xfffbffff;
    *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x210);
    *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x218);
  }
  if ((((uVar5 & 0x2000) != 0) && (iVar6 = cRMouse::IsActive((cRMouse *)(Game + 0x228)), iVar6 != 0)
      ) && (InputText(this), (*(uint *)(this + 0x194) & 0x2000) == 0)) {
    cRBorderManager::ActivateBorders((cRBorderManager *)(Game + 0xd14));
  }
  cRTwinkleManager::AI((cRTwinkleManager *)(this + 0x74));
  cRToolTip::AI((cRToolTip *)(this + 0x284));
  uVar5 = *(uint *)(this + 0x194);
  RePosition(this);
  uVar3 = *(uint *)(this + 0x194);
  if ((uVar3 & 0x1000) == 0) {
    tColour::Set((tColour *)(this + 0x1a0),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    tColour::Set((tColour *)(this + 0x1d0),extraout_s0_00,extraout_s1_00,extraout_s2_00,
                 extraout_s3_00);
    uVar3 = *(uint *)(this + 0x194);
    if ((uVar3 & 0x8000) != 0) {
      *(float *)(this + 0x1d0) = *(float *)(this + 0x1d0) * 0.5;
      *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) * 0.5;
      *(float *)(this + 0x1ac) = *(float *)(this + 0x1ac) * 0.5;
      *(float *)(this + 0x1d8) = *(float *)(this + 0x1d8) * 0.5;
      *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) * 0.5;
      *(float *)(this + 0x1a0) = *(float *)(this + 0x1a0) * 0.5;
      *(float *)(this + 0x1a4) = *(float *)(this + 0x1a4) * 0.5;
      *(float *)(this + 0x1a8) = *(float *)(this + 0x1a8) * 0.5;
    }
    if ((uVar3 & 0x800) == 0) {
      if ((uVar3 & 0x10000) == 0) {
        FontType(this + 0x2c4,*(undefined4 *)(this + 0x6e4),*(undefined4 *)(this + 0x6e8),
                 *(undefined4 *)(this + 0x6ec),*(undefined4 *)(this + 0x6f0),this + 0x22c,
                 this + 0x230,this + 0x23c,this + 0x240,*(undefined4 *)(this + 0x21c),
                 (gConfig._28_4_ & 0x1ff) >> 8,*(undefined4 *)(this + 0x254),
                 *(undefined4 *)(this + 600),0x1000000,*(undefined4 *)(this + 0x1d0),
                 *(undefined4 *)(this + 0x1d4),*(undefined4 *)(this + 0x1d8),
                 *(undefined4 *)(this + 0x1dc),0,(uVar5 & 0x1ff) >> 8);
        fVar10 = *(float *)(this + 0x22c) + *(float *)(this + 0x23c) * -0.05;
        fVar8 = *(float *)(this + 0x23c) * 1.1;
        *(float *)(this + 0x22c) = fVar10;
        *(float *)(this + 0x23c) = fVar8;
        if ((*(uint *)(this + 0x194) & 0x100000) != 0) {
          *(undefined4 *)(this + 0x23c) = 0x43c80000;
          *(float *)(this + 0x22c) = (fVar10 + fVar8 * 0.5) - 200.0;
          *(float *)(this + 0x240) = *(float *)(this + 0x240) + 50.0;
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
    uVar3 = *(uint *)(this + 0x194);
  }
  if (*(int *)(this + 0x270) != 0) {
    *(int *)(this + 0x270) = *(int *)(this + 0x270) + -1;
  }
  iVar6 = Game;
  *(undefined4 *)(this + 0x274) = *(undefined4 *)(Game + 0x234);
  *(undefined4 *)(this + 0x278) = *(undefined4 *)(iVar6 + 0x238);
  if ((uVar3 & 0x100000) == 0) {
    return;
  }
  iVar6 = *(int *)(this + 0x714);
  if ((*(uint *)(iVar6 + 0x194) & 0x20) == 0) {
    fVar8 = *(float *)(this + 0x170);
    iVar2 = *(int *)(this + 0x710);
    uVar3 = *(uint *)(iVar2 + 0x194);
    if ((uVar3 & 0x20) != 0) goto LAB_00060250;
LAB_00060320:
    if (fVar8 != 0.0) {
      uVar3 = uVar3 & 0xffff7fff;
      *(uint *)(iVar2 + 0x194) = uVar3;
      goto LAB_00060284;
    }
  }
  else {
    fVar8 = *(float *)(this + 0x170) + 0.2;
    iVar2 = *(int *)(this + 0x710);
    *(uint *)(iVar6 + 0x194) = *(uint *)(iVar6 + 0x194) & 0xffffffdf;
    uVar3 = *(uint *)(iVar2 + 0x194);
    *(float *)(this + 0x170) = fVar8;
    if (0.9 <= fVar8) {
      fVar8 = 1.0;
      *(undefined4 *)(this + 0x170) = 0x3f800000;
    }
    if ((uVar3 & 0x20) == 0) goto LAB_00060320;
LAB_00060250:
    fVar8 = fVar8 - 0.2;
    uVar3 = uVar3 & 0xffffffdf;
    *(uint *)(iVar2 + 0x194) = uVar3;
    *(float *)(this + 0x170) = fVar8;
    if (0.1 < fVar8) goto LAB_00060320;
    fVar8 = 0.0;
    *(undefined4 *)(this + 0x170) = 0;
  }
  uVar3 = uVar3 | 0x8000;
  *(uint *)(iVar2 + 0x194) = uVar3;
LAB_00060284:
  bVar1 = fVar8 == 1.0;
  iVar2 = *(int *)(this + 0x718);
  if (bVar1) {
    uVar3 = *(uint *)(iVar6 + 0x194);
  }
  if (!bVar1) {
    uVar3 = *(uint *)(iVar6 + 0x194);
  }
  *(undefined4 *)(iVar2 + 0x204) = *(undefined4 *)(this + 0x204);
  if (bVar1) {
    uVar3 = uVar3 | 0x8000;
  }
  uVar9 = *(undefined4 *)(this + 0x200);
  if (bVar1) {
    *(uint *)(iVar6 + 0x194) = uVar3;
  }
  else {
    *(uint *)(iVar6 + 0x194) = uVar3 & 0xffff7fff;
  }
  *(undefined4 *)(iVar2 + 0x200) = uVar9;
  uVar9 = *(undefined4 *)(this + 0x1d4);
  uVar4 = *(undefined4 *)(this + 0x1d8);
  uVar7 = *(undefined4 *)(this + 0x1dc);
  *(undefined4 *)(iVar2 + 0x1d0) = *(undefined4 *)(this + 0x1d0);
  *(undefined4 *)(iVar2 + 0x1d4) = uVar9;
  *(undefined4 *)(iVar2 + 0x1d8) = uVar4;
  *(undefined4 *)(iVar2 + 0x1dc) = uVar7;
  sprintf((char *)(iVar2 + 0x2c4),"%02i%%",(int)(fVar8 * 100.0 + 0.1));
  return;
}
