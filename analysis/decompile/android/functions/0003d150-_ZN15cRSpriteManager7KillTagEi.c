/*
 * mangled: _ZN15cRSpriteManager7KillTagEi
 * demangled: cRSpriteManager::KillTag(int)
 * address: 0003d150
 * size: 108
 */

/* cRSpriteManager::KillTag(int) */

void __thiscall cRSpriteManager::KillTag(cRSpriteManager *this,int param_1)

{
  cRSprite *pcVar1;
  cRSprite *this_00;
  int iVar2;
  int iVar3;

  iVar3 = *(int *)(DAT_0003d1bc + 0x3d160 + DAT_0003d1c0);
  iVar2 = 0;
  do {
    pcVar1 = *(cRSprite **)(iVar3 + iVar2 + 0x2af84);
    while (this_00 = pcVar1, pcVar1 != (cRSprite *)0x0) {
      while (pcVar1 = *(cRSprite **)(this_00 + 0xc), *(int *)this_00 != param_1) {
        this_00 = pcVar1;
        if (pcVar1 == (cRSprite *)0x0) goto LAB_0003d1ac;
      }
      cRSprite::Kill(this_00);
    }
LAB_0003d1ac:
    iVar2 = iVar2 + 4;
    if (iVar2 == 0xc) {
      return;
    }
  } while( true );
}
