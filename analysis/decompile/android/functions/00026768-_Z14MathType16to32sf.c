/*
 * mangled: _Z14MathType16to32sf
 * demangled: MathType16to32(short, float)
 * address: 00026768
 * size: 32
 */

/* MathType16to32(short, float) */

float MathType16to32(short param_1,float param_2)

{
  float in_r1;
  uint in_fpscr;
  float fVar1;

  fVar1 = (float)VectorSignedToFloat((int)param_1,(byte)(in_fpscr >> 0x16) & 3);
  return fVar1 * in_r1 * 1.5258789e-05;
}
