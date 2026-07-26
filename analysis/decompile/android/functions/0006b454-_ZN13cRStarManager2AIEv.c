/*
 * mangled: _ZN13cRStarManager2AIEv
 * demangled: cRStarManager::AI()
 * address: 0006b454
 * size: 324
 */

/* cRStarManager::AI() */

void cRStarManager::AI(void)

{
  cRStarManager *in_r0;
  float in_s0;
  float fVar1;

  switch(*(undefined4 *)(in_r0 + 0x2c)) {
  case 0:
    if ((gConfig._28_4_ & 4) != 0) {
      *(undefined4 *)(in_r0 + 0x2c) = 2;
      fVar1 = (float)Init(in_r0);
      *(undefined4 *)(in_r0 + 0x2c) = 2;
      *(undefined4 *)(in_r0 + 0x38) = 0;
      *(undefined4 *)(in_r0 + 0x3c) = 0x3caaaaab;
      UpdateStars(in_r0,fVar1);
      return;
    }
    return;
  case 1:
    UpdateStars(in_r0,in_s0);
    if ((gConfig._28_4_ & 4) == 0) {
      *(undefined4 *)(in_r0 + 0x38) = 0x3f800000;
      *(undefined4 *)(in_r0 + 0x3c) = 0x3caaaaab;
      *(undefined4 *)(in_r0 + 0x2c) = 3;
      return;
    }
    return;
  case 2:
    UpdateStars(in_r0,in_s0);
    if ((gConfig._28_4_ & 4) != 0) {
      fVar1 = *(float *)(in_r0 + 0x38);
      *(float *)(in_r0 + 0x38) = fVar1 + *(float *)(in_r0 + 0x3c);
      if (1.0 < fVar1 + *(float *)(in_r0 + 0x3c)) {
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
  if ((gConfig._28_4_ & 4) != 0) {
    *(undefined4 *)(in_r0 + 0x2c) = 2;
    return;
  }
  fVar1 = *(float *)(in_r0 + 0x38);
  *(float *)(in_r0 + 0x38) = fVar1 - *(float *)(in_r0 + 0x3c);
  if (fVar1 - *(float *)(in_r0 + 0x3c) < 0.0) {
    UnInit(in_r0);
    *(undefined4 *)(in_r0 + 0x2c) = 0;
    return;
  }
  return;
}
