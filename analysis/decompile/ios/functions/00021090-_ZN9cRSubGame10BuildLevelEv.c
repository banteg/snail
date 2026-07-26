/*
 * mangled: _ZN9cRSubGame10BuildLevelEv
 * demangled: cRSubGame::BuildLevel()
 * address: 00021090
 * size: 7720
 */

/* cRSubGame::BuildLevel() */

void __thiscall cRSubGame::BuildLevel(cRSubGame *this)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  undefined *puVar4;
  cRSubGame *pcVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  cRSubGame *pcVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  cRSubGame cVar13;
  ushort uVar14;
  int iVar15;
  cRSubGame *pcVar16;
  int iVar17;
  uint uVar18;
  cRBod *this_00;
  bool bVar19;
  bool bVar20;
  uint in_fpscr;
  undefined4 uVar21;
  float fVar22;
  undefined8 uVar23;
  ulonglong uVar24;
  float fVar25;
  int local_78;
  int local_70;
  cRSubGame *local_6c;
  int local_68;
  int local_64;
  cRSubGame *local_5c;
  int local_58;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;

  if (this[0x2e09cc] == (cRSubGame)0x0) {
    iVar17 = *(int *)(this + 0x58);
    if (iVar17 == 7 || iVar17 == 4) {
      iVar15 = 0;
    }
    else {
      fVar6 = (float)RAND(32768.0,"Seed");
      iVar17 = *(int *)(this + 0x58);
      iVar15 = (int)fVar6;
    }
  }
  else {
    iVar17 = *(int *)(this + 0x58);
    iVar15 = *(int *)(*(int *)(this + 0x2e09d0) + 0x68);
  }
  if (iVar17 != 1) {
    if (iVar17 == 4) {
      cRSubSolution::ReSet
                (*(cRSubSolution **)(this + 0x2e09c8),iVar15,*(int *)(this + 0x5c),
                 *(float *)(this + 0x44),*(int *)(this + 100),2,*(int *)(this + 0x5c));
      goto LAB_00021108;
    }
    if (iVar17 != 0) goto LAB_00021108;
  }
  cRSubSolution::ReSet
            (*(cRSubSolution **)(this + 0x2e09c8),iVar15,*(int *)(this + 0x5c),
             *(float *)(this + 0x44),*(int *)(this + 100),iVar17,*(int *)(this + 0x5c));
