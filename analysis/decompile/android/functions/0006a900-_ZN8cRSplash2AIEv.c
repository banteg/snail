/*
 * mangled: _ZN8cRSplash2AIEv
 * demangled: cRSplash::AI()
 * address: 0006a900
 * size: 628
 */

/* cRSplash::AI() */

void __thiscall cRSplash::AI(cRSplash *this)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  cRBorder *this_00;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  float fVar9;

  iVar4 = DAT_0006ab88;
  iVar7 = DAT_0006ab84 + 0x6a918;
  piVar8 = *(int **)(iVar7 + DAT_0006ab88);
  iVar5 = *piVar8;
  if ((*(uint *)(*(int *)(iVar5 + 0x224) + 0x30) & 0x4000) == 0) {
    iVar5 = RShellInkey();
    if (iVar5 == 0xb) {
      iVar5 = *piVar8;
      goto LAB_0006a92c;
    }
    iVar5 = *(int *)(*piVar8 + 0x24);
  }
  else {
LAB_0006a92c:
    if (*(int *)(this + 0xc) < 2) {
      iVar5 = *(int *)(**(int **)(iVar7 + iVar4) + 0x24);
    }
    else {
      iVar5 = *(int *)(iVar5 + 0x24);
      if (iVar5 == 0) {
        cRSound::Play(*(int *)(iVar7 + DAT_0006ab98));
        piVar8 = *(int **)(iVar7 + iVar4);
        cRFade::Start((cRFade *)(*piVar8 + 0x24),(_func_void *)0x0);
        iVar5 = *piVar8;
        *this = (cRSplash)0x1;
        iVar5 = *(int *)(iVar5 + 0x24);
      }
    }
  }
  if ((iVar5 == 4) && (*this != (cRSplash)0x0)) {
    UnInit(this);
  }
  fVar1 = DAT_0006ab74;
  fVar9 = *(float *)(this + 0x10);
  *(float *)(this + 0x10) = fVar9 + *(float *)(this + 0x14);
  if (fVar9 + *(float *)(this + 0x14) <= fVar1) {
    return;
  }
  *(undefined4 *)(this + 0x10) = DAT_0006ab78;
  iVar5 = DAT_0006ab8c;
  uVar3 = DAT_0006ab80;
  uVar2 = DAT_0006ab7c;
  uVar6 = DAT_0006ab78;
  switch(*(undefined4 *)(this + 0xc)) {
  case 0:
    this_00 = *(cRBorder **)(this + 8);
    uVar6 = 1;
    break;
  case 1:
    piVar8 = *(int **)(iVar7 + iVar4);
    *(undefined4 *)(this + 0xc) = 2;
    iVar4 = *piVar8;
    *(undefined4 *)(this + 0x14) = DAT_0006ab7c;
    if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),(char *)(iVar7 + DAT_0006ab9c));
    }
    else if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),(char *)(iVar7 + DAT_0006ab94));
    }
    goto LAB_0006aa1c;
  case 2:
    this_00 = *(cRBorder **)(this + 8);
    uVar6 = 3;
    break;
  case 3:
    piVar8 = *(int **)(iVar7 + iVar4);
    *(undefined4 *)(this + 0xc) = 4;
    iVar4 = *piVar8;
    *(undefined4 *)(this + 0x14) = DAT_0006ab7c;
    if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 0) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),(char *)(iVar7 + DAT_0006aba0));
    }
    else if (*(int *)(gOFOData + iVar4 + 0x1ebc) == 1) {
      Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),(char *)(iVar7 + DAT_0006ab90));
    }
    goto LAB_0006aa1c;
  case 4:
    this_00 = *(cRBorder **)(this + 8);
    uVar6 = 5;
    break;
  case 5:
    *(undefined4 *)(this + 0xc) = 6;
    *(undefined4 *)(this + 0x14) = uVar2;
    Rstrcpy((char *)(*(int *)(this + 8) + 0x2c4),(char *)(iVar7 + iVar5));
LAB_0006aa1c:
    cRBorder::UnHideInit(*(cRBorder **)(this + 8));
    return;
  case 6:
    *(undefined4 *)(this + 0xc) = 7;
    *(undefined4 *)(this + 0x14) = uVar6;
    return;
  case 7:
    *(undefined4 *)(this + 0x14) = DAT_0006ab78;
  default:
    return;
  }
  *(undefined4 *)(this + 0xc) = uVar6;
  *(undefined4 *)(this + 0x14) = uVar3;
  cRBorder::HideInit(this_00);
  return;
}
