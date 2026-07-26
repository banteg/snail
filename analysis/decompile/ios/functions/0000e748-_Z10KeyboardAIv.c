/*
 * mangled: _Z10KeyboardAIv
 * demangled: KeyboardAI()
 * address: 0000e748
 * size: 60
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* KeyboardAI() */

void KeyboardAI(void)

{
  int iVar1;

  iVar1 = 1;
  _KeyboardStateLast = _KeyboardState;
  _KeyboardState = 0;
  do {
    (&_KeyboardStateLast)[iVar1] = (&_KeyboardState)[iVar1];
    (&_KeyboardState)[iVar1] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x100);
  return;
}
