/*
 * mangled: _Z13G0BindTexturei
 * demangled: G0BindTexture(int)
 * address: 0008b184
 * size: 180
 */

/* G0BindTexture(int) */

void G0BindTexture(int param_1)

{
  if (param_1 == gBindTextureRefLast) {
    return;
  }
  gBindCount = gBindCount + 1;
  glBindTexture(0xde1,*(undefined4 *)(texNameList + param_1 * 4));
  gBindTextureRefLast = param_1;
  if ((*(uint *)(gTextureList + param_1 * 0xa4 + 8) & 0x1000) == 0) {
    glTexParameteri(0xde1,0x2802,0x812f);
    glTexParameteri(0xde1,0x2803,0x812f);
    return;
  }
  glTexParameteri(0xde1,0x2802,0x2901);
  glTexParameteri(0xde1,0x2803,0x2901);
  return;
}
