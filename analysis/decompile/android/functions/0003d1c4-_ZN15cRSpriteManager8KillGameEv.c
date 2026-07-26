/*
 * mangled: _ZN15cRSpriteManager8KillGameEv
 * demangled: cRSpriteManager::KillGame()
 * address: 0003d1c4
 * size: 104
 */

/* cRSpriteManager::KillGame() */

void cRSpriteManager::KillGame(void)

{
  cRSprite *pcVar1;
  cRSprite *this;
  int iVar2;
  int iVar3;

  iVar3 = *(int *)(DAT_0003d22c + 0x3d1d4 + DAT_0003d230);
  iVar2 = 0;
  do {
    pcVar1 = *(cRSprite **)(iVar3 + iVar2 + 0x2af84);
    while (this = pcVar1, pcVar1 != (cRSprite *)0x0) {
      while (pcVar1 = *(cRSprite **)(this + 0xc), (*(uint *)(this + 4) & 0x800) == 0) {
        this = pcVar1;
        if (pcVar1 == (cRSprite *)0x0) goto LAB_0003d21c;
      }
      cRSprite::Kill(this);
    }
LAB_0003d21c:
    iVar2 = iVar2 + 4;
    if (iVar2 == 0xc) {
      return;
    }
  } while( true );
}
