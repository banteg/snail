/*
 * mangled: _ZN7tVector9NormalizeEv
 * demangled: tVector::Normalize()
 * address: 00028a34
 * size: 104
 */

/* tVector::Normalize() */

float __thiscall tVector::Normalize(tVector *this)

{
  float fVar1;
  float fVar2;

  fVar1 = (float)Dot(this,this,this);
  fVar1 = (float)Sqrt(fVar1);
  if (fVar1 != 0.0) {
    fVar2 = 1.0 / fVar1;
    *(float *)(this + 8) = *(float *)(this + 8) * fVar2;
    *(float *)this = *(float *)this * fVar2;
    *(float *)(this + 4) = *(float *)(this + 4) * fVar2;
    return fVar1;
  }
  return 0.0;
}
