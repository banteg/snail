/*
 * mangled: _Z6FontAIv
 * demangled: FontAI()
 * address: 00031944
 * size: 260
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* FontAI() */

void FontAI(void)

{
  FontCount = 0;
  FontPrintBufferIndex = FontPrintBufferText;
  FontPrintIndex = 0;
  if ((*(float *)(Game + 0x3c) == 0.0) || (*(float *)(Game + 0x3c) == 180.0)) {
    RFont._2596_4_ = 0x3fa66666;
  }
  else {
    RFont._2596_4_ = 0x3f800000;
  }
  FontWibbleX = FontWibbleX + FontWibbleXRate;
  if (6.2831855 < FontWibbleX) {
    FontWibbleX = FontWibbleX - 6.2831855;
  }
  FontWibbleY = FontWibbleY + FontWibbleYRate;
  if (6.2831855 < FontWibbleY) {
    FontWibbleY = FontWibbleY - 6.2831855;
  }
  return;
}
