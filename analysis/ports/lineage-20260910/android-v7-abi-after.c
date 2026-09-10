
/* tQuaternian::tQuaternian(tMatrix const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  int iVar1;
  float value;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar3 = *(float *)param_1;
  fVar4 = *(float *)(param_1 + 0x14);
  fVar2 = *(float *)(param_1 + 0x28);
  iVar1 = DAT_000285f8 + 0x2836c;
  value = fVar3 + fVar4 + fVar2 + DAT_000285e4;
  if (DAT_000285e8 < value) {
    fVar2 = Sqrt(value);
    fVar2 = DAT_000285f4 / fVar2;
    *(float *)(this + 0xc) = DAT_000285f0 / fVar2;
    *(float *)this = (*(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x24)) * fVar2;
    *(float *)(this + 4) = (*(float *)(param_1 + 0x20) - *(float *)(param_1 + 8)) * fVar2;
    *(float *)(this + 8) = (*(float *)(param_1 + 4) - *(float *)(param_1 + 0x10)) * fVar2;
    return this;
  }
  if (fVar3 < fVar4) {
    if (fVar4 < fVar2) {
      if (fVar3 <= fVar2) goto LAB_00028450;
      goto LAB_000284cc;
    }
  }
  else {
    if (fVar2 < fVar3) {
LAB_000284cc:
      fVar2 = ((fVar3 + DAT_000285e4) - fVar4) - fVar2;
      if (fVar2 < 0.0) {
        wprintf((char *)(iVar1 + DAT_00028600),iVar1,SUB84((double)fVar2,0),
                (int)((ulonglong)(double)fVar2 >> 0x20));
        fVar2 = DAT_000285ec;
      }
      fVar2 = Sqrt(fVar2);
      fVar2 = fVar2 + fVar2;
      *(float *)this = fVar2 * DAT_000285f0;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
      *(float *)(this + 8) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
      return this;
    }
    if (fVar4 <= fVar2) {
LAB_00028450:
      fVar4 = ((fVar2 + DAT_000285e4) - fVar3) - fVar4;
      if (fVar4 < 0.0) {
        wprintf((char *)(iVar1 + DAT_000285fc),iVar1,SUB84((double)fVar4,0),
                (int)((ulonglong)(double)fVar4 >> 0x20));
        fVar4 = DAT_000285ec;
      }
      fVar2 = Sqrt(fVar4);
      fVar2 = fVar2 + fVar2;
      *(float *)this = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
      fVar4 = fVar2 * DAT_000285f0;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
      *(float *)(this + 8) = fVar4;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
      return this;
    }
  }
  fVar2 = ((fVar4 + DAT_000285e4) - fVar3) - fVar2;
  if (fVar2 < 0.0) {
    wprintf((char *)(iVar1 + DAT_000285fc),iVar1,SUB84((double)fVar2,0),
            (int)((ulonglong)(double)fVar2 >> 0x20));
    fVar2 = DAT_000285ec;
  }
  fVar2 = Sqrt(fVar2);
  fVar2 = fVar2 + fVar2;
  fVar4 = fVar2 * DAT_000285f0;
  *(float *)this = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
  *(float *)(this + 4) = fVar4;
  *(float *)(this + 8) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
  *(float *)(this + 0xc) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
  return this;
}

