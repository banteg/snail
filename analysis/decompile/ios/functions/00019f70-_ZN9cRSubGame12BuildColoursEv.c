/*
 * mangled: _ZN9cRSubGame12BuildColoursEv
 * demangled: cRSubGame::BuildColours()
 * address: 00019f70
 * size: 196
 */

/* cRSubGame::BuildColours() */

void cRSubGame::BuildColours(void)

{
  int iVar1;
  int iVar2;

  iVar2 = 0;
  do {
    iVar1 = iVar2 * 0x10;
    tColour::White((tColour *)(&_gLocColourLookupCheckBlack + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupFloor + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupSlide + iVar1));
    iVar2 = iVar2 + 1;
    tColour::White((tColour *)(&_gLocColourLookupSlide + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupWall + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupTrampoline + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupRamp + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupEmpty + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupPath + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupPathWorm + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupPathWorm + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupPathWarp + iVar1));
    tColour::White((tColour *)(&_gLocColourLookupPathWarp + iVar1));
  } while (iVar2 != 0x35);
  return;
}
