/*
 * mangled: _ZN8cRGalaxy11BorderBoundERfS0_S0_S0_P8cRBorder
 * demangled: cRGalaxy::BorderBound(float&, float&, float&, float&, cRBorder*)
 * address: 00058cac
 * size: 204
 */

/* cRGalaxy::BorderBound(float&, float&, float&, float&, cRBorder*) */

void __thiscall
cRGalaxy::BorderBound
          (cRGalaxy *this,float *param_1,float *param_2,float *param_3,float *param_4,
          cRBorder *param_5)

{
  float fVar1;

  if (*(int *)(param_5 + 0x254) == 2) {
    fVar1 = *param_2 - *param_1;
    if (fVar1 < *(float *)(param_5 + 0x23c)) {
      fVar1 = *param_1 + (*(float *)(param_5 + 0x23c) - fVar1) * -0.5;
      *param_1 = fVar1;
      *param_1 = fVar1 + (*(float *)(param_5 + 0x23c) - (*param_2 - fVar1)) * 0.5;
    }
  }
  else {
    fVar1 = *(float *)(param_5 + 0x22c);
    if (fVar1 < *param_1) {
      *param_1 = fVar1;
      fVar1 = *(float *)(param_5 + 0x22c);
    }
    if (*param_2 < fVar1 + *(float *)(param_5 + 0x23c)) {
      *param_2 = fVar1 + *(float *)(param_5 + 0x23c);
    }
  }
  fVar1 = *(float *)(param_5 + 0x230);
  if (fVar1 < *param_3) {
    *param_3 = fVar1;
    fVar1 = *(float *)(param_5 + 0x230);
  }
  if (*param_4 < fVar1 + *(float *)(param_5 + 0x240)) {
    *param_4 = fVar1 + *(float *)(param_5 + 0x240);
  }
  return;
}
