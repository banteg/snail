/*
 * mangled: _ZN10cRMainMenu6UnInitEv
 * demangled: cRMainMenu::UnInit()
 * address: 00061b98
 * size: 48
 */

/* cRMainMenu::UnInit() */

void cRMainMenu::UnInit(void)

{
  cRBorderManager::KillBorders((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  cRSpriteManager::KillGame();
  return;
}
