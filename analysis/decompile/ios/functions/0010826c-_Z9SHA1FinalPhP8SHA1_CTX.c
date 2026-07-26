/*
 * mangled: _Z9SHA1FinalPhP8SHA1_CTX
 * demangled: SHA1Final(unsigned char*, SHA1_CTX*)
 * address: 0010826c
 * size: 264
 */

/* SHA1Final(unsigned char*, SHA1_CTX*) */

void SHA1Final(uchar *param_1,SHA1_CTX *param_2)

{
  uint uVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  uchar local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;

  uVar4 = *(undefined4 *)(param_2 + 0x18);
  local_15 = (undefined1)uVar4;
  local_18 = (uchar)((uint)uVar4 >> 0x18);
  local_17 = (undefined1)((uint)uVar4 >> 0x10);
  local_16 = (undefined1)((uint)uVar4 >> 8);
  uVar4 = *(undefined4 *)(param_2 + 0x14);
  pcVar2 = s__0019eba0;
  local_11 = (undefined1)uVar4;
  local_14 = (undefined1)((uint)uVar4 >> 0x18);
  local_13 = (undefined1)((uint)uVar4 >> 0x10);
  local_12 = (undefined1)((uint)uVar4 >> 8);
  while (SHA1Update(param_2,(uchar *)pcVar2,1), (*(uint *)(param_2 + 0x14) & 0x1f8) != 0x1c0) {
    pcVar2 = "";
  }
  SHA1Update(param_2,&local_18,8);
  *param_1 = (uchar)param_2[3];
  uVar1 = 1;
  do {
    uVar3 = uVar1;
    param_1[uVar3] = (uchar)(*(uint *)(param_2 + (uVar3 & 0xfffffffc)) >> ((~uVar3 & 3) << 3));
    uVar1 = uVar3 + 1;
  } while (uVar3 + 1 != 0x14);
  _memset(param_2 + 0x1c,uVar3 - 0x13,0x40);
  *(undefined4 *)param_2 = 0;
  *(undefined4 *)(param_2 + 4) = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  *(undefined4 *)(param_2 + 0xc) = 0;
  *(undefined4 *)(param_2 + 0x10) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  return;
}
