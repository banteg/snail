/*
 * mangled: _Z8KeyPressh
 * demangled: KeyPress(unsigned char)
 * address: 00030be4
 * size: 56
 */

/* KeyPress(unsigned char) */

int KeyPress(uchar param_1)

{
  int iVar1;

  if (KeyboardState[param_1] == -0x80) {
    iVar1 = 1 - (uint)(byte)KeyboardStateLast[param_1];
    if (1 < (byte)KeyboardStateLast[param_1]) {
      iVar1 = 0;
    }
    return iVar1;
  }
  return 0;
}
