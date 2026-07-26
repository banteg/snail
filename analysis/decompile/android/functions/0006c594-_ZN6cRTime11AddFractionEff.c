/*
 * mangled: _ZN6cRTime11AddFractionEff
 * demangled: cRTime::AddFraction(float, float)
 * address: 0006c594
 * size: 36
 */

/* cRTime::AddFraction(float, float) */

void __thiscall cRTime::AddFraction(cRTime *this,float param_1,float param_2)

{
  float in_r1;
  uint in_fpscr;

  VectorSignedToFloat((int)in_r1,(byte)(in_fpscr >> 0x16) & 3);
  Add(this,param_1);
  return;
}