LAB_00021108:
  *(undefined4 *)(this + 0x2e09d8) = 0;
  if (*(int *)(this + 0x303aa8) == 3) {
    *(undefined4 *)(this + 0x303aa8) = 1;
    *(undefined4 *)(this + 0xf714) = 0;
    *(undefined4 *)(this + 0xf740) = 0;
    iVar17 = 4;
    do {
      iVar10 = iVar17 + 4;
      *(undefined4 *)(this + iVar17 + 0xf740) = 0;
      iVar17 = iVar10;
    } while (iVar10 != 0x1c);
    if (*(int *)(this + 0x2f1dcc) == 0) {
      *(undefined4 *)(this + 0x13434) = 3;
    }
    else if (*(int *)(this + 0x2f1dcc) == 1) {
      *(undefined4 *)(this + 0x13434) = 8;
    }
  }
  *(undefined4 *)(this + 0xf718) = 0;
  *(undefined4 *)(this + 0xf72c) = 0;
  *(undefined4 *)(this + 0xf71c) = 0;
  *(undefined4 *)(this + 0xf730) = 0;
  *(undefined4 *)(this + 0xf720) = 0;
  *(undefined4 *)(this + 0xf724) = 0;
  *(undefined4 *)(this + 0xf728) = 0;
  *(undefined4 *)(this + 0xf738) = 0;
  RandSeed(iVar15);
  cRTrack::Change((cRTrack *)(*(int *)PTR__Game_001b60b8 + 0x848),*(int *)(this + 0x1300));
  iVar17 = *(int *)(this + 0x58);
  if (((iVar17 == 7 || iVar17 == 0) || (iVar17 == 4)) || (iVar17 == 1)) {
    *(int *)(this + 0x68) = *(int *)(this + 0x11d0);
    *(undefined4 *)(this + 0x6c) = *(undefined4 *)(this + 0x1250);
    if (iVar17 == 1) {
      fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x1250),(byte)(in_fpscr >> 0x16) & 3
                                        );
      *(int *)(this + 0x6c) = (int)(fVar6 * (*(float *)(this + 0x48) * 0.65 + 0.35));
    }
    if (this[0x1254] == (cRSubGame)0x0) {
      iVar17 = *(int *)(this + 0x11fc) + *(int *)(this + 0x11d0);
      *(int *)(this + 0x6c) = iVar17;
      if (0 < *(int *)(this + 0x98)) {
        iVar15 = 0;
        pcVar5 = this;
        do {
          iVar15 = iVar15 + 1;
          iVar17 = iVar17 + *(int *)(pcVar5 + 0xa0);
          *(int *)(this + 0x6c) = iVar17;
          pcVar5 = pcVar5 + 0x2c;
        } while (iVar15 < *(int *)(this + 0x98));
      }
    }
    else {
      iVar17 = *(int *)(this + 0x6c);
    }
    *(int *)(this + 0x70) = iVar17 - *(int *)(this + 0x11fc);
    if (0xd47 < iVar17) {
      RShellError("Track (%s) too long, Maximum Length %i",this + 0x1268,0xd48);
    }
  }
  else if (iVar17 == 3) {
    *(int *)(this + 0x68) = *(int *)(this + 0x11d0);
    iVar17 = 1;
    iVar15 = *(int *)(this + 0x11fc) + *(int *)(this + 0x11d0) + *(int *)(this + 0xa0);
    *(int *)(this + 0x6c) = iVar15;
    do {
      iVar17 = iVar17 + 1;
      iVar15 = iVar15 + *(int *)(this + 0xa0);
      *(int *)(this + 0x6c) = iVar15;
    } while (iVar17 != 0x10);
    *(int *)(this + 0x70) = iVar15 - *(int *)(this + 0x11fc);
  }
  this[0xf7f8] = (cRSubGame)0x0;
  this[2] = (cRSubGame)0x0;
  *(undefined4 *)(this + 4) = 0;
  local_40 = 0;
  local_48 = 0;
  local_44 = 0;
  do {
    *(undefined4 *)(this + local_48 + 0x1e41d8) = 0;
    *(undefined4 *)(this + local_48 + 0x1e4278) = 0;
    *(undefined4 *)(this + local_48 + 0x1e426c) = 0;
    *(undefined4 *)(this + local_48 + 0x1e42a8) = 0;
    *(undefined4 *)(this + local_48 + 0x1e4270) = 0;
    *(undefined4 *)(this + local_48 + 0x1e4264) = 0;
    *(undefined4 *)(this + local_48 + 0x1e4260) = 0;
    *(undefined4 *)(this + local_48 + 0x1e425c) = 0;
    *(undefined4 *)(this + local_48 + 0x1e4268) = 0;
    *(undefined4 *)(this + local_48 + 0x1e42ac) = 0;
    *(undefined4 *)(this + local_48 + 0x1e42b0) = 0;
    iVar17 = local_40 * 0x220;
    this[iVar17 + 0x1348b] = (cRSubGame)((byte)this[iVar17 + 0x1348b] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x1348a) = 0;
    this[local_44 + 0x13489] = (cRSubGame)0x0;
    this[iVar17 + 0x1348a] = (cRSubGame)((byte)this[iVar17 + 0x1348a] & 0xa7);
    this[iVar17 + 0x1348b] = (cRSubGame)((byte)this[iVar17 + 0x1348b] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x1348a) = 0;
    *(uint *)(this + local_44 + 0x1345c) = *(uint *)(this + local_44 + 0x1345c) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x13480));
    *(undefined4 *)(this + local_44 + 0x13474) = 0;
    *(undefined4 *)(this + local_44 + 0x13478) = 0;
    this[iVar17 + 0x134cf] = (cRSubGame)((byte)this[iVar17 + 0x134cf] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x134ce) = 0;
    this[local_44 + 0x134cd] = (cRSubGame)0x0;
    this[iVar17 + 0x134ce] = (cRSubGame)((byte)this[iVar17 + 0x134ce] & 0xa7);
    this[iVar17 + 0x134cf] = (cRSubGame)((byte)this[iVar17 + 0x134cf] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x134ce) = 0;
    *(uint *)(this + local_44 + 0x134a0) = *(uint *)(this + local_44 + 0x134a0) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x134c4));
    *(undefined4 *)(this + local_44 + 0x134b8) = 0;
    *(undefined4 *)(this + local_44 + 0x134bc) = 0;
    this[iVar17 + 0x13513] = (cRSubGame)((byte)this[iVar17 + 0x13513] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x13512) = 0;
    this[local_44 + 0x13511] = (cRSubGame)0x0;
    this[iVar17 + 0x13512] = (cRSubGame)((byte)this[iVar17 + 0x13512] & 0xa7);
    this[iVar17 + 0x13513] = (cRSubGame)((byte)this[iVar17 + 0x13513] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x13512) = 0;
    *(uint *)(this + local_44 + 0x134e4) = *(uint *)(this + local_44 + 0x134e4) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x13508));
    *(undefined4 *)(this + local_44 + 0x134fc) = 0;
    *(undefined4 *)(this + local_44 + 0x13500) = 0;
    this[iVar17 + 0x13557] = (cRSubGame)((byte)this[iVar17 + 0x13557] & 0x5f);
    this[local_44 + 0x13555] = (cRSubGame)0x0;
    *(undefined2 *)(this + local_44 + 0x13556) = 0;
    this[iVar17 + 0x13556] = (cRSubGame)((byte)this[iVar17 + 0x13556] & 0xa7);
    this[iVar17 + 0x13557] = (cRSubGame)((byte)this[iVar17 + 0x13557] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x13556) = 0;
    *(uint *)(this + local_44 + 0x13528) = *(uint *)(this + local_44 + 0x13528) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x1354c));
    *(undefined4 *)(this + local_44 + 0x13540) = 0;
    *(undefined4 *)(this + local_44 + 0x13544) = 0;
    this[iVar17 + 0x1359b] = (cRSubGame)((byte)this[iVar17 + 0x1359b] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x1359a) = 0;
    this[local_44 + 0x13599] = (cRSubGame)0x0;
    this[iVar17 + 0x1359a] = (cRSubGame)((byte)this[iVar17 + 0x1359a] & 0xa7);
    this[iVar17 + 0x1359b] = (cRSubGame)((byte)this[iVar17 + 0x1359b] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x1359a) = 0;
    *(uint *)(this + local_44 + 0x1356c) = *(uint *)(this + local_44 + 0x1356c) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x13590));
    *(undefined4 *)(this + local_44 + 0x13584) = 0;
    *(undefined4 *)(this + local_44 + 0x13588) = 0;
    this[iVar17 + 0x135df] = (cRSubGame)((byte)this[iVar17 + 0x135df] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x135de) = 0;
    this[local_44 + 0x135dd] = (cRSubGame)0x0;
    this[iVar17 + 0x135de] = (cRSubGame)((byte)this[iVar17 + 0x135de] & 0xa7);
    this[iVar17 + 0x135df] = (cRSubGame)((byte)this[iVar17 + 0x135df] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x135de) = 0;
    *(uint *)(this + local_44 + 0x135b0) = *(uint *)(this + local_44 + 0x135b0) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x135d4));
    *(undefined4 *)(this + local_44 + 0x135c8) = 0;
    *(undefined4 *)(this + local_44 + 0x135cc) = 0;
    this[iVar17 + 0x13623] = (cRSubGame)((byte)this[iVar17 + 0x13623] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x13622) = 0;
    this[local_44 + 0x13621] = (cRSubGame)0x0;
    this[iVar17 + 0x13622] = (cRSubGame)((byte)this[iVar17 + 0x13622] & 0xa7);
    this[iVar17 + 0x13623] = (cRSubGame)((byte)this[iVar17 + 0x13623] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x13622) = 0;
    *(uint *)(this + local_44 + 0x135f4) = *(uint *)(this + local_44 + 0x135f4) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x13618));
    *(undefined4 *)(this + local_44 + 0x1360c) = 0;
    *(undefined4 *)(this + local_44 + 0x13610) = 0;
    this[iVar17 + 0x13667] = (cRSubGame)((byte)this[iVar17 + 0x13667] & 0x5f);
    *(undefined2 *)(this + local_44 + 0x13666) = 0;
    this[local_44 + 0x13665] = (cRSubGame)0x0;
    this[iVar17 + 0x13666] = (cRSubGame)((byte)this[iVar17 + 0x13666] & 0xa7);
    this[iVar17 + 0x13667] = (cRSubGame)((byte)this[iVar17 + 0x13667] & 0xaf);
    *(undefined2 *)(this + local_44 + 0x13666) = 0;
    *(uint *)(this + local_44 + 0x13638) = *(uint *)(this + local_44 + 0x13638) & 0xffffff7f;
    tColourSmall::White((tColourSmall *)(this + iVar17 + 0x1365c));
    *(undefined4 *)(this + local_44 + 0x13650) = 0;
    pcVar5 = this + (int)(&PTR_caseD_6_00013458 + local_40 * 0x88);
    iVar17 = 0;
    *(undefined4 *)(this + local_44 + 0x13654) = 0;
    do {
      iVar17 = iVar17 + 1;
      iVar15 = 0;
      *(undefined4 *)(pcVar5 + 0x34) = 0;
      *(undefined4 *)(pcVar5 + 0x38) = 0;
      *(undefined4 *)(pcVar5 + 0x3c) = 0;
      *(undefined4 *)(pcVar5 + 0x40) = 0;
      pcVar5 = pcVar5 + 0x44;
    } while (iVar17 != 8);
    local_40 = local_40 + 1;
    local_48 = local_48 + 0xdc;
    local_44 = local_44 + 0x220;
  } while (local_40 != 0xdac);
  if ((this[0x1254] != (cRSubGame)0x0) && (pcVar5 = this, 0 < *(int *)(this + 0x98))) {
    do {
      pcVar5[0xa4] = (cRSubGame)0x0;
      iVar15 = iVar15 + 1;
      pcVar5 = pcVar5 + 0x2c;
    } while (iVar15 < *(int *)(this + 0x98));
  }
  uVar24 = 0;
  local_70 = 0;
  local_3c = 0;
  local_6c = (cRSubGame *)0x0;
  iVar17 = 0;
  local_68 = 0;
  bVar3 = false;
  if (0 < *(int *)(this + 0x6c)) {
    do {
      uVar18 = (uint)uVar24;
      bVar3 = (bool)(bVar3 ^ 1);
      if (uVar18 == 0) {
        local_5c = this + 0x11cc;
        local_64 = *(int *)(this + 0x11d0);
        *(undefined4 *)(this + 0x11cc) = 0;
        local_6c = (cRSubGame *)0x1;
      }
      else {
        uVar12 = *(uint *)(this + 0x70);
        bVar19 = uVar12 != uVar18;
        if (!bVar19) {
          uVar12 = (uint)(byte)this[0x1254];
        }
        if (bVar19 || uVar12 != 0) {
          *(undefined4 *)(this + 0x60) = 0x3f800000;
          if (this[0x1254] == (cRSubGame)0x0) {
            iVar17 = local_3c + 1;
            local_5c = this + local_3c * 0x2c + 0x9c;
          }
          else {
            iVar17 = local_3c;
            if (bVar3) {
              local_5c = this + 0x1224;
              *(uint *)(this + 0x1224) = uVar18;
              local_6c = (cRSubGame *)0x1;
            }
            else {
              if (*(int *)(this + 0x58) == 1) {
                fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x98),
                                                   (byte)(in_fpscr >> 0x16) & 3);
                fVar6 = (float)RAND(fVar6 * (*(float *)(this + 0x48) * 0.9 + 0.1),"Segdif");
              }
              else {
                fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x98),
                                                   (byte)(in_fpscr >> 0x16) & 3);
                fVar6 = (float)RAND(fVar6,"Segtra");
              }
              fVar6 = (float)VectorSignedToFloat((int)fVar6,(byte)(in_fpscr >> 0x16) & 3);
              iVar15 = (int)(fVar6 * *(float *)(this + 0x60)) * 0x2c;
              local_5c = this + iVar15 + 0x9c;
              this[iVar15 + 0xa4] = (cRSubGame)0x1;
            }
          }
          local_64 = *(int *)(local_5c + 4);
          local_3c = iVar17;
        }
        else {
          local_5c = this + 0x11f8;
          local_64 = *(int *)(this + 0x11fc);
          local_6c = (cRSubGame *)(uVar12 + 1);
          *(uint *)(this + 0x11f8) = uVar18;
        }
      }
      fVar6 = (float)RAND(1.0,"Mirror");
      uVar18 = in_fpscr & 0xfffffff | (uint)(fVar6 < 0.5) << 0x1f | (uint)(fVar6 == 0.5) << 0x1e;
      in_fpscr = uVar18 | (uint)NAN(fVar6) << 0x1c;
      bVar2 = (byte)(uVar18 >> 0x18);
      cVar13 = (cRSubGame)(!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1));
      if (this[2] == cVar13) {
        iVar17 = *(int *)(this + 4);
        *(int *)(this + 4) = iVar17 + 1;
        if (iVar17 + 1 < 4) goto LAB_0002175c;
        this[2] = (cRSubGame)((byte)this[2] ^ 1);
        *(undefined4 *)(this + 4) = 0;
        iVar17 = *(int *)(local_5c + 4);
        *(int *)local_5c = (int)uVar24;
      }
      else {
        *(undefined4 *)(this + 4) = 0;
LAB_0002175c:
        this[2] = cVar13;
        iVar17 = *(int *)(local_5c + 4);
        *(int *)local_5c = (int)uVar24;
      }
      pcVar5 = local_5c;
      if (iVar17 < 0) {
        pcVar5 = (cRSubGame *)RShellError("Negative Segment Length");
      }
      iVar17 = (int)uVar24;
      uVar18 = *(uint *)(this + 0x6c);
      if (0 < local_64 && iVar17 < (int)uVar18) {
        local_4c = local_64 + iVar17;
        pcVar16 = this + iVar17 * 0xdc + 0x1e4290;
        local_58 = 0;
        do {
          iVar17 = *(int *)(this + 0x58);
          iVar15 = (int)uVar24;
          if (iVar17 == 2) {
            local_78 = local_58 * 8;
            iVar10 = local_58 * 10;
          }
          else {
            iVar7 = *(int *)(this + 0x70);
            if (iVar15 < iVar7) {
              local_78 = local_58 * 8;
              iVar10 = local_58 * 10;
            }
            else {
              if (((iVar17 == 4 || iVar17 == 0) || (iVar17 == 1)) ||
                 ((iVar17 == 7 || (iVar17 == 3)))) {
                local_5c = this + 0x11f8;
              }
              else {
                local_5c = this + 0x1338;
              }
              if (iVar15 == iVar7) {
                iVar10 = 0;
                local_58 = 0;
                local_78 = 0;
              }
              else {
                local_78 = local_58 * 8;
                iVar10 = local_58 * 10;
              }
            }
            iVar11 = local_4c - local_58;
            if (iVar7 < iVar11) {
              pcVar5 = this + 0x1338;
              bVar19 = pcVar5 != local_5c;
              if (bVar19) {
                pcVar5 = this + 0x1390;
              }
              if (((bVar19 && pcVar5 != local_5c) && (this + 0x13bc != local_5c)) &&
                 (((iVar17 == 4 || iVar17 == 0 ||
                   (((iVar17 == 1 || (iVar17 == 7)) || (iVar17 == 3)))) &&
                  (this + 0x11f8 != local_5c)))) {
                *(int *)(this + 0x70) = iVar11;
                *(uint *)(this + 0x6c) = uVar18 + (iVar11 - iVar7);
              }
            }
          }
          if (this[2] != (cRSubGame)0x0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x20;
          }
          uVar14 = *(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          if ((uVar14 & 0x100) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x100;
            uVar14 = *(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar14 & 0x8000) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x8000;
          }
          *(cRSubGame **)(pcVar16 + 0x1c) = local_5c;
          *(int *)(pcVar16 + 0x20) = local_70;
          uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          if ((*(ushort *)(*(int *)(local_5c + 0x18) + iVar10) & 2) == 0) {
            fVar25 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
          }
          else {
            fVar25 = (float)VectorSignedToFloat(iVar15,(byte)(in_fpscr >> 0x16) & 3);
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 2;
            iVar17 = iVar15 * 0xdc;
            cRBod::SetObject((cRBod *)(this + iVar17 + 0x1e41dc),
                             *(cRObject **)
                              ((uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 3) * 0xb0 +
                               *(int *)PTR__Game_001b60b8 + 0x47afc));
            *(undefined4 *)(*(int *)(pcVar16 + -0x90) + 8) = 1;
            tMatrix::Identity((tMatrix *)(this + iVar17 + 0x1e4208));
            uVar21 = VectorUnsignedToFloat
                               ((uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 6),
                                (byte)(in_fpscr >> 0x16) & 3);
            *(undefined4 *)(pcVar16 + -0x58) = uVar21;
            uVar21 = VectorUnsignedToFloat
                               ((uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 7),
                                (byte)(in_fpscr >> 0x16) & 3);
            *(undefined4 *)(pcVar16 + -0x54) = uVar21;
            fVar6 = (float)VectorUnsignedToFloat
                                     ((uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 8),
                                      (byte)(in_fpscr >> 0x16) & 3);
            *(float *)(pcVar16 + -0x50) = fVar6 + fVar25;
            if ((*(ushort *)(*(int *)(local_5c + 0x18) + iVar10) & 8) == 0) {
              *(undefined4 *)(pcVar16 + -0x38) = 0;
              *(undefined4 *)(pcVar16 + -0x3c) = 0;
              *(undefined4 *)(pcVar16 + -0x40) = 0;
              uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
            }
            else {
              *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 8;
              *(undefined4 *)(pcVar16 + -0x38) = 0;
              *(undefined4 *)(pcVar16 + -0x3c) = 0;
              *(undefined4 *)(pcVar16 + -0x40) = 0;
              uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
            }
          }
          if ((uVar18 & 1) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x4001;
            *(uint *)(pcVar16 + -0x28) = (uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 2);
            *(undefined4 *)(pcVar16 + -0x34) = 0;
            *(undefined4 *)(pcVar16 + -0x30) = 0;
            uVar21 = VectorUnsignedToFloat
                               ((uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 5),
                                (byte)(in_fpscr >> 0x16) & 3);
            *(undefined4 *)(pcVar16 + -0x2c) = uVar21;
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar18 & 8) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 8;
            *(uint *)(pcVar16 + -0x24) = (uint)*(byte *)(*(int *)(local_5c + 0x18) + iVar10 + 4);
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar18 & 4) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 4;
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar18 & 0x200) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x200;
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar18 & 0x400) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x400;
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          if ((uVar18 & 0x2000) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x2000;
            uVar18 = (uint)*(ushort *)(iVar10 + *(int *)(local_5c + 0x18));
          }
          if ((uVar18 & 0x800) != 0) {
            *(uint *)(pcVar16 + -0xb8) = *(uint *)(pcVar16 + -0xb8) | 0x800;
            uVar18 = (uint)*(ushort *)(*(int *)(local_5c + 0x18) + iVar10);
          }
          bVar19 = (uVar18 & 0x1000) != 0;
          if (bVar19) {
            uVar18 = *(uint *)(pcVar16 + -0xb8);
          }
          uVar23 = 0;
          if (bVar19) {
            *(uint *)(pcVar16 + -0xb8) = uVar18 | 0x1000;
          }
          *(undefined4 *)(pcVar16 + 0x18) = 0;
          bVar19 = false;
          fVar6 = (float)VectorSignedToFloat(iVar15 % 8,(byte)(in_fpscr >> 0x16) & 3);
          pcVar5 = this + (int)(&PTR_caseD_6_00013458 + iVar15 * 0x88);
          uVar24 = (ulonglong)(uint)(fVar6 * 0.125);
          iVar17 = iVar15;
          do {
            iVar7 = (int)((ulonglong)uVar23 >> 0x20);
            iVar10 = iVar7;
            if (this[2] != (cRSubGame)0x0) {
              iVar10 = 7 - iVar7;
            }
            iVar11 = iVar7 * 0x44 + iVar15 * 0x220;
            this[iVar11 + 0x1348a] =
                 (cRSubGame)
                 ((byte)this[iVar11 + 0x1348a] & 0xe0 | (byte)((ulonglong)uVar23 >> 0x20) & 7);
            *(undefined4 *)(pcVar5 + 0x34) = 0;
            *(undefined4 *)(pcVar5 + 0x38) = 0;
            *(undefined4 *)(pcVar5 + 0x3c) = 0;
            *(undefined4 *)(pcVar5 + 0x40) = 0;
            if (iVar17 < *(int *)(this + 0x68)) {
              bVar20 = true;
            }
            else {
              bVar20 = *(int *)(this + 0x70) <= iVar17;
            }
            this_00 = (cRBod *)(this + (int)(&PTR_caseD_6_00013458 + iVar15 * 0x88 + iVar7 * 0x11));
            iVar11 = iVar7;
            cRBod::SetObject((cRBod *)(this + (int)(&PTR_caseD_6_00013458 +
                                                   iVar15 * 0x88 + iVar7 * 0x11)),(cRObject *)0x0);
            cVar1 = *(char *)(local_78 + iVar10 + *(int *)(local_5c + 0x14));
            if (iVar17 <= *(int *)(this + 0x70)) {
              switch(cVar1) {
              case ' ':
                if ((*(uint *)(this + 100) & 0x400) == 0) goto switchD_00021da0_caseD_2c;
                if ((*(uint *)(this + 100) & 1) == 0) goto switchD_00021da0_caseD_2e;
                goto switchD_00021da0_caseD_20;
              default:
                goto switchD_00021c18_caseD_21;
              case '$':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 0x800) != 0) goto switchD_00021da0_caseD_24;
LAB_00022cb0:
                if ((uVar18 & 0x40) != 0) goto switchD_00021da0_caseD_5f;
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
                cVar13 = (cRSubGame)0x1;
                goto LAB_00021f84;
              case '-':
                if ((*(uint *)(this + 100) & 0x4000) == 0) goto switchD_00021da0_caseD_2e;
                goto switchD_00021da0_caseD_2d;
              case '<':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                goto switchD_00021da0_caseD_3c;
              case '=':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 0x100) == 0) {
                  if ((uVar18 & 1) == 0) goto switchD_00021da0_caseD_2e;
                  if ((uVar18 & 0x400) != 0) goto switchD_00021da0_caseD_20;
                  goto switchD_00021da0_caseD_2c;
                }
                break;
              case '>':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                goto switchD_00021da0_caseD_3e;
              case '[':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                if ((*(uint *)(this + 100) & 0x20) == 0) goto switchD_00021da0_caseD_3c;
                goto switchD_00021da0_caseD_5b;
              case ']':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                if ((*(uint *)(this + 100) & 0x20) == 0) goto switchD_00021da0_caseD_3c;
                if (this[2] != (cRSubGame)0x0) goto switchD_00021da0_caseD_7b;
                goto switchD_00021da0_caseD_21;
              case '_':
                if ((*(uint *)(this + 100) & 0x40) != 0) goto switchD_00021c18_caseD_21;
                if (!bVar20) goto switchD_00021da0_caseD_2e;
                goto switchD_00021da0_caseD_5f;
              case 'o':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 4) == 0) goto LAB_00022cb0;
                goto switchD_00021da0_caseD_6f;
              case '{':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                if ((*(uint *)(this + 100) & 0x20) == 0) goto switchD_00021da0_caseD_3e;
                if (this[2] == (cRSubGame)0x0) goto switchD_00021da0_caseD_7b;
                goto switchD_00021da0_caseD_7d;
              case '|':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 0x100) == 0) {
                  if ((uVar18 & 1) == 0) goto switchD_00021da0_caseD_20;
                  if ((uVar18 & 0x400) == 0) goto switchD_00021da0_caseD_2c;
                }
                break;
              case '}':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto switchD_00021da0_caseD_2e;
                if ((*(uint *)(this + 100) & 0x20) == 0) goto switchD_00021da0_caseD_3e;
                if (this[2] == (cRSubGame)0x0) goto switchD_00021da0_caseD_7d;
                goto switchD_00021da0_caseD_7b;
              }
