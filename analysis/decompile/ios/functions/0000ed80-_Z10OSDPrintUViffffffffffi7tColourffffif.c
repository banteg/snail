/*
 * mangled: _Z10OSDPrintUViffffffffffi7tColourffffif
 * demangled: OSDPrintUV(int, float, float, float, float, float, float, float, float, float, float, int, tColour, float, float, float, float, int, float)
 * address: 0000ed80
 * size: 252
 */

/* OSDPrintUV(int, float, float, float, float, float, float, float, float, float, float, int,
   tColour, float, float, float, float, int, float) */

void OSDPrintUV(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,uint param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16,
               undefined4 param_17,undefined4 param_18,undefined4 param_19,undefined4 param_20,
               undefined4 param_21,undefined4 param_22)

{
  int iVar1;

  if (*PTR__G0RenderNextFlag_001b60f4 != '\0') {
    if (_FontPrintIndex == 0x200) {
      RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
    }
    else {
      iVar1 = _FontPrintIndex * 0x84;
      *(undefined4 *)(&DAT_00270e8c + iVar1) = param_1;
      *(uint *)(&_FontPrintBuffer + iVar1) = param_12 | 2;
      *(undefined4 *)(&DAT_00270e40 + iVar1) = param_2;
      *(undefined4 *)(&DAT_00270e44 + iVar1) = param_3;
      *(undefined4 *)(&DAT_00270e4c + iVar1) = param_4;
      *(undefined4 *)(&DAT_00270ea8 + iVar1) = param_13;
      *(undefined4 *)(&DAT_00270eac + iVar1) = param_14;
      *(undefined4 *)(&DAT_00270eb0 + iVar1) = param_15;
      *(undefined4 *)(&DAT_00270eb4 + iVar1) = param_16;
      *(undefined4 *)(&DAT_00270e50 + iVar1) = param_5;
      *(undefined4 *)(&DAT_00270e58 + iVar1) = param_6;
      *(undefined4 *)(&DAT_00270e5c + iVar1) = param_7;
      *(undefined4 *)(&DAT_00270e64 + iVar1) = param_8;
      *(undefined4 *)(&DAT_00270e90 + iVar1) = 0;
      *(undefined4 *)(&DAT_00270e94 + iVar1) = 0;
      *(undefined4 *)(&DAT_00270e68 + iVar1) = param_9;
      *(undefined4 *)(&DAT_00270e98 + iVar1) = param_17;
      *(undefined4 *)(&DAT_00270e9c + iVar1) = param_18;
      *(undefined4 *)(&DAT_00270ea0 + iVar1) = param_19;
      *(undefined4 *)(&DAT_00270ea4 + iVar1) = param_20;
      *(undefined4 *)(&DAT_00270eb8 + iVar1) = param_21;
      _FontPrintIndex = _FontPrintIndex + 1;
      *(undefined4 *)(&DAT_00270ebc + iVar1) = param_22;
    }
  }
  return;
}
