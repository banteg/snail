/*
 * mangled: _Z10OSDPrintUViffffi7tColourffffif
 * demangled: OSDPrintUV(int, float, float, float, float, int, tColour, float, float, float, float, int, float)
 * address: 000325d4
 * size: 268
 */

/* OSDPrintUV(int, float, float, float, float, int, tColour, float, float, float, float, int, float)
    */

void OSDPrintUV(undefined4 param_1,undefined4 param_6,undefined4 param_3,float param_4,float param_5
               ,uint param_6_00,undefined4 param_7,undefined4 param_8,undefined4 param_9,
               undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;

  iVar2 = FontPrintIndex;
  if (G0RenderNextFlag == '\x01') {
    if (FontPrintIndex == 0x200) {
      RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
      return;
    }
    if ((param_4 != 0.0) && (param_5 != 0.0)) {
      iVar1 = FontPrintIndex * 0x84;
      FontPrintIndex = FontPrintIndex + 1;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x80) = param_16;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x50) = param_1;
      *(float *)(FontPrintBuffer + iVar1 + 0x54) = param_4;
      *(uint *)(FontPrintBuffer + iVar2 * 0x84) = param_6_00 | 2;
      *(float *)(FontPrintBuffer + iVar1 + 0x58) = param_5;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x5c) = param_11;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 4) = param_6;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x60) = param_12;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 8) = param_3;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 100) = param_13;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x6c) = param_7;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x70) = param_8;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x74) = param_9;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x78) = param_10;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x68) = param_14;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x7c) = param_15;
    }
  }
  return;
}
