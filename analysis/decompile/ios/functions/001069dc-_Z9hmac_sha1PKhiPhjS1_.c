/*
 * mangled: _Z9hmac_sha1PKhiPhjS1_
 * demangled: hmac_sha1(unsigned char const*, int, unsigned char*, unsigned int, unsigned char*)
 * address: 001069dc
 * size: 340
 */

/* hmac_sha1(unsigned char const*, int, unsigned char*, unsigned int, unsigned char*) */

void hmac_sha1(uchar *param_1,int param_2,uchar *param_3,uint param_4,uchar *param_5)

{
  int iVar1;
  SHA1_CTX aSStack_fc [94];
  byte local_9e [65];
  byte local_5d [65];

  if (0x40 < param_4) {
    SHA1Init(aSStack_fc);
    SHA1Update(aSStack_fc,param_3,param_4);
    SHA1Final(param_3,aSStack_fc);
    param_4 = 0x14;
  }
  _memset(local_5d,0,0x41);
  _memset(local_9e,0,0x41);
  _memcpy(local_5d,param_3,param_4);
  _memcpy(local_9e,param_3,param_4);
  iVar1 = 1;
  local_5d[0] = local_5d[0] ^ 0x36;
  local_9e[0] = local_9e[0] ^ 0x5c;
  do {
    local_5d[iVar1] = local_5d[iVar1] ^ 0x36;
    local_9e[iVar1] = local_9e[iVar1] ^ 0x5c;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x40);
  SHA1Init(aSStack_fc);
  SHA1Update(aSStack_fc,local_5d,0x40);
  SHA1Update(aSStack_fc,param_1,param_2);
  SHA1Final(param_5,aSStack_fc);
  SHA1Init(aSStack_fc);
  SHA1Update(aSStack_fc,local_9e,0x40);
  SHA1Update(aSStack_fc,param_5,0x14);
  SHA1Final(param_5,aSStack_fc);
  return;
}
