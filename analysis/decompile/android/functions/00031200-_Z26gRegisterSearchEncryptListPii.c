/*
 * mangled: _Z26gRegisterSearchEncryptListPii
 * demangled: gRegisterSearchEncryptList(int*, int)
 * address: 00031200
 * size: 68
 */

/* gRegisterSearchEncryptList(int*, int) */

undefined4 gRegisterSearchEncryptList(int *param_1,int param_2)

{
  int iVar1;

  iVar1 = 0;
  do {
    if ((&gRegisterEncryptList)[iVar1] == param_2) {
      *param_1 = iVar1;
      return 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x100);
  return 0;
}
