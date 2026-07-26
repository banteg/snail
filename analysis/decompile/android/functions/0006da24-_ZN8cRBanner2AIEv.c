/*
 * mangled: _ZN8cRBanner2AIEv
 * demangled: cRBanner::AI()
 * address: 0006da24
 * size: 184
 */

/* cRBanner::AI() */

void cRBanner::AI(void)

{
  int in_r0;
  float fVar1;
  float in_s0;
  float fVar2;

  if (*(int *)(in_r0 + 0x2c) == 0) {
    if (DAT_0006dadc <= *(float *)(*(int *)(in_r0 + 0x48) + 100)) {
LAB_0006dacc:
      *(uint *)(in_r0 + 4) = *(uint *)(in_r0 + 4) & 0xffffffdf;
      goto LAB_0006da5c;
    }
  }
  else {
    if (*(int *)(in_r0 + 0x2c) != 1) goto LAB_0006da5c;
    if (DAT_0006daec <= *(float *)(in_r0 + 0x18) - *(float *)(*(int *)(in_r0 + 0x48) + 100))
    goto LAB_0006dacc;
  }
  *(uint *)(in_r0 + 4) = *(uint *)(in_r0 + 4) | 0x20;
LAB_0006da5c:
  fVar1 = DAT_0006dae0;
  fVar2 = *(float *)(in_r0 + 0x4c) + *(float *)(in_r0 + 0x50);
  *(float *)(in_r0 + 0x4c) = fVar2;
  if (fVar1 < fVar2) {
    *(float *)(in_r0 + 0x4c) = fVar2 - fVar1;
  }
  fVar1 = (float)Sin(in_s0);
  *(float *)(in_r0 + 0x14) = fVar1 * DAT_0006dae8;
  return;
}
