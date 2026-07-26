/*
 * mangled: _Z9FontPrintPcifffifi7tColourfb
 * demangled: FontPrint(char*, int, float, float, float, int, float, int, tColour, float, bool)
 * address: 00031dec
 * size: 364
 */

/* FontPrint(char*, int, float, float, float, int, float, int, tColour, float, bool) */

void FontPrint(char *param_1,undefined4 param_2,undefined4 param_6,undefined4 param_8,
              undefined4 param_5,undefined4 param_6_00,undefined4 param_7,uint param_8_00,
              undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
              undefined4 param_13,undefined1 param_14)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;

  iVar4 = FontPrintIndex;
  if ((G0RenderNextFlag == '\x01') && (FontPrintIndex != 0x200)) {
    iVar1 = FontPrintIndex * 0x84;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x40) = param_6;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 4) = param_8;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 8) = param_5;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x4c) = param_7;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x3c) = param_2;
    *(uint *)(FontPrintBuffer + iVar4 * 0x84) = param_8_00 | 1;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x34) = param_13;
    FontPrintBuffer[iVar1 + 0x38] = param_14;
    *(char **)(FontPrintBuffer + iVar1 + 0x44) = FontPrintBufferIndex;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x6c) = param_9;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x70) = param_10;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x74) = param_11;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x78) = param_12;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x48) = param_6_00;
    cVar2 = *param_1;
    if (cVar2 != '\0') {
      pcVar5 = FontPrintBufferIndex + -0x121434;
      pcVar3 = FontPrintBufferIndex;
      do {
        if (0x3fe < (int)pcVar5) {
          *pcVar3 = '\0';
          FontPrintBufferIndex = pcVar3 + 1;
          return;
        }
        FontPrintBufferIndex = pcVar3 + 1;
        *pcVar3 = cVar2;
        pcVar5 = pcVar5 + 1;
        cVar2 = param_1[1];
        param_1 = param_1 + 1;
        pcVar3 = FontPrintBufferIndex;
      } while (cVar2 != '\0');
    }
    *FontPrintBufferIndex = '\0';
    FontPrintIndex = FontPrintIndex + 1;
    FontPrintBufferIndex = FontPrintBufferIndex + 1;
  }
  return;
}
