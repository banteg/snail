/*
 * mangled: _ZN10cRContinue6UnInitEv
 * demangled: cRContinue::UnInit()
 * address: 000618d8
 * size: 32
 */

/* cRContinue::UnInit() */

void cRContinue::UnInit(void)

{
  cRBorderManager::KillBorders
            ((cRBorderManager *)(**(int **)(DAT_000618f8 + 0x618e8 + DAT_000618fc) + 0xd14));
  return;
}
