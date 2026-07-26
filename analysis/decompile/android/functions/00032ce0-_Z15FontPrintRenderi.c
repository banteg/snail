/*
 * mangled: _Z15FontPrintRenderi
 * demangled: FontPrintRender(int)
 * address: 00032ce0
 * size: 140
 */

/* FontPrintRender(int) */

void FontPrintRender(int param_1)

{
  int iVar1;
  undefined1 *puVar2;

  if (FontPrintIndex != 0) {
    puVar2 = FontPrintBuffer + FontPrintIndex * 0x84;
    iVar1 = FontPrintIndex;
    do {
      iVar1 = iVar1 + -1;
      if ((param_1 & *(uint *)(puVar2 + -0x84) & 0xff000000) != 0) {
        if ((*(uint *)(puVar2 + -0x84) & 1) == 0) {
          OSDPrintReal((cFontPrintBuffer *)(FontPrintBuffer + iVar1 * 0x84));
        }
        else {
          FontPrintReal((cFontPrintBuffer *)(FontPrintBuffer + iVar1 * 0x84));
        }
      }
      puVar2 = puVar2 + -0x84;
    } while (iVar1 != 0);
    return;
  }
  return;
}
