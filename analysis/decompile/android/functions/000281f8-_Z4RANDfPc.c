/*
 * mangled: _Z4RANDfPc
 * demangled: RAND(float, char*)
 * address: 000281f8
 * size: 48
 */

/* RAND(float, char*) */

float RAND(float param_1,char *param_2)

{
  undefined4 uVar1;
  uint in_fpscr;
  float fVar2;

  uVar1 = Rand();
  fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
  return fVar2 * 3.0517578e-05 * (float)param_2;
}