switchD_00021da0_caseD_3d:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44210));
              cVar13 = (cRSubGame)0xe;
              goto LAB_00021f84;
            }
switchD_00021c18_caseD_21:
            iVar10 = (int)cVar1;
            switch(iVar10) {
            case 0x20:
switchD_00021da0_caseD_20:
              cVar13 = (cRSubGame)0x0;
              goto LAB_000224d0;
            default:
switchD_00021da0_caseD_21:
              if (*(int *)(this + 0x70) < iVar17) goto switchD_00022298_caseD_21;
              switch(cVar1) {
              case ' ':
                if ((*(uint *)(this + 100) & 0x400) != 0) {
                  if ((*(uint *)(this + 100) & 1) == 0) {
                    iVar10 = 0x2e;
                    goto LAB_000228e8;
                  }
                  break;
                }
LAB_0002291c:
                iVar10 = 0x2c;
                goto LAB_000228e8;
              case '$':
                uVar12 = *(uint *)(this + 100);
                uVar18 = uVar12 & 0x800;
                goto joined_r0x00022a24;
              case '-':
                uVar18 = *(uint *)(this + 100) & 0x4000;
                goto joined_r0x000228e0;
              case '<':
              case '>':
                uVar18 = *(uint *)(this + 100) & 0x200;
joined_r0x000228e0:
                if (uVar18 != 0) break;
                goto LAB_00022908;
              case '=':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 0x100) == 0) {
                  if ((uVar18 & 1) == 0) goto LAB_00022908;
                  if ((uVar18 & 0x400) != 0) goto LAB_0002295c;
                  goto LAB_0002291c;
                }
                break;
              case '[':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto LAB_00022908;
                if ((*(uint *)(this + 100) & 0x20) == 0) {
LAB_00022a14:
                  iVar10 = 0x3c;
                  goto LAB_000228e8;
                }
                if (this[2] != (cRSubGame)0x0) {
                  iVar10 = 0x5b;
                  goto LAB_000228e8;
                }
                break;
              case ']':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto LAB_00022908;
                if ((*(uint *)(this + 100) & 0x20) == 0) goto LAB_00022a14;
