/*
 * mangled: _Z4RANDfPc
 * demangled: RAND(float, char*)
 * address: 0000ac14
 * size: 68
 */

/* RAND(float, char*) */

float RAND(float param_1,char *param_2)

{
  uint uVar1;
  uint in_fpscr;
  float fVar2;

  uVar1 = _rand();
  fVar2 = (float)VectorSignedToFloat(uVar1 & 0x7fff,(byte)(in_fpscr >> 0x16) & 3);
  return fVar2 * 3.0517578e-05 * param_1;
}
