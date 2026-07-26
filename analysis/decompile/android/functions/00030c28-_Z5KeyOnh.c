/*
 * mangled: _Z5KeyOnh
 * demangled: KeyOn(unsigned char)
 * address: 00030c28
 * size: 36
 */

/* KeyOn(unsigned char) */

bool KeyOn(uchar param_1)

{
  return KeyboardState[param_1] == -0x80;
}
