/*
 * mangled: _ZN11tQuaternianC2ERK7tMatrix
 * demangled: tQuaternian::tQuaternian(tMatrix const&)
 * address: 0000a650
 * size: 616
 */

/* tQuaternian::tQuaternian(tMatrix const&) */

void __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  fVar2 = *(float *)param_1;
  fVar3 = *(float *)(param_1 + 0x14);
  fVar1 = *(float *)(param_1 + 0x28);
  fVar4 = fVar2 + fVar3 + fVar1 + 1.0;
  if (1e-06 < fVar4) {
    fVar1 = 0.5 / SQRT(fVar4);
    *(float *)(this + 0xc) = 0.25 / fVar1;
    *(float *)this = (*(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x24)) * fVar1;
    *(float *)(this + 4) = (*(float *)(param_1 + 0x20) - *(float *)(param_1 + 8)) * fVar1;
    *(float *)(this + 8) = (*(float *)(param_1 + 4) - *(float *)(param_1 + 0x10)) * fVar1;
    return;
  }
  if (fVar2 < fVar3) {
    if (fVar3 < fVar1) {
      if (fVar2 <= fVar1) goto LAB_0000a6b0;
      goto LAB_0000a7a8;
    }
  }
  else {
    if (fVar1 < fVar2) {
LAB_0000a7a8:
      fVar1 = ((fVar2 + 1.0) - fVar3) - fVar1;
      if (fVar1 < 0.0) {
        wprintf("ERROR:sqrt %f\n",SUB84((double)fVar1,0),(int)((ulonglong)(double)fVar1 >> 0x20));
        fVar1 = 0.0;
      }
      fVar1 = SQRT(fVar1) + SQRT(fVar1);
      *(float *)this = fVar1 * 0.25;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
      *(float *)(this + 8) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
      return;
    }
    if (fVar3 <= fVar1) {
LAB_0000a6b0:
      fVar3 = ((fVar1 + 1.0) - fVar2) - fVar3;
      if (fVar3 < 0.0) {
        wprintf("ERROR:sqt %f\n",SUB84((double)fVar3,0),(int)((ulonglong)(double)fVar3 >> 0x20));
        fVar3 = 0.0;
      }
      fVar1 = SQRT(fVar3) + SQRT(fVar3);
      *(float *)this = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
      *(float *)(this + 8) = fVar1 * 0.25;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
      return;
    }
  }
  fVar1 = ((fVar3 + 1.0) - fVar2) - fVar1;
  if (fVar1 < 0.0) {
    wprintf("ERROR:sqt %f\n",SUB84((double)fVar1,0),(int)((ulonglong)(double)fVar1 >> 0x20));
    fVar1 = 0.0;
  }
  fVar1 = SQRT(fVar1) + SQRT(fVar1);
  *(float *)this = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
  *(float *)(this + 4) = fVar1 * 0.25;
  *(float *)(this + 8) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
  *(float *)(this + 0xc) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
  return;
}
