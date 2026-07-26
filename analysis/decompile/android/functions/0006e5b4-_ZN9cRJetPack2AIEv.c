/*
 * mangled: _ZN9cRJetPack2AIEv
 * demangled: cRJetPack::AI()
 * address: 0006e5b4
 * size: 284
 */

/* cRJetPack::AI() */

void cRJetPack::AI(void)

{
  char cVar1;
  cRBod *in_r0;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float in_s0;
  float fVar6;
  float fVar7;

  fVar2 = DAT_0006e6d0;
  iVar4 = DAT_0006e6dc + 0x6e5d0;
  if (*(char *)(*(int *)(in_r0 + 0x38) + 0x19) == '\0') {
    iVar3 = *(int *)(in_r0 + 0x2c);
    if (iVar3 == 1) {
      if (*(float *)(in_r0 + 0x18) < *(float *)(*(int *)(in_r0 + 0x30) + 0x27fc)) goto LAB_0006e6a4;
    }
    else {
      if (iVar3 == 2) {
LAB_0006e6a4:
        *(undefined4 *)(in_r0 + 0x2c) = 0;
        cLinkedList<cRBod>::Remove
                  ((cLinkedList<cRBod> *)(**(int **)(iVar4 + DAT_0006e6e0) + 0x358),in_r0);
        cRSprite::Kill(*(cRSprite **)(in_r0 + 0x58));
        return;
      }
      if (iVar3 == 0) {
        return;
      }
    }
    fVar6 = *(float *)(in_r0 + 0x60) + *(float *)(in_r0 + 100);
    iVar4 = *(int *)(in_r0 + 0x58);
    fVar7 = *(float *)(in_r0 + 0x14);
    *(float *)(in_r0 + 0x60) = fVar6;
    if (fVar2 < fVar6) {
      *(float *)(in_r0 + 0x60) = fVar6 - fVar2;
    }
    fVar2 = (float)Sin(in_s0);
    iVar5 = *(int *)(in_r0 + 0x30);
    iVar3 = *(int *)(in_r0 + 0x58);
    cVar1 = *(char *)(iVar5 + 0x374);
    *(float *)(iVar4 + 0x4c) = fVar7 + fVar2 * DAT_0006e6d8;
    fVar2 = *(float *)(iVar5 + 0x360) + *(float *)(iVar5 + 0x34c);
    *(float *)(iVar3 + 0x7c) = fVar2;
    if (cVar1 != '\0') {
      *(float *)(iVar3 + 0x7c) = fVar2 + *(float *)(iVar5 + 0x390) + *(float *)(iVar5 + 0x38c);
    }
  }
  return;
}
