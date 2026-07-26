/*
 * mangled: _Z28gRegisterEncryptKeyInfoToKeyPci
 * demangled: gRegisterEncryptKeyInfoToKey(char*, int)
 * address: 00031380
 * size: 268
 */

/* gRegisterEncryptKeyInfoToKey(char*, int) */

void gRegisterEncryptKeyInfoToKey(char *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char local_40;
  char local_3f;
  char local_3e;
  char local_3d;
  char local_38;
  char local_37;
  char local_36;
  char local_35;
  char local_30;
  char local_2f;
  char local_2e;
  char local_2d;

  uVar2 = 0;
  uVar3 = 0;
  iVar5 = (&gRegisterEncryptList)[param_2 & 0xffU];
  uVar4 = (&gRegisterEncryptList)[(param_2 & 0xffffU) >> 8 ^ param_2 & 0xffU];
  do {
    iVar1 = gRegisterGetParity(uVar2,uVar4 | iVar5 << 0x10);
    uVar3 = uVar3 | iVar1 << (uVar2 & 0xff);
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x10);
  gRegisterUserEncrypt(&local_30,iVar5);
  gRegisterUserEncrypt(&local_38,uVar4);
  gRegisterUserEncrypt(&local_40,uVar3);
  param_1[0x10] = '\0';
  param_1[2] = local_30;
  *param_1 = 'D';
  param_1[3] = local_2f;
  param_1[4] = local_2e;
  param_1[5] = local_2d;
  param_1[7] = local_38;
  param_1[8] = local_37;
  param_1[9] = local_36;
  param_1[10] = local_35;
  param_1[0xb] = '-';
  param_1[0xc] = local_40;
  param_1[0xd] = local_3f;
  param_1[0xf] = local_3d;
  param_1[1] = '-';
  param_1[0xe] = local_3e;
  param_1[6] = '-';
  return;
}
