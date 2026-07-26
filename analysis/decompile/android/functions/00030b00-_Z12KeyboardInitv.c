/*
 * mangled: _Z12KeyboardInitv
 * demangled: KeyboardInit()
 * address: 00030b00
 * size: 56
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* KeyboardInit() */

void KeyboardInit(void)

{
  int iVar1;

  iVar1 = 0;
  do {
    KeyboardState[iVar1] = 0;
    KeyboardStateLast[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x100);
  return;
}
