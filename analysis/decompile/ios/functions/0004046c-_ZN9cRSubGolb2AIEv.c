/*
 * mangled: _ZN9cRSubGolb2AIEv
 * demangled: cRSubGolb::AI()
 * address: 0004046c
 * size: 3520
 */

/* cRSubGolb::AI() */

void __thiscall cRSubGolb::AI(cRSubGolb *this)

{
  cRSubLoc *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  tVector *ptVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  cRSubGolb *pcVar10;
  bool bVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;

  if (*(char *)(*(int *)(this + 0x250) + 0x12) != '\0') {
    return;
  }
  uVar5 = (uint)(byte)this[0x19c];
  bVar11 = uVar5 != 0;
  if (bVar11) {
    this[0x19c] = (cRSubGolb)0x0;
  }
  else {
    uVar5 = *(uint *)(this + 0x224);
  }
  if (bVar11 || uVar5 != 1) {
    return;
  }
  if (this[0x29c] == (cRSubGolb)0x0) {
    *(float *)(this + 0x1d4) = *(float *)(this + 0x1d4) + *(float *)(this + 0x22c);
    fVar12 = *(float *)(this + 0x1d8) + *(float *)(this + 0x230);
    *(float *)(this + 0x1d8) = fVar12;
    *(float *)(this + 0x1dc) = *(float *)(this + 0x1dc) + *(float *)(this + 0x234);
    if (*(int *)(this + 0x1a0) == 0) {
      if ((0.49 < fVar12) || (fVar12 < 0.0)) {
        *(float *)(this + 0x230) =
             *(float *)(this + 0x230) + *(float *)(*(int *)(this + 0x250) + 0x4c) * -0.017;
      }
      else {
        *(undefined4 *)(this + 0x230) = 0;
      }
    }
    else if ((*(int *)(this + 0x1a0) == 2) && (*(int *)(this + 0x174) != 0)) {
      fVar9 = *(float *)(this + 0x188);
      fVar12 = 1.0;
      *(float *)(this + 0x188) = fVar9 + *(float *)(this + 0x18c);
      if (1.0 < fVar9 + *(float *)(this + 0x18c)) {
        *(undefined4 *)(this + 0x188) = 0x3f800000;
      }
      fVar9 = (float)tVector::Normalize((tVector *)(this + 0x22c));
      local_3c = *(float *)(this + 0x178) - *(float *)(this + 0x1d4);
      local_38 = *(float *)(this + 0x17c) - *(float *)(this + 0x1d8);
      local_34 = *(float *)(this + 0x180) - *(float *)(this + 0x1dc);
      fVar15 = (float)tVector::Normalize((tVector *)&local_3c);
      if (fVar15 < 0.4) {
        local_54 = *(float *)(this + 0x1d4);
        local_50 = *(float *)(this + 0x1d8);
        local_4c = *(float *)(this + 0x1dc);
        if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
          iVar7 = cRSpriteManager::New
                            ((int)PTR__gRSpriteManager_001b61e4,
                             *(int *)(*(int *)(this + 600) + 0x370),0x13,-1);
          *(float *)(iVar7 + 100) = fVar12;
          *(undefined4 *)(iVar7 + 0x68) = 0;
          *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
          *(undefined4 *)(iVar7 + 0x70) = 0;
          *(undefined4 *)(iVar7 + 0x5c) = 0;
          *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
          *(undefined4 *)(iVar7 + 0x54) = 0;
          *(undefined4 *)(iVar7 + 0x78) = 0;
          *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
          *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
          *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
          *(float *)(iVar7 + 0x48) = local_54;
          *(float *)(iVar7 + 0x4c) = local_50;
          *(float *)(iVar7 + 0x50) = local_4c;
        }
        goto LAB_00040634;
      }
      fVar15 = *(float *)(this + 0x188);
      fVar12 = fVar12 + fVar15 * -1.5;
      *(float *)(this + 0x22c) = fVar15 * local_3c + fVar12 * *(float *)(this + 0x22c);
      *(float *)(this + 0x230) = fVar15 * local_38 + fVar12 * *(float *)(this + 0x230);
      *(float *)(this + 0x234) = fVar15 * local_34 + fVar12 * *(float *)(this + 0x234);
      tVector::Normalize((tVector *)(this + 0x22c));
      *(float *)(this + 0x22c) = *(float *)(this + 0x22c) * fVar9;
      *(float *)(this + 0x230) = *(float *)(this + 0x230) * fVar9;
      *(float *)(this + 0x234) = *(float *)(this + 0x234) * fVar9;
      if (fVar9 < 0.1) goto LAB_00040634;
    }
    ptVar6 = (tVector *)(this + 0x1d4);
    *(undefined4 *)(this + 0x28c) = *(undefined4 *)ptVar6;
    *(undefined4 *)(this + 0x290) = *(undefined4 *)(this + 0x1d8);
    *(undefined4 *)(this + 0x294) = *(undefined4 *)(this + 0x1dc);
    if (*(float *)(this + 0x2c4) < *(float *)(this + 0x294)) {
      fVar12 = 1.0;
      if ((*(float *)(this + 0x1d8) < 1.0) && (0.0 < *(float *)(this + 0x1d8))) {
        pcVar1 = (cRSubLoc *)
                 cRSubGame::LocFromPos
                           (*(undefined4 *)(this + 0x250),*(undefined4 *)(this + 0x28c),
                            *(undefined4 *)(this + 0x290),*(undefined4 *)(this + 0x294));
        if (pcVar1[0x30] == (cRSubLoc)0x1e) {
          *(undefined4 *)(this + 0x2c4) = *(undefined4 *)(this + 0x294);
          cRPathFollowGolb::Init((cRPathFollowGolb *)(this + 0x29c),pcVar1,ptVar6,this);
        }
        if ((fVar12 < *(float *)(this + 0x234)) && (pcVar1[-0x1f0] == (cRSubLoc)0x1e)) {
          *(float *)(this + 0x2c4) = *(float *)(this + 0x294) + fVar12;
          cRPathFollowGolb::Init((cRPathFollowGolb *)(this + 0x29c),pcVar1 + -0x220,ptVar6,this);
        }
      }
    }
  }
  else {
    uVar2 = cRPathFollowGolb::Traverse
                      ((cRPathFollowGolb *)(this + 0x29c),*(float *)(this + 0x244),
                       (tVector *)(this + 0x1d4),(tVector *)(this + 0x22c));
    switch(uVar2) {
    case 0:
    case 2:
      *(undefined4 *)(this + 0x28c) = *(undefined4 *)(this + 0x2b4);
      *(undefined4 *)(this + 0x290) = *(undefined4 *)(this + 0x2b8);
      *(undefined4 *)(this + 0x294) = *(undefined4 *)(this + 700);
      break;
    case 1:
    case 3:
      *(undefined4 *)(this + 0x28c) = *(undefined4 *)(this + 0x1d4);
      *(undefined4 *)(this + 0x290) = *(undefined4 *)(this + 0x1d8);
      *(undefined4 *)(this + 0x294) = *(undefined4 *)(this + 0x1dc);
    }
  }
  pcVar10 = this + 0x28c;
  iVar7 = *(int *)(this + 0x1a0);
  if (iVar7 == 1) {
    cRVapour::Add((cRVapour *)(this + 0x74),(tMatrix *)(this + 0x25c));
    iVar7 = *(int *)(this + 0x1a0);
  }
  else if (iVar7 == 2) {
    fVar9 = *(float *)(this + 400) + *(float *)(this + 0x194);
    *(undefined4 *)(this + 300) = *(undefined4 *)(this + 0x25c);
    *(undefined4 *)(this + 0x130) = *(undefined4 *)(this + 0x260);
    *(undefined4 *)(this + 0x134) = *(undefined4 *)(this + 0x264);
    *(undefined4 *)(this + 0x138) = *(undefined4 *)(this + 0x268);
    *(undefined4 *)(this + 0x13c) = *(undefined4 *)(this + 0x26c);
    *(undefined4 *)(this + 0x140) = *(undefined4 *)(this + 0x270);
    *(undefined4 *)(this + 0x144) = *(undefined4 *)(this + 0x274);
    *(undefined4 *)(this + 0x148) = *(undefined4 *)(this + 0x278);
    *(undefined4 *)(this + 0x14c) = *(undefined4 *)(this + 0x27c);
    *(undefined4 *)(this + 0x150) = *(undefined4 *)(this + 0x280);
    *(undefined4 *)(this + 0x154) = *(undefined4 *)(this + 0x284);
    *(undefined4 *)(this + 0x158) = *(undefined4 *)(this + 0x288);
    *(undefined4 *)(this + 0x15c) = *(undefined4 *)(this + 0x28c);
    *(undefined4 *)(this + 0x160) = *(undefined4 *)(this + 0x290);
    *(undefined4 *)(this + 0x164) = *(undefined4 *)(this + 0x294);
    *(undefined4 *)(this + 0x168) = *(undefined4 *)(this + 0x298);
    *(float *)(this + 400) = fVar9;
    fVar12 = fVar9;
    if (6.2831855 < fVar9) {
      fVar12 = fVar9 - 6.2831855;
    }
    iVar8 = *(int *)(this + 0x198);
    if (6.2831855 < fVar9) {
      *(float *)(this + 400) = fVar12;
    }
    if (iVar8 == 0) {
      local_54 = *(float *)pcVar10;
      local_50 = *(float *)(this + 0x290);
      local_4c = *(float *)(this + 0x294);
      fVar16 = 0.16666667;
      fVar17 = 0.4166667;
      fVar14 = 0.5;
      iVar7 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,*(int *)(*(int *)(this + 600) + 0x370),
                         0x74,-1);
      fVar13 = 0.4;
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
      *(undefined4 *)(iVar7 + 0x68) = 0;
      fVar12 = *(float *)(*(int *)(this + 0x250) + 0x4c);
      *(undefined4 *)(iVar7 + 0x70) = 0;
      *(float *)(iVar7 + 0x6c) = fVar12 * fVar16;
      *(float *)(iVar7 + 0x74) = *(float *)(*(int *)(this + 0x250) + 0x4c) * fVar17;
      tColour::tColour((tColour *)&local_64,1.0,1.0,1.0,1.0);
      *(float *)(iVar7 + 100) = fVar14;
      *(undefined4 *)(iVar7 + 0x2c) = local_64;
      *(undefined4 *)(iVar7 + 0x30) = uStack_60;
      *(undefined4 *)(iVar7 + 0x34) = uStack_5c;
      *(undefined4 *)(iVar7 + 0x38) = uStack_58;
      *(undefined4 *)(iVar7 + 0x60) = 0x3dcccccd;
      fVar12 = *(float *)(this + 0x22c);
      fVar9 = *(float *)(this + 0x230);
      fVar15 = *(float *)(this + 0x234);
      *(undefined4 *)(iVar7 + 0x78) = 0;
      *(float *)(iVar7 + 0x54) = fVar12 * fVar13;
      *(float *)(iVar7 + 0x58) = fVar9 * fVar13;
      *(float *)(iVar7 + 0x5c) = fVar15 * fVar13;
      *(float *)(iVar7 + 0x48) = local_54;
      *(float *)(iVar7 + 0x4c) = local_50;
      *(float *)(iVar7 + 0x50) = local_4c;
      local_54 = *(float *)(this + 0x28c) - *(float *)(this + 0x238) * fVar14;
      local_50 = *(float *)(this + 0x290) - *(float *)(this + 0x23c) * fVar14;
      local_4c = *(float *)(this + 0x294) - *(float *)(this + 0x240) * fVar14;
      iVar7 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,*(int *)(*(int *)(this + 600) + 0x370),
                         0x74,-1);
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
      *(undefined4 *)(iVar7 + 0x68) = 0;
      fVar12 = *(float *)(*(int *)(this + 0x250) + 0x4c);
      *(undefined4 *)(iVar7 + 0x70) = 0;
      *(float *)(iVar7 + 0x6c) = fVar12 * fVar16;
      *(float *)(iVar7 + 0x74) = *(float *)(*(int *)(this + 0x250) + 0x4c) * fVar17;
      tColour::tColour((tColour *)&local_74,1.0,1.0,1.0,1.0);
      *(float *)(iVar7 + 100) = fVar14;
      *(undefined4 *)(iVar7 + 0x2c) = local_74;
      *(undefined4 *)(iVar7 + 0x30) = uStack_70;
      *(undefined4 *)(iVar7 + 0x34) = uStack_6c;
      *(undefined4 *)(iVar7 + 0x38) = uStack_68;
      *(undefined4 *)(iVar7 + 0x60) = 0x3dcccccd;
      fVar12 = *(float *)(this + 0x22c);
      fVar9 = *(float *)(this + 0x230);
      fVar15 = *(float *)(this + 0x234);
      *(undefined4 *)(iVar7 + 0x78) = 0;
      *(float *)(iVar7 + 0x54) = fVar12 * fVar13;
      *(float *)(iVar7 + 0x58) = fVar9 * fVar13;
      *(float *)(iVar7 + 0x5c) = fVar15 * fVar13;
      *(float *)(iVar7 + 0x48) = local_54;
      *(float *)(iVar7 + 0x4c) = local_50;
      *(float *)(iVar7 + 0x50) = local_4c;
      iVar7 = *(int *)(this + 0x1a0);
      iVar8 = *(int *)(this + 0x198);
    }
    *(int *)(this + 0x198) = (iVar8 + 1) % 4;
  }
  else if (iVar7 == 0) {
    iVar7 = *(int *)(this + 0x228);
    uVar2 = *(undefined4 *)(this + 0x290);
    uVar3 = *(undefined4 *)(this + 0x294);
    *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)pcVar10;
    *(undefined4 *)(iVar7 + 0x4c) = uVar2;
    *(undefined4 *)(iVar7 + 0x50) = uVar3;
    iVar7 = *(int *)(this + 0x1a0);
  }
  *(float *)(this + 0x238) = *(float *)(this + 0x28c) - *(float *)(this + 0x214);
  *(float *)(this + 0x23c) = *(float *)(this + 0x290) - *(float *)(this + 0x218);
  *(float *)(this + 0x240) = *(float *)(this + 0x294) - *(float *)(this + 0x21c);
  if (iVar7 == 2) {
    tMatrix::SetZDir((tMatrix *)(this + 300),(tVector *)(this + 0x238));
    tMatrix::RotLocalZ((tMatrix *)(this + 300),*(float *)(this + 400));
  }
  fVar12 = *(float *)(this + 0x248);
  *(undefined4 *)(this + 0x214) = *(undefined4 *)pcVar10;
  *(undefined4 *)(this + 0x218) = *(undefined4 *)(this + 0x290);
  *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x294);
  *(float *)(this + 0x248) = fVar12 + *(float *)(this + 0x24c);
  if (fVar12 + *(float *)(this + 0x24c) <= 1.0) {
    if ((*(float *)(&DAT_000027f4 + *(int *)(this + 600)) <= *(float *)(this + 0x1dc)) &&
       (*(float *)(this + 0x1dc) <= *(float *)(*(int *)(this + 600) + 100) + 48.0)) {
      iVar7 = *(int *)(this + 0x250);
      iVar8 = *(int *)(iVar7 + 0x5e88);
      if (iVar8 != 0) {
        do {
          if (*(int *)(iVar8 + 0x78) == 1) {
            local_48 = *(float *)(iVar8 + 0x5c) - *(float *)(this + 0x28c);
            local_44 = *(float *)(iVar8 + 0x60) - *(float *)(this + 0x290);
            local_40 = *(float *)(iVar8 + 100) - *(float *)(this + 0x294);
            if (local_40 < 0.0) {
              bVar11 = -3.0 < local_40;
            }
            else if (3.0 <= local_40) {
              bVar11 = false;
            }
            else {
              bVar11 = true;
            }
            if ((bVar11) &&
               (fVar12 = (float)tVector::Normalize((tVector *)&local_48),
               fVar12 < *(float *)(iVar8 + 0x90) + 0.49)) {
              uVar2 = 2;
              *(undefined4 *)(iVar8 + 0x78) = 2;
              if (0.0 <= local_48) {
                uVar2 = 1;
              }
              *(undefined4 *)(iVar8 + 0x7c) = uVar2;
              cRSubGoldy::ScoreAdd(*(cRSubGoldy **)(this + 600),0,0);
              if (*(int *)(this + 0x1a0) != 1) {
                Kill(this);
                local_54 = *(float *)pcVar10;
                local_50 = *(float *)(this + 0x290);
                local_4c = *(float *)(this + 0x294);
                if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
                  iVar7 = cRSpriteManager::New
                                    ((int)PTR__gRSpriteManager_001b61e4,
                                     *(int *)(*(int *)(this + 600) + 0x370),0x13,-1);
                  *(undefined4 *)(iVar7 + 0x68) = 0;
                  *(undefined4 *)(iVar7 + 0x70) = 0;
                  *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
                  *(undefined4 *)(iVar7 + 0x5c) = 0;
                  *(undefined4 *)(iVar7 + 0x54) = 0;
                  *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
                  *(undefined4 *)(iVar7 + 0x78) = 0;
                  *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
                  *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
                  *(undefined4 *)(iVar7 + 100) = 0x3f800000;
                  *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
                  *(float *)(iVar7 + 0x48) = local_54;
                  *(float *)(iVar7 + 0x4c) = local_50;
                  *(float *)(iVar7 + 0x50) = local_4c;
                }
                if (*(int *)(this + 0x1a0) != 2) {
                  return;
                }
                for (iVar7 = *(int *)(*(int *)(this + 0x250) + 0x5e88); iVar7 != 0;
                    iVar7 = *(int *)(iVar7 + 0x74)) {
                  if (*(int *)(iVar7 + 0x78) == 1) {
                    local_48 = *(float *)(iVar7 + 0x5c) - *(float *)(this + 0x28c);
                    local_44 = *(float *)(iVar7 + 0x60) - *(float *)(this + 0x290);
                    local_40 = *(float *)(iVar7 + 100) - *(float *)(this + 0x294);
                    fVar12 = (float)tVector::Normalize((tVector *)&local_48);
                    if (fVar12 < 3.0) {
                      uVar2 = 2;
                      *(undefined4 *)(iVar7 + 0x78) = 2;
                      if (0.0 <= local_48) {
                        uVar2 = 1;
                      }
                      *(undefined4 *)(iVar7 + 0x7c) = uVar2;
                      cRSubGoldy::ScoreAdd(*(cRSubGoldy **)(this + 600),0,0);
                    }
                  }
                }
                return;
              }
            }
          }
          iVar8 = *(int *)(iVar8 + 0x74);
        } while (iVar8 != 0);
        iVar7 = *(int *)(this + 0x250);
      }
      iVar8 = 0;
      do {
        iVar4 = iVar8 * 0xe0 + iVar7;
        if (*(int *)(iVar4 + 0x2da4) == 4 || *(int *)(iVar4 + 0x2da4) == 1) {
          local_48 = *(float *)((int)&DAT_00002d8c + iVar4) - *(float *)(this + 0x28c);
          local_44 = *(float *)(tColour::tColour + iVar4) - *(float *)(this + 0x290);
          local_40 = *(float *)(tColourSmall::tColourSmall + iVar4) - *(float *)(this + 0x294);
          if (local_40 < 0.0) {
            bVar11 = -2.5 < local_40;
          }
          else if (2.5 <= local_40) {
            bVar11 = false;
          }
          else {
            bVar11 = true;
          }
          if (bVar11) {
            fVar12 = (float)tVector::Normalize((tVector *)&local_48);
            if (fVar12 < 2.5) {
              this[0x29c] = (cRSubGolb)0x0;
              fVar12 = (float)tVector::Normalize((tVector *)(this + 0x22c));
              local_44 = 0.0;
              tVector::Normalize((tVector *)&local_48);
              iVar7 = *(int *)(this + 0x1a0);
              *(undefined4 *)(this + 0x230) = 0;
              *(float *)(this + 0x22c) = -(local_48 * fVar12);
              *(float *)(this + 0x234) = -(local_40 * fVar12);
              if (iVar7 == 1) {
                Kill(this);
                local_54 = *(float *)pcVar10;
                local_50 = *(float *)(this + 0x290);
                local_4c = *(float *)(this + 0x294);
                if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
                  iVar7 = cRSpriteManager::New
                                    ((int)PTR__gRSpriteManager_001b61e4,
                                     *(int *)(*(int *)(this + 600) + 0x370),0x13,-1);
                  *(undefined4 *)(iVar7 + 0x68) = 0;
                  *(undefined4 *)(iVar7 + 0x70) = 0;
                  *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
                  *(undefined4 *)(iVar7 + 0x5c) = 0;
                  *(undefined4 *)(iVar7 + 0x54) = 0;
                  *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
                  *(undefined4 *)(iVar7 + 0x78) = 0;
                  *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
                  *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
                  *(undefined4 *)(iVar7 + 100) = 0x3f800000;
                  *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
                  *(float *)(iVar7 + 0x48) = local_54;
                  *(float *)(iVar7 + 0x4c) = local_50;
                  *(float *)(iVar7 + 0x50) = local_4c;
                }
                cRSlug::Hit((cRSlug *)(iVar8 * 0xe0 + 0x2d30 + *(int *)(this + 0x250)),2);
                return;
              }
              if (iVar7 == 2) {
                Kill(this);
                local_54 = *(float *)pcVar10;
                local_50 = *(float *)(this + 0x290);
                local_4c = *(float *)(this + 0x294);
                if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
                  iVar7 = cRSpriteManager::New
                                    ((int)PTR__gRSpriteManager_001b61e4,
                                     *(int *)(*(int *)(this + 600) + 0x370),0x13,-1);
                  *(undefined4 *)(iVar7 + 0x68) = 0;
                  *(undefined4 *)(iVar7 + 0x70) = 0;
                  *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
                  *(undefined4 *)(iVar7 + 0x5c) = 0;
                  *(undefined4 *)(iVar7 + 0x54) = 0;
                  *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
                  *(undefined4 *)(iVar7 + 0x78) = 0;
                  *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
                  *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
                  *(undefined4 *)(iVar7 + 100) = 0x3f800000;
                  *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
                  *(float *)(iVar7 + 0x48) = local_54;
                  *(float *)(iVar7 + 0x4c) = local_50;
                  *(float *)(iVar7 + 0x50) = local_4c;
                }
                cRSlug::Hit((cRSlug *)(iVar8 * 0xe0 + 0x2d30 + *(int *)(this + 0x250)),4);
                return;
              }
              if (iVar7 == 0) {
                if (this[0x19d] == (cRSubGolb)0x0) {
                  this[0x19d] = (cRSubGolb)0x1;
                  return;
                }
                Kill(this);
                local_54 = *(float *)pcVar10;
                local_50 = *(float *)(this + 0x290);
                local_4c = *(float *)(this + 0x294);
                if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) == 0) {
                  return;
                }
                iVar7 = cRSpriteManager::New
                                  ((int)PTR__gRSpriteManager_001b61e4,
                                   *(int *)(*(int *)(this + 600) + 0x370),0x13,-1);
                *(undefined4 *)(iVar7 + 0x68) = 0;
                *(undefined4 *)(iVar7 + 0x70) = 0;
                *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
                *(undefined4 *)(iVar7 + 0x5c) = 0;
                *(undefined4 *)(iVar7 + 0x54) = 0;
                *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
                *(undefined4 *)(iVar7 + 0x78) = 0;
                *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
                *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
                *(undefined4 *)(iVar7 + 100) = 0x3f800000;
                *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
                *(float *)(iVar7 + 0x48) = local_54;
                *(float *)(iVar7 + 0x4c) = local_50;
                *(float *)(iVar7 + 0x50) = local_4c;
                return;
              }
            }
            iVar7 = *(int *)(this + 0x250);
          }
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 0x10);
      iVar7 = cRSubGame::LocFromPos
                        (iVar7,*(undefined4 *)pcVar10,*(undefined4 *)(this + 0x290),
                         *(undefined4 *)(this + 0x294));
      if (*(char *)(iVar7 + 0x30) != '\x0e') {
        return;
      }
      fVar12 = *(float *)(this + 0x290);
      if (fVar12 <= -1.0) {
        return;
      }
      if (7.0 <= fVar12) {
        return;
      }
      fVar9 = *(float *)(this + 0x28c);
      fVar15 = *(float *)(this + 0x294);
      if ((*(uint *)(PTR__gConfig_001b60d4 + 0x1c) & 0x10) != 0) {
        iVar7 = cRSpriteManager::New
                          ((int)PTR__gRSpriteManager_001b61e4,*(int *)(*(int *)(this + 600) + 0x370)
                           ,0x13,-1);
        *(undefined4 *)(iVar7 + 100) = 0x3f800000;
        local_4c = fVar15 - 1.0;
        *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
        *(undefined4 *)(iVar7 + 0x68) = 0;
        *(undefined4 *)(iVar7 + 0x70) = 0;
        *(undefined4 *)(iVar7 + 0x6c) = 0x3d638e39;
        *(undefined4 *)(iVar7 + 0x78) = 0;
        *(undefined4 *)(iVar7 + 0x5c) = 0;
        *(undefined4 *)(iVar7 + 0x74) = 0x3f555556;
        *(undefined4 *)(iVar7 + 0x60) = 0x3f000000;
        *(undefined4 *)(iVar7 + 0x54) = 0;
        *(undefined4 *)(iVar7 + 0x58) = 0x3d4ccccd;
        *(float *)(iVar7 + 0x48) = fVar9;
        *(float *)(iVar7 + 0x4c) = fVar12;
        *(float *)(iVar7 + 0x50) = local_4c;
        local_54 = fVar9;
        local_50 = fVar12;
      }
    }
  }
LAB_00040634:
  Kill(this);
  return;
}
