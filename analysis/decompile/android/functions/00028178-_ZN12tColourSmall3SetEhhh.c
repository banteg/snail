/*
 * mangled: _ZN12tColourSmall3SetEhhh
 * demangled: tColourSmall::Set(unsigned char, unsigned char, unsigned char)
 * address: 00028178
 * size: 16
 */

/* tColourSmall::Set(unsigned char, unsigned char, unsigned char) */

void __thiscall tColourSmall::Set(tColourSmall *this,uchar param_1,uchar param_2,uchar param_3)

{
  *this = (tColourSmall)param_3;
  this[2] = (tColourSmall)param_1;
  this[1] = (tColourSmall)param_2;
  return;
}
