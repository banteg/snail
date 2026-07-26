/*
 * mangled: _ZN7cRSnail7AIGoldyEv
 * demangled: cRSnail::AIGoldy()
 * address: 00074fac
 * size: 2040
 */

/* cRSnail::AIGoldy() */

void __thiscall cRSnail::AIGoldy(cRSnail *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  cRSnail *pcVar5;
  tMatrix *this_00;
  cRSnail *pcVar6;
  float fVar7;
  float extraout_s0;
  tMatrix atStack_180 [64];
  undefined4 local_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 local_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  tMatrix atStack_100 [64];
  undefined4 local_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;

  if (*(char *)(Game + 0x718b9) != '\0') {
    return;
  }
  fVar7 = (float)cRSnailSkin::AI((cRSnailSkin *)(this + 6000));
  iVar4 = *(int *)(this + 0xf4);
  if (0.0 < *(float *)(iVar4 + 0x2c4)) {
    fVar7 = *(float *)(iVar4 + 0x2c4) + *(float *)(iVar4 + 0x2c8);
    *(float *)(iVar4 + 0x2c4) = fVar7;
    if (1.0 < fVar7) {
      *(undefined4 *)(iVar4 + 0x2c4) = 0;
    }
    local_80 = *(undefined4 *)(iVar4 + 0x2c);
    uStack_7c = *(undefined4 *)(iVar4 + 0x30);
    uStack_78 = *(undefined4 *)(iVar4 + 0x34);
    uStack_74 = *(undefined4 *)(iVar4 + 0x38);
    local_70 = *(undefined4 *)(iVar4 + 0x3c);
    uStack_6c = *(undefined4 *)(iVar4 + 0x40);
    uStack_68 = *(undefined4 *)(iVar4 + 0x44);
    uStack_64 = *(undefined4 *)(iVar4 + 0x48);
    local_60 = *(undefined4 *)(iVar4 + 0x4c);
    uStack_5c = *(undefined4 *)(iVar4 + 0x50);
    uStack_58 = *(undefined4 *)(iVar4 + 0x54);
    uStack_54 = *(undefined4 *)(iVar4 + 0x58);
    local_50 = *(undefined4 *)(iVar4 + 0x5c);
    uStack_4c = *(undefined4 *)(iVar4 + 0x60);
    uStack_48 = *(undefined4 *)(iVar4 + 100);
    uStack_44 = *(undefined4 *)(iVar4 + 0x68);
    local_c0 = *(undefined4 *)(iVar4 + 0x2c);
    uStack_bc = *(undefined4 *)(iVar4 + 0x30);
    uStack_b8 = *(undefined4 *)(iVar4 + 0x34);
    uStack_b4 = *(undefined4 *)(iVar4 + 0x38);
    local_b0 = *(undefined4 *)(iVar4 + 0x3c);
    uStack_ac = *(undefined4 *)(iVar4 + 0x40);
    uStack_a8 = *(undefined4 *)(iVar4 + 0x44);
    uStack_a4 = *(undefined4 *)(iVar4 + 0x48);
    local_a0 = *(undefined4 *)(iVar4 + 0x4c);
    uStack_9c = *(undefined4 *)(iVar4 + 0x50);
    uStack_98 = *(undefined4 *)(iVar4 + 0x54);
    uStack_94 = *(undefined4 *)(iVar4 + 0x58);
    local_90 = *(undefined4 *)(iVar4 + 0x5c);
    uStack_8c = *(undefined4 *)(iVar4 + 0x60);
    uStack_88 = *(undefined4 *)(iVar4 + 100);
    uStack_84 = *(undefined4 *)(iVar4 + 0x68);
    fVar7 = (float)tMatrix::RotIdentity((tMatrix *)&local_80);
    fVar7 = (float)tMatrix::RotLocalX((tMatrix *)&local_80,fVar7);
    fVar7 = (float)tMatrix::LinearInterpolate
                             ((tMatrix *)(*(int *)(this + 0xf4) + 0x2c),(tMatrix *)&local_80,
                              (tMatrix *)&local_c0,fVar7);
    iVar4 = *(int *)(this + 0xf4);
  }
  else if (*(char *)(iVar4 + 0x415) != '\0') {
    local_80 = *(undefined4 *)(iVar4 + 0x2c);
    uStack_7c = *(undefined4 *)(iVar4 + 0x30);
    uStack_78 = *(undefined4 *)(iVar4 + 0x34);
    uStack_74 = *(undefined4 *)(iVar4 + 0x38);
    local_70 = *(undefined4 *)(iVar4 + 0x3c);
    uStack_6c = *(undefined4 *)(iVar4 + 0x40);
    uStack_68 = *(undefined4 *)(iVar4 + 0x44);
    uStack_64 = *(undefined4 *)(iVar4 + 0x48);
    local_60 = *(undefined4 *)(iVar4 + 0x4c);
    uStack_5c = *(undefined4 *)(iVar4 + 0x50);
    uStack_58 = *(undefined4 *)(iVar4 + 0x54);
    uStack_54 = *(undefined4 *)(iVar4 + 0x58);
    local_50 = *(undefined4 *)(iVar4 + 0x5c);
    uStack_4c = *(undefined4 *)(iVar4 + 0x60);
    uStack_48 = *(undefined4 *)(iVar4 + 100);
    uStack_44 = *(undefined4 *)(iVar4 + 0x68);
    local_c0 = *(undefined4 *)(iVar4 + 0x2c);
    uStack_bc = *(undefined4 *)(iVar4 + 0x30);
    uStack_b8 = *(undefined4 *)(iVar4 + 0x34);
    uStack_b4 = *(undefined4 *)(iVar4 + 0x38);
    local_b0 = *(undefined4 *)(iVar4 + 0x3c);
    uStack_ac = *(undefined4 *)(iVar4 + 0x40);
    uStack_a8 = *(undefined4 *)(iVar4 + 0x44);
    uStack_a4 = *(undefined4 *)(iVar4 + 0x48);
    local_a0 = *(undefined4 *)(iVar4 + 0x4c);
    uStack_9c = *(undefined4 *)(iVar4 + 0x50);
    uStack_98 = *(undefined4 *)(iVar4 + 0x54);
    uStack_94 = *(undefined4 *)(iVar4 + 0x58);
    local_90 = *(undefined4 *)(iVar4 + 0x5c);
    uStack_8c = *(undefined4 *)(iVar4 + 0x60);
    uStack_88 = *(undefined4 *)(iVar4 + 100);
    uStack_84 = *(undefined4 *)(iVar4 + 0x68);
    fVar7 = (float)tMatrix::RotIdentity((tMatrix *)&local_80);
    fVar7 = (float)tMatrix::LinearInterpolate
                             ((tMatrix *)(*(int *)(this + 0xf4) + 0x2c),(tMatrix *)&local_80,
                              (tMatrix *)&local_c0,fVar7);
    iVar4 = *(int *)(this + 0xf4);
  }
  this_00 = (tMatrix *)(this + 0x2c);
  uVar1 = *(undefined4 *)(iVar4 + 0x30);
  uVar2 = *(undefined4 *)(iVar4 + 0x34);
  uVar3 = *(undefined4 *)(iVar4 + 0x38);
  *(undefined4 *)this_00 = *(undefined4 *)(iVar4 + 0x2c);
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
  uVar1 = *(undefined4 *)(iVar4 + 0x27e4);
  uVar2 = *(undefined4 *)(iVar4 + 0x27e8);
  *(undefined4 *)(this + 0x5c) = *(undefined4 *)(iVar4 + 0x27e0);
  *(undefined4 *)(this + 0x60) = uVar1;
  *(undefined4 *)(this + 100) = uVar2;
  local_80 = *(undefined4 *)this_00;
  uStack_7c = *(undefined4 *)(this + 0x30);
  uStack_78 = *(undefined4 *)(this + 0x34);
  uStack_74 = *(undefined4 *)(this + 0x38);
  local_70 = *(undefined4 *)(this + 0x3c);
  uStack_6c = *(undefined4 *)(this + 0x40);
  uStack_68 = *(undefined4 *)(this + 0x44);
  uStack_64 = *(undefined4 *)(this + 0x48);
  local_60 = *(undefined4 *)(this + 0x4c);
  uStack_5c = *(undefined4 *)(this + 0x50);
  uStack_58 = *(undefined4 *)(this + 0x54);
  uStack_54 = *(undefined4 *)(this + 0x58);
  local_50 = *(undefined4 *)(this + 0x5c);
  uStack_4c = *(undefined4 *)(this + 0x60);
  uStack_48 = *(undefined4 *)(this + 100);
  uStack_44 = *(undefined4 *)(this + 0x68);
  fVar7 = (float)tMatrix::LinearInterpolate
                           (this_00,(tMatrix *)&local_80,(tMatrix *)(this + 0xb4),fVar7);
  *(undefined4 *)(this + 0x5c) = local_50;
  *(undefined4 *)(this + 0x60) = uStack_4c;
  *(undefined4 *)(this + 100) = uStack_48;
  if (0.0 < *(float *)(this + 0x40)) {
    tMatrix::RotLocalY(this_00,fVar7);
  }
  fVar7 = *(float *)(this + 0x1418) + *(float *)(this + 0x141c);
  *(float *)(this + 0x1418) = fVar7;
  if (1.0 < fVar7) {
    *(float *)(this + 0x1418) = fVar7 - 1.0;
  }
  fVar7 = *(float *)(this + 0x1420) + *(float *)(this + 0x1424);
  *(float *)(this + 0x1420) = fVar7;
  if (1.0 < fVar7) {
    *(float *)(this + 0x1420) = fVar7 - 1.0;
  }
  local_140 = *(undefined4 *)this_00;
  uStack_13c = *(undefined4 *)(this + 0x30);
  uStack_138 = *(undefined4 *)(this + 0x34);
  uStack_134 = *(undefined4 *)(this + 0x38);
  local_130 = *(undefined4 *)(this + 0x3c);
  uStack_12c = *(undefined4 *)(this + 0x40);
  uStack_128 = *(undefined4 *)(this + 0x44);
  uStack_124 = *(undefined4 *)(this + 0x48);
  local_120 = *(undefined4 *)(this + 0x4c);
  uStack_11c = *(undefined4 *)(this + 0x50);
  uStack_118 = *(undefined4 *)(this + 0x54);
  uStack_114 = *(undefined4 *)(this + 0x58);
  local_110 = *(undefined4 *)(this + 0x5c);
  uStack_10c = *(undefined4 *)(this + 0x60);
  uStack_108 = *(undefined4 *)(this + 100);
  uStack_104 = *(undefined4 *)(this + 0x68);
  fVar7 = (float)tMatrix::Identity(atStack_100);
  fVar7 = (float)Sin(fVar7);
  tMatrix::RotLocalZ(atStack_100,fVar7);
  tMatrix::Invert(atStack_180,this_00);
  tMatrix::operator*=(this_00,atStack_180);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + 1.3;
  tMatrix::operator*=(this_00,atStack_100);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) - 1.3;
  fVar7 = (float)tMatrix::operator*=(this_00,(tMatrix *)&local_140);
  fVar7 = (float)Sin(fVar7);
  *(float *)(this + 100) = *(float *)(this + 100) + fVar7 * *(float *)(this + 0x44) * 0.03;
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + fVar7 * *(float *)(this + 0x40) * 0.03;
  *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + fVar7 * *(float *)(this + 0x3c) * 0.03;
  *(undefined4 *)(this + 0xb4) = *(undefined4 *)(this + 0x2c);
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
  *(undefined4 *)(this + 0xe4) = *(undefined4 *)(this + 0x5c);
  *(undefined4 *)(this + 0xe8) = *(undefined4 *)(this + 0x60);
  *(undefined4 *)(this + 0xec) = *(undefined4 *)(this + 100);
  *(undefined4 *)(this + 0xf0) = *(undefined4 *)(this + 0x68);
  if (0.0 < *(float *)(this + 0x1764)) {
    tMatrix::RotLocalY(this_00,extraout_s0);
    fVar7 = *(float *)(this + 0x1764);
    *(float *)(this + 0x1764) = fVar7 + *(float *)(this + 0x1768);
    if (1.0 < fVar7 + *(float *)(this + 0x1768)) {
      *(undefined4 *)(this + 0x1764) = 0x3f800000;
    }
  }
  if (this[0x176c] == (cRSnail)0x0) {
    pcVar5 = this + 0x2c;
    *(undefined4 *)(this + 0x10b0) = *(undefined4 *)(this + 0x2c);
    *(undefined4 *)(this + 0x10b4) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x10b8) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0x10bc) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0x10c0) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0x10c4) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0x10c8) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0x10cc) = *(undefined4 *)(this + 0x48);
    *(undefined4 *)(this + 0x10d0) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0x10d4) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0x10d8) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0x10dc) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0x10e0) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(this + 0x10e4) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0x10e8) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0x10ec) = *(undefined4 *)(this + 0x68);
    *(undefined4 *)(this + 0x5f4) = *(undefined4 *)pcVar5;
    *(undefined4 *)(this + 0x5f8) = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x5fc) = *(undefined4 *)(this + 0x34);
    *(undefined4 *)(this + 0x600) = *(undefined4 *)(this + 0x38);
    *(undefined4 *)(this + 0x604) = *(undefined4 *)(this + 0x3c);
    *(undefined4 *)(this + 0x608) = *(undefined4 *)(this + 0x40);
    *(undefined4 *)(this + 0x60c) = *(undefined4 *)(this + 0x44);
    *(undefined4 *)(this + 0x610) = *(undefined4 *)(this + 0x48);
    pcVar6 = this + 0x5c;
    *(undefined4 *)(this + 0x614) = *(undefined4 *)(this + 0x4c);
    *(undefined4 *)(this + 0x618) = *(undefined4 *)(this + 0x50);
    *(undefined4 *)(this + 0x61c) = *(undefined4 *)(this + 0x54);
    *(undefined4 *)(this + 0x620) = *(undefined4 *)(this + 0x58);
    *(undefined4 *)(this + 0x624) = *(undefined4 *)pcVar6;
    *(undefined4 *)(this + 0x628) = *(undefined4 *)(this + 0x60);
    *(undefined4 *)(this + 0x62c) = *(undefined4 *)(this + 100);
    *(undefined4 *)(this + 0x630) = *(undefined4 *)(this + 0x68);
    *(undefined4 *)(this + 0xd1c) = *(undefined4 *)pcVar5;
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
    *(undefined4 *)(this + 0x988) = *(undefined4 *)pcVar5;
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
  *(undefined4 *)(this + 0x1454) = *(undefined4 *)(this + 0x2c);
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
  uVar1 = *(undefined4 *)(iVar4 + 0x27e4);
  uVar2 = *(undefined4 *)(iVar4 + 0x27e8);
  *(undefined4 *)(this + 0x14f8) = *(undefined4 *)(iVar4 + 0x27e0);
  *(undefined4 *)(this + 0x14fc) = uVar1;
  *(undefined4 *)(this + 0x1500) = uVar2;
  BuildHotSpots(this);
  if (*(int *)(this + 0x179c) == 0) {
    if (*(int *)(this + 0x134) == 0) {
      iVar4 = *(int *)(this + 0xf4);
      if (*(char *)(iVar4 + 0x2c0) != '\0') goto LAB_00075504;
      SetAnimation(this,1,false,-1);
    }
    iVar4 = *(int *)(this + 0xf4);
  }
  else {
    cRCutScene::AI((cRCutScene *)(this + 0x1790));
    iVar4 = *(int *)(this + 0xf4);
  }
LAB_00075504:
  cRSubHover::Jets((cRSubHover *)(iVar4 + 0x25cc));
  return;
}
