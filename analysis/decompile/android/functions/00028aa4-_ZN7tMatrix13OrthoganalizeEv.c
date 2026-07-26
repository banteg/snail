/*
 * mangled: _ZN7tMatrix13OrthoganalizeEv
 * demangled: tMatrix::Orthoganalize()
 * address: 00028aa4
 * size: 72
 */

/* tMatrix::Orthoganalize() */

void __thiscall tMatrix::Orthoganalize(tMatrix *this)

{
  tVector *this_00;
  tVector *this_01;

  this_00 = (tVector *)(this + 0x10);
  this_01 = (tVector *)(this + 0x20);
  tVector::Normalize((tVector *)this);
  tVector::Normalize(this_00);
  tVector::Normalize(this_01);
  tVector::Cross((tVector *)this,this_00,this_01);
  tVector::Cross(this_01,(tVector *)this,this_00);
  return;
}
