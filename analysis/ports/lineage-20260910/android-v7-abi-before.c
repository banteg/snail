
/* tQuaternian::tQuaternian(tMatrix const&) */

tQuaternian * __thiscall tQuaternian::tQuaternian(tQuaternian *this,tMatrix *param_1)

{
  int iVar1;
  float in_s0;
  float fVar2;
  float fVar3;
  float fVar5;
  double dVar4;
  
  fVar3 = *(float *)param_1;
  fVar5 = *(float *)(param_1 + 0x14);
  fVar2 = *(float *)(param_1 + 0x28);
  iVar1 = DAT_000285f8 + 0x2836c;
  if (DAT_000285e8 < fVar3 + fVar5 + fVar2 + DAT_000285e4) {
    fVar2 = (float)Sqrt(in_s0);
    fVar2 = DAT_000285f4 / fVar2;
    *(float *)(this + 0xc) = DAT_000285f0 / fVar2;
    *(float *)this = (*(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x24)) * fVar2;
    *(float *)(this + 4) = (*(float *)(param_1 + 0x20) - *(float *)(param_1 + 8)) * fVar2;
    *(float *)(this + 8) = (*(float *)(param_1 + 4) - *(float *)(param_1 + 0x10)) * fVar2;
    return this;
  }
  if (fVar3 < fVar5) {
    if (fVar5 < fVar2) {
      if (fVar3 <= fVar2) goto LAB_00028450;
      goto LAB_000284cc;
    }
  }
  else {
    if (fVar2 < fVar3) {
LAB_000284cc:
      fVar2 = ((fVar3 + DAT_000285e4) - fVar5) - fVar2;
      if (fVar2 < 0.0) {
        dVar4 = (double)fVar2;
        in_s0 = (float)wprintf((char *)(iVar1 + DAT_00028600),iVar1,SUB84(dVar4,0),
                               (int)((ulonglong)dVar4 >> 0x20));
      }
      fVar2 = (float)Sqrt(in_s0);
      fVar2 = fVar2 + fVar2;
      *(float *)this = fVar2 * DAT_000285f0;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
      *(float *)(this + 8) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
      return this;
    }
    if (fVar5 <= fVar2) {
LAB_00028450:
      fVar5 = ((fVar2 + DAT_000285e4) - fVar3) - fVar5;
      if (fVar5 < 0.0) {
        dVar4 = (double)fVar5;
        in_s0 = (float)wprintf((char *)(iVar1 + DAT_000285fc),iVar1,SUB84(dVar4,0),
                               (int)((ulonglong)dVar4 >> 0x20));
      }
      fVar2 = (float)Sqrt(in_s0);
      fVar2 = fVar2 + fVar2;
      *(float *)this = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
      fVar3 = fVar2 * DAT_000285f0;
      *(float *)(this + 4) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
      *(float *)(this + 8) = fVar3;
      *(float *)(this + 0xc) = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
      return this;
    }
  }
  fVar2 = ((fVar5 + DAT_000285e4) - fVar3) - fVar2;
  if (fVar2 < 0.0) {
    dVar4 = (double)fVar2;
    in_s0 = (float)wprintf((char *)(iVar1 + DAT_000285fc),iVar1,SUB84(dVar4,0),
                           (int)((ulonglong)dVar4 >> 0x20));
  }
  fVar2 = (float)Sqrt(in_s0);
  fVar2 = fVar2 + fVar2;
  fVar3 = fVar2 * DAT_000285f0;
  *(float *)this = (*(float *)(param_1 + 0x10) + *(float *)(param_1 + 4)) / fVar2;
  *(float *)(this + 4) = fVar3;
  *(float *)(this + 8) = (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x18)) / fVar2;
  *(float *)(this + 0xc) = (*(float *)(param_1 + 0x20) + *(float *)(param_1 + 8)) / fVar2;
  return this;
}

