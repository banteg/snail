/*
 * mangled: _ZN8cRSprite9BuildTailEP7tMatrix
 * demangled: cRSprite::BuildTail(tMatrix*)
 * address: 0003cf04
 * size: 304
 */

/* cRSprite::BuildTail(tMatrix*) */

void __thiscall cRSprite::BuildTail(cRSprite *this,tMatrix *param_1)

{
  float fVar1;
  undefined4 *puVar2;
  float fVar3;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float fVar4;
  float local_2c;
  float local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  float local_14;
  float local_10;
  float local_c;

  if ((*(uint *)(this + 4) & 0x400) == 0) {
    local_2c = *(float *)(this + 0x48) - *(float *)(this + 0x3c);
    local_28 = *(float *)(this + 0x4c) - *(float *)(this + 0x40);
    local_24 = *(float *)(this + 0x50) - *(float *)(this + 0x44);
    puVar2 = (undefined4 *)tVector::Rotate((tVector *)&local_2c,param_1);
    local_20 = *puVar2;
    local_1c = puVar2[1];
    uStack_18 = puVar2[2];
    fVar4 = (float)ATan(extraout_s0,extraout_s1);
    *(float *)(this + 0x7c) = fVar4 + DAT_0003d03c + DAT_0003d040;
  }
  else {
    fVar4 = *(float *)(this + 0x88);
    if (fVar4 == 0.0) {
      local_14 = *(float *)(this + 0x48) - *(float *)(this + 0x3c);
      local_c = *(float *)(this + 0x50) - *(float *)(this + 0x44);
      local_10 = *(float *)(this + 0x4c) - *(float *)(this + 0x40);
      puVar2 = (undefined4 *)tVector::Rotate((tVector *)&local_14,param_1);
      local_20 = *puVar2;
      local_1c = puVar2[1];
      uStack_18 = puVar2[2];
      fVar3 = (float)ATan(extraout_s0_00,extraout_s1_00);
      fVar4 = DAT_0003d044;
      fVar1 = DAT_0003d03c;
      *(float *)(this + 0x88) = DAT_0003d044;
      *(float *)(this + 0x7c) = fVar3 + fVar1 + DAT_0003d040;
    }
    fVar1 = DAT_0003d034;
    *(float *)(this + 0x88) = fVar4 + *(float *)(this + 0x8c);
    if (fVar1 < fVar4 + *(float *)(this + 0x8c)) {
      *(undefined4 *)(this + 0x88) = DAT_0003d038;
    }
  }
  return;
}
