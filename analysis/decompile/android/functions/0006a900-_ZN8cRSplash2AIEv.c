/*
 * mangled: _ZN8cRSplash2AIEv
 * demangled: cRSplash::AI()
 * address: 0006a900
 * size: 628
 */

/* cRSplash::AI() */

void __thiscall cRSplash::AI(cRSplash *this)

{
  cRBorder *this_00;
  undefined4 uVar1;
  int iVar2;
  float fVar3;

  if (((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) == 0) &&
     (iVar2 = RShellInkey(), iVar2 != 0xb)) {
    iVar2 = *(int *)(Game + 0x24);
  }
  else if (*(int *)(this + 0xc) < 2) {
    iVar2 = *(int *)(Game + 0x24);
  }
  else {
    iVar2 = *(int *)(Game + 0x24);
    if (iVar2 == 0) {
      cRSound::Play((int)&gRSound);
      cRFade::Start((cRFade *)(Game + 0x24),(_func_void *)0x0);
      iVar2 = Game;
      *this = (cRSplash)0x1;
      iVar2 = *(int *)(iVar2 + 0x24);
    }
  }
  if ((iVar2 == 4) && (*this != (cRSplash)0x0)) {
    UnInit(this);
  }
  fVar3 = *(float *)(this + 0x10);
  *(float *)(this + 0x10) = fVar3 + *(float *)(this + 0x14);
  if (fVar3 + *(float *)(this + 0x14) <= 1.0) {
    return;
  }
  *(undefined4 *)(this + 0x10) = 0;
  switch(*(undefined4 *)(this + 0xc)) {
  case 0:
    this_00 = *(cRBorder **)(this + 8);
    uVar1 = 1;
    break;
  case 1:
    *(undefined4 *)(this + 0xc) = 2;
    iVar2 = Game;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    if (*(int *)(gOFOData + iVar2 + 0x1ebc) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),"Test your reflexes>in Challenge Mode!");
    }
    else if (*(int *)(gOFOData + iVar2 + 0x1ebc) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">That isn\'t humanly possible!");
    }
    goto LAB_0006aa1c;
  case 2:
    this_00 = *(cRBorder **)(this + 8);
    uVar1 = 3;
    break;
  case 3:
    *(undefined4 *)(this + 0xc) = 4;
    iVar2 = Game;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    if (*(int *)(gOFOData + iVar2 + 0x1ebc) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),"Improve your skills>in Time Trial!");
    }
    else if (*(int *)(gOFOData + iVar2 + 0x1ebc) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">You\'re totally awesome!");
    }
    goto LAB_0006aa1c;
  case 4:
    this_00 = *(cRBorder **)(this + 8);
    uVar1 = 5;
    break;
  case 5:
    *(undefined4 *)(this + 0xc) = 6;
    *(undefined4 *)(this + 0x14) = 0x3b888889;
    Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),">Touch Screen to Continue");
LAB_0006aa1c:
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
  *(undefined4 *)(this + 0xc) = uVar1;
  *(undefined4 *)(this + 0x14) = 0x3d088889;
  cRBorder::HideInit(this_00);
  return;
}
