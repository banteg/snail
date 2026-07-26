/*
 * mangled: _Z20gRegisterUserDecryptPiPc
 * demangled: gRegisterUserDecrypt(int*, char*)
 * address: 0003133c
 * size: 68
 */

/* gRegisterUserDecrypt(int*, char*) */

void gRegisterUserDecrypt(int *param_1,char *param_2)

{
  *param_1 = (uint)(byte)param_2[1] * 100 +
             (uint)(byte)*param_2 * 0xa28 + (uint)(byte)param_2[3] + -0x2af9c +
             (uint)(byte)param_2[2] * 10;
  return;
}
