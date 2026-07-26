/*
 * mangled: _ZN17cRPathFollowGoldy8TraverseEfR7tVectorPS0_
 * demangled: cRPathFollowGoldy::Traverse(float, tVector&, tVector*)
 * address: 0004dfe0
 * size: 3064
 */

/* cRPathFollowGoldy::Traverse(float, tVector&, tVector*) */

int __thiscall
cRPathFollowGoldy::Traverse(cRPathFollowGoldy *this,float param_1,tVector *param_2,tVector *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined *puVar3;
  undefined *this_00;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  cRPath *this_01;
  int iVar9;
  int *piVar10;
  int iVar11;
  uint in_fpscr;
  uint uVar12;
  float fVar13;
  float fVar14;
  undefined1 *puVar15;
  undefined1 *puVar16;
  float fVar17;
  float fVar18;
  ulonglong uVar19;
  float fVar21;
  undefined8 uVar20;
  float fVar22;
  ulonglong uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  undefined8 uVar26;
  undefined8 uVar27;
  float local_194;
  float fStack_190;
  float fStack_18c;
  undefined4 uStack_188;
  float local_184;
  float fStack_180;
  float fStack_17c;
  undefined4 uStack_178;
  undefined4 local_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 local_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  float local_154;
  float fStack_150;
  float fStack_14c;
  undefined4 uStack_148;
  float local_144;
  float fStack_140;
  float fStack_13c;
  undefined4 uStack_138;
  undefined4 local_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 local_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 local_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 local_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 local_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 uStack_d8;
  undefined4 local_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 local_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 local_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 uStack_98;
  float local_94;
  float local_90;
  float local_8c;
  undefined4 uStack_88;
  float local_84;
  float local_80;
  float local_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float afStack_54 [13];

  iVar11 = *(int *)(this + 0xc);
  this_01 = *(cRPath **)(this + 4);
  uVar23 = (ulonglong)(uint)param_1;
  fVar14 = *(float *)(iVar11 * 0xa8 + *(int *)(this_01 + 0x50) + 0x8c);
  uVar19 = (ulonglong)(uint)(fVar14 * param_1);
  while( true ) {
    fVar21 = *(float *)(this + 0x10) + (float)uVar19;
    uVar12 = in_fpscr & 0xfffffff | (uint)(fVar21 < fVar14) << 0x1f |
             (uint)(fVar21 == fVar14) << 0x1e;
    in_fpscr = uVar12 | (uint)(NAN(fVar21) || NAN(fVar14)) << 0x1c;
    bVar2 = (byte)(uVar12 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) break;
    iVar11 = iVar11 + 1;
    *(int *)(this + 0xc) = iVar11;
    uVar19 = (ulonglong)(uint)((float)uVar19 - (fVar14 - *(float *)(this + 0x10)));
    *(undefined4 *)(this + 0x10) = 0;
    iVar6 = *(int *)(this_01 + 0x38);
    if (iVar11 == iVar6 * 2) {
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,4,1,-1);
      this_01 = *(cRPath **)(this + 4);
      iVar11 = *(int *)(this + 0xc);
      iVar6 = *(int *)(this_01 + 0x38);
    }
    puVar3 = PTR__Game_001b60b8;
    if (this_01[0x84] != (cRPath)0x0) {
      if (iVar11 == iVar6 + -1) {
        iVar6 = *(int *)PTR__Game_001b60b8;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        iVar9 = *(int *)puVar3;
        iVar6 = *(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6);
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        *(undefined4 *)(iVar6 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar9) + 0x2c) + 0x8c);
        iVar6 = *(int *)puVar3;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        tColourSmall::Alpha((tColourSmall *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6) + 0x28)
                            ,1.0);
        this_01 = *(cRPath **)(this + 4);
        iVar11 = *(int *)(this + 0xc);
        iVar6 = *(int *)(this_01 + 0x38);
      }
      else if (iVar11 == (iVar6 * 3) / 7) {
        iVar6 = *(int *)PTR__Game_001b60b8;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        *(uint *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6) + 4) =
             *(uint *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6) + 4) | 0x80;
        iVar6 = *(int *)puVar3;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        iVar9 = *(int *)puVar3;
        iVar6 = *(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6);
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        *(undefined4 *)(iVar6 + 0x24) =
             *(undefined4 *)
              (*(int *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar9) + 0x2c) + 0x88);
        iVar6 = *(int *)puVar3;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        tColourSmall::Alpha((tColourSmall *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6) + 0x28)
                            ,0.6);
        iVar6 = *(int *)puVar3;
        iVar11 = cRSubLoc::Yi(*(cRSubLoc **)(this + 8));
        *(undefined4 *)(*(int *)(*(int *)(&DAT_00256de8 + iVar11 * 0xdc + iVar6) + 0x24) + 8) = 1;
        this_01 = *(cRPath **)(this + 4);
        iVar11 = *(int *)(this + 0xc);
        iVar6 = *(int *)(this_01 + 0x38);
      }
    }
    if (iVar6 == iVar11) {
      *this = (cRPathFollowGoldy)0x0;
      fVar14 = (float)uVar19;
      if (1.0 <= (float)uVar19) {
        fVar14 = 0.999;
      }
      fVar21 = (float)uVar23 *
               *(float *)(*(int *)(this_01 + 0x38) * 0xa8 + *(int *)(this_01 + 0x50) + -0x1c);
      if (1.0 < fVar21) {
        fVar21 = 1.0;
      }
      *(float *)(param_3 + 8) = fVar21;
      iVar11 = *(int *)(this + 4);
      if (*(int *)(iVar11 + 0x2c) == 0x26) {
        *(float *)(param_3 + 4) = fVar21 * 0.7;
        this_00 = PTR__gRSound_001b61e0;
        iVar11 = *(int *)(this + 4);
        fVar14 = fVar14 + *(float *)(iVar11 + 0x44);
        iVar11 = *(int *)(iVar11 + 0x50) + -0xa8 + *(int *)(iVar11 + 0x38) * 0xa8;
        fVar21 = *(float *)(iVar11 + 0x38);
        fVar17 = *(float *)(*(int *)(this + 8) + 0x18);
        fVar13 = *(float *)(iVar11 + 0x28);
        *(float *)(param_2 + 4) =
             *(float *)(*(int *)(this + 8) + 0x14) + *(float *)(iVar11 + 0x34) +
             fVar14 * *(float *)(iVar11 + 0x24);
        puVar3 = PTR__Game_001b60b8;
        *(float *)(param_2 + 8) = fVar17 + fVar21 + fVar14 * fVar13;
        *(float *)(*(int *)(this + 0x38) + 0x2c8) =
             *(float *)(*(int *)puVar3 + 0x72bc4) * 0.013888889;
        *(undefined4 *)(*(int *)(this + 0x38) + 0x2c4) =
             *(undefined4 *)(*(int *)(this + 0x38) + 0x2c8);
        cRSound::Play((cRSound *)this_00,0x2a);
        cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0xf,0,-1);
      }
      else {
        *(float *)(param_2 + 8) =
             *(float *)(*(int *)(this + 8) + 0x18) +
             *(float *)(*(int *)(iVar11 + 0x38) * 0xa8 + *(int *)(iVar11 + 0x50) + -0x70) +
             *(float *)(iVar11 + 0x44) + fVar14;
      }
      *(float *)(*(int *)(this + 0x38) + 0x360) =
           *(float *)(*(int *)(this + 0x38) + 0x360) + *(float *)(*(int *)(this + 4) + 0x80);
      return 3;
    }
    fVar14 = *(float *)(*(int *)(this_01 + 0x50) + iVar11 * 0xa8 + 0x8c);
  }
  *(float *)(this + 0x10) = fVar21;
  if (iVar11 == *(int *)(this_01 + 0x38) + -1) {
    iVar6 = iVar11 * 0xa8 + *(int *)(this_01 + 0x4c);
    fVar17 = *(float *)(iVar6 + 0x90);
    fVar13 = *(float *)(iVar6 + 0x9c);
    fVar14 = *(float *)(iVar6 + 0xa0);
  }
  else {
    iVar6 = iVar11 * 0xa8;
    iVar7 = iVar6 + *(int *)(this_01 + 0x4c) + 0xa8;
    iVar9 = *(int *)(this_01 + 0x4c) + iVar6;
    fVar14 = fVar21 / *(float *)(iVar6 + *(int *)(this_01 + 0x50) + 0x8c);
    fVar17 = *(float *)(iVar9 + 0x90) +
             (*(float *)(iVar7 + 0x90) - *(float *)(iVar9 + 0x90)) * fVar14;
    fVar13 = *(float *)(iVar9 + 0x9c) +
             fVar14 * (*(float *)(iVar7 + 0x9c) - *(float *)(iVar9 + 0x9c));
    fVar14 = *(float *)(iVar9 + 0xa0) +
             fVar14 * (*(float *)(iVar7 + 0xa0) - *(float *)(iVar9 + 0xa0));
  }
  uVar20 = CONCAT44(fVar21,fVar13);
  if (*(int *)(this_01 + 0x2c) == 0x39) {
    cRPath::HalfPipePos(this_01,fVar14,*(float *)param_2 - fVar17,0.49,(tMatrix *)&local_94,
                        afStack_54);
    fVar14 = (float)uVar20;
    iVar11 = *(int *)(this + 0xc);
    if ((iVar11 == 0) || (iVar6 = *(int *)(this + 4), iVar11 == *(int *)(iVar6 + 0x38) + -1)) {
      tMatrix::Identity((tMatrix *)&local_194);
      local_164 = local_64;
      uStack_160 = local_60;
      uStack_15c = uStack_5c;
      local_154 = local_94;
      fStack_150 = local_90;
      fStack_14c = local_8c;
      uStack_148 = uStack_88;
      local_144 = local_84;
      fStack_140 = local_80;
      fStack_13c = local_7c;
      uStack_138 = uStack_78;
      local_134 = local_74;
      uStack_130 = uStack_70;
      uStack_12c = uStack_6c;
      uStack_128 = uStack_68;
      local_124 = local_64;
      uStack_120 = local_60;
      uStack_11c = uStack_5c;
      uStack_118 = uStack_58;
      if (*(int *)(this + 0xc) == 0) {
        fVar21 = *(float *)(this + 0x10);
      }
      else {
        fVar21 = 1.0 - *(float *)(this + 0x10);
      }
      tMatrix::LinearInterpolate
                ((tMatrix *)&local_94,(tMatrix *)&local_194,(tMatrix *)&local_154,fVar21);
      iVar6 = *(int *)(this + 4);
      iVar11 = *(int *)(this + 0xc);
    }
    iVar11 = iVar11 * 0xa8 + *(int *)(iVar6 + 0x50);
    fVar21 = *(float *)(iVar11 + 0x38);
    fVar13 = *(float *)(*(int *)(this + 8) + 0x18);
    fVar18 = *(float *)(iVar11 + 0x88);
    *(undefined4 *)(this + 0x2c) = local_64;
    local_94 = local_94 * fVar14;
    *(float *)(this + 0x34) = fVar13 + fVar21 + *(float *)(this + 0x10) * fVar18;
    local_90 = local_90 * fVar14;
    local_8c = local_8c * fVar14;
    fVar14 = *(float *)(param_3 + 4);
    *(undefined4 *)(this + 0x30) = local_60;
    *(float *)(this + 0x14) = *(float *)(this + 0x14) + fVar14;
  }
  else {
    if (*(int *)(this_01 + 0x2c) != 0x3a) {
      iVar6 = *(int *)(this + 8);
      puVar4 = (undefined4 *)(iVar11 * 0xa8 + *(int *)(this_01 + 0x50));
      fVar14 = *(float *)(iVar6 + 0x10);
      uVar24 = CONCAT44(puVar4[0xc],puVar4[0x20]);
      uVar27 = CONCAT44(*(undefined4 *)(iVar6 + 0x14),puVar4[0xd]);
      uVar25 = CONCAT44(puVar4[0xe],*(undefined4 *)(iVar6 + 0x18));
      uVar26 = CONCAT44(puVar4[0x21],puVar4[0x22]);
      if (iVar11 == *(int *)(this_01 + 0x38) + -1) {
        tMatrix::Identity((tMatrix *)&local_94);
      }
      else {
        local_d4 = *puVar4;
        uStack_d0 = puVar4[1];
        uStack_cc = puVar4[2];
        uStack_c8 = puVar4[3];
        local_c4 = puVar4[4];
        uStack_c0 = puVar4[5];
        uStack_bc = puVar4[6];
        uStack_b8 = puVar4[7];
        local_b4 = puVar4[8];
        uStack_b0 = puVar4[9];
        uStack_ac = puVar4[10];
        uStack_a8 = puVar4[0xb];
        uStack_98 = puVar4[0xf];
        iVar6 = iVar11 * 0xa8 + *(int *)(this_01 + 0x50);
        local_114 = *(undefined4 *)(iVar6 + 0xa8);
        uStack_110 = *(undefined4 *)(iVar6 + 0xac);
        uStack_10c = *(undefined4 *)(iVar6 + 0xb0);
        uStack_108 = *(undefined4 *)(iVar6 + 0xb4);
        local_104 = *(undefined4 *)(iVar6 + 0xb8);
        uStack_100 = *(undefined4 *)(iVar6 + 0xbc);
        uStack_fc = *(undefined4 *)(iVar6 + 0xc0);
        uStack_f8 = *(undefined4 *)(iVar6 + 0xc4);
        local_f4 = *(undefined4 *)(iVar6 + 200);
        uStack_f0 = *(undefined4 *)(iVar6 + 0xcc);
        uStack_ec = *(undefined4 *)(iVar6 + 0xd0);
        uStack_e8 = *(undefined4 *)(iVar6 + 0xd4);
        uStack_d8 = *(undefined4 *)(iVar6 + 0xe4);
        local_9c = 0;
        local_a0 = 0;
        local_a4 = 0;
        local_dc = 0;
        local_e0 = 0;
        local_e4 = 0;
        tMatrix::LinearInterpolate
                  ((tMatrix *)&local_94,(tMatrix *)&local_d4,(tMatrix *)&local_114,
                   *(float *)(this + 0x10) /
                   *(float *)(iVar11 * 0xa8 + *(int *)(this_01 + 0x50) + 0x8c));
      }
      piVar10 = (int *)PTR__Game_001b60b8;
      fVar18 = (float)uVar20;
      local_94 = local_94 * fVar18;
      local_90 = local_90 * fVar18;
      local_8c = local_8c * fVar18;
      fVar21 = *(float *)(this + 0x14) + *(float *)(param_3 + 4);
      *(float *)(this + 0x14) = fVar21;
      fVar13 = *(float *)param_2 - fVar17;
      fVar22 = (float)((ulonglong)uVar20 >> 0x20);
      *(float *)(this + 0x2c) =
           fVar14 + (float)((ulonglong)uVar24 >> 0x20) + fVar22 * (float)uVar24 * fVar18 +
           fVar13 * local_94 + fVar21 * local_84;
      *(float *)(this + 0x30) =
           (float)((ulonglong)uVar27 >> 0x20) + (float)uVar27 +
           fVar22 * (float)((ulonglong)uVar26 >> 0x20) * fVar18 + fVar13 * local_90 +
           fVar21 * local_80;
      *(float *)(this + 0x34) =
           (float)uVar25 + (float)((ulonglong)uVar25 >> 0x20) + fVar22 * (float)uVar26 +
           fVar13 * local_8c + fVar21 * local_7c;
      iVar11 = *piVar10;
      goto LAB_0004e5f0;
    }
    cRPath::HalfPolePos(this_01,fVar14,*(float *)param_2 - fVar17,0.49,(tMatrix *)&local_94,
                        afStack_54);
    fVar14 = (float)uVar20;
    iVar11 = *(int *)(this + 0xc);
    if ((iVar11 == 0) || (iVar6 = *(int *)(this + 4), iVar11 == *(int *)(iVar6 + 0x38) + -1)) {
      tMatrix::Identity((tMatrix *)&local_154);
      local_124 = local_64;
      uStack_120 = local_60;
      uStack_11c = uStack_5c;
      local_194 = local_94;
      fStack_190 = local_90;
      fStack_18c = local_8c;
      uStack_188 = uStack_88;
      local_184 = local_84;
      fStack_180 = local_80;
      fStack_17c = local_7c;
      uStack_178 = uStack_78;
      local_174 = local_74;
      uStack_170 = uStack_70;
      uStack_16c = uStack_6c;
      uStack_168 = uStack_68;
      local_164 = local_64;
      uStack_160 = local_60;
      uStack_15c = uStack_5c;
      uStack_158 = uStack_58;
      if (*(int *)(this + 0xc) == 0) {
        fVar21 = *(float *)(this + 0x10);
      }
      else {
        fVar21 = 1.0 - *(float *)(this + 0x10);
      }
      tMatrix::LinearInterpolate
                ((tMatrix *)&local_94,(tMatrix *)&local_154,(tMatrix *)&local_194,fVar21);
      iVar6 = *(int *)(this + 4);
      iVar11 = *(int *)(this + 0xc);
    }
    iVar11 = iVar11 * 0xa8 + *(int *)(iVar6 + 0x50);
    fVar21 = *(float *)(iVar11 + 0x38);
    fVar13 = *(float *)(*(int *)(this + 8) + 0x18);
    fVar18 = *(float *)(iVar11 + 0x88);
    *(undefined4 *)(this + 0x2c) = local_64;
    local_94 = local_94 * fVar14;
    *(float *)(this + 0x34) = fVar13 + fVar21 + *(float *)(this + 0x10) * fVar18;
    local_90 = local_90 * fVar14;
    local_8c = local_8c * fVar14;
    fVar14 = *(float *)(param_3 + 4);
    *(undefined4 *)(this + 0x30) = local_60;
    *(float *)(this + 0x14) = *(float *)(this + 0x14) + fVar14;
  }
  iVar11 = *(int *)PTR__Game_001b60b8;
  piVar10 = (int *)PTR__Game_001b60b8;
