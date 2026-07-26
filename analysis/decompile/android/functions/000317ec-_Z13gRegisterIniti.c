/*
 * mangled: _Z13gRegisterIniti
 * demangled: gRegisterInit(int)
 * address: 000317ec
 * size: 228
 */

/* gRegisterInit(int) */

undefined4 gRegisterInit(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  srand48(param_1);
  uVar1 = lrand48();
  gRegisterEncryptList = uVar1 & 0x7fff;
  printf("0x%x,\t");
  uVar1 = 0;
  uVar4 = 1;
  while( true ) {
    uVar3 = uVar4;
    if (0 < (int)(uVar1 - 1)) {
      if (gRegisterEncryptList == (&gRegisterEncryptList)[uVar1]) {
        return 0;
      }
      iVar2 = 0;
      while (iVar2 = iVar2 + 1, iVar2 < (int)(uVar1 - 1)) {
        if ((&gRegisterEncryptList)[iVar2] == (&gRegisterEncryptList)[uVar1]) {
          return 0;
        }
      }
    }
    if (uVar3 == 0x100) break;
    uVar1 = lrand48();
    uVar4 = uVar3 + 1;
    (&gRegisterEncryptList)[uVar3] = uVar1 & 0x7fff;
    printf("0x%x,\t");
    uVar1 = uVar3;
    if ((uVar4 & 7) == 0) {
      putchar(10);
    }
  }
  putchar(10);
  return 1;
}
