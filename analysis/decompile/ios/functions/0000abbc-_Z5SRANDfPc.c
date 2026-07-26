/*
 * mangled: _Z5SRANDfPc
 * demangled: SRAND(float, char*)
 * address: 0000abbc
 * size: 76
 */

/* SRAND(float, char*) */

float SRAND(float param_1,char *param_2)

{
  uint uVar1;
  uint in_fpscr;
  float fVar2;

  uVar1 = _rand();
  fVar2 = (float)VectorSignedToFloat(uVar1 & 0x7fff,(byte)(in_fpscr >> 0x16) & 3);
  return (fVar2 - 16384.0) * 6.1035156e-05 * param_1;
}
