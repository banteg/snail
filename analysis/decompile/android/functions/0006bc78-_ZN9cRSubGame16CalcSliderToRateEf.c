/*
 * mangled: _ZN9cRSubGame16CalcSliderToRateEf
 * demangled: cRSubGame::CalcSliderToRate(float)
 * address: 0006bc78
 * size: 40
 */

/* cRSubGame::CalcSliderToRate(float) */

float __thiscall cRSubGame::CalcSliderToRate(cRSubGame *this,float param_1)

{
  float in_r1;
  float fVar1;

  if (in_r1 == 1.0) {
    fVar1 = 1.1;
  }
  else {
    fVar1 = in_r1 * 0.90000004 + 0.2;
  }
  return fVar1;
}
