/*
 * mangled: _Z4ATanff
 * demangled: ATan(float, float)
 * address: 0000a960
 * size: 160
 */

/* ATan(float, float) */

float ATan(float param_1,float param_2)

{
  int iVar1;
  float fVar2;

  if (param_1 <= 0.0) {
    param_1 = -param_1;
    if (param_2 <= 0.0) {
      param_2 = -param_2;
      iVar1 = 2;
    }
    else {
      iVar1 = 3;
    }
  }
  else if (param_2 <= 0.0) {
    param_2 = -param_2;
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  if (param_2 == 0.0) {
    fVar2 = 1.5707964;
  }
  else {
    fVar2 = (float)_atanf(param_1 / param_2);
  }
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      fVar2 = 3.1415927 - fVar2;
    }
    else if (iVar1 == 2) {
      fVar2 = fVar2 + 3.1415927;
    }
    else {
      fVar2 = -fVar2;
    }
  }
  return fVar2;
}
