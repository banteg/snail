/*
 * mangled: _ZN14cRSubHighScore10MiniDeleteEi
 * demangled: cRSubHighScore::MiniDelete(int)
 * address: 0003e3bc
 * size: 216
 */

/* cRSubHighScore::MiniDelete(int) */

void __thiscall cRSubHighScore::MiniDelete(cRSubHighScore *this,int param_1)

{
  int iVar1;
  char local_98 [4];
  char acStack_94 [4];
  undefined2 local_90;
  undefined1 local_8e;

  if (param_1 - 0x16U < 0x33) {
    _sprintf(local_98,"TT_%03i.bin");
    iVar1 = param_1 << 6;
  }
  else if (param_1 == 0x49) {
    iVar1 = 0x1240;
    local_98[0] = 'S';
    local_98[1] = 'L';
    local_98[2] = '_';
    local_98[3] = '0';
    acStack_94[0] = '0';
    acStack_94[1] = '0';
    acStack_94[2] = '.';
    acStack_94[3] = 'b';
    local_90 = 0x6e69;
    local_8e = 0;
  }
  else {
    iVar1 = param_1 * 0x40;
    _sprintf(local_98,"HS_%08i.bin",*(undefined4 *)(this + param_1 * 0x38 + 0x28));
  }
  iVar1 = iVar1 + param_1 * -8;
  RShellDeleteFile(local_98);
  *(undefined4 *)(this + iVar1 + 8) = 0;
  cRTime::Zero((cRTime *)(this + iVar1 + 0xc));
  _memcpy(this + iVar1 + 0x2d,"ANON",5);
  *(undefined4 *)(this + iVar1 + 0x24) = 0;
  this[iVar1 + 0x2c] = (cRSubHighScore)0x0;
  return;
}
