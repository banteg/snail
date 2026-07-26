/*
 * mangled: _ZN9cRLogoRow2AIEv
 * demangled: cRLogoRow::AI()
 * address: 00068ba0
 * size: 200
 */

/* cRLogoRow::AI() */

void cRLogoRow::AI(void)

{
  float fVar1;
  int in_r0;
  float in_s0;
  float fVar2;

  fVar1 = DAT_00068c68;
  fVar2 = *(float *)(in_r0 + 100) + *(float *)(in_r0 + 0x7c);
  *(float *)(in_r0 + 100) = fVar2;
  *(float *)(in_r0 + 0x5c) = *(float *)(in_r0 + 0x5c) + *(float *)(in_r0 + 0x74);
  *(float *)(in_r0 + 0x60) = *(float *)(in_r0 + 0x60) + *(float *)(in_r0 + 0x78);
  if (fVar2 <= fVar1) {
    tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),in_s0);
  }
  else {
    tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),in_s0);
  }
  if ((*(float *)(in_r0 + 100) <= DAT_00068c78) && (DAT_00068c7c <= *(float *)(in_r0 + 100))) {
    *(uint *)(in_r0 + 4) = *(uint *)(in_r0 + 4) | 0x20;
    return;
  }
  *(uint *)(in_r0 + 4) = *(uint *)(in_r0 + 4) & 0xffffffdf;
  return;
}
