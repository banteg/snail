/*
 * mangled: _Z10OSDPrintUViffffffffffi7tColourffffif
 * demangled: OSDPrintUV(int, float, float, float, float, float, float, float, float, float, float, int, tColour, float, float, float, float, int, float)
 * address: 00032494
 * size: 296
 */

/* OSDPrintUV(int, float, float, float, float, float, float, float, float, float, float, int,
   tColour, float, float, float, float, int, float) */

void OSDPrintUV(undefined4 param_1,undefined4 param_12,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,uint param_12_00,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16,
               undefined4 param_17,undefined4 param_18,undefined4 param_19,undefined4 param_20,
               undefined4 param_21,undefined4 param_22)

{
  int iVar1;
  int iVar2;

  iVar2 = FontPrintIndex;
  if (G0RenderNextFlag == '\x01') {
    if (FontPrintIndex == 0x200) {
      RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
      return;
    }
    iVar1 = FontPrintIndex * 0x84;
    FontPrintIndex = FontPrintIndex + 1;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x80) = param_22;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x50) = param_1;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x14) = param_5;
    *(uint *)(FontPrintBuffer + iVar2 * 0x84) = param_12_00 | 2;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x1c) = param_6;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x20) = param_7;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 4) = param_12;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x28) = param_8;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 8) = param_3;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x2c) = param_9;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x6c) = param_13;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x70) = param_14;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x74) = param_15;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x78) = param_16;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x58) = 0;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x5c) = param_17;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x10) = param_4;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x60) = param_18;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 100) = param_19;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x68) = param_20;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x7c) = param_21;
    *(undefined4 *)(FontPrintBuffer + iVar1 + 0x54) = 0;
  }
  return;
}
