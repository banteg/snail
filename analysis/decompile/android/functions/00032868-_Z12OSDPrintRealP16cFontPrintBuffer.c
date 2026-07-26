/*
 * mangled: _Z12OSDPrintRealP16cFontPrintBuffer
 * demangled: OSDPrintReal(cFontPrintBuffer*)
 * address: 00032868
 * size: 176
 */

/* OSDPrintReal(cFontPrintBuffer*) */

void OSDPrintReal(cFontPrintBuffer *param_1)

{
  float in_s0;
  float in_s1;
  float in_s2;
  float in_s3;
  float in_s4;
  float in_s5;
  float in_s6;
  float in_s7;
  float in_s8;
  float in_s9;
  float in_s10;
  float in_s11;
  float in_s12;
  float in_s13;

  G0RenderFont(*(cRTexture **)(gSpriteReference + *(int *)(param_1 + 0x50) * 0x20 + 4),in_s0,in_s1,
               in_s2,in_s3,in_s4,in_s5,in_s6,in_s7,in_s8,in_s9,in_s10,in_s11,in_s12,in_s13,
               *(tColour **)(param_1 + 4),*(int *)(param_1 + 8),*(float *)(param_1 + 0x14));
  return;
}
