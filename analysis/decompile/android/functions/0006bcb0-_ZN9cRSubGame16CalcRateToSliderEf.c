/*
 * mangled: _ZN9cRSubGame16CalcRateToSliderEf
 * demangled: cRSubGame::CalcRateToSlider(float)
 * address: 0006bcb0
 * size: 44
 */

/* cRSubGame::CalcRateToSlider(float) */

float __thiscall cRSubGame::CalcRateToSlider(cRSubGame *this,float param_1)

{
  float in_r1;
  float fVar1;

  if (in_r1 == 1.1) {
    fVar1 = 1.0;
  }
  else {
    fVar1 = (in_r1 - 0.2) / 0.90000004;
  }
  return fVar1;
}
