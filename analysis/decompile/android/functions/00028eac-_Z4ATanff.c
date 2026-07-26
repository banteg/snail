/*
 * mangled: _Z4ATanff
 * demangled: ATan(float, float)
 * address: 00028eac
 * size: 172
 */

/* ATan(float, float) */

float ATan(float param_1,float param_2)

{
  float in_r0;
  undefined4 extraout_r0;
  float in_r1;
  undefined4 extraout_r1;
  int iVar1;
  float fVar2;

  if (in_r0 <= 0.0) {
    if (0.0 < in_r1) {
      iVar1 = 3;
    }
    else {
      iVar1 = 2;
      in_r1 = -in_r1;
    }
  }
  else if (in_r1 <= 0.0) {
    in_r1 = -in_r1;
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  if (in_r1 == 0.0) {
    fVar2 = 1.5707964;
  }
  else {
    atan((double)CONCAT44(param_2,param_1));
    fVar2 = (float)(double)CONCAT44(extraout_r1,extraout_r0);
  }
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      return 3.1415927 - fVar2;
    }
    if (iVar1 == 2) {
      fVar2 = fVar2 + 3.1415927;
    }
    else {
      fVar2 = -fVar2;
    }
  }
  return fVar2;
}
