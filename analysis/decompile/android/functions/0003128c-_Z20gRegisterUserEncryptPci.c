/*
 * mangled: _Z20gRegisterUserEncryptPci
 * demangled: gRegisterUserEncrypt(char*, int)
 * address: 0003128c
 * size: 176
 */

/* gRegisterUserEncrypt(char*, int) */

void gRegisterUserEncrypt(char *param_1,int param_2)

{
  char cVar1;

  cVar1 = (char)(param_2 / 10);
  param_1[4] = '\0';
  param_1[3] = (char)param_2 + cVar1 * -10 + '0';
  *param_1 = (char)(param_2 / 0xa28) + (char)((param_2 / 0xa28) / 0x1a) * -0x1a + 'A';
  param_1[2] = cVar1 + (char)((param_2 / 10) / 10) * -10 + '0';
  param_1[1] = (char)(param_2 / 100) + (char)((param_2 / 100) / 0x1a) * -0x1a + 'A';
  return;
}
