/*
 * mangled: _ZN6cRSure6UnInitEv
 * demangled: cRSure::UnInit()
 * address: 0005b8e8
 * size: 32
 */

/* cRSure::UnInit() */

void cRSure::UnInit(void)

{
  cRBorderManager::KillBorders
            ((cRBorderManager *)(**(int **)(DAT_0005b908 + 0x5b8f8 + DAT_0005b90c) + 0xd14));
  return;
}
