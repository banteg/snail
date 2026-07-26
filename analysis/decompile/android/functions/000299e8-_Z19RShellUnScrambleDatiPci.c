/*
 * mangled: _Z19RShellUnScrambleDatiPci
 * demangled: RShellUnScrambleDat(int, char*, int)
 * address: 000299e8
 * size: 84
 */

/* RShellUnScrambleDat(int, char*, int) */

void RShellUnScrambleDat(int param_1,char *param_2,int param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;

  iVar3 = param_3 + param_1;
  if (param_1 < iVar3) {
    iVar4 = 0;
    uVar1 = param_1 * 3;
    do {
      cVar2 = (char)param_1;
      param_1 = param_1 + 1;
      param_2[iVar4] = (byte)uVar1 ^ param_2[iVar4] ^ cVar2 * cVar2;
      iVar4 = iVar4 + 1;
      uVar1 = (uVar1 & 0xff) + 3;
    } while (param_1 < iVar3);
  }
  return;
}
