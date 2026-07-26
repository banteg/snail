/*
 * mangled: _Z16RShellInkeyInputv
 * demangled: RShellInkeyInput()
 * address: 0000c2e0
 * size: 1148
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellInkeyInput() */

uint RShellInkeyInput(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;

  iVar3 = KeyOn('\x1e');
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = 0x61;
  }
  iVar3 = KeyOn('0');
  if (iVar3 != 0) {
    uVar4 = 0x62;
  }
  iVar3 = KeyOn('.');
  if (iVar3 != 0) {
    uVar4 = 99;
  }
  iVar3 = KeyOn(' ');
  if (iVar3 != 0) {
    uVar4 = 100;
  }
  iVar3 = KeyOn('\x12');
  if (iVar3 != 0) {
    uVar4 = 0x65;
  }
  iVar3 = KeyOn('!');
  if (iVar3 != 0) {
    uVar4 = 0x66;
  }
  iVar3 = KeyOn('\"');
  if (iVar3 != 0) {
    uVar4 = 0x67;
  }
  iVar3 = KeyOn('#');
  if (iVar3 != 0) {
    uVar4 = 0x68;
  }
  iVar3 = KeyOn('\x17');
  if (iVar3 != 0) {
    uVar4 = 0x69;
  }
  iVar3 = KeyOn('$');
  if (iVar3 != 0) {
    uVar4 = 0x6a;
  }
  iVar3 = KeyOn('%');
  if (iVar3 != 0) {
    uVar4 = 0x6b;
  }
  iVar3 = KeyOn('&');
  if (iVar3 != 0) {
    uVar4 = 0x6c;
  }
  iVar3 = KeyOn('2');
  if (iVar3 != 0) {
    uVar4 = 0x6d;
  }
  iVar3 = KeyOn('1');
  if (iVar3 != 0) {
    uVar4 = 0x6e;
  }
  iVar3 = KeyOn('\x18');
  if (iVar3 != 0) {
    uVar4 = 0x6f;
  }
  iVar3 = KeyOn('\x19');
  if (iVar3 != 0) {
    uVar4 = 0x70;
  }
  iVar3 = KeyOn('\x10');
  if (iVar3 != 0) {
    uVar4 = 0x71;
  }
  iVar3 = KeyOn('\x13');
  if (iVar3 != 0) {
    uVar4 = 0x72;
  }
  iVar3 = KeyOn('\x1f');
  if (iVar3 != 0) {
    uVar4 = 0x73;
  }
  iVar3 = KeyOn('\x14');
  if (iVar3 != 0) {
    uVar4 = 0x74;
  }
  iVar3 = KeyOn('\x16');
  if (iVar3 != 0) {
    uVar4 = 0x75;
  }
  iVar3 = KeyOn('/');
  if (iVar3 != 0) {
    uVar4 = 0x76;
  }
  iVar3 = KeyOn('\x11');
  if (iVar3 != 0) {
    uVar4 = 0x77;
  }
  iVar3 = KeyOn('-');
  if (iVar3 != 0) {
    uVar4 = 0x78;
  }
  iVar3 = KeyOn('\x15');
  if (iVar3 != 0) {
    uVar4 = 0x79;
  }
  iVar3 = KeyOn(',');
  if (iVar3 == 0) {
    if (uVar4 == 0) goto LAB_0000c49c;
  }
  else {
    uVar4 = 0x7a;
  }
  iVar3 = KeyTest('*');
  if ((iVar3 != 0) || (iVar3 = KeyTest('6'), iVar3 != 0)) {
    uVar4 = uVar4 - 0x20 & 0xff;
  }
