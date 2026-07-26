/*
 * mangled: _ZNK7tVector18MagnitudeSquaredXZEv
 * demangled: tVector::MagnitudeSquaredXZ() const
 * address: 00026cfc
 * size: 24
 */

/* tVector::MagnitudeSquaredXZ() const */

float __thiscall tVector::MagnitudeSquaredXZ(tVector *this)

{
  return *(float *)(this + 8) * *(float *)(this + 8) + *(float *)this * *(float *)this;
}
