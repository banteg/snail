/*
 * mangled: _Z10SHA1UpdateP8SHA1_CTXPhj
 * demangled: SHA1Update(SHA1_CTX*, unsigned char*, unsigned int)
 * address: 00108194
 * size: 216
 */

/* SHA1Update(SHA1_CTX*, unsigned char*, unsigned int) */

void SHA1Update(SHA1_CTX *param_1,uchar *param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uchar *puVar5;
  int iVar6;

  uVar1 = *(uint *)(param_1 + 0x14);
  uVar4 = param_3 * 8;
  uVar2 = uVar4 + uVar1;
  *(uint *)(param_1 + 0x14) = uVar2;
  if (uVar2 < uVar4) {
    iVar3 = *(int *)(param_1 + 0x18);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x18);
  }
  uVar1 = uVar1 >> 3 & 0x3f;
  if (uVar2 < uVar4) {
    iVar3 = iVar3 + 1;
    *(int *)(param_1 + 0x18) = iVar3;
  }
  *(uint *)(param_1 + 0x18) = iVar3 + (param_3 >> 0x1d);
  if (param_3 + uVar1 < 0x40) {
    iVar3 = 0;
  }
  else {
    iVar3 = -uVar1 + 0x40;
    _memcpy(param_1 + uVar1 + 0x1c,param_2,0x40 - uVar1);
    SHA1Transform((ulong *)param_1,(uchar *)(param_1 + 0x1c));
    if (-uVar1 + 0x7f < param_3) {
      puVar5 = param_2 + iVar3;
      iVar6 = iVar3;
      do {
        iVar3 = iVar6 + 0x40;
        SHA1Transform((ulong *)param_1,puVar5);
        uVar4 = iVar6 + 0x7f;
        puVar5 = puVar5 + 0x40;
        iVar6 = iVar3;
      } while (uVar4 < param_3);
    }
    uVar1 = 0;
  }
  _memcpy(param_1 + uVar1 + 0x1c,param_2 + iVar3,param_3 - iVar3);
  return;
}