LAB_0000c49c:
  iVar3 = KeyOn('9');
  if (iVar3 != 0) {
    uVar4 = 0x20;
  }
  iVar3 = KeyOn('\v');
  if (iVar3 != 0) {
    uVar4 = 0x30;
  }
  iVar3 = KeyOn('\x02');
  if (iVar3 != 0) {
    uVar4 = 0x31;
  }
  iVar3 = KeyOn('\x03');
  if (iVar3 != 0) {
    uVar4 = 0x32;
  }
  iVar3 = KeyOn('\x04');
  if (iVar3 != 0) {
    uVar4 = 0x33;
  }
  iVar3 = KeyOn('\x05');
  if (iVar3 != 0) {
    uVar4 = 0x34;
  }
  iVar3 = KeyOn('\x06');
  if (iVar3 != 0) {
    uVar4 = 0x35;
  }
  iVar3 = KeyOn('\a');
  if (iVar3 != 0) {
    uVar4 = 0x36;
  }
  iVar3 = KeyOn('\b');
  if (iVar3 != 0) {
    uVar4 = 0x37;
  }
  iVar3 = KeyOn('\t');
  if (iVar3 != 0) {
    uVar4 = 0x38;
  }
  iVar3 = KeyOn('\n');
  if (iVar3 != 0) {
    uVar4 = 0x39;
  }
  iVar3 = KeyOn('4');
  if (iVar3 != 0) {
    uVar4 = 0x2e;
  }
  iVar3 = KeyOn('3');
  if (iVar3 != 0) {
    uVar4 = 0x2c;
  }
  iVar3 = KeyOn('(');
  if (iVar3 != 0) {
    uVar4 = 0x27;
  }
  iVar3 = KeyOn('+');
  if (iVar3 != 0) {
    uVar4 = 0x5c;
  }
  iVar3 = KeyOn('\x0e');
  if (iVar3 != 0) {
    uVar4 = 1;
  }
  iVar3 = KeyOn(0xd3);
  if (iVar3 != 0) {
    uVar4 = 2;
  }
  iVar3 = KeyOn(0xcb);
  if (iVar3 != 0) {
    uVar4 = 3;
  }
  iVar3 = KeyOn(0xcd);
  if (iVar3 != 0) {
    uVar4 = 4;
  }
  iVar3 = KeyOn(200);
  if (iVar3 != 0) {
    uVar4 = 7;
  }
  iVar3 = KeyOn(0xd0);
  if (iVar3 != 0) {
    uVar4 = 8;
  }
  iVar3 = KeyOn(0xcf);
  if (iVar3 != 0) {
    uVar4 = 9;
  }
  iVar3 = KeyOn(199);
  if (iVar3 != 0) {
    uVar4 = 10;
  }
  iVar3 = KeyOn('\x01');
  if (iVar3 != 0) {
    uVar4 = 0xb;
  }
  iVar3 = KeyOn(';');
  if (iVar3 != 0) {
    uVar4 = 0xc;
  }
  iVar3 = KeyOn('\x1c');
  if (iVar3 == 0) {
    if (uVar4 == 0) {
      _gRShellKeyRepeatLife = 0.0;
      _gRShellOldKey = 0;
      return 0;
    }
    uVar5 = (int)(char)uVar4;
  }
  else {
    iVar3 = KeyTest('\x1d');
    if (iVar3 == 0) {
      uVar4 = 5;
      uVar5 = uVar4;
    }
    else {
      uVar4 = 6;
      uVar5 = uVar4;
    }
  }
  if (_gRShellKeyRepeatLife == 0.0) {
    _gRShellKeyRepeatLifeRate = 0.033333335;
    _gRShellKeyRepeatLife = 0.033333335;
    _gRShellOldKey = (char)uVar4;
  }
  else {
    cVar1 = RstrASC((char)uVar5);
    cVar2 = RstrASC(_gRShellOldKey);
    if (cVar1 == cVar2) {
      _gRShellKeyRepeatLife = _gRShellKeyRepeatLife + _gRShellKeyRepeatLifeRate;
      if (1.0 < _gRShellKeyRepeatLife) {
        _gRShellKeyRepeatLifeRate = 0.11111111;
        _gRShellKeyRepeatLife = 0.11111111;
      }
      else {
        uVar5 = 0;
      }
    }
    else {
      _gRShellKeyRepeatLifeRate = 0.011111111;
      _gRShellKeyRepeatLife = 0.011111111;
      _gRShellOldKey = (char)uVar4;
    }
  }
  return uVar5;
}
