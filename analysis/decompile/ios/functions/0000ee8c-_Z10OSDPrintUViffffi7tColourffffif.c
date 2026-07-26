/*
 * mangled: _Z10OSDPrintUViffffi7tColourffffif
 * demangled: OSDPrintUV(int, float, float, float, float, int, tColour, float, float, float, float, int, float)
 * address: 0000ee8c
 * size: 224
 */

/* OSDPrintUV(int, float, float, float, float, int, tColour, float, float, float, float, int, float)
    */

void OSDPrintUV(undefined4 param_1,undefined4 param_2,undefined4 param_3,float param_4,float param_5
               ,uint param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
               undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;

  if (*PTR__G0RenderNextFlag_001b60f4 == '\0') {
    return;
  }
  if (_FontPrintIndex == 0x200) {
    RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
    return;
  }
  if (param_4 == 0.0) {
    return;
  }
  if (param_5 == 0.0) {
    return;
  }
  iVar1 = _FontPrintIndex * 0x84;
  *(undefined4 *)(&DAT_00270e8c + iVar1) = param_1;
  *(uint *)(&_FontPrintBuffer + iVar1) = param_6 | 2;
  *(undefined4 *)(&DAT_00270e40 + iVar1) = param_2;
  *(undefined4 *)(&DAT_00270e44 + iVar1) = param_3;
  *(float *)(&DAT_00270e90 + iVar1) = param_4;
  *(float *)(&DAT_00270e94 + iVar1) = param_5;
  *(undefined4 *)(&DAT_00270ea8 + iVar1) = param_7;
  *(undefined4 *)(&DAT_00270eac + iVar1) = param_8;
  *(undefined4 *)(&DAT_00270eb0 + iVar1) = param_9;
  *(undefined4 *)(&DAT_00270eb4 + iVar1) = param_10;
  *(undefined4 *)(&DAT_00270e98 + iVar1) = param_11;
  *(undefined4 *)(&DAT_00270e9c + iVar1) = param_12;
  *(undefined4 *)(&DAT_00270ea0 + iVar1) = param_13;
  *(undefined4 *)(&DAT_00270ea4 + iVar1) = param_14;
  *(undefined4 *)(&DAT_00270eb8 + iVar1) = param_15;
  *(undefined4 *)(&DAT_00270ebc + iVar1) = param_16;
  _FontPrintIndex = _FontPrintIndex + 1;
  return;
}
