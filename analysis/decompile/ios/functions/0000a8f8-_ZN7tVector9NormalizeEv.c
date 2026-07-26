/*
 * mangled: _ZN7tVector9NormalizeEv
 * demangled: tVector::Normalize()
 * address: 0000a8f8
 * size: 80
 */

/* tVector::Normalize() */

float __thiscall tVector::Normalize(tVector *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  fVar2 = *(float *)(this + 4);
  fVar4 = *(float *)this;
  fVar1 = *(float *)(this + 8);
  fVar3 = SQRT(fVar2 * fVar2 + fVar4 * fVar4 + fVar1 * fVar1);
  if (fVar3 == 0.0) {
    fVar3 = 0.0;
  }
  else {
    fVar5 = 1.0 / fVar3;
    *(float *)this = fVar4 * fVar5;
    *(float *)(this + 4) = fVar2 * fVar5;
    *(float *)(this + 8) = fVar1 * fVar5;
  }
  return fVar3;
}
