/*
 * mangled: _Z12KeyboardInitv
 * demangled: KeyboardInit()
 * address: 0000e70c
 * size: 52
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* KeyboardInit() */

void KeyboardInit(void)

{
  int iVar1;

  _KeyboardState = 0;
  _KeyboardStateLast = 0;
  iVar1 = 1;
  do {
    (&_KeyboardState)[iVar1] = 0;
    (&_KeyboardStateLast)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x100);
  return;
}
