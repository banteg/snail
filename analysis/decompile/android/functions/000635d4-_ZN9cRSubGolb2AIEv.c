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
  float fVar2;
  cRSubGoldy *pcVar3;
  cRSubLoc *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  tVector *ptVar8;
  int iVar9;
  cRSubGolb *pcVar10;
  int iVar11;
  float in_s0;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
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
    fVar14 = *(float *)(in_r0 + 0x1d8) + *(float *)(in_r0 + 0x230);
    *(float *)(in_r0 + 0x1dc) = *(float *)(in_r0 + 0x1dc) + *(float *)(in_r0 + 0x234);
    *(float *)(in_r0 + 0x1d8) = fVar14;
    fVar12 = DAT_00063a64;
    if (*(int *)(in_r0 + 0x1a0) == 0) {
      if ((DAT_00063a24 < fVar14) || (fVar14 < 0.0)) {
        *(float *)(in_r0 + 0x230) =
             *(float *)(in_r0 + 0x230) + DAT_00063a28 * *(float *)(*(int *)(in_r0 + 0x250) + 0x54);
      }
      else {
        *(float *)(in_r0 + 0x230) = DAT_00063a60;
      }
    }
    else if ((*(int *)(in_r0 + 0x1a0) == 2) && (*(int *)(in_r0 + 0x174) != 0)) {
      fVar14 = *(float *)(in_r0 + 0x188);
      *(float *)(in_r0 + 0x188) = fVar14 + *(float *)(in_r0 + 0x18c);
      if (fVar12 < fVar14 + *(float *)(in_r0 + 0x18c)) {
        *(float *)(in_r0 + 0x188) = fVar12;
      }
      fVar12 = (float)tVector::Normalize((tVector *)(in_r0 + 0x22c));
      local_3c = *(float *)(in_r0 + 0x178) - *(float *)(in_r0 + 0x1d4);
      local_38 = *(float *)(in_r0 + 0x17c) - *(float *)(in_r0 + 0x1d8);
      local_34 = *(float *)(in_r0 + 0x180) - *(float *)(in_r0 + 0x1dc);
      fVar14 = (float)tVector::Normalize((tVector *)&local_3c);
      if (fVar14 < DAT_00063a48) {
        Explode();
        Kill(in_r0);
        return;
      }
      fVar14 = *(float *)(in_r0 + 0x188);
      fVar15 = DAT_00063a64 + fVar14 * DAT_00063a4c;
      *(float *)(in_r0 + 0x234) = fVar14 * local_34 + fVar15 * *(float *)(in_r0 + 0x234);
      *(float *)(in_r0 + 0x230) = fVar14 * local_38 + fVar15 * *(float *)(in_r0 + 0x230);
      *(float *)(in_r0 + 0x22c) = fVar14 * local_3c + fVar15 * *(float *)(in_r0 + 0x22c);
      tVector::Normalize((tVector *)(in_r0 + 0x22c));
      *(float *)(in_r0 + 0x230) = *(float *)(in_r0 + 0x230) * fVar12;
      fVar14 = DAT_00063a50;
      *(float *)(in_r0 + 0x22c) = *(float *)(in_r0 + 0x22c) * fVar12;
      *(float *)(in_r0 + 0x234) = *(float *)(in_r0 + 0x234) * fVar12;
      if (fVar12 < fVar14) goto LAB_00063acc;
    }
    ptVar8 = (tVector *)(in_r0 + 0x1d4);
    *(undefined4 *)(in_r0 + 0x28c) = *(undefined4 *)ptVar8;
    *(undefined4 *)(in_r0 + 0x290) = *(undefined4 *)(in_r0 + 0x1d8);
    *(undefined4 *)(in_r0 + 0x294) = *(undefined4 *)(in_r0 + 0x1dc);
    if (((*(float *)(in_r0 + 0x2c4) < *(float *)(in_r0 + 0x294)) &&
        (*(float *)(in_r0 + 0x1d8) < DAT_00063a64)) && (0.0 < *(float *)(in_r0 + 0x1d8))) {
      pcVar4 = (cRSubLoc *)
               cRSubGame::LocFromPos
                         (*(undefined4 *)(in_r0 + 0x250),*(undefined4 *)(in_r0 + 0x28c),
                          *(undefined4 *)(in_r0 + 0x290),*(undefined4 *)(in_r0 + 0x294));
      if (pcVar4[0x30] == (cRSubLoc)0x1e) {
        *(undefined4 *)(in_r0 + 0x2c4) = *(undefined4 *)(in_r0 + 0x294);
        cRPathFollowGolb::Init((cRPathFollowGolb *)(in_r0 + 0x29c),pcVar4,ptVar8,in_r0);
      }
      if ((DAT_00063a64 < *(float *)(in_r0 + 0x234)) && (pcVar4[-0x210] == (cRSubLoc)0x1e)) {
        *(float *)(in_r0 + 0x2c4) = *(float *)(in_r0 + 0x294) + DAT_00063a64;
        cRPathFollowGolb::Init((cRPathFollowGolb *)(in_r0 + 0x29c),pcVar4 + -0x240,ptVar8,in_r0);
      }
    }
    goto switchD_000639f8_default;
  }
  uVar5 = cRPathFollowGolb::Traverse(in_s0,(tVector *)(in_r0 + 0x29c),*(tVector **)(in_r0 + 0x244));
  switch(uVar5) {
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
  fVar12 = DAT_00063a5c;
  pcVar10 = in_r0 + 0x28c;
  iVar9 = *(int *)(in_r0 + 0x1a0);
  if (iVar9 == 1) {
    cRVapour::Add((cRVapour *)(in_r0 + 0x74),(tMatrix *)(in_r0 + 0x25c));
    iVar9 = *(int *)(in_r0 + 0x1a0);
  }
  else if (iVar9 == 2) {
    fVar15 = *(float *)(in_r0 + 400) + *(float *)(in_r0 + 0x194);
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
    *(float *)(in_r0 + 400) = fVar15;
    fVar14 = fVar15;
    if (fVar12 < fVar15) {
      fVar14 = fVar15 - fVar12;
    }
    iVar11 = *(int *)(in_r0 + 0x198);
    if (fVar12 < fVar15) {
      *(float *)(in_r0 + 400) = fVar14;
    }
    if (iVar11 == 0) {
      Smoke();
      local_60 = *(float *)(in_r0 + 0x28c) - DAT_00063fbc * *(float *)(in_r0 + 0x238);
      local_58 = *(float *)(in_r0 + 0x294) - DAT_00063fbc * *(float *)(in_r0 + 0x240);
      local_5c = *(float *)(in_r0 + 0x290) - DAT_00063fbc * *(float *)(in_r0 + 0x23c);
      Smoke();
      iVar11 = *(int *)(in_r0 + 0x198);
      iVar9 = *(int *)(in_r0 + 0x1a0);
    }
    *(int *)(in_r0 + 0x198) = (iVar11 + 1) % 4;
  }
  else if (iVar9 == 0) {
    uVar5 = *(undefined4 *)(in_r0 + 0x290);
    uVar6 = *(undefined4 *)(in_r0 + 0x294);
    iVar9 = *(int *)(in_r0 + 0x228);
    *(undefined4 *)(iVar9 + 0x48) = *(undefined4 *)pcVar10;
    *(undefined4 *)(iVar9 + 0x4c) = uVar5;
    *(undefined4 *)(iVar9 + 0x50) = uVar6;
    Jet();
    local_48 = *(float *)(in_r0 + 0x28c) - DAT_00063a2c * *(float *)(in_r0 + 0x238);
    local_40 = *(float *)(in_r0 + 0x294) - DAT_00063a2c * *(float *)(in_r0 + 0x240);
    local_44 = *(float *)(in_r0 + 0x290) - DAT_00063a2c * *(float *)(in_r0 + 0x23c);
    Jet();
    local_54 = *(float *)(in_r0 + 0x28c) - DAT_00063a30 * *(float *)(in_r0 + 0x238);
    local_4c = *(float *)(in_r0 + 0x294) - DAT_00063a30 * *(float *)(in_r0 + 0x240);
    local_50 = *(float *)(in_r0 + 0x290) - DAT_00063a30 * *(float *)(in_r0 + 0x23c);
    Jet();
    iVar9 = *(int *)(in_r0 + 0x1a0);
  }
  *(float *)(in_r0 + 0x238) = *(float *)(in_r0 + 0x28c) - *(float *)(in_r0 + 0x214);
  *(float *)(in_r0 + 0x23c) = *(float *)(in_r0 + 0x290) - *(float *)(in_r0 + 0x218);
  *(float *)(in_r0 + 0x240) = *(float *)(in_r0 + 0x294) - *(float *)(in_r0 + 0x21c);
  if (iVar9 == 2) {
    fVar12 = (float)tMatrix::SetZDir((tMatrix *)(in_r0 + 300),(tVector *)(in_r0 + 0x238));
    tMatrix::RotLocalZ((tMatrix *)(in_r0 + 300),fVar12);
  }
  fVar2 = DAT_00063a64;
  fVar13 = *(float *)(in_r0 + 0x248);
  *(undefined4 *)(in_r0 + 0x214) = *(undefined4 *)pcVar10;
  *(undefined4 *)(in_r0 + 0x218) = *(undefined4 *)(in_r0 + 0x290);
  *(undefined4 *)(in_r0 + 0x21c) = *(undefined4 *)(in_r0 + 0x294);
  *(float *)(in_r0 + 0x248) = fVar13 + *(float *)(in_r0 + 0x24c);
  fVar15 = DAT_00063a3c;
  fVar14 = DAT_00063a38;
  fVar12 = DAT_00063a24;
  if (fVar13 + *(float *)(in_r0 + 0x24c) <= fVar2) {
    if ((*(float *)(*(int *)(in_r0 + 600) + 0x27fc) <= *(float *)(in_r0 + 0x1dc)) &&
       (*(float *)(in_r0 + 0x1dc) <= DAT_00063a34 + *(float *)(*(int *)(in_r0 + 600) + 100))) {
      iVar9 = *(int *)(in_r0 + 0x250);
      iVar11 = *(int *)(iVar9 + 0x6500);
      if (iVar11 != 0) {
        do {
          if (*(int *)(iVar11 + 0x78) == 1) {
            local_64 = *(float *)(iVar11 + 100) - *(float *)(in_r0 + 0x294);
            local_6c = *(float *)(iVar11 + 0x5c) - *(float *)(in_r0 + 0x28c);
            local_68 = *(float *)(iVar11 + 0x60) - *(float *)(in_r0 + 0x290);
            if (0.0 <= local_64) {
              bVar1 = local_64 < fVar14;
            }
            else if (local_64 <= fVar15) {
              bVar1 = false;
            }
            else {
              bVar1 = true;
            }
            if ((bVar1) &&
               (fVar2 = (float)tVector::Normalize((tVector *)&local_6c),
               fVar2 < fVar12 + *(float *)(iVar11 + 0x90))) {
              *(undefined4 *)(iVar11 + 0x78) = 2;
              pcVar3 = *(cRSubGoldy **)(in_r0 + 600);
              if (0.0 <= local_6c) {
                uVar5 = 1;
              }
              else {
                uVar5 = 2;
              }
              *(undefined4 *)(iVar11 + 0x7c) = uVar5;
              cRSubGoldy::ScoreAdd(pcVar3,0,0);
              if (*(int *)(in_r0 + 0x1a0) != 1) {
                Kill(in_r0);
                Explode();
                fVar12 = DAT_00063a38;
                if (*(int *)(in_r0 + 0x1a0) != 2) {
                  return;
                }
                for (iVar9 = *(int *)(*(int *)(in_r0 + 0x250) + 0x6500); iVar9 != 0;
                    iVar9 = *(int *)(iVar9 + 0x74)) {
                  if (*(int *)(iVar9 + 0x78) == 1) {
                    local_6c = *(float *)(iVar9 + 0x5c) - *(float *)(in_r0 + 0x28c);
                    local_64 = *(float *)(iVar9 + 100) - *(float *)(in_r0 + 0x294);
                    local_68 = *(float *)(iVar9 + 0x60) - *(float *)(in_r0 + 0x290);
                    fVar14 = (float)tVector::Normalize((tVector *)&local_6c);
                    if (fVar14 < fVar12) {
                      *(undefined4 *)(iVar9 + 0x78) = 2;
                      pcVar3 = *(cRSubGoldy **)(in_r0 + 600);
                      if (local_6c < 0.0) {
                        uVar5 = 2;
                      }
                      else {
                        uVar5 = 1;
                      }
                      *(undefined4 *)(iVar9 + 0x7c) = uVar5;
                      cRSubGoldy::ScoreAdd(pcVar3,0,0);
                    }
                  }
                }
                return;
              }
            }
          }
          iVar11 = *(int *)(iVar11 + 0x74);
        } while (iVar11 != 0);
        iVar9 = *(int *)(in_r0 + 0x250);
      }
      fVar15 = DAT_00063a60;
      fVar14 = DAT_00063a58;
      fVar12 = DAT_00063a54;
      iVar11 = 0;
      do {
        iVar7 = iVar9 + iVar11 * 0xe0;
        if (*(int *)(iVar7 + 0x341c) == 1 || *(int *)(iVar7 + 0x341c) == 4) {
          local_64 = *(float *)(iVar7 + 0x340c) - *(float *)(in_r0 + 0x294);
          local_6c = *(float *)(iVar7 + 0x3404) - *(float *)(in_r0 + 0x28c);
          local_68 = *(float *)(iVar7 + 0x3408) - *(float *)(in_r0 + 0x290);
          if (local_64 < 0.0) {
            if (fVar14 < local_64) goto LAB_00063cd0;
          }
          else if (local_64 < fVar12) {
LAB_00063cd0:
            fVar2 = (float)tVector::Normalize((tVector *)&local_6c);
            if (fVar2 < fVar12) {
              in_r0[0x29c] = (cRSubGolb)0x0;
              fVar2 = (float)tVector::Normalize((tVector *)(in_r0 + 0x22c));
              local_68 = fVar15;
              tVector::Normalize((tVector *)&local_6c);
              iVar9 = *(int *)(in_r0 + 0x1a0);
              *(float *)(in_r0 + 0x230) = fVar15;
              *(float *)(in_r0 + 0x22c) = -(local_6c * fVar2);
              *(float *)(in_r0 + 0x234) = -(local_64 * fVar2);
              if (iVar9 == 1) {
                Kill(in_r0);
                Explode();
                iVar9 = *(int *)(in_r0 + 0x250);
                iVar7 = 2;
LAB_00063f80:
                cRSlug::Hit((cRSlug *)(iVar9 + iVar11 * 0xe0 + 0x33a8),iVar7);
                return;
              }
              if (iVar9 == 2) {
                Kill(in_r0);
                Explode();
                iVar9 = *(int *)(in_r0 + 0x250);
                iVar7 = 4;
                goto LAB_00063f80;
              }
              if (iVar9 == 0) {
                if (in_r0[0x19d] != (cRSubGolb)0x0) {
                  Kill(in_r0);
                  Explode();
                  return;
                }
                in_r0[0x19d] = (cRSubGolb)0x1;
                return;
              }
            }
            iVar9 = *(int *)(in_r0 + 0x250);
          }
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 != 0x10);
      iVar9 = cRSubGame::LocFromPos
                        (iVar9,*(undefined4 *)pcVar10,*(undefined4 *)(in_r0 + 0x290),
                         *(undefined4 *)(in_r0 + 0x294));
      if (*(char *)(iVar9 + 0x30) != '\x0e') {
        return;
      }
      if (*(float *)(in_r0 + 0x290) <= DAT_00063a40) {
        return;
      }
      if (DAT_00063a44 <= *(float *)(in_r0 + 0x290)) {
        return;
      }
      Explode();
    }
  }
LAB_00063acc:
  Kill(in_r0);
  return;
}
