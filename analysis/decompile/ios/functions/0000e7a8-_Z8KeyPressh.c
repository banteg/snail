/*
 * mangled: _Z8KeyPressh
 * demangled: KeyPress(unsigned char)
 * address: 0000e7a8
 * size: 44
 */

/* KeyPress(unsigned char) */

int KeyPress(uchar param_1)

{
  int iVar1;

  if ((&_KeyboardState)[param_1] == -0x80) {
    iVar1 = 1 - (uint)(byte)(&_KeyboardStateLast)[param_1];
    if (1 < (byte)(&_KeyboardStateLast)[param_1]) {
      iVar1 = 0;
    }
    return iVar1;
  }
  return 0;
}