LAB_000229ec:
                if (this[2] != (cRSubGame)0x0) {
                  iVar10 = 0x7b;
                  goto LAB_000228e8;
                }
                break;
              case 'o':
                uVar12 = *(uint *)(this + 100);
                uVar18 = uVar12 & 4;
joined_r0x00022a24:
                if (uVar18 != 0) break;
                if ((uVar12 & 0x40) == 0) {
LAB_00022908:
                  iVar10 = 0x2e;
                }
                else {
                  iVar10 = 0x5f;
                }
                goto LAB_000228e8;
              case '{':
                if ((*(uint *)(this + 100) & 0x200) == 0) goto LAB_00022908;
                if ((*(uint *)(this + 100) & 0x20) == 0) {
LAB_00023128:
                  iVar10 = 0x3e;
                  goto LAB_000228e8;
                }
                if (this[2] != (cRSubGame)0x0) {
                  iVar10 = 0x7d;
                  goto LAB_000228e8;
                }
                break;
              case '|':
                uVar18 = *(uint *)(this + 100);
                if ((uVar18 & 0x100) == 0) {
                  if ((uVar18 & 1) == 0) {
LAB_0002295c:
                    iVar10 = 0x20;
                  }
                  else {
                    if ((uVar18 & 0x400) == 0) goto LAB_0002291c;
                    iVar10 = 0x3d;
                  }
                  goto LAB_000228e8;
                }
                break;
              case '}':
                if ((*(uint *)(this + 100) & 0x200) != 0) {
                  if ((*(uint *)(this + 100) & 0x20) == 0) goto LAB_00023128;
                  goto LAB_000229ec;
                }
                goto LAB_00022908;
              }
