/*
 * mangled: _ZN7cRTrack6ChangeEi
 * demangled: cRTrack::Change(int)
 * address: 0004265c
 * size: 232
 */

/* cRTrack::Change(int) */

void __thiscall cRTrack::Change(cRTrack *this,int param_1)

{
  float fVar1;
  int unaff_r5;

  switch(param_1) {
  case 0:
    unaff_r5 = 0;
    if (*(int *)(this + 900) == 0) {
      return;
    }
    break;
  case 1:
    unaff_r5 = 1;
    if (*(int *)(this + 900) == 1) {
      return;
    }
    break;
  case 2:
    unaff_r5 = 2;
    if (*(int *)(this + 900) == 2) {
      return;
    }
    break;
  case 3:
    unaff_r5 = 3;
    if (*(int *)(this + 900) == 3) {
      return;
    }
    break;
  case 4:
    unaff_r5 = 4;
    if (*(int *)(this + 900) == 4) {
      return;
    }
    break;
  case 5:
    unaff_r5 = 5;
    if (*(int *)(this + 900) == 5) {
      return;
    }
    break;
  case 6:
    unaff_r5 = 6;
  default:
    if (*(int *)(this + 900) == unaff_r5) {
      return;
    }
    break;
  case 8:
    fVar1 = (float)RAND(7.0,(char *)0x0);
    unaff_r5 = (int)fVar1;
    if (*(int *)(this + 900) == unaff_r5) {
      return;
    }
  }
  G0TextureReLoad(*(int *)(*(int *)this + 0x8c),(char *)(this + unaff_r5 * 0x80 + 4));
  *(int *)(this + 900) = unaff_r5;
  return;
}
