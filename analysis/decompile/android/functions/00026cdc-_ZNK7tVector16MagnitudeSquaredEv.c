/*
 * mangled: _ZNK7tVector16MagnitudeSquaredEv
 * demangled: tVector::MagnitudeSquared() const
 * address: 00026cdc
 * size: 32
 */

/* tVector::MagnitudeSquared() const */

float __thiscall tVector::MagnitudeSquared(tVector *this)

{
  return *(float *)(this + 4) * *(float *)(this + 4) + *(float *)this * *(float *)this +
         *(float *)(this + 8) * *(float *)(this + 8);
}