switchD_00022298_caseD_21:
              iVar10 = (int)cVar1;
LAB_000228e8:
              wprintf("TrackError:%c in Segment %s\n",iVar10,*(undefined4 *)(local_5c + 0x10));
LAB_0002274c:
              fVar6 = fVar25 + 0.5;
              goto LAB_00021f9c;
            case 0x23:
              cVar13 = (cRSubGame)0x20;
              goto LAB_000224d0;
            case 0x24:
switchD_00021da0_caseD_24:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x17;
              break;
            case 0x26:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
              cVar13 = (cRSubGame)0x22;
              break;
            case 0x28:
              iVar8 = local_68 + 1;
              uVar18 = *(uint *)(pcVar5 + 4);
              if (iVar8 == 0xf) {
                iVar10 = 0;
              }
              *(uint *)(pcVar5 + 4) = uVar18 & 0xffffffdf;
              local_68 = iVar10;
              if (iVar8 != 0xf) {
                local_68 = iVar8;
                if (iVar8 == 8) {
                  cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44134));
                  *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
                  tColourSmall::Set((tColourSmall *)(this + iVar7 * 0x44 + iVar15 * 0x220 + 0x13480)
                                    ,1.0,1.0,1.0,0.999);
                }
                else {
                  *(uint *)(pcVar5 + 4) = uVar18 & 0xffffffdf;
                }
              }
              pcVar5[0x30] = (cRSubGame)0x16;
              fVar6 = fVar25 + 0.5;
              goto LAB_00021f9c;
            case 0x2b:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x18;
              break;
            case 0x2c:
