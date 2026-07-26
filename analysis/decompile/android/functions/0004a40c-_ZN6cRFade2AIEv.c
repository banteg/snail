/*
 * mangled: _ZN6cRFade2AIEv
 * demangled: cRFade::AI()
 * address: 0004a40c
 * size: 364
 */

/* cRFade::AI() */

void cRFade::AI(void)

{
  undefined4 *in_r0;
  int iVar1;
  float in_s0;
  float in_s1;
  float in_s2;
  float in_s3;
  float fVar2;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;

  switch(*in_r0) {
  case 0:
    return;
  case 1:
    fVar2 = (float)in_r0[1];
    iVar1 = *(int *)(Game + 0x328);
    in_r0[1] = fVar2 - 0.055555556;
    if (iVar1 < 1) {
      if (fVar2 - 0.055555556 <= 0.0) {
        in_r0[1] = 0;
        *in_r0 = 0;
      }
    }
    else {
      in_r0[1] = 0x3f800000;
    }
    break;
  case 2:
    fVar2 = (float)in_r0[1];
    in_r0[1] = fVar2 + 0.055555556;
    if (1.0 < fVar2 + 0.055555556) {
      in_r0[1] = 0x3f800000;
      if (G0RenderNextFlag != '\0') {
        *in_r0 = 4;
        in_r0[2] = 0;
        in_r0[3] = 0x3eaaaaab;
      }
    }
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    iVar1 = in_r0[5];
    in_r0[5] = iVar1 + -1;
    if (iVar1 + -1 == 0) {
      *in_r0 = 1;
    }
  }
  tColour::tColour((tColour *)&local_18,in_s0,in_s1,in_s2,in_s3);
  OSDPrint(3,0,0,0x44200000,0x43f00000,0x1000000,local_18,uStack_14,uStack_10,uStack_c,9);
  return;
}
