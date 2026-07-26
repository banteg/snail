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
    fVar3 = (float)VectorSignedToFloat(*(undefined4 *)(in_r0 + 0x78),(byte)(in_fpscr >> 0x16) & 3);
    fVar3 = *(float *)(in_r0 + 0xfb28) / fVar3;
    fVar4 = DAT_0006dc68;
    if ((0.0 <= fVar3) && (fVar4 = fVar3, DAT_0006dc58 < fVar3)) {
      fVar4 = DAT_0006dc58;
    }
    iVar1 = *(int *)(in_r0 + 0x60);
    if (iVar1 != 1 && iVar1 != 3) {
      fVar2 = *(float *)(in_r0 + 0x4c);
      fVar3 = DAT_0006dc60;
    }
    else {
      fVar2 = *(float *)(in_r0 + 0x4c) + fVar4 * DAT_0006dc5c;
      fVar3 = DAT_0006dc5c;
    }
    if (iVar1 != 1 && iVar1 != 3) {
      *(float *)(in_r0 + 0x54) = fVar2 + fVar4 * fVar3;
    }
    else {
      *(float *)(in_r0 + 0x54) = fVar2;
    }
    if (*(int *)(in_r0 + 0xfe78) == 2) {
      fVar4 = DAT_0006dc5c;
      if (iVar1 != 1 && iVar1 != 4) {
        fVar4 = DAT_0006dc6c;
      }
      if ((*(float *)(in_r0 + 0xfe98) < DAT_0006dc70) || (DAT_0006dc74 < *(float *)(in_r0 + 0xfe98))
         ) {
        fVar2 = *(float *)(in_r0 + 0x54);
        fVar3 = (float)Sin(in_s0);
        *(float *)(in_r0 + 0x54) = fVar2 + (DAT_0006dc58 - fVar3) * DAT_0006dc64 * fVar4;
      }
      else {
        *(float *)(in_r0 + 0x54) = *(float *)(in_r0 + 0x54) + fVar4;
      }
    }
    if (*(int *)((int)DWORD_ARRAY_000110f8 + in_r0 + 0xfa4) == 1) {
      *(float *)(in_r0 + 0x54) =
           *(float *)(in_r0 + 0x54) +
           DAT_0006dc64 * *(float *)((int)DWORD_ARRAY_000110f8 + in_r0 + 0x11a4);
    }
  }
  else {
    *(undefined4 *)(in_r0 + 0x54) = *(undefined4 *)(in_r0 + 0x4c);
  }
  return;
}
