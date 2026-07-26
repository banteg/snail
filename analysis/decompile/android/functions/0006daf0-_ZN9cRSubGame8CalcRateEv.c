/*
 * mangled: _ZN9cRSubGame8CalcRateEv
 * demangled: cRSubGame::CalcRate()
 * address: 0006daf0
 * size: 360
 */

/* cRSubGame::CalcRate() */

void cRSubGame::CalcRate(void)

{
  int in_r0;
  int iVar1;
  uint in_fpscr;
  float in_s0;
  float fVar2;
  float fVar3;
  float fVar4;

  if (*(int *)(in_r0 + 0x5c) == 2) {
    fVar4 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x78),(byte)(in_fpscr >> 0x16) & 3);
    fVar4 = *(float *)(in_r0 + 0xfb28) / fVar4;
    if (fVar4 < 0.0) {
      fVar4 = 0.0;
    }
    else if (1.0 < fVar4) {
      fVar4 = 1.0;
    }
    iVar1 = *(int *)(in_r0 + 0x60);
    if (iVar1 != 1 && iVar1 != 3) {
      fVar3 = *(float *)(in_r0 + 0x4c);
      fVar2 = 0.2;
    }
    else {
      fVar2 = 0.3;
      fVar3 = *(float *)(in_r0 + 0x4c) + fVar4 * 0.3;
    }
    if (iVar1 != 1 && iVar1 != 3) {
      *(float *)(in_r0 + 0x54) = fVar3 + fVar4 * fVar2;
    }
    else {
      *(float *)(in_r0 + 0x54) = fVar3;
    }
    if (*(int *)(in_r0 + 0xfe78) == 2) {
      fVar4 = 0.3;
      if (iVar1 != 1 && iVar1 != 4) {
        fVar4 = 0.4;
      }
      if ((*(float *)(in_r0 + 0xfe98) < 0.25) || (0.75 < *(float *)(in_r0 + 0xfe98))) {
        fVar3 = *(float *)(in_r0 + 0x54);
        fVar2 = (float)Sin(in_s0);
        *(float *)(in_r0 + 0x54) = fVar3 + (1.0 - fVar2) * 0.5 * fVar4;
      }
      else {
        *(float *)(in_r0 + 0x54) = *(float *)(in_r0 + 0x54) + fVar4;
      }
    }
    if (*(int *)((int)DWORD_ARRAY_000110f8 + in_r0 + 0xfa4) == 1) {
      *(float *)(in_r0 + 0x54) =
           *(float *)(in_r0 + 0x54) + *(float *)((int)DWORD_ARRAY_000110f8 + in_r0 + 0x11a4) * 0.5;
    }
  }
  else {
    *(undefined4 *)(in_r0 + 0x54) = *(undefined4 *)(in_r0 + 0x4c);
  }
  return;
}
