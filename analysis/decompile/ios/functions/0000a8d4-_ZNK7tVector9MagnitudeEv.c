/*
 * mangled: _ZNK7tVector9MagnitudeEv
 * demangled: tVector::Magnitude() const
 * address: 0000a8d4
 * size: 36
 */

/* tVector::Magnitude() const */

float __thiscall tVector::Magnitude(tVector *this)

{
  return SQRT(*(float *)(this + 4) * *(float *)(this + 4) + *(float *)this * *(float *)this +
              *(float *)(this + 8) * *(float *)(this + 8));
}
