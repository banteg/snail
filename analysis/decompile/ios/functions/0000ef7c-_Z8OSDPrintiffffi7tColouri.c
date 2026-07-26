/*
 * mangled: _Z8OSDPrintiffffi7tColouri
 * demangled: OSDPrint(int, float, float, float, float, int, tColour, int)
 * address: 0000ef7c
 * size: 264
 */

/* OSDPrint(int, float, float, float, float, int, tColour, int) */

void OSDPrint(int param_1,undefined4 param_2,undefined4 param_3,float param_4,float param_5,
             uint param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
             undefined4 param_10,undefined4 param_11)

{
  int iVar1;
  undefined *puVar2;

  if (*PTR__G0RenderNextFlag_001b60f4 != '\0') {
    if (_FontPrintIndex == 0x200) {
      RShellError("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
    }
    else if ((param_4 != 0.0) && (param_5 != 0.0)) {
      iVar1 = _FontPrintIndex * 0x84;
      *(uint *)(&_FontPrintBuffer + iVar1) = param_6 | 2;
      *(int *)(&DAT_00270e8c + iVar1) = param_1;
      *(float *)(&DAT_00270e94 + iVar1) = param_5;
      *(float *)(&DAT_00270e90 + iVar1) = param_4;
      *(undefined4 *)(&DAT_00270e40 + iVar1) = param_2;
      *(undefined4 *)(&DAT_00270ea8 + iVar1) = param_7;
      *(undefined4 *)(&DAT_00270eac + iVar1) = param_8;
      *(undefined4 *)(&DAT_00270eb0 + iVar1) = param_9;
      *(undefined4 *)(&DAT_00270eb4 + iVar1) = param_10;
      *(undefined4 *)(&DAT_00270e44 + iVar1) = param_3;
      puVar2 = PTR__gSpriteReference_001b61c8;
      *(undefined4 *)(&DAT_00270e98 + iVar1) =
           *(undefined4 *)(PTR__gSpriteReference_001b61c8 + param_1 * 0x20 + 0x10);
      *(float *)(&DAT_00270e9c + iVar1) = 1.0 - *(float *)(puVar2 + param_1 * 0x20 + 0x1c);
      *(undefined4 *)(&DAT_00270ea0 + iVar1) = *(undefined4 *)(puVar2 + param_1 * 0x20 + 0x18);
      *(float *)(&DAT_00270ea4 + iVar1) = 1.0 - *(float *)(puVar2 + param_1 * 0x20 + 0x14);
      *(undefined4 *)(&DAT_00270eb8 + iVar1) = param_11;
      *(undefined4 *)(&DAT_00270ebc + iVar1) = 0;
      _FontPrintIndex = _FontPrintIndex + 1;
    }
  }
  return;
}
