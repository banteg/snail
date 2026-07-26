/*
 * mangled: _ZN7tMatrix11InterpolateEf
 * demangled: tMatrix::Interpolate(float)
 * address: 0000ad68
 * size: 824
 */

/* tMatrix::Interpolate(float) */

void __thiscall tMatrix::Interpolate(tMatrix *this,float param_1)

{
  float *pfVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined4 local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  float local_78;
  float local_74;
  float local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;

  pfVar1 = &local_c8;
  tQuaternian::tQuaternian((tQuaternian *)&local_48,this);
  local_28 = local_48;
  local_24 = fStack_44;
  local_20 = fStack_40;
  local_1c = fStack_3c;
  if ((-0.001 < local_48) && (local_48 < 0.001)) {
    local_28 = 0.0;
  }
  if ((-0.001 < fStack_44) && (fStack_44 < 0.001)) {
    local_24 = 0.0;
  }
  if ((-0.001 < fStack_40) && (fStack_40 < 0.001)) {
    local_20 = 0.0;
  }
  if (((local_28 == 0.0) && (local_24 == 0.0)) && (local_20 == 0.0)) {
    local_9c = 0;
    local_ac = 0;
    local_bc = 0;
    fVar3 = local_28 * local_24 - local_20 * fStack_3c;
    local_90 = 0;
    local_94 = 0;
    local_98 = 0;
    local_8c = 0x3f800000;
    local_c8 = (local_24 * local_24 + local_20 * local_20) * -2.0 + 1.0;
    local_b8 = fVar3 + fVar3;
    fVar3 = local_28 * local_20 + local_24 * fStack_3c;
    local_a8 = fVar3 + fVar3;
    fVar3 = local_28 * local_24 + local_20 * fStack_3c;
    local_c4 = fVar3 + fVar3;
    fVar3 = local_24 * local_20 - local_28 * fStack_3c;
    local_b4 = (local_28 * local_28 + local_20 * local_20) * -2.0 + 1.0;
    local_a4 = fVar3 + fVar3;
    fVar3 = local_28 * local_20 - local_24 * fStack_3c;
    local_c0 = fVar3 + fVar3;
    fVar3 = local_24 * local_20 + local_28 * fStack_3c;
    local_b0 = fVar3 + fVar3;
    local_a0 = (local_28 * local_28 + local_24 * local_24) * -2.0 + 1.0;
  }
  else {
    tAxis::operator=((tAxis *)&local_38,(tQuaternian *)&local_28);
    if (local_2c == 0.0) {
      return;
    }
    pfVar1 = &local_88;
    uVar2 = (int)(((local_2c * param_1 * 0.5) / 6.2831855) * 32768.0) & 0x7fff;
    fVar4 = (float)(&_RMathSin)[uVar2];
    local_34 = fVar4 * local_34;
    local_38 = fVar4 * local_38;
    fVar4 = fVar4 * local_30;
    fVar3 = (float)(&_RMathCos)[uVar2];
    local_4c = 0x3f800000;
    local_5c = 0;
    local_6c = 0;
    local_7c = 0;
    local_50 = 0;
    local_54 = 0;
    local_58 = 0;
    fVar5 = local_38 * local_34 - fVar3 * fVar4;
    local_88 = (local_34 * local_34 + fVar4 * fVar4) * -2.0 + 1.0;
    local_78 = fVar5 + fVar5;
    fVar5 = local_38 * fVar4 + fVar3 * local_34;
    local_68 = fVar5 + fVar5;
    fVar5 = local_38 * local_34 + fVar3 * fVar4;
    local_84 = fVar5 + fVar5;
    fVar5 = local_34 * fVar4 - fVar3 * local_38;
    local_74 = (local_38 * local_38 + fVar4 * fVar4) * -2.0 + 1.0;
    local_64 = fVar5 + fVar5;
    fVar5 = local_38 * fVar4 - fVar3 * local_34;
    local_80 = fVar5 + fVar5;
    fVar3 = local_34 * fVar4 + fVar3 * local_38;
    local_70 = fVar3 + fVar3;
    local_60 = (local_38 * local_38 + local_34 * local_34) * -2.0 + 1.0;
  }
  fVar3 = pfVar1[1];
  fVar4 = pfVar1[2];
  fVar5 = pfVar1[3];
  *(float *)this = *pfVar1;
  *(float *)(this + 4) = fVar3;
  *(float *)(this + 8) = fVar4;
  *(float *)(this + 0xc) = fVar5;
  fVar3 = pfVar1[5];
  fVar4 = pfVar1[6];
  fVar5 = pfVar1[7];
  *(float *)(this + 0x10) = pfVar1[4];
  *(float *)(this + 0x14) = fVar3;
  *(float *)(this + 0x18) = fVar4;
  *(float *)(this + 0x1c) = fVar5;
  fVar3 = pfVar1[9];
  fVar4 = pfVar1[10];
  fVar5 = pfVar1[0xb];
  *(float *)(this + 0x20) = pfVar1[8];
  *(float *)(this + 0x24) = fVar3;
  *(float *)(this + 0x28) = fVar4;
  *(float *)(this + 0x2c) = fVar5;
  fVar3 = pfVar1[0xd];
  fVar4 = pfVar1[0xe];
  fVar5 = pfVar1[0xf];
  *(float *)(this + 0x30) = pfVar1[0xc];
  *(float *)(this + 0x34) = fVar3;
  *(float *)(this + 0x38) = fVar4;
  *(float *)(this + 0x3c) = fVar5;
  return;
}