LAB_0004e5f0:
  *(float *)(iVar11 + 0x81fec) = local_94;
  *(float *)(iVar11 + 0x81ff0) = local_90;
  *(float *)(iVar11 + 0x81ff4) = local_8c;
  iVar11 = *piVar10;
  *(float *)(iVar11 + 0x81ffc) = local_84;
  *(float *)(iVar11 + 0x82000) = local_80;
  *(float *)(iVar11 + 0x82004) = local_7c;
  iVar11 = *piVar10;
  *(undefined4 *)(iVar11 + 0x8200c) = local_74;
  *(undefined4 *)(iVar11 + 0x82010) = uStack_70;
  *(undefined4 *)(iVar11 + 0x82014) = uStack_6c;
  iVar11 = *(int *)(this + 4);
  iVar6 = *(int *)(this + 0xc);
  *(float *)(this + 0x20) = local_84;
  *(float *)(this + 0x24) = local_80;
  *(float *)(this + 0x28) = local_7c;
  if (iVar6 == *(int *)(iVar11 + 0x38) + -1) {
    *(undefined4 *)(this + 0x1c) = *(undefined4 *)(iVar6 * 0xa8 + *(int *)(iVar11 + 0x4c) + 0x98);
    *(undefined4 *)(this + 0x18) = *(undefined4 *)(iVar6 * 0xa8 + *(int *)(iVar11 + 0x4c) + 0x94);
  }
  else {
    iVar9 = *(int *)(iVar11 + 0x4c) + iVar6 * 0xa8;
    fVar14 = *(float *)(iVar9 + 0x98);
    fVar21 = *(float *)(iVar9 + 0x140) - fVar14;
    uVar12 = in_fpscr & 0xfffffff | (uint)(fVar21 < 3.1415927) << 0x1f |
             (uint)(fVar21 == 3.1415927) << 0x1e;
    bVar2 = (byte)(uVar12 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar21)) {
      uVar12 = in_fpscr & 0xfffffff | (uint)(fVar21 < -3.1415927) << 0x1f;
      if (SUB41(uVar12 >> 0x1f,0)) {
        fVar21 = fVar21 + 6.2831855;
      }
    }
    else {
      fVar21 = fVar21 - 6.2831855;
    }
    *(float *)(this + 0x1c) =
         fVar14 + (*(float *)(this + 0x10) /
                  *(float *)(iVar6 * 0xa8 + *(int *)(iVar11 + 0x50) + 0x8c)) * fVar21;
    iVar9 = *(int *)(iVar11 + 0x4c) + iVar6 * 0xa8;
    fVar14 = *(float *)(iVar9 + 0x94);
    fVar21 = *(float *)(iVar9 + 0x13c) - fVar14;
    uVar1 = uVar12 & 0xfffffff | (uint)(fVar21 < 3.1415927) << 0x1f |
            (uint)(fVar21 == 3.1415927) << 0x1e;
    in_fpscr = uVar1 | (uint)NAN(fVar21) << 0x1c;
    bVar2 = (byte)(uVar1 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) {
      in_fpscr = uVar12 & 0xfffffff | (uint)(fVar21 < -3.1415927) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        fVar21 = fVar21 + 6.2831855;
      }
    }
    else {
      fVar21 = fVar21 - 6.2831855;
    }
    *(float *)(this + 0x18) =
         fVar14 + (*(float *)(this + 0x10) /
                  *(float *)(iVar6 * 0xa8 + *(int *)(iVar11 + 0x50) + 0x8c)) * fVar21;
  }
  uVar12 = in_fpscr & 0xfffffff | (uint)(*(float *)(iVar11 + 0x80) == 0.0) << 0x1e;
  if (!SUB41(uVar12 >> 0x1e,0)) {
    fVar14 = (float)VectorSignedToFloat(iVar6,(byte)(uVar12 >> 0x16) & 3);
    fVar21 = (float)VectorSignedToFloat(*(undefined4 *)(iVar11 + 0x38),(byte)(uVar12 >> 0x16) & 3);
    *(float *)(this + 0x1c) =
         (*(float *)(iVar11 + 0x80) *
         (*(float *)(this + 0x10) / *(float *)(iVar6 * 0xa8 + *(int *)(iVar11 + 0x50) + 0x8c) +
         fVar14)) / fVar21;
  }
  fVar14 = (float)VectorSignedToFloat(*(undefined4 *)(iVar11 + 0x48),(byte)(uVar12 >> 0x16) & 3);
  if (ABS(*(float *)param_2 - fVar17) <= fVar14 * 0.5 + 0.3) {
    fVar14 = *(float *)(this + 0x14);
  }
  else {
    fVar14 = *(float *)(this + 0x14);
    if (fVar14 <= 0.0) {
      uVar5 = *(undefined4 *)(this + 0x30);
      uVar8 = *(undefined4 *)(this + 0x34);
      *(undefined4 *)param_2 = *(undefined4 *)(this + 0x2c);
      *(undefined4 *)(param_2 + 4) = uVar5;
      *(undefined4 *)(param_2 + 8) = uVar8;
      *(float *)(*(int *)(this + 0x38) + 0x360) =
           *(float *)(*(int *)(this + 0x38) + 0x360) + *(float *)(*(int *)(this + 4) + 0x80);
      puVar15 = *(undefined1 **)param_2;
      puVar16 = (undefined1 *)0xc0800000;
      if ((-4.0 <= (float)puVar15) && (puVar16 = puVar15, 4.0 < (float)puVar15)) {
        puVar16 = &DAT_40800000;
      }
      *(undefined1 **)param_2 = puVar16;
      if (*(uint *)(*(int *)(this + 4) + 0x34) < 2) {
        return 1 - *(uint *)(*(int *)(this + 4) + 0x34);
      }
      return 0;
    }
  }
  if (fVar14 < 0.0) {
    *(undefined4 *)(this + 0x14) = 0;
    *(undefined4 *)(param_3 + 4) = 0;
  }
  return 0;
}
