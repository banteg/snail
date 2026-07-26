/*
 * mangled: _ZN10cRMainMenu6UnInitEv
 * demangled: cRMainMenu::UnInit()
 * address: 00069be0
 * size: 52
 */

/* cRMainMenu::UnInit() */

void cRMainMenu::UnInit(void)

{
  cRBorderManager::KillBorders((cRBorderManager *)(Game + 0xd14));
  cRSpriteManager::KillGame();
  return;
}
