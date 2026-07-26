/*
 * mangled: _Z13G0BindTexturei
 * demangled: G0BindTexture(int)
 * address: 0006e358
 * size: 184
 */

/* G0BindTexture(int) */

void G0BindTexture(int param_1)

{
  if (param_1 == _gBindTextureRefLast) {
    return;
  }
  _gBindCount = _gBindCount + 1;
  _glBindTexture(0xde1,*(undefined4 *)(texNameList + param_1 * 4));
  _gBindTextureRefLast = param_1;
  if ((*(uint *)(PTR__gTextureList_001b61d0 + param_1 * 0xa4 + 8) & 0x1000) != 0) {
    _glTexParameteri(0xde1,&DAT_00002802,&DAT_00002901);
    _glTexParameteri(0xde1,&DAT_00002803,&DAT_00002901);
    return;
  }
  _glTexParameteri(0xde1,&DAT_00002802,0x812f);
  _glTexParameteri(0xde1,&DAT_00002803,0x812f);
  return;
}
