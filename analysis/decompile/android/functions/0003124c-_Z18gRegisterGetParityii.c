/*
 * mangled: _Z18gRegisterGetParityii
 * demangled: gRegisterGetParity(int, int)
 * address: 0003124c
 * size: 64
 */

/* gRegisterGetParity(int, int) */

uint gRegisterGetParity(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;

  iVar2 = param_1 + 1;
  uVar3 = 0;
  uVar1 = 0;
  iVar4 = iVar2;
  do {
    iVar4 = iVar4 + iVar2;
    if ((param_2 >> (uVar3 & 0xff) & 1U) != 0) {
      uVar1 = uVar1 + 1;
    }
    uVar3 = iVar2 + uVar3;
  } while (iVar4 - iVar2 < 0x20);
  return uVar1 & 1;
}
