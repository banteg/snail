/*
 * mangled: _Z15FontPrintRenderi
 * demangled: FontPrintRender(int)
 * address: 000107ac
 * size: 312
 */

/* FontPrintRender(int) */

void FontPrintRender(int param_1)

{
  int *piVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  int *piVar16;
  float *pfVar17;
  undefined *puVar18;
  int iVar19;

  if (_FontPrintIndex != 0) {
    puVar18 = &_FontPrintBuffer + _FontPrintIndex * 0x84;
    iVar19 = _FontPrintIndex;
    do {
      while( true ) {
        iVar19 = iVar19 + -1;
        if ((param_1 & *(uint *)(puVar18 + -0x84) & 0xff000000) == 0) break;
        if ((*(uint *)(puVar18 + -0x84) & 1) != 0) {
          FontPrintReal((cFontPrintBuffer *)(&_FontPrintBuffer + iVar19 * 0x84));
          break;
        }
        piVar1 = (int *)(puVar18 + -0x34);
        pfVar2 = (float *)(puVar18 + -0x70);
        pfVar3 = (float *)(puVar18 + -0x80);
        pfVar4 = (float *)(puVar18 + -0x7c);
        pfVar5 = (float *)(puVar18 + -0x74);
        pfVar6 = (float *)(puVar18 + -0x68);
        pfVar7 = (float *)(puVar18 + -100);
        pfVar8 = (float *)(puVar18 + -0x5c);
        pfVar9 = (float *)(puVar18 + -0x58);
        pfVar10 = (float *)(puVar18 + -0x30);
        pfVar11 = (float *)(puVar18 + -0x2c);
        pfVar12 = (float *)(puVar18 + -0x28);
        pfVar13 = (float *)(puVar18 + -0x24);
        pfVar14 = (float *)(puVar18 + -0x20);
        pfVar15 = (float *)(puVar18 + -0x1c);
        piVar16 = (int *)(puVar18 + -8);
        pfVar17 = (float *)(puVar18 + -4);
        puVar18 = puVar18 + -0x84;
        G0RenderFont(*(cRTexture **)(PTR__gSpriteReference_001b61c8 + *piVar1 * 0x20 + 4),*pfVar3,
                     *pfVar4,*pfVar5,*pfVar2,*pfVar6,*pfVar7,*pfVar8,*pfVar9,*pfVar10,*pfVar11,
                     *pfVar12,*pfVar13,*pfVar14,*pfVar15,(tColour *)(&DAT_00270ea8 + iVar19 * 0x84),
                     *piVar16,*pfVar17);
        if (iVar19 == 0) {
          return;
        }
      }
      puVar18 = puVar18 + -0x84;
    } while (iVar19 != 0);
  }
  return;
}
