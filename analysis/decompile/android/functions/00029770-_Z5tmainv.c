/*
 * mangled: _Z5tmainv
 * demangled: tmain()
 * address: 00029770
 * size: 464
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* tmain() */

void tmain(void)

{
  float in_s0;
  float fVar1;
  tMatrix atStack_1a0 [16];
  undefined4 local_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 local_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 local_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 local_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  tMatrix atStack_14c [64];
  undefined4 local_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 local_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 local_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 local_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  tMatrix atStack_cc [64];
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
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;

  local_30 = 0.0;
  local_2c = 0.0;
  local_34 = 1.0;
  local_40 = 0.0;
  local_3c = 1.0;
  local_38 = 0.0;
  tMatrix::tMatrix((tMatrix *)&local_8c,in_s0);
  local_4c = ((local_34 + local_40) - local_34 / 2.0) + local_40 * 3.0;
  local_44 = ((local_2c + local_38) - local_2c / 2.0) + local_38 * 3.0;
  local_48 = ((local_30 + local_3c) - local_30 / 2.0) + local_3c * 3.0;
  tVector::Normalize((tVector *)&local_4c);
  tVector::Cross((tVector *)&local_4c,(tVector *)&local_34,(tVector *)&local_40);
  tMatrix::operator+((tMatrix *)&local_190,(tMatrix *)&local_8c);
  local_8c = local_190;
  uStack_88 = uStack_18c;
  uStack_84 = uStack_188;
  uStack_80 = uStack_184;
  local_7c = local_180;
  uStack_78 = uStack_17c;
  uStack_74 = uStack_178;
  uStack_70 = uStack_174;
  local_6c = local_170;
  uStack_68 = uStack_16c;
  uStack_64 = uStack_168;
  uStack_60 = uStack_164;
  local_5c = local_160;
  uStack_58 = uStack_15c;
  uStack_54 = uStack_158;
  uStack_50 = uStack_154;
  fVar1 = (float)tMatrix::Orthoganalize((tMatrix *)&local_8c);
  tMatrix::tMatrix((tMatrix *)&local_10c,(tVector *)&local_4c,fVar1);
  local_8c = local_10c;
  uStack_88 = uStack_108;
  uStack_84 = uStack_104;
  uStack_80 = uStack_100;
  local_7c = local_fc;
  uStack_78 = uStack_f8;
  uStack_74 = uStack_f4;
  uStack_70 = uStack_f0;
  local_6c = local_ec;
  uStack_68 = uStack_e8;
  uStack_64 = uStack_e4;
  uStack_60 = uStack_e0;
  local_5c = local_dc;
  uStack_58 = uStack_d8;
  uStack_54 = uStack_d4;
  uStack_50 = uStack_d0;
  fVar1 = (float)tMatrix::Invert((tMatrix *)&local_8c);
  fVar1 = (float)tMatrix::tMatrix(atStack_14c,fVar1);
  fVar1 = (float)tMatrix::RotLocalY(atStack_14c,fVar1);
  fVar1 = (float)tMatrix::RotLocalX(atStack_14c,fVar1);
  tMatrix::Interpolate(atStack_14c,fVar1);
  tMatrix::Invert(atStack_cc,atStack_14c);
  tMatrix::Multiply(atStack_cc,atStack_14c);
  tMatrix::operator*(atStack_1a0,(tVector *)atStack_14c);
  tVector::operator*((tVector *)atStack_1a0,(tMatrix *)&local_34);
  return;
}
