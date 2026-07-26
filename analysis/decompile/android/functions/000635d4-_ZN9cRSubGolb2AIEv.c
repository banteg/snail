/*
 * mangled: _ZN9cRSubGolb2AIEv
 * demangled: cRSubGolb::AI()
 * address: 000635d4
 * size: 2468
 */

/* cRSubGolb::AI() */

void cRSubGolb::AI(void)

{
  bool bVar1;
  cRSubGolb *in_r0;
  cRSubGoldy *pcVar2;
  cRSubLoc *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  tVector *ptVar7;
  int iVar8;
  cRSubGolb *pcVar9;
  int iVar10;
  float in_s0;
  float fVar11;
  float fVar12;
  float fVar13;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;

  if (*(char *)(*(int *)(in_r0 + 0x250) + 0x19) != '\0') {
    return;
  }
  if (in_r0[0x19c] != (cRSubGolb)0x0) {
    in_r0[0x19c] = (cRSubGolb)0x0;
    return;
  }
  if (*(int *)(in_r0 + 0x224) != 1) {
    return;
  }
  if (in_r0[0x29c] == (cRSubGolb)0x0) {
    *(float *)(in_r0 + 0x1d4) = *(float *)(in_r0 + 0x1d4) + *(float *)(in_r0 + 0x22c);
    fVar11 = *(float *)(in_r0 + 0x1d8) + *(float *)(in_r0 + 0x230);
    *(float *)(in_r0 + 0x1dc) = *(float *)(in_r0 + 0x1dc) + *(float *)(in_r0 + 0x234);
    *(float *)(in_r0 + 0x1d8) = fVar11;
    if (*(int *)(in_r0 + 0x1a0) == 0) {
      if ((0.49 < fVar11) || (fVar11 < 0.0)) {
        *(float *)(in_r0 + 0x230) =
             *(float *)(in_r0 + 0x230) + *(float *)(*(int *)(in_r0 + 0x250) + 0x54) * -0.017;
      }
      else {
        *(undefined4 *)(in_r0 + 0x230) = 0;
      }
    }
    else if ((*(int *)(in_r0 + 0x1a0) == 2) && (*(int *)(in_r0 + 0x174) != 0)) {
      fVar11 = *(float *)(in_r0 + 0x188);
      *(float *)(in_r0 + 0x188) = fVar11 + *(float *)(in_r0 + 0x18c);
      if (1.0 < fVar11 + *(float *)(in_r0 + 0x18c)) {
        *(undefined4 *)(in_r0 + 0x188) = 0x3f800000;
      }
      fVar11 = (float)tVector::Normalize((tVector *)(in_r0 + 0x22c));
      local_3c = *(float *)(in_r0 + 0x178) - *(float *)(in_r0 + 0x1d4);
      local_38 = *(float *)(in_r0 + 0x17c) - *(float *)(in_r0 + 0x1d8);
      local_34 = *(float *)(in_r0 + 0x180) - *(float *)(in_r0 + 0x1dc);
      fVar13 = (float)tVector::Normalize((tVector *)&local_3c);
      if (fVar13 < 0.4) {
        Explode();
        Kill(in_r0);
        return;
      }
      fVar13 = *(float *)(in_r0 + 0x188);
      fVar12 = fVar13 * -1.5 + 1.0;
      *(float *)(in_r0 + 0x234) = fVar13 * local_34 + fVar12 * *(float *)(in_r0 + 0x234);
      *(float *)(in_r0 + 0x230) = fVar13 * local_38 + fVar12 * *(float *)(in_r0 + 0x230);
      *(float *)(in_r0 + 0x22c) = fVar13 * local_3c + fVar12 * *(float *)(in_r0 + 0x22c);
      tVector::Normalize((tVector *)(in_r0 + 0x22c));
      *(float *)(in_r0 + 0x230) = *(float *)(in_r0 + 0x230) * fVar11;
      *(float *)(in_r0 + 0x22c) = *(float *)(in_r0 + 0x22c) * fVar11;
      *(float *)(in_r0 + 0x234) = *(float *)(in_r0 + 0x234) * fVar11;
      if (fVar11 < 0.1) goto LAB_00063acc;
    }
    ptVar7 = (tVector *)(in_r0 + 0x1d4);
    *(undefined4 *)(in_r0 + 0x28c) = *(undefined4 *)ptVar7;
    *(undefined4 *)(in_r0 + 0x290) = *(undefined4 *)(in_r0 + 0x1d8);
    *(undefined4 *)(in_r0 + 0x294) = *(undefined4 *)(in_r0 + 0x1dc);
    if (((*(float *)(in_r0 + 0x2c4) < *(float *)(in_r0 + 0x294)) &&
        (*(float *)(in_r0 + 0x1d8) < 1.0)) && (0.0 < *(float *)(in_r0 + 0x1d8))) {
      pcVar3 = (cRSubLoc *)
               cRSubGame::LocFromPos
                         (*(undefined4 *)(in_r0 + 0x250),*(undefined4 *)(in_r0 + 0x28c),
                          *(undefined4 *)(in_r0 + 0x290),*(undefined4 *)(in_r0 + 0x294));
      if (pcVar3[0x30] == (cRSubLoc)0x1e) {
        *(undefined4 *)(in_r0 + 0x2c4) = *(undefined4 *)(in_r0 + 0x294);
        cRPathFollowGolb::Init((cRPathFollowGolb *)(in_r0 + 0x29c),pcVar3,ptVar7,in_r0);
      }
      if ((1.0 < *(float *)(in_r0 + 0x234)) && (pcVar3[-0x210] == (cRSubLoc)0x1e)) {
        *(float *)(in_r0 + 0x2c4) = *(float *)(in_r0 + 0x294) + 1.0;
        cRPathFollowGolb::Init((cRPathFollowGolb *)(in_r0 + 0x29c),pcVar3 + -0x240,ptVar7,in_r0);
      }
    }
    goto switchD_000639f8_default;
  }
  uVar4 = cRPathFollowGolb::Traverse(in_s0,(tVector *)(in_r0 + 0x29c),*(tVector **)(in_r0 + 0x244));
  switch(uVar4) {
  case 0:
    break;
  case 1:
    goto LAB_00063e80;
  case 2:
    break;
  case 3:
LAB_00063e80:
    *(undefined4 *)(in_r0 + 0x28c) = *(undefined4 *)(in_r0 + 0x1d4);
    *(undefined4 *)(in_r0 + 0x290) = *(undefined4 *)(in_r0 + 0x1d8);
    *(undefined4 *)(in_r0 + 0x294) = *(undefined4 *)(in_r0 + 0x1dc);
  default:
    goto switchD_000639f8_default;
  }
  *(undefined4 *)(in_r0 + 0x28c) = *(undefined4 *)(in_r0 + 0x2b4);
  *(undefined4 *)(in_r0 + 0x290) = *(undefined4 *)(in_r0 + 0x2b8);
  *(undefined4 *)(in_r0 + 0x294) = *(undefined4 *)(in_r0 + 700);
switchD_000639f8_default:
  pcVar9 = in_r0 + 0x28c;
  iVar8 = *(int *)(in_r0 + 0x1a0);
  if (iVar8 == 1) {
    cRVapour::Add((cRVapour *)(in_r0 + 0x74),(tMatrix *)(in_r0 + 0x25c));
    iVar8 = *(int *)(in_r0 + 0x1a0);
  }
  else if (iVar8 == 2) {
    fVar13 = *(float *)(in_r0 + 400) + *(float *)(in_r0 + 0x194);
    *(undefined4 *)(in_r0 + 300) = *(undefined4 *)(in_r0 + 0x25c);
    *(undefined4 *)(in_r0 + 0x130) = *(undefined4 *)(in_r0 + 0x260);
    *(undefined4 *)(in_r0 + 0x134) = *(undefined4 *)(in_r0 + 0x264);
    *(undefined4 *)(in_r0 + 0x138) = *(undefined4 *)(in_r0 + 0x268);
    *(undefined4 *)(in_r0 + 0x13c) = *(undefined4 *)(in_r0 + 0x26c);
    *(undefined4 *)(in_r0 + 0x140) = *(undefined4 *)(in_r0 + 0x270);
    *(undefined4 *)(in_r0 + 0x144) = *(undefined4 *)(in_r0 + 0x274);
    *(undefined4 *)(in_r0 + 0x148) = *(undefined4 *)(in_r0 + 0x278);
    *(undefined4 *)(in_r0 + 0x14c) = *(undefined4 *)(in_r0 + 0x27c);
    *(undefined4 *)(in_r0 + 0x150) = *(undefined4 *)(in_r0 + 0x280);
    *(undefined4 *)(in_r0 + 0x154) = *(undefined4 *)(in_r0 + 0x284);
    *(undefined4 *)(in_r0 + 0x158) = *(undefined4 *)(in_r0 + 0x288);
    *(undefined4 *)(in_r0 + 0x15c) = *(undefined4 *)(in_r0 + 0x28c);
    *(undefined4 *)(in_r0 + 0x160) = *(undefined4 *)(in_r0 + 0x290);
    *(undefined4 *)(in_r0 + 0x164) = *(undefined4 *)(in_r0 + 0x294);
    *(undefined4 *)(in_r0 + 0x168) = *(undefined4 *)(in_r0 + 0x298);
    *(float *)(in_r0 + 400) = fVar13;
    fVar11 = fVar13;
    if (6.2831855 < fVar13) {
      fVar11 = fVar13 - 6.2831855;
    }
    iVar10 = *(int *)(in_r0 + 0x198);
    if (6.2831855 < fVar13) {
      *(float *)(in_r0 + 400) = fVar11;
    }
    if (iVar10 == 0) {
      Smoke();
      local_60 = *(float *)(in_r0 + 0x28c) - *(float *)(in_r0 + 0x238) * 0.5;
      local_58 = *(float *)(in_r0 + 0x294) - *(float *)(in_r0 + 0x240) * 0.5;
      local_5c = *(float *)(in_r0 + 0x290) - *(float *)(in_r0 + 0x23c) * 0.5;
      Smoke();
      iVar10 = *(int *)(in_r0 + 0x198);
      iVar8 = *(int *)(in_r0 + 0x1a0);
    }
    *(int *)(in_r0 + 0x198) = (iVar10 + 1) % 4;
  }
  else if (iVar8 == 0) {
    uVar4 = *(undefined4 *)(in_r0 + 0x290);
    uVar5 = *(undefined4 *)(in_r0 + 0x294);
    iVar8 = *(int *)(in_r0 + 0x228);
    *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)pcVar9;
    *(undefined4 *)(iVar8 + 0x4c) = uVar4;
    *(undefined4 *)(iVar8 + 0x50) = uVar5;
    Jet();
    local_48 = *(float *)(in_r0 + 0x28c) - *(float *)(in_r0 + 0x238) * 0.3;
    local_40 = *(float *)(in_r0 + 0x294) - *(float *)(in_r0 + 0x240) * 0.3;
    local_44 = *(float *)(in_r0 + 0x290) - *(float *)(in_r0 + 0x23c) * 0.3;
    Jet();
    local_54 = *(float *)(in_r0 + 0x28c) - *(float *)(in_r0 + 0x238) * 0.6;
    local_4c = *(float *)(in_r0 + 0x294) - *(float *)(in_r0 + 0x240) * 0.6;
    local_50 = *(float *)(in_r0 + 0x290) - *(float *)(in_r0 + 0x23c) * 0.6;
    Jet();
    iVar8 = *(int *)(in_r0 + 0x1a0);
  }
  *(float *)(in_r0 + 0x238) = *(float *)(in_r0 + 0x28c) - *(float *)(in_r0 + 0x214);
  *(float *)(in_r0 + 0x23c) = *(float *)(in_r0 + 0x290) - *(float *)(in_r0 + 0x218);
  *(float *)(in_r0 + 0x240) = *(float *)(in_r0 + 0x294) - *(float *)(in_r0 + 0x21c);
  if (iVar8 == 2) {
    fVar11 = (float)tMatrix::SetZDir((tMatrix *)(in_r0 + 300),(tVector *)(in_r0 + 0x238));
    tMatrix::RotLocalZ((tMatrix *)(in_r0 + 300),fVar11);
  }
  fVar11 = *(float *)(in_r0 + 0x248);
  *(undefined4 *)(in_r0 + 0x214) = *(undefined4 *)pcVar9;
  *(undefined4 *)(in_r0 + 0x218) = *(undefined4 *)(in_r0 + 0x290);
  *(undefined4 *)(in_r0 + 0x21c) = *(undefined4 *)(in_r0 + 0x294);
  *(float *)(in_r0 + 0x248) = fVar11 + *(float *)(in_r0 + 0x24c);
  if (fVar11 + *(float *)(in_r0 + 0x24c) <= 1.0) {
    if ((*(float *)(*(int *)(in_r0 + 600) + 0x27fc) <= *(float *)(in_r0 + 0x1dc)) &&
       (*(float *)(in_r0 + 0x1dc) <= *(float *)(*(int *)(in_r0 + 600) + 100) + 48.0)) {
      iVar8 = *(int *)(in_r0 + 0x250);
      iVar10 = *(int *)(iVar8 + 0x6500);
      if (iVar10 != 0) {
        do {
          if (*(int *)(iVar10 + 0x78) == 1) {
            local_64 = *(float *)(iVar10 + 100) - *(float *)(in_r0 + 0x294);
            local_6c = *(float *)(iVar10 + 0x5c) - *(float *)(in_r0 + 0x28c);
            local_68 = *(float *)(iVar10 + 0x60) - *(float *)(in_r0 + 0x290);
            if (0.0 <= local_64) {
              bVar1 = local_64 < 3.0;
            }
            else if (local_64 <= -3.0) {
              bVar1 = false;
            }
            else {
              bVar1 = true;
            }
            if ((bVar1) &&
               (fVar11 = (float)tVector::Normalize((tVector *)&local_6c),
               fVar11 < *(float *)(iVar10 + 0x90) + 0.49)) {
              *(undefined4 *)(iVar10 + 0x78) = 2;
              pcVar2 = *(cRSubGoldy **)(in_r0 + 600);
              if (0.0 <= local_6c) {
                uVar4 = 1;
              }
              else {
                uVar4 = 2;
              }
              *(undefined4 *)(iVar10 + 0x7c) = uVar4;
              cRSubGoldy::ScoreAdd(pcVar2,0,0);
              if (*(int *)(in_r0 + 0x1a0) != 1) {
                Kill(in_r0);
                Explode();
                if (*(int *)(in_r0 + 0x1a0) != 2) {
                  return;
                }
                for (iVar8 = *(int *)(*(int *)(in_r0 + 0x250) + 0x6500); iVar8 != 0;
                    iVar8 = *(int *)(iVar8 + 0x74)) {
                  if (*(int *)(iVar8 + 0x78) == 1) {
                    local_6c = *(float *)(iVar8 + 0x5c) - *(float *)(in_r0 + 0x28c);
                    local_64 = *(float *)(iVar8 + 100) - *(float *)(in_r0 + 0x294);
                    local_68 = *(float *)(iVar8 + 0x60) - *(float *)(in_r0 + 0x290);
                    fVar11 = (float)tVector::Normalize((tVector *)&local_6c);
                    if (fVar11 < 3.0) {
                      *(undefined4 *)(iVar8 + 0x78) = 2;
                      pcVar2 = *(cRSubGoldy **)(in_r0 + 600);
                      if (local_6c < 0.0) {
                        uVar4 = 2;
                      }
                      else {
                        uVar4 = 1;
                      }
                      *(undefined4 *)(iVar8 + 0x7c) = uVar4;
                      cRSubGoldy::ScoreAdd(pcVar2,0,0);
                    }
                  }
                }
                return;
              }
            }
          }
          iVar10 = *(int *)(iVar10 + 0x74);
        } while (iVar10 != 0);
        iVar8 = *(int *)(in_r0 + 0x250);
      }
      iVar10 = 0;
      do {
        iVar6 = iVar8 + iVar10 * 0xe0;
        if (*(int *)(iVar6 + 0x341c) == 1 || *(int *)(iVar6 + 0x341c) == 4) {
          local_64 = *(float *)(iVar6 + 0x340c) - *(float *)(in_r0 + 0x294);
          local_6c = *(float *)(iVar6 + 0x3404) - *(float *)(in_r0 + 0x28c);
          local_68 = *(float *)(iVar6 + 0x3408) - *(float *)(in_r0 + 0x290);
          if (local_64 < 0.0) {
            if (-2.5 < local_64) goto LAB_00063cd0;
          }
          else if (local_64 < 2.5) {
LAB_00063cd0:
            fVar11 = (float)tVector::Normalize((tVector *)&local_6c);
            if (fVar11 < 2.5) {
              in_r0[0x29c] = (cRSubGolb)0x0;
              fVar11 = (float)tVector::Normalize((tVector *)(in_r0 + 0x22c));
              local_68 = 0.0;
              tVector::Normalize((tVector *)&local_6c);
              iVar8 = *(int *)(in_r0 + 0x1a0);
              *(undefined4 *)(in_r0 + 0x230) = 0;
              *(float *)(in_r0 + 0x22c) = -(local_6c * fVar11);
              *(float *)(in_r0 + 0x234) = -(local_64 * fVar11);
              if (iVar8 == 1) {
                Kill(in_r0);
                Explode();
                iVar8 = *(int *)(in_r0 + 0x250);
                iVar6 = 2;
LAB_00063f80:
                cRSlug::Hit((cRSlug *)(iVar8 + iVar10 * 0xe0 + 0x33a8),iVar6);
                return;
              }
              if (iVar8 == 2) {
                Kill(in_r0);
                Explode();
                iVar8 = *(int *)(in_r0 + 0x250);
                iVar6 = 4;
                goto LAB_00063f80;
              }
              if (iVar8 == 0) {
                if (in_r0[0x19d] != (cRSubGolb)0x0) {
                  Kill(in_r0);
                  Explode();
                  return;
                }
                in_r0[0x19d] = (cRSubGolb)0x1;
                return;
              }
            }
            iVar8 = *(int *)(in_r0 + 0x250);
          }
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 != 0x10);
      iVar8 = cRSubGame::LocFromPos
                        (iVar8,*(undefined4 *)pcVar9,*(undefined4 *)(in_r0 + 0x290),
                         *(undefined4 *)(in_r0 + 0x294));
      if (*(char *)(iVar8 + 0x30) != '\x0e') {
        return;
      }
      if (*(float *)(in_r0 + 0x290) <= -1.0) {
        return;
      }
      if (7.0 <= *(float *)(in_r0 + 0x290)) {
        return;
      }
      Explode();
    }
  }
LAB_00063acc:
  Kill(in_r0);
  return;
}
