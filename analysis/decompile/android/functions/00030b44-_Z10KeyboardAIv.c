/*
 * mangled: _Z10KeyboardAIv
 * demangled: KeyboardAI()
 * address: 00030b44
 * size: 104
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* KeyboardAI() */

void KeyboardAI(void)

{
  undefined1 uVar1;
  int iVar2;

  iVar2 = 0;
  do {
    uVar1 = KeyboardState[iVar2];
    KeyboardState[iVar2] = 0;
    KeyboardStateLast[iVar2] = uVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x100);
  if (KeyNext != -1) {
    KeyboardState[KeyNext] = 0x80;
  }
  KeyNext = 0xffffffff;
  return;
}
