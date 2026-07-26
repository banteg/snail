/*
 * mangled: _ZN8cRSplash2AIEv
 * demangled: cRSplash::AI()
 * address: 00063dac
 * size: 580
 */

/* cRSplash::AI() */

void __thiscall cRSplash::AI(cRSplash *this)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  float fVar6;

  puVar1 = PTR__Game_001b60b8;
  if (((*(uint *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x30) & 0x4000) == 0) &&
     (cVar2 = RShellInkey(), cVar2 != '\v')) {
    iVar3 = *(int *)PTR__Game_001b60b8;
    iVar4 = *(int *)(iVar3 + 0x24);
  }
  else {
    if ((1 < *(int *)(this + 0xc)) && (*(int *)(*(int *)puVar1 + 0x24) == 0)) {
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
      cRFade::Start((cRFade *)(*(int *)puVar1 + 0x24),(_func_void *)0x0);
      *this = (cRSplash)0x1;
    }
    iVar3 = *(int *)PTR__Game_001b60b8;
    iVar4 = *(int *)(iVar3 + 0x24);
  }
  puVar1 = PTR__Game_001b60b8;
  if ((iVar4 == 4) && (*this != (cRSplash)0x0)) {
    cRBorderManager::Kill((cRBorder *)(iVar3 + 0xd14));
    *(undefined4 *)(*(int *)puVar1 + 0x15c) = 0xe;
  }
  fVar6 = *(float *)(this + 0x10);
  *(float *)(this + 0x10) = fVar6 + *(float *)(this + 0x14);
  if (fVar6 + *(float *)(this + 0x14) <= 1.0) {
    return;
  }
  *(undefined4 *)(this + 0x10) = 0;
  switch(*(undefined4 *)(this + 0xc)) {
  case 0:
    uVar5 = 1;
    break;
  case 1:
    *(undefined4 *)(this + 0xc) = 2;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),"Test your reflexes>in Challenge Mode!");
    }
    else if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">That isn\'t humanly possible!");
    }
    goto LAB_00063fc8;
  case 2:
    uVar5 = 3;
    break;
  case 3:
    *(undefined4 *)(this + 0xc) = 4;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),"Improve your skills>in Time Trial!");
    }
    else if (*(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">You\'re totally awesome!");
    }
    goto LAB_00063fc8;
  case 4:
    uVar5 = 5;
    break;
  case 5:
    *(undefined4 *)(this + 0xc) = 6;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">Touch Screen to Continue");
LAB_00063fc8:
    cRBorder::UnHideInit(*(cRBorder **)(this + 8));
    return;
  case 6:
    *(undefined4 *)(this + 0xc) = 7;
    *(undefined4 *)(this + 0x14) = 0;
    return;
  case 7:
    *(undefined4 *)(this + 0x14) = 0;
  default:
    return;
  }
  *(undefined4 *)(this + 0xc) = uVar5;
  *(undefined4 *)(this + 0x14) = 0x3d088889;
  cRBorder::HideInit(*(cRBorder **)(this + 8));
  return;
}
