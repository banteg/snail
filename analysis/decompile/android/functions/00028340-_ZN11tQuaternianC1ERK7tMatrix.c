/*
 * mangled: _ZN11tQuaternianC1ERK7tMatrix
 * demangled: tQuaternian::tQuaternian(tMatrix const&)
 * address: 00028340
 * size: 676
 */

/* tQuaternian::tQuaternian(tMatrix const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  float in_s0;
  float fVar1;
  float fVar2;
  float fVar4;
  double dVar3;

  fVar2 = *(float *)param_1;
  fVar4 = *(float *)(param_1 + 0x14);
  fVar1 = *(float *)(param_1 + 0x28);
  if (1e-06 < fVar2 + fVar4 + fVar1 + 1.0) {
    fVar1 = (float)Sqrt(in_s0);
    fVar1 = 0.5 / fVar1;
    *(float *)(this + 0xc) = 0.25 / fVar1;
    *(float *)this = (*(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x24)) * fVar1;
    *(float *)(this + 4) = (*(float *)(param_1 + 0x20) - *(float *)(param_1 + 8)) * fVar1;
    *(float *)(this + 8) = (*(float *)(param_1 + 4) - *(float *)(param_1 + 0x10)) * fVar1;
    return this;
  }
  if (fVar2 < fVar4) {
    if (fVar4 < fVar1) {
      if (fVar2 <= fVar1) goto LAB_00028450;
      goto LAB_000284cc;
    }
  }
  else {
    if (fVar1 < fVar2) {
LAB_000284cc:
      fVar1 = ((fVar2 + 1.0) - fVar4) - fVar1;
      if (fVar1 < 0.0) {
        dVar3 = (double)fVar1;
        in_s0 = (float)wprintf("ERROR:sqrt %f\n",&__DT_PLTGOT,SUB84(dVar3,0),
                               (int)((ulonglong)dVar3 >> 0x20));
      }
      fVar1 = (float)Sqrt(in_s0);
      fVar1 = fVar1 + fVar1;
      *(float *)this = fVar1 * 0.25;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
      *(float *)(this + 8) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
      return this;
    }
    if (fVar4 <= fVar1) {
LAB_00028450:
      fVar4 = ((fVar1 + 1.0) - fVar2) - fVar4;
      if (fVar4 < 0.0) {
        dVar3 = (double)fVar4;
        in_s0 = (float)wprintf("ERROR:sqt %f\n",&__DT_PLTGOT,SUB84(dVar3,0),
                               (int)((ulonglong)dVar3 >> 0x20));
      }
      fVar1 = (float)Sqrt(in_s0);
      fVar1 = fVar1 + fVar1;
      *(float *)this = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
      *(float *)(this + 8) = fVar1 * 0.25;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
      return this;
    }
  }
  fVar1 = ((fVar4 + 1.0) - fVar2) - fVar1;
  if (fVar1 < 0.0) {
    dVar3 = (double)fVar1;
    in_s0 = (float)wprintf("ERROR:sqt %f\n",&__DT_PLTGOT,SUB84(dVar3,0),
                           (int)((ulonglong)dVar3 >> 0x20));
  }
  fVar1 = (float)Sqrt(in_s0);
  fVar1 = fVar1 + fVar1;
  *(float *)this = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar1;
  *(float *)(this + 4) = fVar1 * 0.25;
  *(float *)(this + 8) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar1;
  *(float *)(this + 0xc) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar1;
  return this;
}
