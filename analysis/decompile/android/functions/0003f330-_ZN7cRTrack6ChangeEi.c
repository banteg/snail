/*
 * mangled: _ZN7cRTrack6ChangeEi
 * demangled: cRTrack::Change(int)
 * address: 0003f330
 * size: 264
 */

/* cRTrack::Change(int) */

void cRTrack::Change(int param_1)

{
  float fVar1;
  undefined4 in_r1;
  int unaff_r5;
  float in_s0;

  switch(in_r1) {
  case 0:
    unaff_r5 = 0;
    if (*(int *)(param_1 + 900) == 0) {
      return;
    }
    break;
  case 1:
    unaff_r5 = 1;
    if (*(int *)(param_1 + 900) == 1) {
      return;
    }
    break;
  case 2:
    unaff_r5 = 2;
    if (*(int *)(param_1 + 900) == 2) {
      return;
    }
    break;
  case 3:
    unaff_r5 = 3;
    if (*(int *)(param_1 + 900) == 3) {
      return;
    }
    break;
  case 4:
    unaff_r5 = 4;
    if (*(int *)(param_1 + 900) == 4) {
      return;
    }
    break;
  case 5:
    unaff_r5 = 5;
    if (*(int *)(param_1 + 900) == 5) {
      return;
    }
    break;
  case 6:
    unaff_r5 = 6;
    if (*(int *)(param_1 + 900) == 6) {
      return;
    }
    break;
  case 7:
  default:
switchD_0003f33c_default:
    if (*(int *)(param_1 + 900) == unaff_r5) {
      return;
    }
    break;
  case 8:
    fVar1 = (float)RAND(in_s0,(char *)0x40e00000);
    unaff_r5 = (int)fVar1;
    goto switchD_0003f33c_default;
  }
  G0TextureReLoad(*(int *)(*(int *)param_1 + 0x8c),(char *)(param_1 + unaff_r5 * 0x80 + 4));
  *(int *)(param_1 + 900) = unaff_r5;
  return;
}
