/*
 * mangled: _Z16RShellInkeyInputv
 * demangled: RShellInkeyInput()
 * address: 0002a710
 * size: 1160
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellInkeyInput() */

char RShellInkeyInput(void)

{
  int iVar1;
  int iVar2;
  char cVar3;

  iVar1 = KeyOn('\x1e');
  if (iVar1 == 0) {
    cVar3 = '\0';
  }
  else {
    cVar3 = 'a';
  }
  iVar1 = KeyOn('0');
  if (iVar1 != 0) {
    cVar3 = 'b';
  }
  iVar1 = KeyOn('.');
  if (iVar1 != 0) {
    cVar3 = 'c';
  }
  iVar1 = KeyOn(' ');
  if (iVar1 != 0) {
    cVar3 = 'd';
  }
  iVar1 = KeyOn('\x12');
  if (iVar1 != 0) {
    cVar3 = 'e';
  }
  iVar1 = KeyOn('!');
  if (iVar1 != 0) {
    cVar3 = 'f';
  }
  iVar1 = KeyOn('\"');
  if (iVar1 != 0) {
    cVar3 = 'g';
  }
  iVar1 = KeyOn('#');
  if (iVar1 != 0) {
    cVar3 = 'h';
  }
  iVar1 = KeyOn('\x17');
  if (iVar1 != 0) {
    cVar3 = 'i';
  }
  iVar1 = KeyOn('$');
  if (iVar1 != 0) {
    cVar3 = 'j';
  }
  iVar1 = KeyOn('%');
  if (iVar1 != 0) {
    cVar3 = 'k';
  }
  iVar1 = KeyOn('&');
  if (iVar1 != 0) {
    cVar3 = 'l';
  }
  iVar1 = KeyOn('2');
  if (iVar1 != 0) {
    cVar3 = 'm';
  }
  iVar1 = KeyOn('1');
  if (iVar1 != 0) {
    cVar3 = 'n';
  }
  iVar1 = KeyOn('\x18');
  if (iVar1 != 0) {
    cVar3 = 'o';
  }
  iVar1 = KeyOn('\x19');
  if (iVar1 != 0) {
    cVar3 = 'p';
  }
  iVar1 = KeyOn('\x10');
  if (iVar1 != 0) {
    cVar3 = 'q';
  }
  iVar1 = KeyOn('\x13');
  if (iVar1 != 0) {
    cVar3 = 'r';
  }
  iVar1 = KeyOn('\x1f');
  if (iVar1 != 0) {
    cVar3 = 's';
  }
  iVar1 = KeyOn('\x14');
  if (iVar1 != 0) {
    cVar3 = 't';
  }
  iVar1 = KeyOn('\x16');
  if (iVar1 != 0) {
    cVar3 = 'u';
  }
  iVar1 = KeyOn('/');
  if (iVar1 != 0) {
    cVar3 = 'v';
  }
  iVar1 = KeyOn('\x11');
  if (iVar1 != 0) {
    cVar3 = 'w';
  }
  iVar1 = KeyOn('-');
  if (iVar1 != 0) {
    cVar3 = 'x';
  }
  iVar1 = KeyOn('\x15');
  if (iVar1 != 0) {
    cVar3 = 'y';
  }
  iVar1 = KeyOn(',');
  if (iVar1 == 0) {
    if (cVar3 == '\0') goto LAB_0002a8e8;
  }
  else {
    cVar3 = 'z';
  }
  iVar1 = KeyTest('*');
  if ((iVar1 != 0) || (iVar1 = KeyTest('6'), iVar1 != 0)) {
    cVar3 = cVar3 + -0x20;
  }
LAB_0002a8e8:
  iVar1 = KeyOn('9');
  if (iVar1 != 0) {
    cVar3 = ' ';
  }
  iVar1 = KeyOn('\v');
  if (iVar1 != 0) {
    cVar3 = '0';
  }
  iVar1 = KeyOn('\x02');
  if (iVar1 != 0) {
    cVar3 = '1';
  }
  iVar1 = KeyOn('\x03');
  if (iVar1 != 0) {
    cVar3 = '2';
  }
  iVar1 = KeyOn('\x04');
  if (iVar1 != 0) {
    cVar3 = '3';
  }
  iVar1 = KeyOn('\x05');
  if (iVar1 != 0) {
    cVar3 = '4';
  }
  iVar1 = KeyOn('\x06');
  if (iVar1 != 0) {
    cVar3 = '5';
  }
  iVar1 = KeyOn('\a');
  if (iVar1 != 0) {
    cVar3 = '6';
  }
  iVar1 = KeyOn('\b');
  if (iVar1 != 0) {
    cVar3 = '7';
  }
  iVar1 = KeyOn('\t');
  if (iVar1 != 0) {
    cVar3 = '8';
  }
  iVar1 = KeyOn('\n');
  if (iVar1 != 0) {
    cVar3 = '9';
  }
  iVar1 = KeyOn('4');
  if (iVar1 != 0) {
    cVar3 = '.';
  }
  iVar1 = KeyOn('3');
  if (iVar1 != 0) {
    cVar3 = ',';
  }
  iVar1 = KeyOn('(');
  if (iVar1 != 0) {
    cVar3 = '\'';
  }
  iVar1 = KeyOn('+');
  if (iVar1 != 0) {
    cVar3 = '\\';
  }
  iVar1 = KeyOn('\x0e');
  if (iVar1 != 0) {
    cVar3 = '\x01';
  }
  iVar1 = KeyOn(0xd3);
  if (iVar1 != 0) {
    cVar3 = '\x02';
  }
  iVar1 = KeyOn(0xcb);
  if (iVar1 != 0) {
    cVar3 = '\x03';
  }
  iVar1 = KeyOn(0xcd);
  if (iVar1 != 0) {
    cVar3 = '\x04';
  }
  iVar1 = KeyOn(200);
  if (iVar1 != 0) {
    cVar3 = '\a';
  }
  iVar1 = KeyOn(0xd0);
  if (iVar1 != 0) {
    cVar3 = '\b';
  }
  iVar1 = KeyOn(0xcf);
  if (iVar1 != 0) {
    cVar3 = '\t';
  }
  iVar1 = KeyOn(199);
  if (iVar1 != 0) {
    cVar3 = '\n';
  }
  iVar1 = KeyOn('\x01');
  if (iVar1 != 0) {
    cVar3 = '\v';
  }
  iVar1 = KeyOn(';');
  if (iVar1 != 0) {
    cVar3 = '\f';
  }
  iVar1 = KeyOn('\x1c');
  if (iVar1 == 0) {
    if (cVar3 == '\0') {
      gRShellKeyRepeatLife = 0.0;
      gRShellOldKey = 0;
      return '\0';
    }
  }
  else {
    iVar1 = KeyTest('\x1d');
    if (iVar1 == 0) {
      cVar3 = '\x05';
    }
    else {
      cVar3 = '\x06';
    }
  }
  if (gRShellKeyRepeatLife != 0.0) {
    iVar1 = RstrASC(cVar3);
    iVar2 = RstrASC(gRShellOldKey);
    if (iVar1 == iVar2) {
      gRShellKeyRepeatLife = gRShellKeyRepeatLife + gRShellKeyRepeatLifeRate;
      if (1.0 < gRShellKeyRepeatLife) {
        gRShellKeyRepeatLife = 0.11111111;
        gRShellKeyRepeatLifeRate = 0.11111111;
      }
      else {
        cVar3 = '\0';
      }
      return cVar3;
    }
    gRShellOldKey = cVar3;
    gRShellKeyRepeatLife = 0.011111111;
    gRShellKeyRepeatLifeRate = 0.011111111;
    return cVar3;
  }
  gRShellKeyRepeatLife = 0.033333335;
  gRShellKeyRepeatLifeRate = 0.033333335;
  gRShellOldKey = cVar3;
  return cVar3;
}