switchD_00021da0_caseD_2c:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x43e48));
              cVar13 = (cRSubGame)0x1c;
              break;
            case 0x2d:
switchD_00021da0_caseD_2d:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
              cVar13 = (cRSubGame)0x15;
              break;
            case 0x2e:
switchD_00021da0_caseD_2e:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
              cVar13 = (cRSubGame)0x1;
              break;
            case 0x30:
              if (*(int *)(this + 0x58) != 1) goto switchD_00021da0_caseD_31;
              fVar6 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
              *(undefined4 *)(pcVar16 + -0x28) = 0;
              uVar18 = *(uint *)(pcVar16 + -0xb8) & 0xffffbfff | 1;
              *(uint *)(pcVar16 + -0xb8) = uVar18;
              *(undefined4 *)(pcVar16 + -0x30) = *(undefined4 *)(pcVar5 + 0x14);
              fVar6 = (fVar6 - 4.0) + 0.5;
              *(float *)(pcVar16 + -0x2c) = fVar25 + 0.5;
              *(float *)(pcVar16 + -0x34) = fVar6;
              if (this[2] != (cRSubGame)0x0) {
                *(float *)(pcVar16 + -0x34) = -fVar6;
              }
              goto LAB_000225fc;
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
switchD_00021da0_caseD_31:
              uVar18 = *(uint *)(pcVar16 + -0xb8);
LAB_000225fc:
              fVar6 = fVar25 + 0.5;
              if (((uVar18 & 0x40) == 0) && ((uVar18 & 0x80) == 0)) {
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
                pcVar5[0x30] = (cRSubGame)0xf;
                *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
              }
              else {
                *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffdf;
                pcVar5[0x30] = (cRSubGame)0x0;
              }
              goto LAB_00021f9c;
            case 0x3c:
switchD_00021da0_caseD_3c:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x447bc));
              *(undefined4 *)(pcVar5 + 0x1c) = 0;
              *(undefined4 *)(pcVar5 + 0x20) = 0;
              cVar13 = (cRSubGame)0x6;
              break;
            case 0x3d:
            case 0x7c:
              goto switchD_00021da0_caseD_3d;
            case 0x3e:
