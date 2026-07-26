/*
 * mangled: _Z28gRegisterDecryptKeyToKeyInfoPiPc
 * demangled: gRegisterDecryptKeyToKeyInfo(int*, char*)
 * address: 000314c8
 * size: 360
 */

/* gRegisterDecryptKeyToKeyInfo(int*, char*) */

undefined4 gRegisterDecryptKeyToKeyInfo(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  char local_3c;
  char local_3b;
  char local_3a;
  char local_39;
  char local_34;
  char local_33;
  char local_32;
  char local_31;
  char local_2c;
  char local_2b;
  char local_2a;
  char local_29;
  uint local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_14;

  if ((*param_2 == 'D') && (param_2[1] == '-')) {
    local_2c = param_2[2];
    local_2b = param_2[3];
    local_2a = param_2[4];
    local_29 = param_2[5];
    if (param_2[6] == '-') {
      local_34 = param_2[7];
      local_33 = param_2[8];
      local_32 = param_2[9];
      local_31 = param_2[10];
      if (param_2[0xb] == '-') {
        local_3c = param_2[0xc];
        local_3b = param_2[0xd];
        local_3a = param_2[0xe];
        local_39 = param_2[0xf];
        if (param_2[0x10] == '\0') {
          gRegisterUserDecrypt(&local_20,&local_2c);
          gRegisterUserDecrypt((int *)&local_24,&local_34);
          gRegisterUserDecrypt((int *)&local_1c,&local_3c);
          uVar2 = 0;
          uVar3 = 0;
          do {
            iVar1 = gRegisterGetParity(uVar2,local_24 | local_20 << 0x10);
            uVar3 = uVar3 | iVar1 << (uVar2 & 0xff);
            uVar2 = uVar2 + 1;
          } while (uVar2 != 0x10);
          uVar2 = gRegisterGetParityMask();
          if (((((uVar3 ^ local_1c) & uVar2) == 0) &&
              (iVar1 = gRegisterSearchEncryptList((int *)&local_14,local_20), iVar1 != 0)) &&
             (iVar1 = gRegisterSearchEncryptList((int *)&local_18,local_24), iVar1 != 0)) {
            *param_1 = ((local_14 ^ local_18) & 0xff) << 8 | local_14 & 0xff;
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
