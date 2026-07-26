/*
 * mangled: _ZN8cRSprite9BuildTailEP7tMatrix
 * demangled: cRSprite::BuildTail(tMatrix*)
 * address: 00010a5c
 * size: 308
 */

/* cRSprite::BuildTail(tMatrix*) */

void __thiscall cRSprite::BuildTail(cRSprite *this,tMatrix *param_1)

{
  float *pfVar1;
  float fVar2;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float fStack_1c;
  float local_18;
  float local_14;
  float local_10;

  if ((*(uint *)(this + 4) & 0x400) == 0) {
    local_30 = *(float *)(this + 0x48) - *(float *)(this + 0x3c);
    local_2c = *(float *)(this + 0x4c) - *(float *)(this + 0x40);
    local_28 = *(float *)(this + 0x50) - *(float *)(this + 0x44);
    pfVar1 = (float *)tVector::Rotate((tVector *)&local_30,param_1);
    local_24 = *pfVar1;
    local_20 = pfVar1[1];
    fStack_1c = pfVar1[2];
    fVar2 = (float)ATan(local_24,local_20);
    *(float *)(this + 0x7c) = fVar2 + 0.7853982 + 6.2831855;
  }
  else {
    fVar2 = *(float *)(this + 0x88);
    if (fVar2 == 0.0) {
      local_18 = *(float *)(this + 0x48) - *(float *)(this + 0x3c);
      local_14 = *(float *)(this + 0x4c) - *(float *)(this + 0x40);
      local_10 = *(float *)(this + 0x50) - *(float *)(this + 0x44);
      pfVar1 = (float *)tVector::Rotate((tVector *)&local_18,param_1);
      local_24 = *pfVar1;
      local_20 = pfVar1[1];
      fStack_1c = pfVar1[2];
      fVar2 = (float)ATan(local_24,local_20);
      *(float *)(this + 0x7c) = fVar2 + 0.7853982 + 6.2831855;
      fVar2 = 0.001;
      *(undefined4 *)(this + 0x88) = 0x3a83126f;
    }
    *(float *)(this + 0x88) = fVar2 + *(float *)(this + 0x8c);
    if (1.0 < fVar2 + *(float *)(this + 0x8c)) {
      *(undefined4 *)(this + 0x88) = 0;
    }
  }
  return;
}
