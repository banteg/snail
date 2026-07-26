/*
 * mangled: _Z11RShellInkeyv
 * demangled: RShellInkey()
 * address: 0000c778
 * size: 932
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* RShellInkey() */

int RShellInkey(void)

{
  int iVar1;
  char cVar2;

  iVar1 = KeyPress('\x1e');
  if (iVar1 == 0) {
    cVar2 = '\0';
  }
  else {
    cVar2 = 'a';
  }
  iVar1 = KeyPress('0');
  if (iVar1 != 0) {
    cVar2 = 'b';
  }
  iVar1 = KeyPress('.');
  if (iVar1 != 0) {
    cVar2 = 'c';
  }
  iVar1 = KeyPress(' ');
  if (iVar1 != 0) {
    cVar2 = 'd';
  }
  iVar1 = KeyPress('\x12');
  if (iVar1 != 0) {
    cVar2 = 'e';
  }
  iVar1 = KeyPress('!');
  if (iVar1 != 0) {
    cVar2 = 'f';
  }
  iVar1 = KeyPress('\"');
  if (iVar1 != 0) {
    cVar2 = 'g';
  }
  iVar1 = KeyPress('#');
  if (iVar1 != 0) {
    cVar2 = 'h';
  }
  iVar1 = KeyPress('\x17');
  if (iVar1 != 0) {
    cVar2 = 'i';
  }
  iVar1 = KeyPress('$');
  if (iVar1 != 0) {
    cVar2 = 'j';
  }
  iVar1 = KeyPress('%');
  if (iVar1 != 0) {
    cVar2 = 'k';
  }
  iVar1 = KeyPress('&');
  if (iVar1 != 0) {
    cVar2 = 'l';
  }
  iVar1 = KeyPress('2');
  if (iVar1 != 0) {
    cVar2 = 'm';
  }
  iVar1 = KeyPress('1');
  if (iVar1 != 0) {
    cVar2 = 'n';
  }
  iVar1 = KeyPress('\x18');
  if (iVar1 != 0) {
    cVar2 = 'o';
  }
  iVar1 = KeyPress('\x19');
  if (iVar1 != 0) {
    cVar2 = 'p';
  }
  iVar1 = KeyPress('\x10');
  if (iVar1 != 0) {
    cVar2 = 'q';
  }
  iVar1 = KeyPress('\x13');
  if (iVar1 != 0) {
    cVar2 = 'r';
  }
  iVar1 = KeyPress('\x1f');
  if (iVar1 != 0) {
    cVar2 = 's';
  }
  iVar1 = KeyPress('\x14');
  if (iVar1 != 0) {
    cVar2 = 't';
  }
  iVar1 = KeyPress('\x16');
  if (iVar1 != 0) {
    cVar2 = 'u';
  }
  iVar1 = KeyPress('/');
  if (iVar1 != 0) {
    cVar2 = 'v';
  }
  iVar1 = KeyPress('\x11');
  if (iVar1 != 0) {
    cVar2 = 'w';
  }
  iVar1 = KeyPress('-');
  if (iVar1 != 0) {
    cVar2 = 'x';
  }
  iVar1 = KeyPress('\x15');
  if (iVar1 != 0) {
    cVar2 = 'y';
  }
  iVar1 = KeyPress(',');
  if (iVar1 == 0) {
    if (cVar2 == '\0') goto LAB_0000c930;
  }
  else {
    cVar2 = 'z';
  }
  iVar1 = KeyTest('*');
  if ((iVar1 != 0) || (iVar1 = KeyTest('6'), iVar1 != 0)) {
    cVar2 = cVar2 + -0x20;
  }
LAB_0000c930:
  iVar1 = KeyPress('9');
  if (iVar1 != 0) {
    cVar2 = ' ';
  }
  iVar1 = KeyPress('\v');
  if (iVar1 != 0) {
    cVar2 = '0';
  }
  iVar1 = KeyPress('\x02');
  if (iVar1 != 0) {
    cVar2 = '1';
  }
  iVar1 = KeyPress('\x03');
  if (iVar1 != 0) {
    cVar2 = '2';
  }
  iVar1 = KeyPress('\x04');
  if (iVar1 != 0) {
    cVar2 = '3';
  }
  iVar1 = KeyPress('\x05');
  if (iVar1 != 0) {
    cVar2 = '4';
  }
  iVar1 = KeyPress('\x06');
  if (iVar1 != 0) {
    cVar2 = '5';
  }
  iVar1 = KeyPress('\a');
  if (iVar1 != 0) {
    cVar2 = '6';
  }
  iVar1 = KeyPress('\b');
  if (iVar1 != 0) {
    cVar2 = '7';
  }
  iVar1 = KeyPress('\t');
  if (iVar1 != 0) {
    cVar2 = '8';
  }
  iVar1 = KeyPress('\n');
  if (iVar1 != 0) {
    cVar2 = '9';
  }
  iVar1 = KeyPress('4');
  if (iVar1 != 0) {
    cVar2 = '.';
  }
  iVar1 = KeyPress('3');
  if (iVar1 != 0) {
    cVar2 = ',';
  }
  iVar1 = KeyPress('(');
  if (iVar1 != 0) {
    cVar2 = '\'';
  }
  iVar1 = KeyPress('+');
  if (iVar1 != 0) {
    cVar2 = '\\';
  }
  iVar1 = KeyPress('\x0e');
  if (iVar1 != 0) {
    cVar2 = '\x01';
  }
  iVar1 = KeyPress(0xd3);
  if (iVar1 != 0) {
    cVar2 = '\x02';
  }
  iVar1 = KeyPress(0xcb);
  if (iVar1 != 0) {
    cVar2 = '\x03';
  }
  iVar1 = KeyPress(0xcd);
  if (iVar1 != 0) {
    cVar2 = '\x04';
  }
  iVar1 = KeyPress(200);
  if (iVar1 != 0) {
    cVar2 = '\a';
  }
  iVar1 = KeyPress(0xd0);
  if (iVar1 != 0) {
    cVar2 = '\b';
  }
  iVar1 = KeyPress(0xcf);
  if (iVar1 != 0) {
    cVar2 = '\t';
  }
  iVar1 = KeyPress(199);
  if (iVar1 != 0) {
    cVar2 = '\n';
  }
  iVar1 = KeyPress('\x01');
  if (iVar1 != 0) {
    cVar2 = '\v';
  }
  iVar1 = KeyPress(';');
  if (iVar1 != 0) {
    cVar2 = '\f';
  }
  iVar1 = KeyPress('\x1c');
  if (iVar1 == 0) {
    return (int)cVar2;
  }
  iVar1 = KeyTest('\x1d');
  if (iVar1 == 0) {
    iVar1 = 5;
  }
  else {
    iVar1 = 6;
  }
  return iVar1;
}
