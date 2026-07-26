/*
 * mangled: _ZN18OFSdbmHashedStringC1EPKc
 * demangled: OFSdbmHashedString::OFSdbmHashedString(char const*)
 * address: 0000376c
 * size: 80
 */

/* OFSdbmHashedString::OFSdbmHashedString(char const*) */

void __thiscall OFSdbmHashedString::OFSdbmHashedString(OFSdbmHashedString *this,char *param_1)

{
  uint in_r3;
  int iVar1;

  if (param_1 != (char *)0x0) {
    in_r3 = (uint)(byte)*param_1;
  }
  if (param_1 != (char *)0x0 && in_r3 != 0) {
    iVar1 = 0;
    do {
      iVar1 = iVar1 * 0x1003f + (in_r3 & 0xff);
      param_1 = param_1 + 1;
      in_r3 = (uint)(byte)*param_1;
    } while (in_r3 != 0);
  }
  else {
    iVar1 = 0;
  }
  *(int *)this = iVar1;
  return;
}
