/*
 * mangled: _ZN6cRFade2AIEv
 * demangled: cRFade::AI()
 * address: 0004a40c
 * size: 364
 */

/* cRFade::AI() */

void cRFade::AI(void)

{
  int iVar1;
  undefined4 *in_r0;
  int iVar2;
  float in_s0;
  float in_s1;
  float in_s2;
  float in_s3;
  float fVar3;
  float fVar4;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;

  fVar4 = DAT_0004a580;
  iVar2 = DAT_0004a58c + 0x4a420;
  switch(*in_r0) {
  case 0:
    return;
  case 1:
    fVar4 = (float)in_r0[1] - DAT_0004a57c;
    iVar2 = *(int *)(**(int **)(iVar2 + DAT_0004a594) + 0x328);
    in_r0[1] = fVar4;
    if (iVar2 < 1) {
      if (fVar4 <= 0.0) {
        in_r0[1] = DAT_0004a584;
        *in_r0 = 0;
      }
    }
    else {
      in_r0[1] = DAT_0004a580;
    }
    break;
  case 2:
    fVar3 = DAT_0004a57c + (float)in_r0[1];
    in_r0[1] = fVar3;
    iVar1 = DAT_0004a590;
    if (fVar4 < fVar3) {
      in_r0[1] = fVar4;
      if (**(char **)(iVar2 + iVar1) != '\0') {
        *in_r0 = 4;
        in_r0[2] = DAT_0004a584;
        in_r0[3] = DAT_0004a588;
      }
    }
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    iVar2 = in_r0[5];
    in_r0[5] = iVar2 + -1;
    if (iVar2 + -1 == 0) {
      *in_r0 = 1;
    }
  }
  tColour::tColour((tColour *)&local_18,in_s0,in_s1,in_s2,in_s3);
  OSDPrint(3,0,0,0x44200000,DAT_0004a578,0x1000000,local_18,uStack_14,uStack_10,uStack_c,9);
  return;
}
