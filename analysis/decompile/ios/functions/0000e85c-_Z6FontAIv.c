/*
 * mangled: _Z6FontAIv
 * demangled: FontAI()
 * address: 0000e85c
 * size: 188
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* FontAI() */

void FontAI(void)

{
  _FontCount = 0;
  _FontPrintBufferIndex = &_FontPrintBufferText;
  _FontPrintIndex = 0;
  if ((*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) == 0.0) ||
     (*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) == 180.0)) {
    DAT_0026f238 = 0x3fa66666;
  }
  else {
    DAT_0026f238 = 0x3f800000;
  }
  _FontWibbleX = _FontWibbleX + _FontWibbleXRate;
  if (6.2831855 < _FontWibbleX) {
    _FontWibbleX = _FontWibbleX - 6.2831855;
  }
  _FontWibbleY = _FontWibbleY + _FontWibbleYRate;
  if (6.2831855 < _FontWibbleY) {
    _FontWibbleY = _FontWibbleY - 6.2831855;
  }
  return;
}
