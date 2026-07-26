/*
 * mangled: _Z8SHA1InitP8SHA1_CTX
 * demangled: SHA1Init(SHA1_CTX*)
 * address: 00108148
 * size: 56
 */

/* SHA1Init(SHA1_CTX*) */

void SHA1Init(SHA1_CTX *param_1)

{
  *(undefined4 *)param_1 = 0x67452301;
  *(undefined4 *)(param_1 + 4) = 0xefcdab89;
  *(undefined4 *)(param_1 + 8) = 0x98badcfe;
  *(undefined4 *)(param_1 + 0xc) = 0x10325476;
  *(undefined4 *)(param_1 + 0x10) = 0xc3d2e1f0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}
