/*
 * mangled: _Z14RTextCompStartPcS_
 * demangled: RTextCompStart(char*, char*)
 * address: 00029c3c
 * size: 172
 */

/* RTextCompStart(char*, char*) */

int RTextCompStart(char *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;

  uVar2 = (uint)(byte)*param_1;
  uVar3 = (uint)(byte)*param_2;
  uVar5 = uVar2 - 0x61 & 0xff;
  uVar4 = uVar2;
  if (uVar5 < 0x1a) {
    uVar4 = uVar2 - 0x20;
  }
  if (uVar5 < 0x1a) {
    uVar4 = uVar4 & 0xff;
  }
  uVar5 = uVar3;
  if ((uVar3 - 0x61 & 0xff) < 0x1a) {
    uVar5 = uVar3 - 0x20 & 0xff;
  }
  while ((uVar2 != 0 && (uVar3 != 0 && uVar4 == uVar5))) {
    param_1 = param_1 + 1;
    uVar2 = (uint)(byte)*param_1;
    param_2 = param_2 + 1;
    uVar3 = (uint)(byte)*param_2;
    uVar4 = uVar2;
    if ((uVar2 - 0x61 & 0xff) < 0x1a) {
      uVar4 = uVar2 - 0x20 & 0xff;
    }
    uVar5 = uVar3;
    if ((uVar3 - 0x61 & 0xff) < 0x1a) {
      uVar5 = uVar3 - 0x20 & 0xff;
    }
  }
  iVar1 = 1 - uVar3;
  if (1 < uVar3) {
    iVar1 = 0;
  }
  return iVar1;
}
