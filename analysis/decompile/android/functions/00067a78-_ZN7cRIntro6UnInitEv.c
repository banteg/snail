/*
 * mangled: _ZN7cRIntro6UnInitEv
 * demangled: cRIntro::UnInit()
 * address: 00067a78
 * size: 52
 */

/* cRIntro::UnInit() */

void cRIntro::UnInit(void)

{
  cRBorderManager::KillBorders((cRBorderManager *)(Game + 0xd14));
  cRSpriteManager::KillGame();
  return;
}
