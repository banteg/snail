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
  float fVar2;
  cRBod *in_r0;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float in_s0;
  float fVar7;
  float fVar8;

  fVar2 = DAT_0006e890;
  fVar3 = DAT_0006e88c;
  iVar5 = DAT_0006e898 + 0x6e788;
  if (*(char *)(*(int *)(in_r0 + 0x38) + 0x19) == '\0') {
    iVar4 = *(int *)(in_r0 + 0x2c);
    if (iVar4 == 1) {
      if (*(float *)(in_r0 + 0x18) < *(float *)(*(int *)(in_r0 + 0x30) + 0x27fc)) goto LAB_0006e860;
    }
    else {
      if (iVar4 == 2) {
LAB_0006e860:
        *(undefined4 *)(in_r0 + 0x2c) = 0;
        cLinkedList<cRBod>::Remove
                  ((cLinkedList<cRBod> *)(**(int **)(iVar5 + DAT_0006e89c) + 0x358),in_r0);
        cRSprite::Kill(*(cRSprite **)(in_r0 + 0x58));
        return;
      }
      if (iVar4 == 0) {
        return;
      }
    }
    fVar7 = *(float *)(in_r0 + 0x60) + *(float *)(in_r0 + 100);
    iVar5 = *(int *)(in_r0 + 0x58);
    fVar8 = *(float *)(in_r0 + 0x14);
    *(float *)(in_r0 + 0x60) = fVar7;
    if (fVar3 < fVar7) {
      *(float *)(in_r0 + 0x60) = fVar7 - fVar3;
    }
    fVar3 = (float)Sin(in_s0);
    iVar6 = *(int *)(in_r0 + 0x30);
    iVar4 = *(int *)(in_r0 + 0x58);
    cVar1 = *(char *)(iVar6 + 0x374);
    *(float *)(iVar5 + 0x4c) = fVar2 + fVar8 + fVar3 * fVar2;
    fVar3 = *(float *)(iVar6 + 0x360) + *(float *)(iVar6 + 0x34c);
    *(float *)(iVar4 + 0x7c) = fVar3;
    if (cVar1 != '\0') {
      *(float *)(iVar4 + 0x7c) = fVar3 + *(float *)(iVar6 + 0x390) + *(float *)(iVar6 + 0x38c);
    }
  }
  return;
}
