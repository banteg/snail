/*
 * mangled: _ZN12tColourSmall3SetEhhhh
 * demangled: tColourSmall::Set(unsigned char, unsigned char, unsigned char, unsigned char)
 * address: 00028104
 * size: 24
 */

/* tColourSmall::Set(unsigned char, unsigned char, unsigned char, unsigned char) */

void __thiscall
tColourSmall::Set(tColourSmall *this,uchar param_1,uchar param_2,uchar param_3,uchar param_4)

{
  this[2] = (tColourSmall)param_1;
  this[1] = (tColourSmall)param_2;
  this[3] = (tColourSmall)param_4;
  *this = (tColourSmall)param_3;
  return;
}
