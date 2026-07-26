/*
 * mangled: _Z23gRegisterEmailToKeyInfoPiPc
 * demangled: gRegisterEmailToKeyInfo(int*, char*)
 * address: 00031494
 * size: 44
 */

/* gRegisterEmailToKeyInfo(int*, char*) */

void gRegisterEmailToKeyInfo(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;

  uVar2 = (uint)(byte)*param_2;
  if (uVar2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 0;
    do {
      iVar1 = iVar1 + uVar2;
      param_2 = param_2 + 1;
      uVar2 = (uint)(byte)*param_2;
    } while (uVar2 != 0);
  }
  *param_1 = iVar1;
  return;
}
