/*
 * mangled: _Z7RstrASCc
 * demangled: RstrASC(char)
 * address: 0006a48c
 * size: 24
 */

/* RstrASC(char) */

uint RstrASC(char param_1)

{
  uint uVar1;

  uVar1 = (uint)param_1;
  if ((uVar1 - 0x61 & 0xff) < 0x1a) {
    uVar1 = uVar1 - 0x20 & 0xff;
  }
  return uVar1;
}