switchD_00021da0_caseD_3e:
              if ((iVar17 < 1) || (pcVar5[-0x1f0] != (cRSubGame)0x3)) {
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x447bc));
                *(undefined4 *)(pcVar5 + 0x1c) = 0;
                *(undefined4 *)(pcVar5 + 0x20) = 0;
                cVar13 = (cRSubGame)0x3;
                break;
              }
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x447bc));
              *(undefined4 *)(pcVar5 + 0x1c) = 0;
              *(undefined4 *)(pcVar5 + 0x20) = 0;
              fVar6 = fVar25 + 0.5;
              pcVar5[0x30] = (cRSubGame)0x9;
              *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
              pcVar5[-0x1f0] = (cRSubGame)0xc;
              goto LAB_00021f9c;
            case 0x40:
              pcVar5[0x30] = (cRSubGame)0x0;
              *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffdf;
              fVar6 = (float)RAND(1.0,"Mirror");
              uVar18 = in_fpscr & 0xfffffff | (uint)(fVar6 < 0.5) << 0x1f |
                       (uint)(fVar6 == 0.5) << 0x1e;
              in_fpscr = uVar18 | (uint)NAN(fVar6) << 0x1c;
              bVar2 = (byte)(uVar18 >> 0x18);
              cVar13 = (cRSubGame)
                       (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1));
              if (this[2] == cVar13) {
                iVar10 = *(int *)(this + 4);
                *(int *)(this + 4) = iVar10 + 1;
                if (3 < iVar10 + 1) {
                  this[2] = (cRSubGame)((byte)this[2] ^ 1);
                  fVar6 = fVar25 + 0.5;
                  *(undefined4 *)(this + 4) = 0;
                  goto LAB_00021f9c;
                }
              }
              else {
                *(undefined4 *)(this + 4) = 0;
              }
              this[2] = cVar13;
              fVar6 = fVar25 + 0.5;
              goto LAB_00021f9c;
            case 0x46:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x13;
              break;
            case 0x47:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x11;
              break;
            case 0x4a:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x19;
              break;
            case 0x4d:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x12;
              break;
            case 0x50:
            case 0x70:
              if (iVar10 == 0x50) {
                pcVar5[0x30] = (cRSubGame)0x1e;
              }
              else if (iVar10 == 0x70) {
                pcVar5[0x30] = (cRSubGame)0x1d;
              }
              if (this[2] == (cRSubGame)0x0) {
                *(cRSubGame **)(pcVar5 + 0x2c) =
                     this + (int)(&DAT_002e0d10 + *(int *)(pcVar16 + -0x24) * 0x120);
                *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffdf;
              }
              else {
                *(cRSubGame **)(pcVar5 + 0x2c) =
                     this + (int)(&DAT_002e0da0 + *(int *)(pcVar16 + -0x24) * 0x120);
                *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffdf;
              }
              if (!bVar19) {
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)(pcVar5 + 0x2c) + 0x24));
                *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
                iVar10 = iVar17 * 0xdc;
                cRBod::SetObject((cRBod *)(this + iVar10 + 0x1e427c),
                                 *(cRObject **)(*(int *)(pcVar5 + 0x2c) + 0x78));
                *(uint *)(pcVar16 + -0x10) = *(uint *)(pcVar16 + -0x10) | 0x20;
                *(undefined4 *)(pcVar16 + -0x18) = *(undefined4 *)(local_5c + 0x1c);
                if (*(int *)(*(int *)(pcVar5 + 0x2c) + 0x3c) < 1) {
                  bVar19 = true;
                  fVar6 = fVar25 + 0.5;
                }
                else {
                  pcVar9 = this + iVar10 + 0x1e4274;
                  iVar10 = 0;
                  do {
                    while (uVar18 = *(uint *)(pcVar9 + -0x9c), (uVar18 & 0x40) == 0) {
                      *(uint *)(pcVar9 + -0x9c) = uVar18 | 0x40;
                      iVar10 = iVar10 + 1;
                      *(cRSubGame **)(pcVar9 + -4) =
                           this + (int)(&PTR_caseD_6_00013458 + iVar15 * 0x88 + iVar7 * 0x11);
                      pcVar9 = pcVar9 + 0xdc;
                      if (*(int *)(*(int *)(pcVar5 + 0x2c) + 0x3c) <= iVar10) goto LAB_00022e98;
                    }
                    *(uint *)(pcVar9 + -0x9c) = uVar18 | 0x80;
                    iVar10 = iVar10 + 1;
                    *(cRSubGame **)pcVar9 =
                         this + (int)(&PTR_caseD_6_00013458 + iVar15 * 0x88 + iVar7 * 0x11);
                    pcVar9 = pcVar9 + 0xdc;
                  } while (iVar10 < *(int *)(*(int *)(pcVar5 + 0x2c) + 0x3c));
LAB_00022e98:
                  bVar19 = true;
                  fVar6 = fVar25 + 0.5;
                }
                goto LAB_00021f9c;
              }
              goto LAB_0002274c;
            case 0x52:
              cVar13 = (cRSubGame)0x23;
LAB_000224d0:
              pcVar5[0x30] = cVar13;
              fVar6 = fVar25 + 0.5;
              *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffdf;
              goto LAB_00021f9c;
            case 0x5b:
switchD_00021da0_caseD_5b:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44790));
              *(undefined4 *)(pcVar5 + 0x1c) = 0;
              *(undefined4 *)(pcVar5 + 0x20) = 0;
              cVar13 = (cRSubGame)0x5;
              break;
            case 0x5f:
switchD_00021da0_caseD_5f:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0xf;
              break;
            case 0x6f:
switchD_00021da0_caseD_6f:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44630));
              cVar13 = (cRSubGame)0x10;
              break;
            case 0x73:
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44370));
              cVar13 = (cRSubGame)0x21;
              break;
            case 0x7b:
switchD_00021da0_caseD_7b:
              if ((iVar17 < 1) || (pcVar5[-0x1f0] != (cRSubGame)0x3)) {
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44790));
                *(undefined4 *)(pcVar5 + 0x1c) = 0;
                *(undefined4 *)(pcVar5 + 0x20) = 0;
                cVar13 = (cRSubGame)0x2;
                break;
              }
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x44790));
              *(undefined4 *)(pcVar5 + 0x1c) = 0;
              *(undefined4 *)(pcVar5 + 0x20) = 0;
              fVar6 = fVar25 + 0.5;
              pcVar5[0x30] = (cRSubGame)0x8;
              *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
              pcVar5[-0x1f0] = (cRSubGame)0xb;
              goto LAB_00021f9c;
            case 0x7d:
switchD_00021da0_caseD_7d:
              if ((iVar17 < 1) || (pcVar5[-0x1f0] != (cRSubGame)0x3)) {
                cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x447e8));
                *(undefined4 *)(pcVar5 + 0x1c) = 0;
                *(undefined4 *)(pcVar5 + 0x20) = 0;
                cVar13 = (cRSubGame)0x4;
                break;
              }
              cRBod::SetObject(this_00,*(cRObject **)(*(int *)PTR__Game_001b60b8 + 0x447e8));
              *(undefined4 *)(pcVar5 + 0x1c) = 0;
              *(undefined4 *)(pcVar5 + 0x20) = 0;
              fVar6 = fVar25 + 0.5;
              pcVar5[0x30] = (cRSubGame)0xa;
              *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
              pcVar5[-0x1f0] = (cRSubGame)0xd;
              goto LAB_00021f9c;
            }
