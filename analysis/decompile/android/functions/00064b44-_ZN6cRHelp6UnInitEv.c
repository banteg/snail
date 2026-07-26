/*
 * mangled: _ZN6cRHelp6UnInitEv
 * demangled: cRHelp::UnInit()
 * address: 00064b44
 * size: 32
 */

/* cRHelp::UnInit() */

void cRHelp::UnInit(void)

{
  cRBorderManager::KillBorders
            ((cRBorderManager *)(**(int **)(DAT_00064b64 + 0x64b54 + DAT_00064b68) + 0xd14));
  return;
}
