/*
 * mangled: _ZN6cRTime3AddEf
 * demangled: cRTime::Add(float)
 * address: 0006c4f4
 * size: 144
 */

/* cRTime::Add(float) */

void __thiscall cRTime::Add(cRTime *this,float param_1)

{
  float in_r1;
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar4 = in_r1 / 60.0 + *(float *)(this + 0x14);
  *(float *)(this + 0x14) = fVar4;
  *(float *)this = *(float *)this + in_r1 / 60.0;
  fVar5 = fVar4;
  if (1.0 <= fVar4) {
    fVar5 = fVar4 - 1.0;
    iVar1 = *(int *)(this + 8);
    iVar2 = iVar1 + 1;
    *(int *)(this + 8) = iVar2;
    fVar3 = fVar5;
    if (0x3b < iVar2) {
      *(int *)(this + 8) = iVar1 + -0x3b;
      *(int *)(this + 4) = *(int *)(this + 4) + 1;
      fVar3 = fVar4;
    }
    *(float *)(this + 0x14) = fVar5;
    fVar4 = fVar3;
    if (0x3b < iVar2) {
      fVar4 = fVar5;
    }
  }
  *(int *)(this + 0xc) = (int)(fVar5 * 100.0);
  *(int *)(this + 0x10) = (int)(fVar4 * 1000.0);
  return;
}
