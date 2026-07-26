/*
 * mangled: _ZN13cRStarManager2AIEv
 * demangled: cRStarManager::AI()
 * address: 0006b454
 * size: 324
 */

/* cRStarManager::AI() */

void cRStarManager::AI(void)

{
  undefined4 uVar1;
  cRStarManager *in_r0;
  int iVar2;
  float in_s0;
  float fVar3;
  float fVar4;

  iVar2 = DAT_0006b5a0 + 0x6b46c;
  switch(*(undefined4 *)(in_r0 + 0x2c)) {
  case 0:
    if ((*(uint *)(*(int *)(iVar2 + DAT_0006b5a4) + 0x1c) & 4) != 0) {
      *(undefined4 *)(in_r0 + 0x2c) = 2;
      fVar3 = (float)Init(in_r0);
      uVar1 = DAT_0006b598;
      *(undefined4 *)(in_r0 + 0x2c) = 2;
      *(undefined4 *)(in_r0 + 0x38) = 0;
      *(undefined4 *)(in_r0 + 0x3c) = uVar1;
      UpdateStars(in_r0,fVar3);
      return;
    }
    return;
  case 1:
    UpdateStars(in_r0,in_s0);
    uVar1 = DAT_0006b598;
    if ((*(uint *)(*(int *)(iVar2 + DAT_0006b5a4) + 0x1c) & 4) == 0) {
      *(undefined4 *)(in_r0 + 0x38) = 0x3f800000;
      *(undefined4 *)(in_r0 + 0x3c) = uVar1;
      *(undefined4 *)(in_r0 + 0x2c) = 3;
      return;
    }
    return;
  case 2:
    UpdateStars(in_r0,in_s0);
    fVar3 = DAT_0006b59c;
    if ((*(uint *)(*(int *)(iVar2 + DAT_0006b5a4) + 0x1c) & 4) != 0) {
      fVar4 = *(float *)(in_r0 + 0x38);
      *(float *)(in_r0 + 0x38) = fVar4 + *(float *)(in_r0 + 0x3c);
      if (fVar3 < fVar4 + *(float *)(in_r0 + 0x3c)) {
        *(undefined4 *)(in_r0 + 0x2c) = 1;
      }
      return;
    }
    *(undefined4 *)(in_r0 + 0x2c) = 3;
    return;
  case 3:
    break;
  default:
    return;
  }
  UpdateStars(in_r0,in_s0);
  if ((*(uint *)(*(int *)(iVar2 + DAT_0006b5a4) + 0x1c) & 4) != 0) {
    *(undefined4 *)(in_r0 + 0x2c) = 2;
    return;
  }
  fVar3 = *(float *)(in_r0 + 0x38);
  *(float *)(in_r0 + 0x38) = fVar3 - *(float *)(in_r0 + 0x3c);
  if (fVar3 - *(float *)(in_r0 + 0x3c) < 0.0) {
    UnInit(in_r0);
    *(undefined4 *)(in_r0 + 0x2c) = 0;
    return;
  }
  return;
}
