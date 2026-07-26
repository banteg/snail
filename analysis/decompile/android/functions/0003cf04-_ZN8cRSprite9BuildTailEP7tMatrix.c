/*
 * mangled: _ZN8cRSprite9BuildTailEP7tMatrix
 * demangled: cRSprite::BuildTail(tMatrix*)
 * address: 0003cf04
 * size: 304
 */

/* cRSprite::BuildTail(tMatrix*) */

void __thiscall cRSprite::BuildTail(cRSprite *this,tMatrix *param_1)

{
  undefined4 *puVar1;
  float fVar2;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s1;
  float extraout_s1_00;
  float fVar3;
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
    puVar1 = (undefined4 *)tVector::Rotate((tVector *)&local_2c,param_1);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    uStack_18 = puVar1[2];
    fVar3 = (float)ATan(extraout_s0,extraout_s1);
    *(float *)(this + 0x7c) = fVar3 + 0.7853982 + 6.2831855;
  }
  else {
    fVar3 = *(float *)(this + 0x88);
    if (fVar3 == 0.0) {
      local_14 = *(float *)(this + 0x48) - *(float *)(this + 0x3c);
      local_c = *(float *)(this + 0x50) - *(float *)(this + 0x44);
      local_10 = *(float *)(this + 0x4c) - *(float *)(this + 0x40);
      puVar1 = (undefined4 *)tVector::Rotate((tVector *)&local_14,param_1);
      local_20 = *puVar1;
      local_1c = puVar1[1];
      uStack_18 = puVar1[2];
      fVar2 = (float)ATan(extraout_s0_00,extraout_s1_00);
      fVar3 = 0.001;
      *(undefined4 *)(this + 0x88) = 0x3a83126f;
      *(float *)(this + 0x7c) = fVar2 + 0.7853982 + 6.2831855;
    }
    *(float *)(this + 0x88) = fVar3 + *(float *)(this + 0x8c);
    if (1.0 < fVar3 + *(float *)(this + 0x8c)) {
      *(undefined4 *)(this + 0x88) = 0;
    }
  }
  return;
}
