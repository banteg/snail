/*
 * mangled: _ZN10cRMainMenu6UnInitEv
 * demangled: cRMainMenu::UnInit()
 * address: 00069be0
 * size: 52
 */

/* cRMainMenu::UnInit() */

void cRMainMenu::UnInit(void)

{
  cRBorderManager::KillBorders
            ((cRBorderManager *)(**(int **)(DAT_00069c14 + 0x69bf4 + DAT_00069c18) + 0xd14));
  cRSpriteManager::KillGame();
  return;
}