LAB_00021f84:
            pcVar5[0x30] = cVar13;
            fVar6 = fVar25 + 0.5;
            *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x20;
LAB_00021f9c:
            *(undefined4 *)(pcVar5 + 0x18) = 0;
            *(undefined4 *)(pcVar5 + 0x14) = 0;
            *(undefined4 *)(pcVar5 + 0x10) = 0;
            *(undefined4 *)(pcVar16 + 4) = 0;
            *(undefined4 *)pcVar16 = 0;
            *(undefined4 *)(pcVar16 + -4) = 0;
            cVar13 = pcVar5[0x30];
            if ((byte)((char)cVar13 - 0x1dU) < 2) {
              *(undefined4 *)(pcVar5 + 0x10) = 0;
              puVar4 = PTR__gConfig_001b60d4;
              *(float *)(pcVar5 + 0x18) = fVar6 - 0.5;
              if ((*(uint *)(puVar4 + 0x1c) & 0x20) == 0) {
                *(uint *)(pcVar16 + -0x10) = *(uint *)(pcVar16 + -0x10) & 0xffffffdf;
                cVar13 = pcVar5[0x30];
              }
              else {
                *(float *)(pcVar16 + 4) = fVar6 - 0.5;
                *(undefined4 *)(pcVar16 + -4) = 0;
                iVar10 = *(int *)PTR__Game_001b60b8;
                tColourSmall::Set((tColourSmall *)(this + iVar17 * 0xdc + 0x1e42a4),
                                  *(float *)(iVar10 + 0x73dd0),*(float *)(iVar10 + 0x73dd4),
                                  *(float *)(iVar10 + 0x73dd8),0.5);
                cVar13 = pcVar5[0x30];
              }
            }
            else {
              fVar22 = (float)VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
              *(undefined4 *)(pcVar5 + 0x14) = 0;
              *(float *)(pcVar5 + 0x18) = fVar6;
              if ((byte)((char)cVar13 - 8U) < 3) {
                *(undefined4 *)(pcVar5 + 0x14) = 0x3f000000;
              }
              *(float *)(pcVar5 + 0x10) = (fVar22 - 4.0) + 0.5;
            }
            if ((iVar17 < 4) && (*(int *)(this + 0x58) != 2)) {
              *(undefined4 *)(pcVar5 + 0x14) = *(undefined4 *)(*(int *)(this + 0x2e3edc) + 0x34);
            }
            if (cVar13 == (cRSubGame)0x1c) {
              *(float *)(pcVar5 + 0x14) = *(float *)(pcVar5 + 0x14) - 0.03;
            }
            if ((((cVar13 == (cRSubGame)0x15 || cVar13 == (cRSubGame)0x1) ||
                 (((((cVar13 == (cRSubGame)0x14 || cVar13 == (cRSubGame)0x21) ||
                    cVar13 == (cRSubGame)0x22) || cVar13 == (cRSubGame)0xf) ||
                  cVar13 == (cRSubGame)0x10) || cVar13 == (cRSubGame)0x17)) ||
                (((((cVar13 == (cRSubGame)0x18 || cVar13 == (cRSubGame)0x19) ||
                   cVar13 == (cRSubGame)0x1a) || cVar13 == (cRSubGame)0x1b) ||
                 cVar13 == (cRSubGame)0x12) || cVar13 == (cRSubGame)0x13)) ||
               (cVar13 == (cRSubGame)0x11)) {
              *(int *)(pcVar5 + 0x20) = (int)uVar24;
              fVar22 = (float)VectorSignedToFloat(8 - iVar11,(byte)(in_fpscr >> 0x16) & 3);
              *(float *)(pcVar5 + 0x1c) = fVar22 * 0.25 * 0.125;
              if (cVar13 == (cRSubGame)0x1f) goto LAB_00022a5c;
LAB_0002208c:
              if (cVar13 == (cRSubGame)0x16) {
                if ((*(int *)(this + 0x58) == 3) && ((*(uint *)(this + 100) & 0x400) == 0)) {
                  *(float *)(pcVar5 + 0x18) = fVar6;
                }
                else {
                  *(float *)(pcVar5 + 0x18) = fVar6;
                  *(undefined4 *)(pcVar5 + 0x14) = 0xc0400000;
                }
              }
            }
            else {
              if (cVar13 != (cRSubGame)0x1f) goto LAB_0002208c;
LAB_00022a5c:
              *(float *)(pcVar5 + 0x10) = *(float *)(pcVar5 + 0x10) * 1.1;
            }
            pcVar5 = pcVar5 + 0x44;
            uVar23 = CONCAT44(iVar11 + 1,fVar6);
          } while (iVar11 + 1 != 8);
          uVar18 = *(uint *)(this + 0x6c);
          local_58 = local_58 + 1;
          uVar12 = iVar17 + 1;
          local_4c = local_4c + 1;
          bVar20 = SBORROW4(uVar18,uVar12);
          iVar17 = uVar18 - uVar12;
          bVar19 = uVar18 == uVar12;
          if ((int)uVar12 < (int)uVar18) {
            bVar20 = SBORROW4(local_64,local_58);
            iVar17 = local_64 - local_58;
            bVar19 = local_64 == local_58;
          }
          uVar24 = (ulonglong)uVar12;
          pcVar16 = pcVar16 + 0xdc;
          pcVar5 = (cRSubGame *)0x8;
        } while (!bVar19 && iVar17 < 0 == bVar20);
      }
      iVar17 = (int)uVar24;
      pcVar16 = local_6c;
      if (*(int *)(this + 0x58) != 3) {
        local_70 = local_70 + 1;
        pcVar16 = pcVar5;
      }
      if (*(int *)(this + 0x58) == 3 && pcVar16 == (cRSubGame *)0x0) {
        local_70 = local_70 + 1;
      }
    } while (iVar17 < (int)uVar18);
  }
  wprintf("Track Length %i\n",iVar17);
  return;
}
