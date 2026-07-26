/*
 * mangled: _Z13FontPrintRealP16cFontPrintBuffer
 * demangled: FontPrintReal(cFontPrintBuffer*)
 * address: 00032920
 * size: 920
 */

/* FontPrintReal(cFontPrintBuffer*) */

void FontPrintReal(cFontPrintBuffer *param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint in_fpscr;
  float extraout_s0;
  float fVar6;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s4;
  float extraout_s5;
  float extraout_s6;
  float extraout_s7;
  float extraout_s8;
  float fVar7;
  float fVar8;
  float fVar9;
  tColour *ptVar10;
  tColour atStack_68 [20];

  tColour::tColour(atStack_68);
  fVar6 = (float)tColour::Set(atStack_68,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  iVar4 = *(int *)(param_1 + 0x48);
  fVar7 = *(float *)(param_1 + 4);
  if (iVar4 == 2) {
    fVar7 = (float)FontGetStringX(*(char **)(param_1 + 0x44),*(int *)(param_1 + 0x3c),fVar6);
    fVar7 = *(float *)(param_1 + 0x4c) + 320.0 + fVar7 * -0.5;
  }
  else if (iVar4 == 1) {
    FontGetStringX(*(char **)(param_1 + 0x44),*(int *)(param_1 + 0x3c),fVar6);
    fVar7 = *(float *)(param_1 + 0x4c) + 320.0;
  }
  else if (iVar4 == 3) {
    fVar7 = (float)FontGetStringX(*(char **)(param_1 + 0x44),*(int *)(param_1 + 0x3c),fVar6);
    fVar7 = (*(float *)(param_1 + 0x4c) + 320.0) - fVar7;
  }
  pcVar5 = *(char **)(param_1 + 0x44);
  cVar1 = *pcVar5;
  do {
    if (cVar1 == '\0') {
      return;
    }
    while( true ) {
      iVar4 = FontASCIIRemap(cVar1);
      fVar8 = *(float *)(param_1 + 0x34);
      fVar6 = (float)Sin(extraout_s0_00);
      fVar9 = *(float *)(param_1 + 0x34);
      fVar2 = (float)Cos(extraout_s0_01);
      if (iVar4 != 0x35) {
        iVar3 = *(int *)(param_1 + 0x3c) * 0xa28;
        fVar8 = fVar7 + (fVar8 + fVar8) * fVar6;
        fVar6 = (float)VectorSignedToFloat((int)(*(float *)(param_1 + 8) + fVar9 * 4.0 * fVar2),
                                           (byte)(in_fpscr >> 0x16) & 3);
        ptVar10 = (tColour *)VectorSignedToFloat((int)fVar8,(byte)(in_fpscr >> 0x16) & 3);
        G0RenderFont(*(cRTexture **)(RFont + iVar3 + 4),extraout_s0_02,extraout_s1_00,extraout_s2_00
                     ,extraout_s3_00,extraout_s4,extraout_s5,extraout_s6,extraout_s7,extraout_s8,
                     *(float *)(RFont + iVar3 + 0xa08),fVar9 * 4.0,fVar2,fVar6,
                     *(float *)(RFont + iVar3 + 0xa14) * *(float *)(RFont + iVar3 + 0xa08),ptVar10,
                     (int)fVar6,fVar8);
      }
      if (9 < (byte)(*pcVar5 - 0x30U)) break;
      iVar3 = FontASCIIRemap('0');
      iVar4 = *(int *)(param_1 + 0x3c) * 0xa28;
      pcVar5 = pcVar5 + 1;
      cVar1 = *pcVar5;
      fVar6 = (float)VectorSignedToFloat((int)*(float *)(RFont + (*(int *)(param_1 + 0x3c) * 0x28a +
                                                                  iVar3 + 0x202) * 4),
                                         (byte)(in_fpscr >> 0x16) & 3);
      fVar7 = fVar7 + fVar6 * *(float *)(RFont + iVar4 + 0xa14) * *(float *)(RFont + iVar4 + 0xa18)
                      * *(float *)(param_1 + 0x40) * *(float *)(RFont + iVar4 + 0xa24);
      if (cVar1 == '\0') {
        return;
      }
    }
    pcVar5 = pcVar5 + 1;
    cVar1 = *pcVar5;
    iVar3 = *(int *)(param_1 + 0x3c) * 0xa28;
    fVar6 = (float)VectorSignedToFloat((int)*(float *)(RFont + (*(int *)(param_1 + 0x3c) * 0x28a +
                                                                iVar4 + 0x202) * 4),
                                       (byte)(in_fpscr >> 0x16) & 3);
    fVar7 = fVar7 + fVar6 * *(float *)(RFont + iVar3 + 0xa14) * *(float *)(RFont + iVar3 + 0xa18) *
                    *(float *)(param_1 + 0x40) * *(float *)(RFont + iVar3 + 0xa24);
  } while( true );
}
