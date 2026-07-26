/*
 * mangled: _Z5KeyOnh
 * demangled: KeyOn(unsigned char)
 * address: 0000e7dc
 * size: 28
 */

/* KeyOn(unsigned char) */

bool KeyOn(uchar param_1)

{
  return (&_KeyboardState)[param_1] == -0x80;
}
