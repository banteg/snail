/*
 * mangled: _ZN16cRPathFollowGolb8TraverseEfR7tVectorPS0_
 * demangled: cRPathFollowGolb::Traverse(float, tVector&, tVector*)
 * address: 0004f8f4
 * size: 1476
 */

/* cRPathFollowGolb::Traverse(float, tVector&, tVector*) */

int __thiscall
cRPathFollowGolb::Traverse(cRPathFollowGolb *this,float param_1,tVector *param_2,tVector *param_3)

{
  uint uVar1;
  byte bVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  cRPath *this_00;
  int iVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  ulonglong uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined4 local_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 local_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined4 local_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 uStack_94;
  float local_90;
  float local_8c;
  float local_88;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 local_60;
  undefined4 local_5c;
  float afStack_50 [13];

  iVar9 = *(int *)(this + 0xc);
  this_00 = *(cRPath **)(this + 4);
  fVar12 = *(float *)(iVar9 * 0xa8 + *(int *)(this_00 + 0x50) + 0x8c);
  fVar10 = fVar12 * param_1;
  while( true ) {
    fVar11 = *(float *)(this + 0x10);
    fVar13 = fVar11 + fVar10;
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f |
            (uint)(fVar13 == fVar12) << 0x1e;
    in_fpscr = uVar1 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
    bVar2 = (byte)(uVar1 >> 0x18);
    if ((bool)(bVar2 >> 6 & 1) || bVar2 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) break;
    iVar9 = iVar9 + 1;
    *(undefined4 *)(this + 0x10) = 0;
    *(int *)(this + 0xc) = iVar9;
    fVar10 = fVar10 - (fVar12 - fVar11);
    if (iVar9 == *(int *)(this_00 + 0x38)) {
      *this = (cRPathFollowGolb)0x0;
      *(float *)(param_3 + 8) =
           *(float *)(*(int *)(this_00 + 0x38) * 0xa8 + *(int *)(this_00 + 0x50) + -0x1c) * param_1;
      iVar9 = *(int *)(this + 0x24);
      uVar4 = *(undefined4 *)(this + 0x1c);
      uVar6 = *(undefined4 *)(this + 0x20);
      *(undefined4 *)(iVar9 + 0x1d4) = *(undefined4 *)(this + 0x18);
      *(undefined4 *)(iVar9 + 0x1d8) = uVar4;
      *(undefined4 *)(iVar9 + 0x1dc) = uVar6;
      iVar9 = *(int *)(this + 4);
      if (*(int *)(iVar9 + 0x2c) != 0x26) {
        fVar10 = *(float *)(*(int *)(this + 8) + 0x18) +
                 *(float *)(*(int *)(iVar9 + 0x38) * 0xa8 + *(int *)(iVar9 + 0x50) + -0x70) +
                 *(float *)(iVar9 + 0x44) + fVar10;
        *(float *)(param_2 + 8) = fVar10;
        *(float *)(*(int *)(this + 0x24) + 0x1dc) = fVar10;
        return 3;
      }
      *(float *)(param_3 + 4) = *(float *)(param_3 + 8) * 0.7;
      iVar9 = *(int *)(this + 4);
      fVar10 = fVar10 + *(float *)(iVar9 + 0x44);
      iVar9 = *(int *)(iVar9 + 0x50) + -0xa8 + *(int *)(iVar9 + 0x38) * 0xa8;
      fVar12 = *(float *)(iVar9 + 0x38);
      fVar13 = *(float *)(*(int *)(this + 8) + 0x18);
      fVar11 = *(float *)(iVar9 + 0x28);
      *(float *)(param_2 + 4) =
           *(float *)(*(int *)(this + 8) + 0x14) + *(float *)(iVar9 + 0x34) +
           fVar10 * *(float *)(iVar9 + 0x24);
      *(float *)(param_2 + 8) = fVar13 + fVar12 + fVar10 * fVar11;
      iVar9 = *(int *)(this + 0x24);
      uVar4 = *(undefined4 *)(param_2 + 4);
      uVar6 = *(undefined4 *)(param_2 + 8);
      *(undefined4 *)(iVar9 + 0x1d4) = *(undefined4 *)param_2;
      *(undefined4 *)(iVar9 + 0x1d8) = uVar4;
      *(undefined4 *)(iVar9 + 0x1dc) = uVar6;
      return 3;
    }
    fVar12 = *(float *)(iVar9 * 0xa8 + *(int *)(this_00 + 0x50) + 0x8c);
  }
  *(float *)(this + 0x10) = fVar13;
  if (iVar9 == *(int *)(this_00 + 0x38) + -1) {
    iVar8 = iVar9 * 0xa8 + *(int *)(this_00 + 0x4c);
    fVar11 = *(float *)(iVar8 + 0x90);
    fVar12 = *(float *)(iVar8 + 0x9c);
    fVar10 = *(float *)(iVar8 + 0xa0);
  }
  else {
    iVar8 = iVar9 * 0xa8;
    iVar7 = iVar8 + *(int *)(this_00 + 0x4c) + 0xa8;
    iVar5 = *(int *)(this_00 + 0x4c) + iVar8;
    fVar10 = fVar13 / *(float *)(iVar8 + *(int *)(this_00 + 0x50) + 0x8c);
    fVar11 = *(float *)(iVar5 + 0x90) +
             (*(float *)(iVar7 + 0x90) - *(float *)(iVar5 + 0x90)) * fVar10;
    fVar12 = *(float *)(iVar5 + 0x9c) +
             fVar10 * (*(float *)(iVar7 + 0x9c) - *(float *)(iVar5 + 0x9c));
    fVar10 = *(float *)(iVar5 + 0xa0) +
             fVar10 * (*(float *)(iVar7 + 0xa0) - *(float *)(iVar5 + 0xa0));
  }
  uVar14 = (ulonglong)(uint)fVar11;
  if (*(int *)(this_00 + 0x2c) == 0x39) {
    cRPath::HalfPipePos(this_00,fVar10,*(float *)param_2 - fVar11,0.49,(tMatrix *)&local_90,
                        afStack_50);
  }
  else {
    if (*(int *)(this_00 + 0x2c) != 0x3a) {
      iVar8 = *(int *)(this + 8);
      puVar3 = (undefined4 *)(iVar9 * 0xa8 + *(int *)(this_00 + 0x50));
      uVar17 = CONCAT44(puVar3[0xc],puVar3[0x20]);
      uVar16 = CONCAT44(*(undefined4 *)(iVar8 + 0x14),puVar3[0xd]);
      uVar18 = CONCAT44(*(undefined4 *)(iVar8 + 0x10),*(undefined4 *)(iVar8 + 0x18));
      uVar14 = CONCAT44(puVar3[0xe],fVar11);
      uVar15 = CONCAT44(puVar3[0x21],puVar3[0x22]);
      if (iVar9 == *(int *)(this_00 + 0x38) + -1) {
        tMatrix::Identity((tMatrix *)&local_90);
      }
      else {
        local_d0 = *puVar3;
        uStack_cc = puVar3[1];
        uStack_c8 = puVar3[2];
        uStack_c4 = puVar3[3];
        local_c0 = puVar3[4];
        uStack_bc = puVar3[5];
        uStack_b8 = puVar3[6];
        uStack_b4 = puVar3[7];
        local_b0 = puVar3[8];
        uStack_ac = puVar3[9];
        uStack_a8 = puVar3[10];
        uStack_a4 = puVar3[0xb];
        uStack_94 = puVar3[0xf];
        iVar8 = iVar9 * 0xa8 + *(int *)(this_00 + 0x50);
        local_110 = *(undefined4 *)(iVar8 + 0xa8);
        uStack_10c = *(undefined4 *)(iVar8 + 0xac);
        uStack_108 = *(undefined4 *)(iVar8 + 0xb0);
        uStack_104 = *(undefined4 *)(iVar8 + 0xb4);
        local_100 = *(undefined4 *)(iVar8 + 0xb8);
        uStack_fc = *(undefined4 *)(iVar8 + 0xbc);
        uStack_f8 = *(undefined4 *)(iVar8 + 0xc0);
        uStack_f4 = *(undefined4 *)(iVar8 + 0xc4);
        local_f0 = *(undefined4 *)(iVar8 + 200);
        uStack_ec = *(undefined4 *)(iVar8 + 0xcc);
        uStack_e8 = *(undefined4 *)(iVar8 + 0xd0);
        uStack_e4 = *(undefined4 *)(iVar8 + 0xd4);
        uStack_d4 = *(undefined4 *)(iVar8 + 0xe4);
        local_98 = 0;
        local_9c = 0;
        local_a0 = 0;
        local_d8 = 0;
        local_dc = 0;
        local_e0 = 0;
        tMatrix::LinearInterpolate
                  ((tMatrix *)&local_90,(tMatrix *)&local_d0,(tMatrix *)&local_110,
                   *(float *)(this + 0x10) /
                   *(float *)(iVar9 * 0xa8 + *(int *)(this_00 + 0x50) + 0x8c));
      }
      local_90 = local_90 * fVar12;
      iVar9 = *(int *)(this + 0x24);
      local_8c = local_8c * fVar12;
      local_88 = local_88 * fVar12;
      *(float *)(this + 0x14) = *(float *)(this + 0x14) + *(float *)(param_3 + 4);
      fVar10 = *(float *)param_2 - (float)uVar14;
      *(float *)(this + 0x18) =
           (float)((ulonglong)uVar18 >> 0x20) + (float)((ulonglong)uVar17 >> 0x20) +
           fVar13 * (float)uVar17 * fVar12 + fVar10 * local_90;
      *(float *)(this + 0x1c) =
           (float)((ulonglong)uVar16 >> 0x20) + (float)uVar16 +
           fVar13 * (float)((ulonglong)uVar15 >> 0x20) * fVar12 + fVar10 * local_8c;
      *(float *)(this + 0x20) =
           (float)uVar18 + (float)(uVar14 >> 0x20) + fVar13 * (float)uVar15 + fVar10 * local_88;
      goto LAB_0004fc48;
    }
    cRPath::HalfPolePos(this_00,fVar10,*(float *)param_2 - fVar11,0.49,(tMatrix *)&local_90,
                        afStack_50);
  }
  iVar9 = *(int *)(this + 0xc) * 0xa8 + *(int *)(*(int *)(this + 4) + 0x50);
  fVar10 = *(float *)(iVar9 + 0x38);
  fVar11 = *(float *)(*(int *)(this + 8) + 0x18);
  fVar13 = *(float *)(iVar9 + 0x88);
  *(undefined4 *)(this + 0x18) = local_60;
  local_90 = local_90 * fVar12;
  *(float *)(this + 0x20) = fVar11 + fVar10 + *(float *)(this + 0x10) * fVar13;
  local_8c = local_8c * fVar12;
  local_88 = local_88 * fVar12;
  fVar10 = *(float *)(param_3 + 4);
  *(undefined4 *)(this + 0x1c) = local_5c;
  iVar9 = *(int *)(this + 0x24);
  *(float *)(this + 0x14) = *(float *)(this + 0x14) + fVar10;
LAB_0004fc48:
  *(float *)(iVar9 + 0x1a4) = local_90;
  *(float *)(iVar9 + 0x1a8) = local_8c;
  *(float *)(iVar9 + 0x1ac) = local_88;
  iVar9 = *(int *)(this + 0x24);
  *(undefined4 *)(iVar9 + 0x1b4) = local_80;
  *(undefined4 *)(iVar9 + 0x1b8) = uStack_7c;
  *(undefined4 *)(iVar9 + 0x1bc) = uStack_78;
  iVar9 = *(int *)(this + 0x24);
  *(undefined4 *)(iVar9 + 0x1c4) = local_70;
  *(undefined4 *)(iVar9 + 0x1c8) = uStack_6c;
  *(undefined4 *)(iVar9 + 0x1cc) = uStack_68;
  iVar9 = *(int *)(this + 0x24);
  *(undefined4 *)(iVar9 + 0x22c) = *(undefined4 *)(iVar9 + 0x238);
  *(undefined4 *)(iVar9 + 0x230) = *(undefined4 *)(iVar9 + 0x23c);
  *(undefined4 *)(iVar9 + 0x234) = *(undefined4 *)(iVar9 + 0x240);
  fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(this + 4) + 0x48),
                                      (byte)(in_fpscr >> 0x16) & 3);
  if (ABS(*(float *)param_2 - (float)uVar14) <= fVar10 * 0.5 + 0.3) {
    iVar9 = 0;
    if (1 < *(int *)(*(int *)(this + 4) + 0x2c) - 0x39U) {
      *(float *)param_2 = *(float *)param_2 + *(float *)param_3;
    }
  }
  else {
    *this = (cRPathFollowGolb)0x0;
    uVar4 = *(undefined4 *)(this + 0x1c);
    uVar6 = *(undefined4 *)(this + 0x20);
    iVar9 = *(int *)(this + 0x24);
    *(undefined4 *)(iVar9 + 0x1d4) = *(undefined4 *)(this + 0x18);
    *(undefined4 *)(iVar9 + 0x1d8) = uVar4;
    *(undefined4 *)(iVar9 + 0x1dc) = uVar6;
    iVar9 = 1 - *(uint *)(*(int *)(this + 4) + 0x34);
    if (1 < *(uint *)(*(int *)(this + 4) + 0x34)) {
      iVar9 = 0;
    }
  }
  return iVar9;
}
