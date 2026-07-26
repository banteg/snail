/*
 * mangled: _ZN7cRSnail7AIGoldyEv
 * demangled: cRSnail::AIGoldy()
 * address: 00023df4
 * size: 2204
 */

/* cRSnail::AIGoldy() */

void __thiscall cRSnail::AIGoldy(cRSnail *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  tMatrix *this_00;
  int iVar5;
  cRSnail *pcVar6;
  cRSnail *pcVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  tMatrix atStack_17c [64];
  undefined4 local_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 local_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 local_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 local_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  tMatrix atStack_fc [64];
  undefined4 local_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 local_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 local_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  tVector atStack_3c [28];

  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) != '\0') {
    return;
  }
  **(uint **)(*(int *)(this + 0x1780) + 0x24) = **(uint **)(*(int *)(this + 0x1780) + 0x24) | 8;
  *(undefined4 *)(*(int *)(*(int *)(this + 0x1780) + 0x24) + 0xc) =
       *(undefined4 *)(this + (*(int *)(this + 6000) + 1) * 4 + 6000);
  if (*(int *)(this + 0x1784) == 1) {
    pcVar6 = this + 0x1788;
    fVar8 = *(float *)pcVar6;
    iVar4 = *(int *)(this + 0xf4);
    *(float *)pcVar6 = fVar8 + *(float *)(this + 0x178c);
    if (1.0 < fVar8 + *(float *)(this + 0x178c)) {
      *(undefined4 *)pcVar6 = 0;
      *(undefined4 *)(this + 0x1784) = 0;
      *(undefined4 *)(this + 6000) = 0;
    }
    fVar8 = *(float *)(iVar4 + 0x2c4);
  }
  else {
    iVar4 = *(int *)(this + 0xf4);
    fVar8 = *(float *)(iVar4 + 0x2c4);
  }
  if (0.0 < fVar8) {
    *(float *)(iVar4 + 0x2c4) = fVar8 + *(float *)(iVar4 + 0x2c8);
    iVar4 = *(int *)(this + 0xf4);
    if (1.0 < *(float *)(iVar4 + 0x2c4)) {
      *(undefined4 *)(iVar4 + 0x2c4) = 0;
      iVar4 = *(int *)(this + 0xf4);
    }
    local_7c = *(undefined4 *)(iVar4 + 0x2c);
    uStack_78 = *(undefined4 *)(iVar4 + 0x30);
    uStack_74 = *(undefined4 *)(iVar4 + 0x34);
    uStack_70 = *(undefined4 *)(iVar4 + 0x38);
    local_6c = *(undefined4 *)(iVar4 + 0x3c);
    uStack_68 = *(undefined4 *)(iVar4 + 0x40);
    uStack_64 = *(undefined4 *)(iVar4 + 0x44);
    uStack_60 = *(undefined4 *)(iVar4 + 0x48);
    local_5c = *(undefined4 *)(iVar4 + 0x4c);
    uStack_58 = *(undefined4 *)(iVar4 + 0x50);
    uStack_54 = *(undefined4 *)(iVar4 + 0x54);
    uStack_50 = *(undefined4 *)(iVar4 + 0x58);
    local_4c = *(undefined4 *)(iVar4 + 0x5c);
    uStack_48 = *(undefined4 *)(iVar4 + 0x60);
    uStack_44 = *(undefined4 *)(iVar4 + 100);
    uStack_40 = *(undefined4 *)(iVar4 + 0x68);
    local_bc = *(undefined4 *)(iVar4 + 0x2c);
    uStack_b8 = *(undefined4 *)(iVar4 + 0x30);
    uStack_b4 = *(undefined4 *)(iVar4 + 0x34);
    uStack_b0 = *(undefined4 *)(iVar4 + 0x38);
    local_ac = *(undefined4 *)(iVar4 + 0x3c);
    uStack_a8 = *(undefined4 *)(iVar4 + 0x40);
    uStack_a4 = *(undefined4 *)(iVar4 + 0x44);
    uStack_a0 = *(undefined4 *)(iVar4 + 0x48);
    local_9c = *(undefined4 *)(iVar4 + 0x4c);
    uStack_98 = *(undefined4 *)(iVar4 + 0x50);
    uStack_94 = *(undefined4 *)(iVar4 + 0x54);
    uStack_90 = *(undefined4 *)(iVar4 + 0x58);
    local_8c = *(undefined4 *)(iVar4 + 0x5c);
    uStack_88 = *(undefined4 *)(iVar4 + 0x60);
    uStack_84 = *(undefined4 *)(iVar4 + 100);
    uStack_80 = *(undefined4 *)(iVar4 + 0x68);
    tMatrix::RotIdentity((tMatrix *)&local_7c);
    fVar8 = -6.2831855;
    fVar9 = (*(float *)(*(int *)(this + 0xf4) + 0x2c4) * -6.2831855 - 0.7853982) * 1.4;
    if (-6.2831855 <= fVar9) {
      fVar8 = fVar9;
    }
    tMatrix::RotLocalX((tMatrix *)&local_7c,fVar8);
    tMatrix::LinearInterpolate
              ((tMatrix *)(*(int *)(this + 0xf4) + 0x2c),(tMatrix *)&local_7c,(tMatrix *)&local_bc,
               0.94);
    iVar4 = *(int *)(this + 0xf4);
  }
  else if (*(char *)(iVar4 + 0x40d) != '\0') {
    local_7c = *(undefined4 *)(iVar4 + 0x2c);
    uStack_78 = *(undefined4 *)(iVar4 + 0x30);
    uStack_74 = *(undefined4 *)(iVar4 + 0x34);
    uStack_70 = *(undefined4 *)(iVar4 + 0x38);
    local_6c = *(undefined4 *)(iVar4 + 0x3c);
    uStack_68 = *(undefined4 *)(iVar4 + 0x40);
    uStack_64 = *(undefined4 *)(iVar4 + 0x44);
    uStack_60 = *(undefined4 *)(iVar4 + 0x48);
    local_5c = *(undefined4 *)(iVar4 + 0x4c);
    uStack_58 = *(undefined4 *)(iVar4 + 0x50);
    uStack_54 = *(undefined4 *)(iVar4 + 0x54);
    uStack_50 = *(undefined4 *)(iVar4 + 0x58);
    local_4c = *(undefined4 *)(iVar4 + 0x5c);
    uStack_48 = *(undefined4 *)(iVar4 + 0x60);
    uStack_44 = *(undefined4 *)(iVar4 + 100);
    uStack_40 = *(undefined4 *)(iVar4 + 0x68);
    local_bc = *(undefined4 *)(iVar4 + 0x2c);
    uStack_b8 = *(undefined4 *)(iVar4 + 0x30);
    uStack_b4 = *(undefined4 *)(iVar4 + 0x34);
    uStack_b0 = *(undefined4 *)(iVar4 + 0x38);
    local_ac = *(undefined4 *)(iVar4 + 0x3c);
    uStack_a8 = *(undefined4 *)(iVar4 + 0x40);
    uStack_a4 = *(undefined4 *)(iVar4 + 0x44);
    uStack_a0 = *(undefined4 *)(iVar4 + 0x48);
    local_9c = *(undefined4 *)(iVar4 + 0x4c);
    uStack_98 = *(undefined4 *)(iVar4 + 0x50);
    uStack_94 = *(undefined4 *)(iVar4 + 0x54);
    uStack_90 = *(undefined4 *)(iVar4 + 0x58);
    local_8c = *(undefined4 *)(iVar4 + 0x5c);
    uStack_88 = *(undefined4 *)(iVar4 + 0x60);
    uStack_84 = *(undefined4 *)(iVar4 + 100);
    uStack_80 = *(undefined4 *)(iVar4 + 0x68);
    tMatrix::RotIdentity((tMatrix *)&local_7c);
    tMatrix::LinearInterpolate
              ((tMatrix *)(*(int *)(this + 0xf4) + 0x2c),(tMatrix *)&local_7c,(tMatrix *)&local_bc,
               0.97);
    iVar4 = *(int *)(this + 0xf4);
  }
  uVar1 = *(undefined4 *)(iVar4 + 0x30);
  uVar2 = *(undefined4 *)(iVar4 + 0x34);
  uVar3 = *(undefined4 *)(iVar4 + 0x38);
  *(undefined4 *)(this + 0x2c) = *(undefined4 *)(iVar4 + 0x2c);
  *(undefined4 *)(this + 0x30) = uVar1;
  *(undefined4 *)(this + 0x34) = uVar2;
  *(undefined4 *)(this + 0x38) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x40);
  uVar2 = *(undefined4 *)(iVar4 + 0x44);
  uVar3 = *(undefined4 *)(iVar4 + 0x48);
  *(undefined4 *)(this + 0x3c) = *(undefined4 *)(iVar4 + 0x3c);
  *(undefined4 *)(this + 0x40) = uVar1;
  *(undefined4 *)(this + 0x44) = uVar2;
  *(undefined4 *)(this + 0x48) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x50);
  uVar2 = *(undefined4 *)(iVar4 + 0x54);
  uVar3 = *(undefined4 *)(iVar4 + 0x58);
  *(undefined4 *)(this + 0x4c) = *(undefined4 *)(iVar4 + 0x4c);
  *(undefined4 *)(this + 0x50) = uVar1;
  *(undefined4 *)(this + 0x54) = uVar2;
  *(undefined4 *)(this + 0x58) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x60);
  uVar2 = *(undefined4 *)(iVar4 + 100);
  uVar3 = *(undefined4 *)(iVar4 + 0x68);
  *(undefined4 *)(this + 0x5c) = *(undefined4 *)(iVar4 + 0x5c);
  *(undefined4 *)(this + 0x60) = uVar1;
  *(undefined4 *)(this + 100) = uVar2;
  *(undefined4 *)(this + 0x68) = uVar3;
  this_00 = (tMatrix *)(this + 0x2c);
  uVar1 = *(undefined4 *)(&DAT_000027dc + iVar4);
  uVar2 = *(undefined4 *)(&DAT_000027e0 + iVar4);
  *(undefined4 *)(this + 0x5c) = *(undefined4 *)(&DAT_000027d8 + iVar4);
  *(undefined4 *)(this + 0x60) = uVar1;
  *(undefined4 *)(this + 100) = uVar2;
  local_7c = *(undefined4 *)(this + 0x2c);
  uStack_78 = *(undefined4 *)(this + 0x30);
  uStack_74 = *(undefined4 *)(this + 0x34);
  uStack_70 = *(undefined4 *)(this + 0x38);
  local_6c = *(undefined4 *)(this + 0x3c);
  uStack_68 = *(undefined4 *)(this + 0x40);
  uStack_64 = *(undefined4 *)(this + 0x44);
  uStack_60 = *(undefined4 *)(this + 0x48);
  local_5c = *(undefined4 *)(this + 0x4c);
  uStack_58 = *(undefined4 *)(this + 0x50);
  uStack_54 = *(undefined4 *)(this + 0x54);
  uStack_50 = *(undefined4 *)(this + 0x58);
  local_4c = *(undefined4 *)(this + 0x5c);
  uStack_48 = *(undefined4 *)(this + 0x60);
  uStack_44 = *(undefined4 *)(this + 100);
  uStack_40 = *(undefined4 *)(this + 0x68);
  tMatrix::LinearInterpolate
            ((tMatrix *)(this + 0x2c),(tMatrix *)&local_7c,(tMatrix *)(this + 0xb4),0.7);
  *(undefined4 *)(this + 0x5c) = local_4c;
  *(undefined4 *)(this + 0x60) = uStack_48;
  *(undefined4 *)(this + 100) = uStack_44;
  if (0.0 < *(float *)(this + 0x40)) {
    tMatrix::RotLocalY(this_00,(*(float *)(this + 0x5c) - *(float *)(this + 0xe4)) * 0.8);
  }
  pcVar6 = this + 0x1418;
  fVar10 = 1.0;
  pcVar7 = this + 0x1420;
  fVar8 = *(float *)pcVar6 + *(float *)(this + 0x141c);
  fVar11 = 6.2831855;
  fVar9 = 1.3;
  *(float *)pcVar6 = fVar8;
  if (1.0 < fVar8) {
    *(float *)pcVar6 = fVar8 - 1.0;
  }
  local_13c = *(undefined4 *)this_00;
  uStack_138 = *(undefined4 *)(this + 0x30);
  uStack_134 = *(undefined4 *)(this + 0x34);
  uStack_130 = *(undefined4 *)(this + 0x38);
  fVar8 = *(float *)pcVar7 + *(float *)(this + 0x1424);
  *(float *)pcVar7 = fVar8;
  if (1.0 < fVar8) {
    *(float *)pcVar7 = fVar8 - 1.0;
  }
  local_12c = *(undefined4 *)(this + 0x3c);
  uStack_128 = *(undefined4 *)(this + 0x40);
  uStack_124 = *(undefined4 *)(this + 0x44);
  uStack_120 = *(undefined4 *)(this + 0x48);
  local_11c = *(undefined4 *)(this + 0x4c);
  uStack_118 = *(undefined4 *)(this + 0x50);
  uStack_114 = *(undefined4 *)(this + 0x54);
  uStack_110 = *(undefined4 *)(this + 0x58);
  local_10c = *(undefined4 *)(this + 0x5c);
  uStack_108 = *(undefined4 *)(this + 0x60);
  uStack_104 = *(undefined4 *)(this + 100);
  uStack_100 = *(undefined4 *)(this + 0x68);
  tMatrix::Identity(atStack_fc);
  fVar8 = (float)Sin(*(float *)pcVar6 * fVar11);
  tMatrix::RotLocalZ(atStack_fc,fVar8 * 0.01745);
  tMatrix::Invert(atStack_17c,this_00);
  tMatrix::operator*=(this_00,atStack_17c);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + fVar9;
  tMatrix::operator*=(this_00,atStack_fc);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) - fVar9;
  tMatrix::operator*=(this_00,(tMatrix *)&local_13c);
  fVar8 = (float)Sin(*(float *)pcVar7 * fVar11);
  *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + fVar8 * *(float *)(this + 0x3c) * 0.03;
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + fVar8 * *(float *)(this + 0x40) * 0.03;
  *(float *)(this + 100) = *(float *)(this + 100) + fVar8 * *(float *)(this + 0x44) * 0.03;
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)this_00;
  *(undefined4 *)(this + 0xb8) = *(undefined4 *)(this + 0x30);
  *(undefined4 *)(this + 0xbc) = *(undefined4 *)(this + 0x34);
  *(undefined4 *)(this + 0xc0) = *(undefined4 *)(this + 0x38);
  *(undefined4 *)(this + 0xc4) = *(undefined4 *)(this + 0x3c);
  *(undefined4 *)(this + 200) = *(undefined4 *)(this + 0x40);
  *(undefined4 *)(this + 0xcc) = *(undefined4 *)(this + 0x44);
  *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 0x4c);
  *(undefined4 *)(this + 0xd8) = *(undefined4 *)(this + 0x50);
  *(undefined4 *)(this + 0xdc) = *(undefined4 *)(this + 0x54);
  *(undefined4 *)(this + 0xe0) = *(undefined4 *)(this + 0x58);
  pcVar6 = this + 0x1764;
  *(undefined4 *)(this + 0xe4) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0xe8) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0xec) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0xf0) = *(undefined4 *)(this + 0x68);
  if (0.0 < *(float *)pcVar6) {
    tMatrix::RotLocalY(this_00,*(float *)pcVar6 * -2.0943952);
    fVar8 = *(float *)pcVar6 + *(float *)(this + 0x1768);
    if (fVar10 < *(float *)pcVar6 + *(float *)(this + 0x1768)) {
      fVar8 = fVar10;
    }
    *(float *)pcVar6 = fVar8;
  }
  if (this[0x176c] == (cRSnail)0x0) {
    *(undefined4 *)(this + 0x10b0) = *(undefined4 *)this_00;
    *(undefined4 *)(this + 0x10b4) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x10b8) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0x10bc) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0x10c0) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0x10c4) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0x10c8) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0x10cc) = *(undefined4 *)(this + 0x48);
    pcVar6 = this + 0x5c;
    *(undefined4 *)(this + 0x10d0) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0x10d4) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0x10d8) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0x10dc) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0x10e0) = *(undefined4 *)pcVar6;
    *(undefined4 *)(this + 0x10e4) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0x10e8) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0x10ec) = *(undefined4 *)(this + 0x68);
    *(undefined4 *)(this + 0x5f4) = *(undefined4 *)this_00;
    *(undefined4 *)(this + 0x5f8) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x5fc) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0x600) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0x604) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0x608) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0x60c) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0x610) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0x614) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0x618) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0x61c) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0x620) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0x624) = *(undefined4 *)pcVar6;
    *(undefined4 *)(this + 0x628) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0x62c) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0x630) = *(undefined4 *)(this + 0x68);
    *(undefined4 *)(this + 0xd1c) = *(undefined4 *)this_00;
    *(undefined4 *)(this + 0xd20) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0xd24) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0xd28) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0xd2c) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0xd30) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0xd34) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0xd38) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0xd3c) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0xd40) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0xd44) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0xd48) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0xd4c) = *(undefined4 *)pcVar6;
    *(undefined4 *)(this + 0xd50) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0xd54) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0xd58) = *(undefined4 *)(this + 0x68);
    *(undefined4 *)(this + 0x988) = *(undefined4 *)this_00;
    *(undefined4 *)(this + 0x98c) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x990) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0x994) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0x998) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0x99c) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0x9a0) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0x9a4) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0x9a8) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0x9ac) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0x9b0) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0x9b4) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0x9b8) = *(undefined4 *)pcVar6;
    *(undefined4 *)(this + 0x9bc) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0x9c0) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0x9c4) = *(undefined4 *)(this + 0x68);
  }
  else {
    *(float *)(this + 0x10e0) = *(float *)(this + 0x10e0) + *(float *)(this + 0x140c);
    *(float *)(this + 0x10e4) = *(float *)(this + 0x10e4) + *(float *)(this + 0x1410);
    *(float *)(this + 0x10e8) = *(float *)(this + 0x10e8) + *(float *)(this + 0x1414);
    *(float *)(this + 0x624) = *(float *)(this + 0x624) + *(float *)(this + 0x950);
    *(float *)(this + 0x628) = *(float *)(this + 0x628) + *(float *)(this + 0x954);
    *(float *)(this + 0x62c) = *(float *)(this + 0x62c) + *(float *)(this + 0x958);
    *(float *)(this + 0xd4c) = *(float *)(this + 0xd4c) + *(float *)(this + 0x1078);
    *(float *)(this + 0xd50) = *(float *)(this + 0xd50) + *(float *)(this + 0x107c);
    *(float *)(this + 0xd54) = *(float *)(this + 0xd54) + *(float *)(this + 0x1080);
    *(float *)(this + 0x9b8) = *(float *)(this + 0x9b8) + *(float *)(this + 0xce4);
    *(float *)(this + 0x9bc) = *(float *)(this + 0x9bc) + *(float *)(this + 0xce8);
    *(float *)(this + 0x9c0) = *(float *)(this + 0x9c0) + *(float *)(this + 0xcec);
  }
  iVar4 = *(int *)(this + 0xf4);
  iVar5 = 0;
  *(undefined4 *)(this + 0x1454) = *(undefined4 *)this_00;
  *(undefined4 *)(this + 0x1458) = *(undefined4 *)(this + 0x30);
  *(undefined4 *)(this + 0x145c) = *(undefined4 *)(this + 0x34);
  *(undefined4 *)(this + 0x1460) = *(undefined4 *)(this + 0x38);
  *(undefined4 *)(this + 0x1464) = *(undefined4 *)(this + 0x3c);
  *(undefined4 *)(this + 0x1468) = *(undefined4 *)(this + 0x40);
  *(undefined4 *)(this + 0x146c) = *(undefined4 *)(this + 0x44);
  *(undefined4 *)(this + 0x1470) = *(undefined4 *)(this + 0x48);
  *(undefined4 *)(this + 0x1474) = *(undefined4 *)(this + 0x4c);
  *(undefined4 *)(this + 0x1478) = *(undefined4 *)(this + 0x50);
  *(undefined4 *)(this + 0x147c) = *(undefined4 *)(this + 0x54);
  *(undefined4 *)(this + 0x1480) = *(undefined4 *)(this + 0x58);
  *(undefined4 *)(this + 0x1484) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0x1488) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0x148c) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0x1490) = *(undefined4 *)(this + 0x68);
  uVar1 = *(undefined4 *)(iVar4 + 0x30);
  uVar2 = *(undefined4 *)(iVar4 + 0x34);
  uVar3 = *(undefined4 *)(iVar4 + 0x38);
  *(undefined4 *)(this + 0x14c8) = *(undefined4 *)(iVar4 + 0x2c);
  *(undefined4 *)(this + 0x14cc) = uVar1;
  *(undefined4 *)(this + 0x14d0) = uVar2;
  *(undefined4 *)(this + 0x14d4) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x40);
  uVar2 = *(undefined4 *)(iVar4 + 0x44);
  uVar3 = *(undefined4 *)(iVar4 + 0x48);
  *(undefined4 *)(this + 0x14d8) = *(undefined4 *)(iVar4 + 0x3c);
  *(undefined4 *)(this + 0x14dc) = uVar1;
  *(undefined4 *)(this + 0x14e0) = uVar2;
  *(undefined4 *)(this + 0x14e4) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x50);
  uVar2 = *(undefined4 *)(iVar4 + 0x54);
  uVar3 = *(undefined4 *)(iVar4 + 0x58);
  *(undefined4 *)(this + 0x14e8) = *(undefined4 *)(iVar4 + 0x4c);
  *(undefined4 *)(this + 0x14ec) = uVar1;
  *(undefined4 *)(this + 0x14f0) = uVar2;
  *(undefined4 *)(this + 0x14f4) = uVar3;
  uVar1 = *(undefined4 *)(iVar4 + 0x60);
  uVar2 = *(undefined4 *)(iVar4 + 100);
  uVar3 = *(undefined4 *)(iVar4 + 0x68);
  *(undefined4 *)(this + 0x14f8) = *(undefined4 *)(iVar4 + 0x5c);
  *(undefined4 *)(this + 0x14fc) = uVar1;
  *(undefined4 *)(this + 0x1500) = uVar2;
  *(undefined4 *)(this + 0x1504) = uVar3;
  uVar1 = *(undefined4 *)(&DAT_000027dc + iVar4);
  uVar2 = *(undefined4 *)(&DAT_000027e0 + iVar4);
  pcVar6 = this + 0x1510;
  *(undefined4 *)(this + 0x14f8) = *(undefined4 *)(&DAT_000027d8 + iVar4);
  *(undefined4 *)(this + 0x14fc) = uVar1;
  *(undefined4 *)(this + 0x1500) = uVar2;
  do {
    while (_memcpy(atStack_3c,pcVar6,0xc), 10 < iVar5) {
      iVar5 = iVar5 + 1;
      tVector::operator*=(atStack_3c,*(undefined4 *)(this + 0x1454),*(undefined4 *)(this + 0x1458),
                          *(undefined4 *)(this + 0x145c),*(undefined4 *)(this + 0x1460),
                          *(undefined4 *)(this + 0x1464),*(undefined4 *)(this + 0x1468),
                          *(undefined4 *)(this + 0x146c),*(undefined4 *)(this + 0x1470),
                          *(undefined4 *)(this + 0x1474),*(undefined4 *)(this + 0x1478),
                          *(undefined4 *)(this + 0x147c),*(undefined4 *)(this + 0x1480),
                          *(undefined4 *)(this + 0x1484),*(undefined4 *)(this + 0x1488),
                          *(undefined4 *)(this + 0x148c),*(undefined4 *)(this + 0x1490));
      _memcpy(pcVar6 + 0xe4,atStack_3c,0xc);
      pcVar6 = pcVar6 + 0xc;
      if (iVar5 == 0x13) goto LAB_00024448;
    }
    iVar5 = iVar5 + 1;
    tVector::operator*=(atStack_3c,*(undefined4 *)(this + 0x14c8),*(undefined4 *)(this + 0x14cc),
                        *(undefined4 *)(this + 0x14d0),*(undefined4 *)(this + 0x14d4),
                        *(undefined4 *)(this + 0x14d8),*(undefined4 *)(this + 0x14dc),
                        *(undefined4 *)(this + 0x14e0),*(undefined4 *)(this + 0x14e4),
                        *(undefined4 *)(this + 0x14e8),*(undefined4 *)(this + 0x14ec),
                        *(undefined4 *)(this + 0x14f0),*(undefined4 *)(this + 0x14f4),
                        *(undefined4 *)(this + 0x14f8),*(undefined4 *)(this + 0x14fc),
                        *(undefined4 *)(this + 0x1500),*(undefined4 *)(this + 0x1504));
    _memcpy(pcVar6 + 0xe4,atStack_3c,0xc);
    pcVar6 = pcVar6 + 0xc;
  } while (iVar5 != 0x13);
LAB_00024448:
  if (*(int *)(this + 0x179c) == 0) {
    if (*(int *)(this + 0x134) == 0) {
      iVar4 = *(int *)(this + 0xf4);
      if (*(char *)(iVar4 + 0x2c0) == '\0') {
        *(undefined4 *)(this + 0x10c) = 1;
        *(undefined4 *)(this + 0x134) = 1;
      }
    }
    else {
      iVar4 = *(int *)(this + 0xf4);
    }
  }
  else {
    cRCutScene::AI((cRCutScene *)(this + 0x1790));
    iVar4 = *(int *)(this + 0xf4);
  }
  cRSubHover::Jets((cRSubHover *)(&DAT_000025c4 + iVar4));
  return;
}
