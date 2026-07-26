/*
 * mangled: _ZN11cRSubHealth2AIEv
 * demangled: cRSubHealth::AI()
 * address: 0006e76c
 * size: 288
 */

/* cRSubHealth::AI() */

void cRSubHealth::AI(void)

{
  char cVar1;
  cRBod *in_r0;
  int iVar2;
  int iVar3;
  int iVar4;
  float in_s0;
  float fVar5;
  float fVar6;

  if (*(char *)(*(int *)(in_r0 + 0x38) + 0x19) == '\0') {
    iVar2 = *(int *)(in_r0 + 0x2c);
    if (iVar2 == 1) {
      if (*(float *)(in_r0 + 0x18) < *(float *)(*(int *)(in_r0 + 0x30) + 0x27fc)) goto LAB_0006e860;
    }
    else {
      if (iVar2 == 2) {
LAB_0006e860:
        *(undefined4 *)(in_r0 + 0x2c) = 0;
        cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),in_r0);
        cRSprite::Kill(*(cRSprite **)(in_r0 + 0x58));
        return;
      }
      if (iVar2 == 0) {
        return;
      }
    }
    fVar5 = *(float *)(in_r0 + 0x60) + *(float *)(in_r0 + 100);
    iVar2 = *(int *)(in_r0 + 0x58);
    fVar6 = *(float *)(in_r0 + 0x14);
    *(float *)(in_r0 + 0x60) = fVar5;
    if (1.0 < fVar5) {
      *(float *)(in_r0 + 0x60) = fVar5 - 1.0;
    }
    fVar5 = (float)Sin(in_s0);
    iVar4 = *(int *)(in_r0 + 0x30);
    iVar3 = *(int *)(in_r0 + 0x58);
    cVar1 = *(char *)(iVar4 + 0x374);
    *(float *)(iVar2 + 0x4c) = fVar6 + 0.3 + fVar5 * 0.3;
    fVar5 = *(float *)(iVar4 + 0x360) + *(float *)(iVar4 + 0x34c);
    *(float *)(iVar3 + 0x7c) = fVar5;
    if (cVar1 != '\0') {
      *(float *)(iVar3 + 0x7c) = fVar5 + *(float *)(iVar4 + 0x390) + *(float *)(iVar4 + 0x38c);
    }
  }
  return;
}
