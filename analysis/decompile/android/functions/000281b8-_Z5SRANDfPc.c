/*
 * mangled: _Z5SRANDfPc
 * demangled: SRAND(float, char*)
 * address: 000281b8
 * size: 56
 */

/* SRAND(float, char*) */

float SRAND(float param_1,char *param_2)

{
  undefined4 uVar1;
  uint in_fpscr;
  float fVar2;

  uVar1 = Rand();
  fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
  return (fVar2 - 16384.0) * 6.1035156e-05 * (float)param_2;
}
