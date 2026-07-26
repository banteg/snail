/*
 * mangled: _ZN6cRSalt2AIEv
 * demangled: cRSalt::AI()
 * address: 00072318
 * size: 216
 */

/* cRSalt::AI() */

void cRSalt::AI(void)

{
  cRBod *in_r0;
  float in_s0;
  float fVar1;
  float fVar2;

  if (*(char *)(*(int *)(in_r0 + 0x7c) + 0x19) != '\0') {
    return;
  }
  if (*(int *)(in_r0 + 0x74) != 1) {
    if (*(int *)(in_r0 + 0x74) != 2) {
      return;
    }
    cLinkedList<cRBod>::Remove
              ((cLinkedList<cRBod> *)(**(int **)(DAT_000723fc + 0x72334 + DAT_00072400) + 0x358),
               in_r0);
    *(undefined4 *)(in_r0 + 0x74) = 0;
    return;
  }
  fVar1 = (*(float *)(in_r0 + 100) - *(float *)(*(int *)(in_r0 + 0x7c) + 0xfb28)) / DAT_000723f0 +
          DAT_000723f4;
  fVar2 = DAT_000723f8;
  if ((0.0 <= fVar1) && (fVar2 = fVar1, DAT_000723f4 < fVar1)) {
    fVar2 = DAT_000723f4;
  }
  *(float *)(in_r0 + 0x80) = fVar2;
  tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),in_s0);
  if (*(float *)(in_r0 + 100) <
      *(float *)((int)DWORD_ARRAY_000110f8 + *(int *)(in_r0 + 0x7c) + 0x11c8)) {
    *(undefined4 *)(in_r0 + 0x74) = 2;
  }
  return;
}
