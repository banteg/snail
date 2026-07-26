/*
 * mangled: _Z8OSDPrintiffffi7tColouri
 * demangled: OSDPrint(int, float, float, float, float, int, tColour, int)
 * address: 000326f4
 * size: 340
 */

/* OSDPrint(int, float, float, float, float, int, tColour, int) */

void OSDPrint(int param_1,undefined4 param_6,undefined4 param_3,float param_4,float param_5,
             uint param_6_00,undefined4 param_7,undefined4 param_8,undefined4 param_9,
             undefined4 param_10,undefined4 param_11)

{
  int iVar1;
  int iVar2;
  float fVar3;

  if (G0RenderNextFlag == '\x01') {
    if (FontPrintIndex == 0x200) {
      RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
      return;
    }
    if ((param_4 != 0.0) && (param_5 != 0.0)) {
      iVar1 = FontPrintIndex * 0x84;
      *(float *)(FontPrintBuffer + iVar1 + 0x54) = param_4;
      *(float *)(FontPrintBuffer + iVar1 + 0x58) = param_5;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 4) = param_6;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x6c) = param_7;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x70) = param_8;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x74) = param_9;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x78) = param_10;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 8) = param_3;
      iVar2 = (param_1 * 2 + 1) * 0x10;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x5c) = *(undefined4 *)(gSpriteReference + iVar2);
      fVar3 = *(float *)(gSpriteReference + param_1 * 0x20 + 0x1c);
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x7c) = param_11;
      *(int *)(FontPrintBuffer + iVar1 + 0x50) = param_1;
      *(uint *)(FontPrintBuffer + FontPrintIndex * 0x84) = param_6_00 | 2;
      FontPrintIndex = FontPrintIndex + 1;
      *(float *)(FontPrintBuffer + iVar1 + 0x60) = 1.0 - fVar3;
      *(undefined4 *)(FontPrintBuffer + iVar1 + 100) =
           *(undefined4 *)(gSpriteReference + param_1 * 0x20 + 0x18);
      fVar3 = *(float *)(gSpriteReference + iVar2 + 4);
      *(undefined4 *)(FontPrintBuffer + iVar1 + 0x80) = 0;
      *(float *)(FontPrintBuffer + iVar1 + 0x68) = 1.0 - fVar3;
    }
  }
  return;
}
